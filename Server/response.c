#include "response.h"
  
int response(int cSock, int* conFlag, char **type, char **path, char **ip){
	if(type==NULL||path==NULL||ip==NULL)
	{
		perror("execute");
		return -1;
	}
printf("response함수 진입 완료\n");
	if(strcmp(*type, "ls")==0)
	{
		int fd=open("./list.txt", O_RDWR, O_CREAT, O_TRUNC, 0666);
		if(fd==-1)
		{
			perror("open");
			close(fd);
			return -1;
		}
		close(1);
		dup(fd);
		chdir("./home");
		system("/bin/ls -alR");
		char buf[BUFSIZ];
		while(1){
			int nRead=read(fd, buf, sizeof(buf));
			if(nRead<0){
				perror("read");
				close(fd);
				return -1;
			}
			else if(nRead==0){
				break;
			}

			int nWritten=write(cSock,buf, sizeof(buf));
			if(nWritten<0){
				perror("write");
				close(fd);
				return -1;
				//클라이언트에게 list.txt전송
			}
		}
		close(fd);
	}
	else if(strcmp(*type, "download")==0)
	{
		int fd=open(*path, O_RDONLY, 0444);
		if(fd==-1){
			perror("open");
			return -1;
		}
		close(1);
		dup(fd);
		char buf[BUFSIZ];
		while(1){
			int nRead=read(fd, buf, sizeof(buf));
			if(nRead<0){
				perror("nRead");
				close(fd);
				return -1;
			}
			else if(nRead==0){
				break;
			}
			int nWritten=write(cSock, buf, sizeof(buf));
			if(nWritten<0){
				perror("write");
				close(fd);
				return -1;
			}
		}
		//클라이언트에게 해당경로의  파일내용 전송
		close(fd);
	}
	else if(strcmp(*type, "quit")==0)
	{
		fprintf(stdout, "[ client ] : %s disconnected", *ip);
		*conFlag=0;
	}
	else
	{
		perror("type");
		return -1;
	}
	return 0;
}
