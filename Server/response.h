#ifndef MODULE_2_RESPONSE_H
#define MODULE_2_RESPONSE_H

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h> 
int response(int cSock, int* conFlag, char **type, char **path, char **ip);
#endif
