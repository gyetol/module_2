#include "getRequest.h"	

int getRequest(int cSock, char **type, char **path, char **ip){
    char buf[BUFSIZ]="";
	int nRead=read(cSock, buf, sizeof(buf));
       
		printf("nRead:%d\n", nRead);
	   	if(nRead<0){
            perror("read");
            return -1;
        }
    char *savePtr;
    char *saveStr;
    char *ptr=strtok_r(buf,"\n", &savePtr);

    *type=strtok_r(ptr,":", &saveStr);
    *type=strtok_r(NULL,":", &saveStr);
    if(strcmp(*type, "ls")!=0&&strcmp(*type, "download")!=0&&strcmp(*type, "quit")!=0)
    {
        perror("type");
        return -1;
    }

    ptr=strtok_r(NULL, "\n", &savePtr);

    *path=strtok_r(ptr, ":", &saveStr);
    *path=strtok_r(NULL, ":", &saveStr);

    ptr=strtok_r(NULL, "\n", &savePtr);

    *ip=strtok_r(ptr, ":", &saveStr);
    *ip=strtok_r(NULL, ":", &saveStr);
   return 0;
}
