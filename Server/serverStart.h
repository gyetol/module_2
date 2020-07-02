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
 #include "getRequest.h"
 #include "response.h"

 #define err_quit(msg) __quit(msg,__LINE__)
 #define LISTENQ (10)
 #define EPOLL_SIZ (128)
 #define DATA_PORT (20629)
 #define CONTROL_PORT (20630)

typedef struct {
     char * type;
     char * path;
     char * ip;
 }RequestInfo;

typedef struct{
     RequestInfo reqInfo;
     int sock;
 }ResponseInfo;





 void __quit(const char * msg,int line);
 void* serverStart(void* arg);
