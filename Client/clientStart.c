 //Echo Client
#include <sys/types.h>       
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include "clientStart.h"
//#include "listOpen.h"

/*
typedef struct ResponseInfo{
	char * type;
	char * path;
	char * ip;
}ResponseInfo;
*/

int clientStart(const char * ip){

    //make socket for client
    int sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1){
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr = {0,};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(PORT_NUM);
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

	/*
	char * work[BUFSIZ]={0,};
	while(1){
		printf("어떤 작업을 수행하실건가요?(LIST:출력,DOWNLOAD:다운로드,QUIT:작업종료):");
		int nRead=read(0,buf,sizeof(buf));
		if(nRead<0){
			perror("read");
			return -1;
		}
		else if(nRead==0){
			printf("수행하실 작업을 입력하세요!");
			continue;

		}
		break;
	}

	char * path;
	if(strcmp(work,"DOWNLOAD")==0){
		printf("다운로드 받을 파일의 경로를 입력하세요:");
		scanf("%s",path);
	}
	
	
	pthread_ t tid;
	if(strcmp(work,"LIST")){
		pthread_create(&tid,NULL,doListThread,(void*)&sock);
	}
	else{
		pthread_create(&tid,NULL,doDownloadThread,(void*)&sock);
	}


	int * retVal;
	pthread_join(&tid,(void **)&retval);
	*/

    return 0;
}
