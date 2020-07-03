#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int fileDownload(int cSock, char *ip, char *fname);
int listDownload(int cSock, char *ip);
int quit(int cSock, char *ip);
