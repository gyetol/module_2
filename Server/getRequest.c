#include "getRequest.h"	

int getRequest(int cSock, char **type, char **path, char **ip){
	printf("getRequest진입\n");
	int fd=open("./request.txt", O_RDWR, 0744);
    if(fd==-1){
        perror("open");
		close(fd);
        return -1;
    }
	int count=0;
    char buf[BUFSIZ]="";
    while(1){
        int nRead=read(cSock, buf, sizeof(buf));
       printf("nRead:%d\n", nRead);
	   	if(nRead<0){
            perror("read");
			close(fd);
            return -1;
        }
        else if(nRead==0){
            break;
        }

		printf("read완료\n");
		int nWritten=write(fd, buf, nRead);
		if(nWritten<0){
			perror("write");
			return -1;
		}
		printf("write완료\n");
		close(fd);
	}
	getchar();
	printf("while문탈출\n");
    char *savePtr;
    char *saveStr;
    char *ptr=strtok_r(buf,"\n", &savePtr);

    *type=strtok_r(ptr,":", &saveStr);
    *type=strtok_r(NULL,":", &saveStr);
    if(strcmp(*type, "ls")!=0&&strcmp(*type, "download")!=0)
    {
        perror("type");
		close(fd);
        return -1;
    }

    ptr=strtok_r(NULL, "\n", &savePtr);

    *path=strtok_r(ptr, ":", &saveStr);
    *path=strtok_r(NULL, ":", &saveStr);

    ptr=strtok_r(NULL, "\n", &savePtr);

    *ip=strtok_r(ptr, ":", &saveStr);
    *ip=strtok_r(NULL, ":", &saveStr);
   printf("getRequest수행완료\n");
   return 0;
}
