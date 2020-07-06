#include "sendRequest.h"

/*
ssize_t writen(int fd, const void *buf, size_t count){
	if(fd<0||buf==NULL||count==0){
		return -1;
	}
	int totalWritten=0;
	while(1){
		int nWritten=write(fd,buf,count);
		if(nWritten<0){
			perror("write");
			return -1;
		}
		else if(nWritten==0){
			if(totalWritten==count){
				return totalWritten;
			}
			return -1;
		}
		totalWritten+=nWritten;
	}
	return totalWritten;
}
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int listDownload(int sock, char *ip){
	printf("\n(listDownload)listDownload들어옴\n");
	printf("(listDownload)받은 ip:%s\n",ip);

   if (ip == NULL){
		perror("listDownload");
		return -1;
	}



	//긁어온 코드
	char * myIp;
	struct ifaddrs* addrs;
	if(getifaddrs(&addrs)==-1){
		perror("getifaddrs");
		return -1;
	}
	struct ifaddrs* tmp = addrs;

	while (tmp) 
	{
		if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
		{
			struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
			myIp=inet_ntoa(pAddr->sin_addr);
		}

		tmp = tmp->ifa_next;
	}

	freeifaddrs(addrs);
	printf("\t내 ip:%s\n",myIp);
	//여기까지
	/*
	char buf[BUFFER_SIZE]={0,};
	strcat(buf,"type:");
    strcat(buf,"ls\n");
	strcat(buf,"path:");
	strcat(buf,"./home\n");
	strcat(buf,"ip:");
	strcat(buf,myIp);
	strcat(buf,"\n");
	*/
    char command[100]="/bin/echo -e 'type:ls\npath:./home\nip:";
	strcat(command, myIp);
	strcat(command, "'");
	strcat(command," > request.txt");
	system(command);

	/*
	int nWritten1=writen(fd,buf,strlen(buf)+1);
	if(nWritten1<0){
		perror("write");
		close(fd);
		return -1;
	}
	*/

	int fd = open("./request.txt", O_RDONLY|O_CREAT, 0744);
	if (fd==-1){
		perror("open");
		return -1;
	}

	char buf[BUFFER_SIZE]={0,};
	while(1){
		int nRead=read(fd,buf,sizeof(buf));
		if(nRead<0){
			perror("read");
			return -1;
		}
		else if(nRead==0)
			break;
		buf[nRead]='\0';
		printf("(listDownload)./request.txt에 끄는 중에 버퍼 확인:%s\n",buf);
		int nWritten=write(sock,buf,nRead);
		if(nWritten<0){
			perror("write");
			close(fd);
			return -1;
		}
	}

	close(fd);
	printf("(listDownload):server에 요청완료\n");

	int listFd=open("./list.txt",O_WRONLY|O_CREAT|O_TRUNC,0744);
	if(listFd==-1){
		perror("open");
		close(listFd);
		return -1;
	}
	while(1){
		printf("(listDownload):sock에서 읽어오는 while문 진입\n");
		int nRead=read(sock,buf,sizeof(buf));
		if(nRead<0){
			perror("read");
			close(listFd);
			return -1;
		}
		else if(nRead==0)
			break;
		printf("in buf\n%s\n",buf);
		int nWritten=write(listFd,buf,nRead);
		if(nWritten<0){
			perror("write");
			close(listFd);
			return -1;
		}

	}
	close(listFd);
	listOpen();
}

int fileDownload(int sock, char *ip, char *fName){
	printf("\n(fileDownload)fileDownload진입\n");
	printf("(fileDownload)받은fName : %s\n", fName);
	
	if (ip == NULL){
		perror("fileDownload");

		return -1;
	}

	char command[100]="/bin/echo -e 'type:download\npath:";
	strcat(command,fName);
	strcat(command,"\n");
	strcat(command,"ip:");
	strcat(command,ip);
	strcat(command,"'");
	strcat(command," > request.txt");
	system(command);
	printf("(fileDownload)request.txt작성 완료\n");    

	int fd = open("./request.txt", O_RDONLY);	
	if (fd==-1){
		perror("open");
		return -1;
	}

	/*
	char requestBuf[BUFFER_SIZE]=" ";
	strcat(requestBuf,"type:");
	strcat(requestBuf,"download\n");
	strcat(requestBuf,"path:");
	strcat(requestBuf,fName);
	strcat(requestBuf,"\n");
	strcat(requestBuf,"ip:");
	strcat(requestBuf,ip);
	*/
    
	/*
	int nFdWritten=write(fd, command, sizeof(command));
	if (nFdWritten < 0){
		perror("write");
		return -1;
	}
	*/
	printf("(fileDownload)request.txt open성공\n");
	char buf[BUFSIZ];
	
	int nRead=read(fd,buf,sizeof(buf));
	if(nRead<0){
		perror("read");
		close(fd);
		return -1;
	}
	buf[nRead]='\0';
	printf("(fileDownload)request.txt read성공\n");
	int nSockWritten=write(sock,buf,nRead);
	if (nSockWritten < 0){
		perror("write");
		return -1;
	}
	printf("(fileDownload)sock에 write성공\n");
	close(fd);

	char actBuf[BUFFER_SIZE]={0,};
	int fd2 = open(actBuf, O_RDWR|O_CREAT|O_TRUNC, 0744);
	memset(actBuf,0,strlen(actBuf));
	while(1){
		int nRead = read(sock, actBuf,sizeof(actBuf));
		if(nRead < 0){
			perror("nRead");
			return -1;
		}
		else if(nRead == 0){
			break;
		}
		printf("(fileDownload)원하는 파일에 쓰기전 read성공\n");
		int nWritten=write(fd2, actBuf, nRead);
        if (nWritten < 0){
			perror("write");
			return -1;
		}
		printf("(fileDownload)원하는 파일에 쓰기 성공\n");
	}
    
	/*
   	while(1){
		int nWritten=write(sock, actBuf, sizeof(actBuf));
        if (nWritten < 0){
			perror("write");
			return -1;
		}
	}
	*/

    close(fd2);
	return 0;
}

int clientQuit(int sock, char *ip){
	printf("(clientQuit)clientQuit들어옴\n");
	if (ip == NULL){
		perror("quit");
		return -1;
	}

	/*
	char buf[BUFFER_SIZE];
	strcat(buf,"type:");
	strcat(buf,"quit\n");
	strcat(buf,"path:");
	strcat(buf,"./\n");
	strcat(buf,"ip:");
	strcat(buf,"192.168.198.144");
	*/
 	char command[100]="/bin/echo -e 'type:quit\npath:./home\nip:";
	strcat(command,ip);
	strcat(command,"'");
	strcat(command," > ./request.txt");
	printf("(clientQuit)command is : %s\n", command);
	system(command);

	int fd = open("./request.txt", O_RDONLY);
	if (fd==-1){
		perror("quit");
		return -1;
	}

	char buf[BUFFER_SIZE];
	int nRead=read(fd,buf,sizeof(buf));
	if(nRead<0){
		perror("read");
		close(fd);
		return -1;
	}
	int nWritten=write(sock, buf, nRead);
	if(nWritten<0){
		perror("write");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}

