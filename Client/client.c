#include <pthread.h>
#include <errno.h>
#include<stdio.h>
#include<stdlib.h>
#include "clientStart.h"
//#include "clientMain.h"

void * localClientThread(void *arg){
	printf("localClientThread\n");
	char* ip=(char*)arg;
	int * retVal=calloc(1,sizeof(int));
	if(clientStart(ip)==-1){
		fprintf(stderr,"clientStart()");
		*retVal=-1;
	}
	*retVal=0;
	return retVal;
}


int main(){
	char * ip;

	/*
	if(IP_INSERT_PAGE(&ip)==-1){
		//클라이언트에게 ip재입력 받음
	}
	*/

	printf("접속할 서버의 IP를 입력하세요:");
	scanf("%s",ip);

	printf("%s\n",ip);

	if(ip==NULL){
		perror("scanf");
		return -1;
	}

	pthread_t tid;
	if(pthread_create(&tid,NULL,localClientThread,(void*)ip)==EAGAIN){
		fprintf(stderr,"client_main:thread생성 실패\n");
		return -1;
	}

	//clientMain();

	int* retVal;
	pthread_join(tid,(void**)&retVal);

	return 0;
}

