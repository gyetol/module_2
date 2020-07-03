#include "clientMain.h"

int clientMain(void){
	myListOpen();
	if(clientCommand()==-1){
		fprintf(stderr,"clientExecute:clientCommand() error\n");
		return -1;
	}
	return 0;
}
