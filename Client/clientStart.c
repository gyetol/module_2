#include "clientStart.h"
//#include "listOpen.h"

/*
typedef struct ResponseInfo{
	char * type;
	char * path;
	char * ip;
}ResponseInfo;
*/

int clientStart(const char * ip,int * sock){
	//printf("  clientStart들어옴\n");
    //make socket for client
    *sock=socket(PF_INET,SOCK_STREAM,0);
    if(*sock==-1){
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr = {0,};
    addr.sin_family=AF_INET;
    addr.sin_port=htons((int)PORT_NUM);
    addr.sin_addr.s_addr=inet_addr(ip);

    //try to connect to server
    if(connect(*sock,(struct sockaddr*)&addr,sizeof(addr))==-1){
        perror("connect");
        return -1;
    }

    return 0;
}
