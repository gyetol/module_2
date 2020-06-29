#include "serverStart.h"
int serverStart(char *ip){
	if(ip==NULL){
		perror("serverIp");
		return -1;
	}
	printf("[server] is running : %s\n\n", ip);
	return 0;
}
