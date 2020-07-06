#ifndef DO_COMMAND_H
#define DO_COMMAND_H
#include "sendRequest.h"
#include <stdlib.h>
#include <pthread.h>
typedef struct ResInfo{
	int sock;
	char * ip;
}ResInfo;

void * fileDownloadThread(void * arg);
int doCommand(ResInfo *resInfo);
//int doCommand(int sock,char * ip);

#endif
