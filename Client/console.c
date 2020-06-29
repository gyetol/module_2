//
// Created by linux on 6/28/20.
//

#include "console.h"
#include <ncurses.h>
#include <string.h>
#define KEYBOARD_UP 65
#define KEYBOARD_DOWN 66
#define KEYBOARD_LEFT 68
#define KEYBOARD_RIGHT 67
#define KEYBOARD_ENTER 13
#define KEYBOARD_BACKSPACE 127

#define MENU_MAIN 0
#define MENU_CONNECT 1
#define MENU_HISTORY 2
#define MENU_EXIT 3
#define MENU_SIGNIN 4
#define MENU_SIGNOUT 5
#define MENU_PLAY 6
#define MENU_INGAME 7
#define MENU_STATISTICS 8
#define MENU_2PLOGIN 9
#define MENU_2PMAIN 10

#define MENU_GAMESTART 21
#define MENU_NEXTTURN 22
#define MENU_PLAYER1 23
#define MENU_PLAYER2 24

#define MENU_IP 100

#define MENU_WIN 200
#define MENU_LOSE 201

#define IPADDRESSLENGTH 15

void init_scr()
{
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(2, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_MAGENTA);
}

void init_updownWindow(WINDOW *upWindow, WINDOW *middleWindow, WINDOW *downWindow)
{
    upWindow = subwin(stdscr, 14, 80, 0, 0);
    wbkgd(upWindow, COLOR_PAIR(1));

    middleWindow = subwin(stdscr, 7, 80, 14, 0);
    wbkgd(middleWindow, COLOR_PAIR(2));

    downWindow = subwin(stdscr, 3, 80, 21, 0);
    wbkgd(downWindow, COLOR_PAIR(3));
    attron(COLOR_PAIR(1));
}

/////////////////////////////////////////////////////////////
/// to show main menu
/// input1 : ip Address space to store
/// return : menunum
////////////////////////////////////////////////////////////
int mainMenu(char**ip){
    werase(stdscr); // Clear Window
    curs_set(0); // Not need Cursor pointer
    char key; // User Input
    char ipAddress[IPADDRESSLENGTH] = "";

    int selectingMenu = MENU_CONNECT;

    WINDOW *upMenu, *middleWindow,*downMenu;
    init_updownWindow(upMenu, middleWindow, downMenu);

    mvprintw(3, 34, "FILE DANZI");
    mvprintw(7, 32, "cute FTP Cleint");

    attron(COLOR_PAIR(2));
    mvprintw(16, 27, "INSERT SERVER'S IP ADDRESS");
    mvprintw(18, 36, " : ");

    while(1){
        attron(COLOR_PAIR(2));
        mvprintw(18, 26, "IP ADDRESS");
        mvprintw(18, 39, "               ");
        mvprintw(18, 39, ipAddress);

        attron(COLOR_PAIR(1));
        mvprintw(22, 15, "CONNECT IP");
        mvprintw(22, 36, "HISTORY");
        mvprintw(22, 58, "EXIT");

        attron(A_STANDOUT | A_UNDERLINE); // selected effect

        // Overwriting menu font
        switch(selectingMenu){
            case MENU_CONNECT :
                mvprintw(22, 15, "CONNECT IP");
                break;
            case MENU_HISTORY :
                mvprintw(22, 36, "HISTORY");
                break;
            case MENU_EXIT :
                mvprintw(22, 58, "EXIT");
                break;
        }

        attroff(A_STANDOUT | A_UNDERLINE);

        refresh();

        key = getchar();

        switch(key) {
            case KEYBOARD_UP:
                if (selectingMenu == MENU_CONNECT || selectingMenu == MENU_EXIT || selectingMenu == MENU_HISTORY) {
                    selectingMenu = MENU_IP;
                }
                break;
            case KEYBOARD_DOWN:
                if (selectingMenu == MENU_IP) {
                    selectingMenu = MENU_CONNECT;
                }
                break;
            case KEYBOARD_RIGHT :
                if (selectingMenu == MENU_CONNECT)
                    selectingMenu = MENU_HISTORY;
                else if (selectingMenu == MENU_HISTORY)
                    selectingMenu = MENU_EXIT;
                else if (selectingMenu == MENU_EXIT)
                    selectingMenu = MENU_CONNECT;
                break;
            case KEYBOARD_LEFT :
                if (selectingMenu == MENU_HISTORY)
                    selectingMenu = MENU_CONNECT;
                else if (selectingMenu == MENU_EXIT)
                    selectingMenu = MENU_HISTORY;
                else if (selectingMenu == MENU_CONNECT)
                    selectingMenu = MENU_EXIT;
                break;
            case KEYBOARD_BACKSPACE:
                if (selectingMenu == MENU_IP) {
                    ipAddress[strlen(ipAddress) - 1] = '\0';
                }
                break;
            case KEYBOARD_ENTER :
                if (selectingMenu == MENU_IP){
                    *ip=ipAddress;
                    delwin(upMenu);
                    delwin(middleWindow);
                    delwin(downMenu);
                    return selectingMenu;
                }
                else{
                    *ip=ipAddress;
                    delwin(upMenu);
                    delwin(middleWindow);
                    delwin(downMenu);
                    return selectingMenu;
                }
            default:
                if ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z') || (key == '.') ) {
                    char tempKey[2];
                    tempKey[0] = key;
                    tempKey[1] = '\0';
                    if ((selectingMenu == MENU_IP) && (strlen(ipAddress) < IPADDRESSLENGTH)) {
                        strcat(ipAddress, tempKey);
                    }
                }
                break;
        }
    }
}

int main(){
    init_scr();
    char * str = "";
    int rest = mainMenu(&str);
    if (rest = MENU_IP){

    }

    //
    endwin();
    printf("%s", str);
    return 0;
}