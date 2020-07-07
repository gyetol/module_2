#ifndef MODULE_2_COMMANDFUNC_H
#define MODULE_2_COMMANDFUNC_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <fcntl.h>

int putSrcPath(char **srcPath, char **msg);
int freeDestPath(char *destPath, char **msg);
int getDestPath(char *destPath, char **msg, const char * checkMsg);
int doRemove(char **srcPath, int len, char **msg);
int doMkdir(char **msg);
int doMove(char **srcPath, int len, char *destPath, char **msg);
int doCopy(char **srcPath, int len, char *destPath, char **msg);
int doRename(char **srcPath, int len, char *destPath, char **msg);
int putSrcPath(char **srcPath, char **msg);
void myflush();

#endif //MODULE_2_COMMANDFUNC_H
