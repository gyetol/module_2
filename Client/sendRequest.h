#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "FtpCommand.h"
#include "ClientSocket.h"
#include "listOpen.h"
#define BUFSIZ 1024
#define END_OF_PROTOCOL "\r\n"


int fileDownload(char *type, char *path, char *ip, int cSock);
int listDownload(char *type, char *path, char *ip, int cSock);
int quit(char *type, char *path, char *ip, int cScok);
