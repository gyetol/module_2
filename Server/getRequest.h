#ifndef MODULE_2_GETREQUEST_H
#define MODULE_2_GETREQUEST_H

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
int getRequest(int cSock, char** type, char** path, char **ip);
#endif
