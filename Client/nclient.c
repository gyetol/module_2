#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "myListOpen.h"
#include "clientStart.h"
#include "doCommand.h"
#include "commandFunc.h"
#include "commonNucurses.h"


char * sampleFiles[] = {"this is file 1", "this is file 2"};

int main(){
	init_scr();
	int sock=0;
	char *ipAddress="";
	int thisMenu = MENU_MAIN;
	int *selected = NULL;
	ResInfo resInfo={0,};
	char *msg= ".";

	while(thisMenu != MENU_EXIT){
		switch(thisMenu){
			case MENU_MAIN:
				thisMenu= IP_insert_Page(&ipAddress);
				break;
			case MENU_FIRSTWINODW: 
			case MENU_SECONDWINDOW:
			case MENU_THIRDWINDOW:
			case MENU_FOURTHWINDOW:
				thisMenu= print_Selected_Page(MODE_CLIENT,thisMenu,sampleFiles,selected, 17, "CLIENT PATH", "SERVER PATH",&resInfo,&msg);
				break;
			case MENU_IP_INSERT: 
				ipAddress= "192.168.30.2";
				if(clientStart(ipAddress,&sock)==-1 || sock==0){
					fprintf(stderr,"error in clientStart\n");
					return -1;
				}
				thisMenu =MENU_FTP_PAGE;
				break;
	
			case MENU_FTP_PAGE:
				thisMenu = FTP_Main_Page(MODE_CLIENT,"CLIENT PATH","SERVER PATH",&resInfo,&msg);
				break;
			case MENU_IP_MANAGE:
				break;
			case MENU_HELP:
				break;
			case MENU_BOOKMARKS:
				break;
			case MENU_HISTORY:
				break;
		}
	}


	//printf("접속할 서버의 IP를 입력하세요:");
	//scanf("%s",ip);

	//printf("%s\n",ip);//디버그 코드
	//if(ip==NULL){
	//	perror("scanf");
	//	return -1;
	//}


	if(myListOpen()==-1){
		fprintf(stderr,"error in myListOpen\n");
		return -1;
	}


	if(clientStart(ipAddress,&sock)==-1||sock==0){
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

