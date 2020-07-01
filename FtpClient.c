#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include "FtpCommand.h"
#include "ClientSocket.h"

#define COMMAND_MAX_SIZE 1024
#define BUFFER_SIZE 1024
#define FILENAME_SIZE 256
#define END_OF_PROTOCOL "\r\n"

void initializeFtpClient();
void startFtpClient(char *ip, char *port);
void commandHandle(char *cmd); 
void defaultHandler(char *cmd);
int modeCheck(const char *option);
void printMessage(char *msg);

void openCon(char *cmd);
void list(char *listCmd);
void get(char *getCmd);
void put(char *putCmd);
void cd(char *cdCmd);
void quit(char *quitCmd);
void pwd(char *pwdCmd);
void bye(char *byeCmd);
void hash(char *hashCmd);
void passiveMode(char *ip, int *port);
void shellEscape(char *shellCmd);

unsigned int downloadFile(int sock, char *filePath, unsigned int fileSize);
unsigned int uploadFile(int sock, char *filePath);


typedef struct _FtpCmdHandler {
	char cmd[5];
	void (*handler)(char* arg);
	
} FtpCmdHandler;

// Map Ftp Command to Handler
FtpCmdHandler ftpCmdHandler[] = {
	{ CMD_OPEN, openCon },
	{ CMD_LIST, list },
	{ CMD_PUT, put },
	{ CMD_GET, get },
	{ CMD_CD, cd },
	{ CMD_PWD, pwd },
	{ CMD_HASH, hash },
	{ CMD_QUIT, quit },
	{ CMD_BYE, bye },
	{ CMD_SHELL, shellEscape },
	
};

// sock - PI socket ,  dtpSock - DTP socket
int sock, dtpSock;
int mode;
int hashFlag;


int main (int argc, char const *argv[])
{
	if (argc == 3) {
	// argv[1] == ip, argv[2] == port
		startFtpClient(argv[1], argv[2]);
	} else if (argc == 4 && modeCheck(argv[1]) == MODE_DEBUG) {
	// argv[1] == -d, argv[2] = ip, argv[3] == port
		startFtpClient(argv[2], argv[3]);
	}  else {
		fprintf(stderr, "Usage: %s [-d] <ftp_server_ip> <ftp_server_port>\n", argv[0]);
	}
		
	return 0;
}

int modeCheck(const char *option) {
	if (!strcmp(option, "-d")) {
		// debug mode
		mode = MODE_DEBUG;
	} else {
		mode = MODE_NORMAL;
	}
	return mode;
}

// initialize ftp client
void initializeFtpClient() {
	hashFlag = 1;
	debug("initialized");
}



// ftp client start 
void startFtpClient(char *ip, char *port) {	
	char cmd[COMMAND_MAX_SIZE];

	initializeFtpClient();
	
	while (1) { 
		// input user command
		if (ip == 0 && port == 0) {
			printMessage("ftp>");
			fgets(cmd, COMMAND_MAX_SIZE, stdin);
		} else {
			sprintf(cmd, "open %s %s", ip, port);
			ip = port = 0;
		}	
		// call handler 
		commandHandle(cmd);
	}

}

// map command to handler 
void commandHandle(char *cmd) {
	int i;
	int numCmd = sizeof(ftpCmdHandler)/sizeof(FtpCmdHandler);
	
	for (i = 0; i < numCmd; i++) {
		if (!strncmp(cmd, ftpCmdHandler[i].cmd, strlen(ftpCmdHandler[i].cmd))) {
			(*(ftpCmdHandler[i].handler))(cmd);
			break;
		}
	}	
}


void defaultHandler(char *cmd) {
	printf("default handler: %s\n", cmd);
}

// ftp server connect 
void openCon(char *openCmd) {
	char serverIp[16], serverPort[16];
	char cmd[BUFFER_SIZE];
	char sendBuffer[BUFFER_SIZE];
	char recvBuffer[BUFFER_SIZE];
	
	debug(openCmd);
	sscanf(openCmd,"%*s %s %s%*c", serverIp, serverPort);
	debug(serverIp);
	
	// connect to server
	sock = connectServer(serverIp, atoi(serverPort));
	recvProtocol(sock, recvBuffer, BUFFER_SIZE-1);
	
	// send user name
	printf("Name: ");
	fgets(cmd, COMMAND_MAX_SIZE, stdin);
	sprintf(sendBuffer, "User %s", cmd);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE-1);
	printMessage(recvBuffer);

	// send password
	printf("Password: ");
	fgets(cmd, COMMAND_MAX_SIZE, stdin);
	sprintf(sendBuffer, "PASS %s", cmd);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE-1);
	printMessage(recvBuffer);
		
	// get server os information	
	sprintf(sendBuffer, "SYST%s", END_OF_PROTOCOL);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE-1);
	printMessage(recvBuffer);

}

// send EPSV or PASS to Server
void passiveMode(char *ip, int *port) {
	char sendBuffer[BUFFER_SIZE];
	char recvBuffer[BUFFER_SIZE];
	int host0, host1, host2, host3;
	int port0, port1;
	
	sprintf(sendBuffer, "PASV%s", END_OF_PROTOCOL);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE-1);
	printMessage(recvBuffer);
	
	sscanf(strchr(recvBuffer, '(')+1, "%d,%d,%d,%d,%d,%d", &host0, &host1, &host2, &host3, &port0, &port1);
	sprintf(ip, "%d.%d.%d.%d", host0, host1, host2, host3);

	*port = port0*256 + port1;
	
	debug(ip);
	printf("dtp port : %d\n", *port);
}


// get remote working directory file list
void list(char *listCmd) {
	int port;
	char ip[16];
	char sendBuffer[BUFFER_SIZE];
	char recvBuffer[BUFFER_SIZE*8];
	
	debug("list");

	// recv server response and parsing 
	passiveMode(ip, &port);
	
	// connect to DTP  
	dtpSock = connectServer(ip, port);
	
	// send LIST command to PI server
	sprintf(sendBuffer, "LIST%s", END_OF_PROTOCOL);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE);
	printMessage(recvBuffer);
	
	// recv file list from DTP
	recvProtocol(dtpSock, recvBuffer, BUFFER_SIZE*8);
	printMessage(recvBuffer);
	
	// recv complete message from PI server
	recvProtocol(sock, recvBuffer, BUFFER_SIZE);
	printMessage(recvBuffer);
	
	close(dtpSock);
}


// file download
void get(char *getCmd) {
	int port;
	unsigned int fileSize;
	char ip[16], filePath[FILENAME_SIZE], fileName[50];
	char sendBuffer[BUFFER_SIZE];
	char recvBuffer[BUFFER_SIZE];
	
	// get local current working directory 
	getcwd(filePath, FILENAME_SIZE);
	sscanf(getCmd, "%*s %s%*c", fileName);
	sprintf(filePath, "%s/%s", filePath, fileName);

	debug("get");
	printf("fileName: %s\n", fileName);
	printf("filePath: %s\n", filePath);

	passiveMode(ip, &port);
	
	// connect to DTP
	dtpSock = connectServer(ip, port);
	
	// request server for transfer start - RETR fileName
	sprintf(sendBuffer, "RETR %s%s", fileName, END_OF_PROTOCOL);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE);
	printMessage(recvBuffer);
	
	// extract fileSize 
	sscanf(strchr(recvBuffer, '(')+1, "%u", &fileSize);
	printf("fileSize: %u\n", fileSize);
	
	// download file from DTP 
	downloadFile(dtpSock, filePath, fileSize, hashFlag);
	
	// recv complete message from PI server
	recvProtocol(sock, recvBuffer, BUFFER_SIZE);
	printMessage(recvBuffer);
	
	close(dtpSock);
}




// file upload
void put(char *putCmd) {
	int port;
	unsigned int fileSize;
	char ip[16], filePath[FILENAME_SIZE], fileName[50];
	char sendBuffer[BUFFER_SIZE];
	char recvBuffer[BUFFER_SIZE];
	
	sscanf(putCmd, "%*s %s%*c", fileName);
	
	// get local current working directory
	getcwd(filePath, FILENAME_SIZE);
	sscanf(putCmd, "%*s %s%*c", fileName);
	sprintf(filePath, "%s/%s", filePath, fileName);

	debug("put");
	debug(filePath);
	
	passiveMode(ip, &port);
	
	// connect to DTP
	dtpSock = connectServer(ip, port);
	
	// request server for transfer start - STOR fileName
	sprintf(sendBuffer, "STOR %s%s", fileName, END_OF_PROTOCOL);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE);
	printMessage(recvBuffer);
	
	// file upload to DTP 
	fileSize = uploadFile(dtpSock, filePath, hashFlag);
	
	close(dtpSock);
	
	/// recv complete message from PI server
	recvProtocol(sock, recvBuffer, BUFFER_SIZE);
	printMessage(recvBuffer);
}


// change remote working directory
void cd(char *cdCmd) {
	char sendBuffer[BUFFER_SIZE];
	char recvBuffer[BUFFER_SIZE];
	debug("cd");

	sscanf(cdCmd, "%*s %s%*c", recvBuffer);
	debug(recvBuffer);

	sprintf(sendBuffer, "CWD %s%s", recvBuffer, END_OF_PROTOCOL);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE);
	printMessage(recvBuffer);
}

// ftp client exit 
void quit(char *quitCmd) {
	char sendBuffer[BUFFER_SIZE];
	char recvBuffer[BUFFER_SIZE];
	debug("quit");
	
	sprintf(sendBuffer, "QUIT%s", END_OF_PROTOCOL);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE);
	printMessage(recvBuffer);
	
	close(sock);
	exit(0);
}

// same quit  
void bye(char *byeCmd) {
	quit(0);
}

// get remote working directory
void pwd(char *pwdCmd) {
	char sendBuffer[BUFFER_SIZE];
	char recvBuffer[BUFFER_SIZE];
	debug("pwd");
	
	sprintf(sendBuffer, "PWD%s", END_OF_PROTOCOL);
	sendProtocol(sock, sendBuffer);
	recvProtocol(sock, recvBuffer, BUFFER_SIZE);
	printMessage(recvBuffer);
}


// hash option on/off
void hash(char *hashCmd) {
	debug("hash");
	hashFlag = !hashFlag;
	
	if (hashFlag == 0) {
		printMessage("hash off\n");
	} else {
		printMessage("hash on\n");
	}
}

// shell command - not implemented
void shellEscape(char *shellCmd) {
	printMessage("not implemented");
}



void printMessage(char *msg) {
	printf("%s", msg);
}




