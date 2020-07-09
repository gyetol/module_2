#ifndef SERVER_START_H_
#define SERVER_START_H_

 #include <sys/types.h>
 #include <sys/socket.h>
 #include <pthread.h>
 #include <sys/epoll.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <errno.h>
 #include <netinet/in.h>
 #include <netinet/ip.h>
 #include <arpa/inet.h>
 #include<time.h>
 #include "getRequest.h"
 #include "response.h"

 #define err_quit(msg) __quit(msg,__LINE__)
 #define LISTENQ (10)
 #define EPOLL_SIZ (128)
 #define DATA_PORT (20629)

typedef struct {
     char * type;
     char * path;
     char * ip;
 }RequestInfo;

typedef struct{
     RequestInfo reqInfo;
     int sock;
 }ResponseInfo;


 void* serverStart(void* arg);
#endif
