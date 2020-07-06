#include "sendRequest.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
int listDownload(int sock, char *ip){
	printf("listDownload들어옴\n");
	printf("받은 ip:%s\n",ip);

   if (ip == NULL){
		perror("listDownload");
		return -1;
	}



    char command[100]="/bin/echo -e 'type:ls\npath:./home\nip:";
	strcat(command, ip);
	strcat(command, "'");
	strcat(command," > request.txt");
	system(command);


	int fd = open("./request.txt", O_RDONLY|O_CREAT, 0444);
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
*/
int fileDownload(int sock, char *ip, char *fName){
	printf("받은fName : %s\n", fName);
	printf("fileDownload진입\n");
	
	//int readBytes, totalBytes;
	if (ip == NULL){
		perror("fileDownload");
		return -1;
	}

	char command[100]="/bin/echo -e 'type:download\npath:";
	strcat(command,fName);
	strcat(command,"\nip:");
	strcat(command,ip);
	strcat(command,"'");
	strcat(command," > ./request.txt");
	printf("command is : %s", command);
	system(command);

	printf("request.txt작성 완료\n");    
	int fd = open("./request.txt", O_RDONLY, 0444);	
	if (fd==-1){
		perror("open");
		return -1;
	}

	printf("open성공\n");
	char buf[BUFSIZ];
	
	int nRead=read(fd,buf,sizeof(buf));
	if(nRead<0){
		perror("read");
		close(fd);
		return -1;
	}
	buf[nRead]='\0';
	printf("read성공\n");
	int nSockWritten=write(sock,buf,nRead);
	if (nSockWritten < 0){
		perror("write");
		close(fd);
		return -1;
	}
	printf("write성공\n");

//	close(fd);

	char actBuf[BUFFER_SIZE]={0,};
	chdir("./home");
 //	strcat(actBuf,"./home/");
//	strcat(actBuf,fName);
	printf("열 fName : %s\n", fName);
	int fd2 = open(fName, O_WRONLY|O_CREAT|O_TRUNC, 0222);
    if(fd2<0){
	   perror("open");
	   return -1;
    }
    printf("원하는 파일 오픈 성공\n");
	while(1){
		int nRead = read(sock, actBuf,sizeof(actBuf));
		if(nRead < 0){
			perror("nRead");
			return -1;
		}
		else if(nRead == 0){
			break;
		}
		printf("원하는 파일에 쓰기전 read성공\n");
		int nWritten=write(fd2, actBuf, nRead);
        if (nWritten < 0){
			perror("write");
			return -1;
		}
		printf("원하는 파일에 쓰기 성공\n");

	}
    chdir("..");
   // close(fd2);
	return 0;
}

/*int clientQuit(int sock, char *ip){
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

}*/

