#include "getRequest.h"

int execute(char *type, char *path, char *ip, int cSock){
	if(type==NULL||path==NULL||ip==NULL)
	{
		perror("execute");
		return -1;
	}
	if(strcmp(type, "ls")==0)
	{
		int fd=open("./list.txt", O_RDWR, O_CREAT, O_TRUNC, 0666);
		if(fd==-1)
		{
			perror("open");
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
				return -1;
			}
				else if(nRead==0){
					break;
				}
		
		int nWritten=write(cSock,buf, sizeof(buf));
			if(nWritten<0){
				perror("write");
				return -1;
			//클라이언트에게 list.txt전송
			}
		}
	}
	else if(strcmp(type, "download")==0)
	{
		int fd=open(path, O_RDONLY,0444);
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
				return -1;
			}
			else if(nRead==0){
				break;
			}
		int nWritten=write(cSock, buf, sizeof(buf));
			if(nWritten<0){
				perror("write");
				return -1;
			}
		}
		//클라이언트에게 해당경로의  파일내용 전송
	}
	else
	{
		perror("type");
		return -1;
	}
	return 0;
}


int main(int cSock){ //getRequest(int cSock);
	int fd=open("./request.txt", O_RDONLY, 0444);
	if(fd==-1){
		perror("open");
		return -1;
	}
	char buf[BUFSIZ];
	while(1){
		int nRead=read(fd, buf, sizeof(buf));
		if(nRead<0){
			perror("read");
			return -1;
		}
		else if(nRead==0){
			break;
		}
	}
	char *savePtr;
	char *saveStr;
	char *ptr=strtok_r(buf,"\n", &savePtr); 
	
		char *type=strtok_r(ptr,":", &saveStr);
			  										//printf("%s", str);
			  type=strtok_r(NULL,":", &saveStr);
												// printf("%s\n", str); 
			  
			  if(strcmp(type, "ls")!=0&&strcmp(type, "download")!=0)
				{
				  perror("type");
				  return -1;
				}
					  
		ptr=strtok_r(NULL, "\n", &savePtr);
	
		char *path=strtok_r(ptr, ":", &saveStr);
			  path=strtok_r(NULL, ":", &saveStr);
			  printf("path : %s\n", path);

		ptr=strtok_r(NULL, "\n", &savePtr);

		char *ip=strtok_r(ptr, ":", &saveStr);
			  ip=strtok_r(NULL, ":", &saveStr);
			  printf("ip : %s\n", ip);

		execute(type, path, ip, cSock);
			  
return 0;
}
