// Created by linux on 6/30/20.
//

#include <unistd.h>
#include <sys/types.h>
#include <ifaddrs.h>                                                                          
#include "commonNcurses.h"
#include "parsing.h"
#include "clientStart.h"
#include "sendRequest.h"
#include "myListOpen.h"

typedef struct ResInfo{
	int sock;
	char * ip;
}ResInfo;

typedef struct Array{
	char * array[ARR_SIZ];
 	int next;
}Array;


char * sampleFiles[] = {
        "this is file 1", "this is file 2", "this is file 3", "this is file 4",
        "this is file 5", "this is file 6", "this is file 7", "this is file 8",
        "this is file 9", "this is file 10", "this is file 11", "this is file 12",
        "this is file 13", "this is file 14", "this is file 15", "this is file 16"
};


char *getMyIp(){
	char * myIp;
	struct ifaddrs* addrs;
	if(getifaddrs(&addrs)==-1){
		perror("getifaddrs");
		return NULL;
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
	return myIp;
}

int main(){
    init_scr();
    int sock = 0;
    //char * ipAddress = "";
	char * ipAddress = NULL;
    int thisMenu = MENU_MAIN;
    int * selected =NULL;
	char * myIp;

	Array* myDirectories=NULL;
	Array* myFiles=NULL;
	char clientPath[1024]="/home/linux/module2";
	char serverPath[1024]="/home";
	char * msg={0,};

	Array* directories=NULL;
	Array* files=NULL;

	ResInfo resInfo={0,};

	int index;
	char** destination=calloc(1,sizeof(char*));

	int fd=open("error.txt",O_WRONLY|O_CREAT|O_APPEND,0777);
	char cPath[255];
	getcwd(cPath,255);

    while (thisMenu != MENU_EXIT){
        switch (thisMenu) {
            case MENU_MAIN :
                thisMenu = IP_insert_Page(&ipAddress);
                break;
            case MENU_FIRSTWINODW :
				chdir(clientPath);
				myListOpen();
				mvprintw(1,1,cPath);
				chdir(cPath);
 				free(myDirectories);
 				free(myFiles);
				parsing("myList.txt",&myDirectories,&myFiles);//myListOpen
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, myDirectories->array, selected, myDirectories->next, clientPath, serverPath,&resInfo,&msg);
				break;
            case MENU_SECONDWINDOW :
				listDownload(resInfo.sock,resInfo.ip);
				free(directories);
				free(files);
				parsing("list.txt",&directories,&files);//myListOpen
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, directories->array, selected, directories->next, clientPath, serverPath,&resInfo,&msg);
				break;
            case MENU_THIRDWINDOW :
				chdir(clientPath);
				myListOpen();
				chdir(cPath);
				free(myDirectories);
				free(myFiles);
				parsing("myList.txt",&myDirectories,&myFiles);//myListOpen
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, myFiles->array, selected, myFiles->next, clientPath, serverPath,&resInfo,&msg);
				break;
            case MENU_FOURTHWINDOW :
				listDownload(resInfo.sock,resInfo.ip);
				free(directories);
				free(files);
				parsing("list.txt",&directories,&files);//myListOpen
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, files->array, selected, files->next, clientPath, serverPath,&resInfo,&msg);
                break;
            case MENU_IP_INSERT :
				clientStart(ipAddress,&sock);
				myIp=getMyIp();
				mvprintw(0,0,"myIP:%s",myIp);
				resInfo.ip=myIp;
				resInfo.sock=sock;
            case MENU_FTP_PAGE:
				free(myDirectories);
				free(myFiles);
				free(directories);
				free(files);
				chdir(clientPath);
				myListOpen();
				chdir(cPath);
				parsing("myList.txt",&myDirectories,&myFiles);//myListOpen
				//printf server side list
				listDownload(resInfo.sock,resInfo.ip);
				parsing("list.txt",&directories,&files);//myListOpen
                thisMenu = FTP_Main_Page(MODE_CLIENT, clientPath, serverPath,&resInfo,&msg,myDirectories,myFiles,directories,files);
                break;
            case MENU_IP_MANAGE:
                //
                break;
            case MENU_HELP:
               thisMenu = Help_Page();
                break;
            case MAIN_HELP:
               thisMenu = Help_Page();
                break;
            case MENU_HISTORY:
                //
                break;
			case MENU_INTO_DIR:
				index=selected[0];
				*destination=myDirectories->array[index];
				chdir(*destination);
				memset(clientPath,0,strlen(clientPath));
				strcpy(clientPath,*destination);
				free(myDirectories);
				free(myFiles);
				parsing("myList.txt",&myDirectories,&myFiles);
				print_Sub_Block(MODE_CLIENT,myFiles->array,myFiles->next);
				thisMenu=MENU_THIRDWINDOW;
				break;
			//case MENU_OUT_DIR:
        }
    }

    //to do when exit
	free(myDirectories);
	free(myFiles);
	free(directories);
	free(files);
    close(sock);
    endwin();
    return 0;
}

