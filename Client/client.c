#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "myListOpen.h"
#include "clientStart.h"
#include "doCommand.h"
#include "commandFunc.h"
#include "commonNcurses.h"

int clientMain(int *thisMenu){
    init_scr();
    int sock = 0;
    char * ip = "";
    int thisMenu = MENU_MAIN;

	ResInfo resInfo={0,};

	*thisMenu=IP_insert_Page(&ip);//IP입력을 받아야한다.

	printf("(client.c)입력받은 ip:%s\n",ip);

	if(myListOpen()==-1){
		fprintf(stderr,"error in myListOpen\n");
		return -1;
	}


	if(clientStart(ip,&sock)==-1||sock==0){
		fprintf(stderr,"error in clientStart\n");
		return -1;
	}	
	resInfo.sock=sock;

	//자기 ip뽑아내기-----------------------------------
	char * myIp;
	struct ifaddrs* addrs;
	if(getifaddrs(&addrs)==-1){
		perror("getifaddrs");
		return -1;
	}
	struct ifaddrs* tmp = addrs;

	while (tmp) 
	{
		if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
		{
			struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
			myIp=inet_ntoa(pAddr->sin_addr);
		}

		tmp = tmp->ifa_next;
	}
	freeifaddrs(addrs);
	//--------------------------------------------------------

	resInfo.ip=myIp;//resInfo= {sock,ip};
	printf("(client.c)resInfo.ip==myIp : %s\n",resInfo.ip);


	if(doCommand(&resInfo)==-1){
		fprintf(stderr,"error in doCommand\n");
		return -1;
	}

	close(sock);
	return 0;
}

