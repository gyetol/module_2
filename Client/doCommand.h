#ifndef DO_COMMAND_H
#define DO_COMMAND_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include "commandFunc.h"
#include "sendRequest.h"
#include "listOpen.h"
#include "myListOpen.h"

typedef struct ResInfo{
	int sock;
	char * ip;
}ResInfo;

void * fileDownloadThread(void * arg);
int doCommand(ResInfo *resInfo);
//int doCommand(int sock,char * ip);

#endif
