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

int listDownload(int sock, char *ip){
	printf("listDownload들어옴\n");
	printf("받은 ip:%s\n",ip);

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
		printf("\tlistDownload:%s\n",buf);
		int nWritten=write(sock,buf,nRead);
		if(nWritten<0){
			perror("write");
			close(fd);
			return -1;
		}
	}

	close(fd);
	printf("\tlistDownload:server에 요청완료\n");

	int listFd=open("./list.txt",O_WRONLY|O_CREAT|O_TRUNC,0744);
	if(listFd==-1){
		perror("open");
		close(listFd);
		return -1;
	}
	while(1){
		printf("\tlistDownload:sock에서 읽어오는 while문 진입\n");
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
	printf("fileDownload들어옴\n");
	
	//int readBytes, totalBytes;
	if (ip == NULL){
		perror("fileDownload");

		return -1;
	}

	int fd = open("./request.txt", O_RDWR|O_CREAT|O_TRUNC, 0744);	
		//mode는 0700 파일 소유자에게 읽기 쓰기, 쓰기 실행 권한 
		//0004 0으로 그룹에게 읽기 권한
		//00004으로 기타 사용자에게 읽기 권한을 준다

	if (fd==-1){
		perror("open");
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
	int nSockWritten=write(sock,command,sizeof(command));
	if (nSockWritten < 0){
		perror("write");
		return -1;
	}


	close(fd);

	char actBuf[BUFFER_SIZE]={0,};
 	strcat(actBuf,"./home/");
	strcat(actBuf,fName);

	int fd2 = open(actBuf, O_RDWR|O_CREAT|O_TRUNC, 0744);
    while(1){
		int nRead = read(sock, actBuf,sizeof(actBuf));
		if(nRead < 0){
			perror("nRead");
			return -1;
		}
		else if(nRead == 0){
			break;
		}
		int nWritten=write(fd2, actBuf, nRead);
        if (nWritten < 0){
			perror("write");
			return -1;
		}

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
	printf("clientQuit들어옴\n");

	if (ip == NULL){
		perror("quit");
		return -1;
	}

	int fd = open("./request.txt", O_RDWR, O_CREAT, O_TRUNC, 0744);

	if (fd==-1){
		perror("quit");
		return -1;
	}

	char buf[BUFFER_SIZE];
	strcat(buf,"type:");
	strcat(buf,"quit\n");
	strcat(buf,"path:");
	strcat(buf,"./\n");
	strcat(buf,"ip:");
	strcat(buf,"192.168.198.144");
 
	while(1){
		int nWritten=write(sock, buf, sizeof(buf));
		if(nWritten<0){
			perror("write");
			close(fd);
			return -1;
		}
	}
	close(fd);

}

