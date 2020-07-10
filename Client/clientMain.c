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
        "192.168.30.22에 접속 요청...", "192.168.30.22과 접속 성공...", "192.168.30.22과 연결완료..."
};

char *getMyIp(){
	char * myIp;//내 ip저장할 변수
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


	Array* myDirectories=NULL;//로컬 디렉토리 정보
	Array* myFiles=NULL;//로컬 세부정보
	Array* directories=NULL;//서버 디렉토리 정보
	Array* files=NULL;//서버 세부 정보

	char clientPath[512]="/home/linux/module2";//로컬 세부정보가 보여주는 디렉토리 경로
	char serverPath[512]="/home";//서버 세부정보가 보여주는 디렉토리 경로
	char * msg={0,};//오류 메세지 저장하는 out-parameter

	ResInfo resInfo={0,};//sock,ip정보 저장하는 정보 관리 구조체

	int index;//현재 선택된 친구의 index저장하는 변수
	char** destination=NULL;//

	char pBuf[512];//현재 위치하는 경로
	char originPath[512]={0,};//현재 위치하는 경로
	getcwd(originPath,sizeof(originPath));//현재 경로 뽑아내는 함수

    while (thisMenu != MENU_EXIT){
        switch (thisMenu) {
            case MENU_MAIN :
                thisMenu = IP_insert_Page(&ipAddress);
                break;
            case MENU_FIRSTWINODW :
				chdir(clientPath);
				myListOpen();
// 				mvprintw(1,1,pBuf);
				chdir(originPath);
 				free(myDirectories);
 				free(myFiles);
				parsing("myList.txt",&myDirectories,&myFiles);//myListOpen
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, myDirectories->array, &selected, myDirectories->next, clientPath, serverPath,&resInfo,&msg);
				break;
            case MENU_SECONDWINDOW :
				listDownload(resInfo.sock,resInfo.ip);
				free(directories);
				free(files);
				parsing("list.txt",&directories,&files);//myListOpen
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, directories->array, &selected, directories->next, clientPath, serverPath,&resInfo,&msg);
				break;
            case MENU_THIRDWINDOW :
				chdir(clientPath);
				myListOpen();
				chdir(originPath);
				free(myDirectories);
				free(myFiles);
				parsing("myList.txt",&myDirectories,&myFiles);//myListOpen
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, myFiles->array, &selected, myFiles->next, clientPath, serverPath,&resInfo,&msg);
				break;
            case MENU_FOURTHWINDOW :
				listDownload(resInfo.sock,resInfo.ip);
				free(directories);
				free(files);
				parsing("list.txt",&directories,&files);//myListOpen
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, files->array, &selected, files->next, clientPath, serverPath,&resInfo,&msg);
                break;
            case MENU_IP_INSERT :
				clientStart(ipAddress,&sock);
				myIp=getMyIp();
				//mvprintw(0,0,"myIP:%s",myIp);
				resInfo.ip=myIp;
				resInfo.sock=sock;
            case MENU_FTP_PAGE:
				free(myDirectories);
				free(myFiles);
				free(directories);
				free(files);
				chdir(clientPath);
				myListOpen();
				chdir(originPath);
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
			case MENU_INTO_MYDIR:
				index=selected[0];
				destination=&(myDirectories->array[index]);
				if(strcmp(*destination,"..")==0){
					chdir("..");
					getcwd(pBuf,sizeof(pBuf));
					chdir(originPath);
					memset(clientPath,0,strlen(clientPath));
					strncpy(clientPath,pBuf,strlen(pBuf)+1);
				}
				else if(strcmp(*destination,".")==0){
					;
				}
				else{
					strcat(clientPath,*destination);
				}
				/*
				if(strcmp(*destination,".")==0){
					memset(clientPath,0,strlen(clientPath));
					strcpy(clientPath,pBuf);
				}
				else if(strcmp(*destination,"..")==0){
					chdir("..");
					getcwd(pBuf,sizeof(pBuf));
					chdir(clientPath);
					memset(clientPath,0,strlen(clientPath));
					strcpy(clientPath,pBuf);
				}
				else{
					strcat(clientPath,"/");
					strcat(clientPath,*destination);
				}
				*/
// 				mvprintw(2,60,"cp=%s",clientPath);
// 				refresh();
// 				getchar();
				chdir(clientPath);
				strcpy(clientPath,*destination);
// 				mvprintw(3,60,"cp=%s strcpy성공",clientPath);
// 				refresh();
// 				getchar();

				   chdir(clientPath);
				   myListOpen();
				   chdir(originPath);

 				free(myDirectories);
				free(myFiles);
				parsing("myList.txt",&myDirectories,&myFiles);
				print_Sub_Block(MODE_CLIENT,myFiles->array,myFiles->next);
				thisMenu=MENU_THIRDWINDOW;
				break;
			case MENU_INTO_SERVDIR:
				/*
				index=selected[0];
				destination=&(directories->array[index]);
				if(strcmp(*destination,".")==0){
					memset(clientPath,0,strlen(clientPath));
					strcpy(clientPath,pBuf);
				}
				else if(strcmp(*destination,"..")==0){
					chdir("..");
					getcwd(pBuf,sizeof(pBuf));
					chdir(clientPath);
					memset(clientPath,0,strlen(clientPath));
					strcpy(clientPath,pBuf);
				}
				else{
					strcat(clientPath,"/");
					strcat(clientPath,*destination);
				}
 				mvprintw(2,60,"cp=%s",clientPath);
 				refresh();
 				getchar();
				chdir(clientPath);
				strcpy(clientPath,*destination);
 				mvprintw(3,60,"cp=%s strcpy성공",clientPath);
 				refresh();
 				getchar();
 				free(directories);
				free(files);
				parsing("list.txt",&directories,&files);
				print_Sub_Block(MODE_CLIENT,files->array,files->next);
				*/
				thisMenu=MENU_FOURTHWINDOW;
				break;

			case MENU_OUT_MYDIR:
<<<<<<< HEAD
				//mvprintw(2,1,"LEFT INSERT");
				//refresh();
				//getchar();
				thisMenu=MENU_FTP_PAGE;
=======
// 				mvprintw(2,1,"LEFT INSERT");
// 				refresh();
// 				getchar();
				thisMenu=MENU_EXIT;
>>>>>>> develop
				break;
        }
    }

	free(selected);
	//mvprintw(1,1,"%s","exit");
    //to do when exit
	free(myDirectories);
	free(myFiles);
	free(directories);
	free(files);
    close(sock);
    endwin();
    return 0;
}

