#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "FtpCommand.h"
#include "ClientSocket.h"
#define BUFSIZ 1024

int listDownload(char *type, char *path, char *ip int sSock){

	if (type == NULL || path == NULL || ip == NULL){
		perror("listDownload");
		return -1;
	}

	int fd = open("./request.txt", O_RDWR, O_CREAT, O_TRUNC, 0744);
	
	if (fd==-1){
		perror("open");
		return -1;
	}

	char buf[BUFSIZ]=" ";
	strcat(buf,"type:");
    strcat(buf,"ls\n");
	strcat(buf,"path:");
	strcat(buf,"./home\n");
	strcat(buf,"ip:");
	strcat(buf,"192.168.198.141");
    
	while(1){
	int nRead = read(fd, buf, sizeof(buf));

	if (nRead < 0){
		perror("nRead");
		close(fd);
		return -1;
	}

	else if(nRead == 0){
		break;
	}

	int nWritten=write(cSock,buf,sizeof(buf));
	if(nWritten<0){
		perror("write");
		close(fd);
		return -1;
	   } 
	}
	close(fd);

}

int fileDownload(char *type, char *path, char *ip, int sSock){

	int readBytes, totalBytes;

	if (type == NULL || path == NULL || ip == NULL){
		perror("fileDownload");
		return -1;
	}

	int fd = open("./requst.txt", O_RDWR, O_CREAT, O_TRUNC, 0744);	
		//mode는 0700 파일 소유자에게 읽기 쓰기, 쓰기 실행 권한 
		//00040으로 그룹에게 읽기 권한
		//00004으로 기타 사용자에게 읽기 권한을 준다

	if (fd==-1){
		perror("open");
		return -1;
	}

	char requestBuf[BUFSIZ]=" ";
	strcat(requestBuf,"type:");
	strcat(requestBuf,"download\n");
	strcat(requestBuf,"path:");
	strcat(requestBuf,"./home\n");
	strcat(requestBuf,"ip:");
	strcat(requestBuf,"192.168.198.141");
    
	while(1){
    int nRead = read(fd, requestBuf, sizeof(requestBuf));

	if(nRead < 0){
		perror("nRead");
		return -1;
	}
	else if(nRead == 0){
		break;
	}
    
	while(1){
	int nWritten=write(sSock, requestBuf, sizeof(requestBuf));
	if (nWritten < 0){
		perror("write");
		return -1;
	}

	close(fd);

	char actBuf[BUFSIZ]=" ";
	strcat(actBuf,"./");
	strcat(actBuf,path);

	int fd = open(actBuf, O_RDWR, O_CREAT, O_TRUNC, 0744);
    while(1){
		int nRead = read(fd, actBuf,sizeof(actBuf));

		if(nRead < 0){
			perror("nRead");
			return -1;
		}
		else if(nRead == 0){
			break;
		}
	}
    
	while(1){
		int nWritten=write(sSock, actBuf, sizeof(actBuf));
        if (nWritten < 0){
			perror("write");
			return -1;
		}
	}
    close(fd);

	return 0;
}

int main(int argc, char **argv){

	unsigned int fileSize;
	char fileName[100];
	char recvBuffer[BUFFER_SIZE];
    
	if(argc !=2){
		fprintf(stderr, "./ls OR ./download [filePath]");
		return -1;
	}
	
	while(1){
			int nWritten=write(fd, buf, sizeof(buf));
			if(nWritten<0){
				perror("write");
				return -1;
			}//request.txt
		}
		close(1);
		dup(fd);

		while(1){
			//키보드로부터 데이터를 읽습니다.
			int nRead = read(0, buf, sizeof(buf));
			if (nRead < 0) {
				perror("read");
				return -1;
			}
			else if (nRead == 0) {
				break;
			}

			int nWritten=write(sSock, buf, sizeof(buf));
			if (nWritten < 0){
				perror("write");
				return -1;
			}
		} 
	}

    if (strcmp(type, "ls")==0){
		listDownload();
	}
    else if (strcmp(type,"downLoad")==0){
		fileDownload();
	}
	else if (strcmp(type, "download")==0){
       }
