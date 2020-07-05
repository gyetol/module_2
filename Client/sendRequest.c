#include "sendRequest.h"

int listDownload(int sock, char *ip){
	printf("listDownload들어옴\n");

   if (ip == NULL){
		perror("listDownload");
		return -1;
	}

	int fd = open("./request.txt", O_RDWR, O_CREAT, O_TRUNC, 0744);
	
	if (fd==-1){
		perror("open");
		return -1;
	}

	char buf[BUFFER_SIZE]=" ";
	strcat(buf,"type:");
    strcat(buf,"ls\n");
	strcat(buf,"path:");
	strcat(buf,"./home\n");
	strcat(buf,"ip:");
	strcat(buf,"192.168.198.141");
    
	while(1){

	int nWritten=write(sock,buf,sizeof(buf));
	if(nWritten<0){
		perror("write");
		close(fd);
		return -1;
	   } 
	}
	close(fd);
	listOpen();

}


int fileDownload(int sock, char *ip, char *fName){
	printf("fileDownload들어옴\n");

	int readBytes, totalBytes;

	if (ip == NULL){
		perror("fileDownload");
		return -1;
	}

	int fd = open("./request.txt", O_RDWR, O_CREAT, O_TRUNC, 0744);	
		//mode는 0700 파일 소유자에게 읽기 쓰기, 쓰기 실행 권한 
		//0004 0으로 그룹에게 읽기 권한
		//00004으로 기타 사용자에게 읽기 권한을 준다

	if (fd==-1){
		perror("open");
		return -1;
	}

	char requestBuf[BUFFER_SIZE]=" ";
	strcat(requestBuf,"type:");
	strcat(requestBuf,"download\n");
	strcat(requestBuf,"path:");
	strcat(requestBuf,"./home\n");
	strcat(requestBuf,"ip:");
	strcat(requestBuf,"192.168.198.141");
    
	while(1){
		/*
		int nFdWritten=write(fd, requestBuf, sizeof(requestBuf));
		if (nFdWritten < 0){
			perror("write");
			return -1;
		}
		*/
		int nSockWritten=write(sock,requestBuf,sizeof(requestBuf));
		if (nSockWritten < 0){
			perror("write");
			return -1;
		}
	}

	

	close(fd);

	char actBuf[BUFFER_SIZE]=" ";
 	strcat(actBuf,"./");
	strcat(actBuf,fName);

	int fd2 = open(actBuf, O_RDWR, O_CREAT, O_TRUNC, 0744);
    while(1){
		int nRead = read(fd2, actBuf,sizeof(actBuf));

		if(nRead < 0){

			perror("nRead");
			return -1;
		}
		else if(nRead == 0){
			break;
		}
	}
    
   /*	while(1){
		int nWritten=write(cSock, actBuf, sizeof(actBuf));
        if (nWritten < 0){
			perror("write");
			return -1;
		}
	}*/

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

