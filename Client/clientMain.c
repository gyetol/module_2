//
// Created by linux on 6/30/20.
//
#include <unistd.h>

#include "commonNcurses.h"
#include "clientStart.h"

char * sampleFiles[] = {
        "this is file 1", "this is file 2", "this is file 3", "this is file 4",
        "this is file 5", "this is file 6", "this is file 7", "this is file 8",
        "this is file 9", "this is file 10", "this is file 11", "this is file 12",
        "this is file 13", "this is file 14", "this is file 15", "this is file 16"
};

int main(){
    init_scr();
    int sock = 0;
    char * ipAddress = "";
    int thisMenu = MENU_MAIN;
    int * selected =NULL;

    while (thisMenu != MENU_EXIT){
        switch (thisMenu) {
            case MENU_MAIN :
                thisMenu = IP_insert_Page(&ipAddress);
                break;
            case MENU_FIRSTWINODW :
            case MENU_SECONDWINDOW :
            case MENU_THIRDWINDOW :
            case MENU_FOURTHWINDOW :
                thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, sampleFiles, selected, 16, "CLIENT PATH", "SERVER PATH");
                break;
            case MENU_IP_INSERT :
				ipAddress="192.168.30.2";
				clientStart(ipAddress,&sock);
            case MENU_FTP_PAGE:
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
