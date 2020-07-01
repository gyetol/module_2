//
// Created by linux on 6/30/20.
//

#include "clientNcurses.h"
//
// Created by linux on 6/30/20.
//

#include "serverNcurses.h"
#include "commonNucurses.h"

int main(){
    init_scr();
    char * ipAddress = "";
    int thisMenu = MENU_MAIN;

    while (thisMenu != MENU_EXIT){
        switch (thisMenu) {
            case MENU_MAIN :
                thisMenu = IP_insert_Page(&ipAddress);
                break;
            case MENU_BOOKMARKS :
//                thisMenu = _loginMenu();
                break;
            case MENU_HISTORY :
//                thisMenu = _signioMenu();
                break;
            case MENU_IP :
                thisMenu = FTP_Main_Page(MODE_CLIENT, NULL, NULL);
                break;
        }
    }
    endwin();
    return 0;
}