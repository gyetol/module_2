#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include "myListOpen.h"
#include "clientStart.h"
#include "doCommand.h"

typedef struct ResInfo{
	int sock;
	char * ip;
}ResInfo;

void * subThread(void *arg){
	if(arg==NULL){
		fprintf(stderr,"subThread:argument is null\n");
		return NULL;
	}
	int * retVal=calloc(1,sizeof(int));
	if(retVal==NULL){
		perror("calloc");
		*retVal=-1;
	}
	ResInfo* ptr=(ResInfo*)arg;
	if(doCommand(ptr->sock,ptr->ip)==-1)
		*retVal=-1;
	*retVal=0;
	return retVal;
}

int main(){
	char * ip;
	ResInfo resInfo={0,};

	/*
	if(IP_INSERT_PAGE(&ip)==-1){
		//클라이언트에게 ip재입력 받음
	}
	*/

	printf("접속할 서버의 IP를 입력하세요:");
	scanf("%s",ip);

	printf("%s\n",ip);//디버그 코드
	if(ip==NULL){
		perror("scanf");
		return -1;
	}


	if(myListOpen()==-1){
		fprintf(stderr,"error in myListOpen\n");
		return -1;
	}


	pthread_t tid;
	if(pthread_create(&tid,NULL,subThread,&resInfo)!=0){
		perror("pthread_create");
		return -1;
	}

	int *retVal;
	if(pthread_join(tid,(void**)&retVal)!=0){
			perror("pthread_join");
			return -1;
	}
	if(*retVal==-1){
		fprintf(stderr,"error in doCommand\n");
		return -1;
	}

	int sock=0;
	if(clientStart(ip,&sock)==-1||sock==0){
		fprintf(stderr,"error in clientStart\n");
		return -1;
	}

	if(doCommand(sock,ip)==-1){
		fprintf(stderr,"error in doCommand\n");
		return -1;
	}

	close(sock);
	return 0;
}

