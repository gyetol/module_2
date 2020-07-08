#ifndef SEND_REQUEST_H
#define SEND_REQUEST_H

#define BUFFER_SIZE (1024)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/statfs.h>
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include "listOpen.h"

int fileDownload(int cSock, char *ip, char *fName);
int listDownload(int cSock, char *ip);
int clientQuit(int cSock, char *ip);
static ssize_t fileSize(const char *fName){
    struct stat sb;
    if(stat(fName, &sb) != 0){
        perror("error");
        exit(EXIT_FAILURE);
    }
    return sb.st_size;
}
#endif

