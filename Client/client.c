#include <pthread.h>
#include <errno.h>
#include<stdio.h>
#include<stdlib.h>
#include "localClientThread.h"

int main(){
	char * ip;
	/*
	if(IP_INSERT_PAGE(&ip)==-1){
		//클라이언트에게 ip재입력 받음
	}
	*/
	printf("접속할 서버의 IP를 입력하세요:");
	scanf("%s",ip);
	if(ip==NULL){
		perror("scanf");
		return -1;
	}

	pthread_t tid;
	if(pthread_create(&tid,NULL,localClientThread,(void*)ip)==EAGAIN){
		fprintf(stderr,"client_main:thread생성 실패\n");
		return -1;
	}

	/*
	if(clientCommand()==-1){
		perror("clientCommad");
		return -1;
	}
	*/

	return 0;
}
