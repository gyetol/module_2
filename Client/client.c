#include <pthread.h>
#include <errno.h>
#include "localClientThread.h"

int main(){
	char * ip;
	if(IP_INSERT_PAGE(&ip)==-1){
		//클라이언트에게 ip재입력 받음
	}

	pthread_t tid;
	if(pthread_create(&tid,NULL,localClientThread,NULL)==EAGAIN){
		fprintf(stderr,"client_main:thread생성 실패\n");
		return -1;
	}

	doCommand();

	return 0;
}
