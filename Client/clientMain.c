//
// Created by linux on 6/30/20.
//
#include <unistd.h>
         #include <sys/types.h>
#include <ifaddrs.h>                                                                          
#include "commonNcurses.h"
#include "clientStart.h"

char * sampleFiles[] = {
        "this is file 1", "this is file 2", "this is file 3", "this is file 4",
        "this is file 5", "this is file 6", "this is file 7", "this is file 8",
        "this is file 9", "this is file 10", "this is file 11", "this is file 12",
        "this is file 13", "this is file 14", "this is file 15", "this is file 16"
};

void help(){
	 printf("\n
         Usage : PUT IP ADDRESS WHERE YOU WANT TO CONNECT + ENTER KEY\n

         If you want to move the cursor then use Arrow key and push the Enter key then
         it will be selected. \n

         HISTORY : 'History' page shows the record history where you logged in before
         EXIT : Terminate the FTP service

         1. Copyfile : Select the file or files what you want and
                       press the 'c' key

         2. Movefile : Select the file or files what you wnat and
                       press the 'm' key


                       \n");
}

typedef struct ResInfo{
	int sock;
	char * ip;
}ResInfo;

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
    char * ipAddress = "";
    int thisMenu = MENU_MAIN;
    int * selected =NULL;
	char * myIp;

	char *myDirectories[DIRECTORY_SIZE];
 	int mydNext=0;
	char *myFiles[FILE_SIZE];
	int myfNext=0;

	char *directories[DIRECTORY_SIZE];
 	int dNext=0;
	char *files[FILE_SIZE];
	int fNext=0;


	
	ResInfo resInfo={0,};

    while (thisMenu != MENU_EXIT){
        switch (thisMenu) {
            case MENU_MAIN :
                thisMenu = IP_insert_Page(&ipAddress);

                break;
            case MENU_FIRSTWINODW :
            case MENU_SECONDWINDOW :
            case MENU_THIRDWINDOW :
            case MENU_FOURTHWINDOW :
				myListOpen();
				//list.txt파싱하는 함수 
				parsing(myDirectories,myFiles,&mydNext,&myfNext);

				listOpen();
				//list.txt파싱하는 함수
				parsing(directories,files,&dNext,&fNext);
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, sampleFiles, selected, 16, "CLIENT PATH", "SERVER PATH");
                break;
            case MENU_IP_INSERT :
				clientStart(ipAddress,&sock);
				myIp=getMyIp();
				mvprintw(0,0,"myIP:%s",myIp);
				resInfo.ip=myIp;

            case MENU_FTP_PAGE:
				myListOpen();
				//list.txt파싱하는 함수 
				parsing(myDirectories,myFiles,&mydNext,&myfNext);

				listOpen();
				//list.txt파싱하는 함수
				parsing(directories,files,&dNext,&fNext);

                thisMenu = FTP_Main_Page(MODE_CLIENT, "CLIENT PATH", "SERVER PATH");
                break;
            case MENU_IP_MANAGE:
                //
                break;
            case MENU_HELP:
                //
                break;
            case MENU_BOOKMARKS:
                //
                break;
            case MENU_HISTORY:
                //
                break;
        }
    }

    //to do when exit
    close(sock);
    endwin();
    return 0;
}
