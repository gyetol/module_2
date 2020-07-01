//Echo Client
#include <sys/types.h>       
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
//#include "listOpen.h"

void localThread(void * arg){

}

int clientStart(const char * ip, int * sock){
    //make socket for client
    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1){
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr = {0,};
    addr.sin_family=AF_INET;
    addr.sin_port=htons((int)PORT_NUM);
    addr.sin_addr.s_addr=inet_addr((char * )ip);

    //try to connect to server
    if(connect(sock,(struct sockaddr*)&addr,sizeof(addr))==-1){
        perror("connect");
        return -1;
    }

//    //get command from keyboard
//    char buf[BUFSIZ];
//    int nRead=read(0,buf,sizeof(buf)); //stdin
//
//    if(nRead<0){
//        perror("read");
//        return -1;
//    }
//    else if(nRead==0){
//        return -1;
//    }
//
//    //request to server
//    buf[nRead]='\0';
//    write(sock,buf,nRead);
//
//    nRead=read(sock,buf,sizeof(buf));
//    if(nRead<0){
//        perror("read");
//        return -1;
//    }
//    else if(nRead==0){
//        return -1;
//    }
//
//    buf[nRead]='\0';
//    fputs(buf,stdout);
    return 0;
}
