#include "response.h"
  
int response(int cSock, char **type, char **path, char **ip){
	printf("response진입\n");
	if(type==NULL||path==NULL||ip==NULL)
	{
		perror("execute");
		return -1;
	}
	if(strcmp(*type, "ls")==0)
	{
		printf("ls진입\n");
		 chdir("./home");
		char command[100]="/bin/ls -alR > ./list.txt";
		system(command);
		 int fd=open("list.txt", O_RDONLY, 0444);
		 if(fd==-1)
 		{
    		 perror("open");
			 close(fd);
    		 chdir("..");
			 return -1;
		 }
		 printf("open성공\n");
		char buf[BUFSIZ];
		int count=0;
		while(1){
			count++;
			printf("list 응답 내부에 있는 %d번째 while문입니다\n", count);
			int nRead=read(fd, buf, sizeof(buf));
			printf("list 응답 내부에 있는 nRead : %d\n", nRead);
			if(nRead<0){
				perror("read");
				close(fd);
				chdir("..");
				return -1;
			}
			else if(nRead==0){
				break;
			}
		    printf("list요청의 read완료\n"); 
		 	int nWritten=write(cSock,buf, nRead);	
			if(nWritten<0){
				perror("write");
				close(fd);
				chdir("..");
				return -1;
			}
			char eofBuf[3]="EOF";
			int eofWritten=write(cSock, eofBuf, sizeof(eofBuf));
			if(eofWritten<0){
				perror("write");
				close(fd);
				chdir("..");
				return -1;
			}
			getchar();
			printf("list요청의 write완료\n");
		}
		chdir("..");
	}
	else if(strcmp(*type, "download")==0)
	{
	printf("download진입\n");
	chdir("./home");
	printf("path : %s\n", *path);
		int fd=open(*path, O_RDONLY, 0444);
		if(fd==-1){
			perror("open");
			close(fd);
			chdir("..");
			return -1;
		}
		printf("open성공\n");
		char buf[BUFSIZ];
		int count=0;
		while(1){
			count++;
			printf("download 응답 내부의 %d번째 while문입니다\n", count);
			int nRead=read(fd, buf, sizeof(buf));
			printf("download 응답 내부의 nRead : %d\n", nRead);
			if(nRead<0){
				perror("nRead");
				close(fd);
				chdir("..");
				return -1;
			}
			else if(nRead==0){
				break;
			}
			printf("download요청의 read완료\n");
			int nWritten=write(cSock, buf, nRead);
			if(nWritten<0){
				perror("write");
				close(fd);
				chdir("..");
				return -1;
			}
			getchar();
			printf("write완료\n");
		}
		chdir("..");
	}
 
	else if(strcmp(*type, "quit")==0)
	{
		fprintf(stdout, "[ client ] : %s disconnected", *ip);
	}
	else
	{
		perror("type");
		return -1;
	}
	printf("response끝남\n");
	return 0;
}
