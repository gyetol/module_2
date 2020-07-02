#include "localClientThread.h"

////////////////////////////////////////
/// client main에서 생성하는 sub_thread : myListOpen하고 내부 명령 처리하면 된다
/// input : pthread_create에서 전달해주는 arg
/// return : 내부에서 동적할당
void * localClientThread(void *arg){
	char* ip=(char*)arg;
	int * retVal=calloc(1,sizeof(int));
	if(clientStart(ip)==-1){
		fprintf(stderr,"clientStart()");
		*retVal=-1;
	}
	*retVal=0;
	return retVal;
}

