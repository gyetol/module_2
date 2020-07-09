#include "sendRequest.h"

/*
int listDownload(int sock,char * ip,const char * cmd){
*/

int listDownload(int sock, char *ip){
// 	printf("\n(listDownload)listDownload들어옴\n");
// 	printf("(listDownload)받은 ip:%s\n",ip);

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
// 		printf("(listDownload)./request.txt에 끄는 중에 버퍼 확인:%s\n",buf);
		int nWritten=write(sock,buf,nRead);
		if(nWritten<0){
			perror("write");
			close(fd);
			return -1;
		}
	}

	close(fd);
// 	printf("(listDownload):server에 요청완료\n");

	int listFd=open("./list.txt",O_WRONLY|O_CREAT|O_TRUNC,0744);
	if(listFd==-1){
		perror("open");
		close(listFd);
		return -1;
	}
	while(1){
// 		printf("(listDownload):sock에서 읽어오는 while문 진입\n");
		int nRead=read(sock,buf,sizeof(buf));
// 		printf("(listDownload)nRead:%d\n",nRead);
		if(nRead<0){
			perror("read");
			close(listFd);
			return -1;

		}
		else if(strstr(buf,"EOF"))
			break;
		else{
// 			printf("(listDownload)nRead완료\n");
// 			printf("in buf\n%s\n",buf);
			int nWritten=write(listFd,buf,nRead);
			if(nWritten<0){
				perror("write");
				close(listFd);
				return -1;
			}
// 			printf("(listDownload)write완료\n");
		}
	}
// 	printf("(listDownload)write탈출\n");
	//listOpen();
}

int fileDownload(int sock, char *ip, char *fName){
// 	printf("\n(fileDownload)fileDownload진입\n");
// 	printf("(fileDownload)받은fName : %s\n", fName);	
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
// 	printf("(fileDownload)command is : %s", command);
	system(command);
// 	printf("(fileDownload)request.txt작성 완료\n");    
   
	int fd = open("./request.txt", O_RDONLY);	
	if (fd==-1){
		perror("open");
		return -1;
	}
//     printf("(fileDownload)request.txt open성공\n");

	char buf[BUFSIZ];

	int nRead=read(fd,buf,sizeof(buf));
	if(nRead<0){
		perror("read");
		close(fd);
		return -1;
	}
// 	printf("(fileDownload)request.txt read성공\n");
	buf[nRead]='\0';

	int nSockWritten=write(sock,buf,nRead);
	if(nSockWritten<0){
		perror("write");
		close(fd);
		return -1;
	}
// 	printf("(fileDownload)request.txt sock에 write성공\n");
	close(fd);


	char actBuf[BUFFER_SIZE]={0,};
	size_t fSize;

	//하드코딩-----------
	mkdir("./home",0744);
	chdir("./home");
	//---------------------
// 	printf("(fileDownload)열 fileName:%s\n",fName);
	int fd2 = open(actBuf, O_RDWR|O_CREAT|O_TRUNC, 0744);
	if(fd2<0){
		perror("open");
		return -1;
	}
// 	printf("(fileDownload)%s 파일 open 성공\n",fName);

	memset(actBuf,0,strlen(actBuf));

   //extract fileSize
   fSize = fileSize(fName);
//    printf("%20s :%ld MB\n", fName, fSize);

   sscanf(strchr(actBuf, '(')+1, "%lu", &fSize);
//    printf("fileSize : %lu\n", fSize);

	while(1){
		int nRead = read(sock, actBuf,sizeof(actBuf));
		if(nRead < 0){
			perror("nRead");
			return -1;
		}
		else if(strstr(buf,"EOF"))
			break;
// 		printf("(fileDownload)원하는 파일에 쓰기전 read성공\n");

		int nWritten=write(fd2, actBuf, nRead);
        if (nWritten < 0){
			perror("write");
			return -1;
		}
// 		printf("(fileDownload)원하는 파일에 쓰기 성공\n");
	}
	chdir("..");
  
    close(fd2);
	return 0;
}


int clientQuit(int sock, char *ip){
// 	printf("(clientQuit)clientQuit들어옴\n");
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
// 	printf("(clientQuit)command is : %s\n", command);
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


