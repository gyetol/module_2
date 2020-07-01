#if 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "FtpCommand.h"
#include "ClientSocket.h"

#define BUFFER_SIZE 1024
#define FILENAME_SIZE 256
#endif

#define CMD_OPEN "open"
#define	CMD_LIST "ls"
#define CMD_GET "get"
#define CMD_PUT "put"
#define CMD_PWD "pwd"
#define CMD_CD "cd"
#define CMD_QUIT "quit"
#define CMD_BYE "bye"
#define CMD_HASH "hash"
#define CMD_SHELL "!"

#define MODE_DEBUG 1
#define MODE_NORMAL 0

#define FTP_PORT 21

extern int mode;

void debug(char *msg) {
	if (mode == MODE_DEBUG) {
		printf("[debug] : %s \n", msg);
	}
}
