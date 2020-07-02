//
// Created by linux on 6/30/20.
//
#include <unistd.h>
#include "clientNcurses.h"
#include "serverNcurses.h"
#include "commonNucurses.h"
#include "../socket_con/ftp_client.h"
int main(){
    init_scr();
    int sock;
    char * ipAddress = "";
    int thisMenu = MENU_MAIN;
    int selectedMenu  = MENU_FIRSTWINODW;

    while (thisMenu != MENU_EXIT){
        switch (thisMenu) {
            case MENU_MAIN :
                thisMenu = IP_insert_Page(&ipAddress);
                int ret = clientStart(ipAddress, sock);
                if (ret != 0){
                    //to do when exit
                    close(sock);
                    endwin();
                    return 0;
                }
                break;
            case MENU_BOOKMARKS :
//                thisMenu = _loginMenu();
                break;
            case MENU_HISTORY :
//                thisMenu = _signioMenu();
                break;
            case MENU_IP :
                thisMenu = FTP_Main_Page(MODE_CLIENT, "CLIENT PATH", "SERVER PATH");

                break;
        }
    }

    //to do when exit
    close(sock);
    endwin();
    return 0;
}