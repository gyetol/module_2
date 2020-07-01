//
// Created by moosong on 6/30/20.
//
#include <ncurses.h>
#include <string.h>
#include "commonNucurses.h"

///////////////////////SAMPLE FILES/////////////////////////////////////////
char * sampleFile[] = {
        "this is file 1", "this is file 2", "this is file 3", "this is file 4",
        "this is file 5", "this is file 6", "this is file 7", "this is file 8",
        "this is file 9", "this is file 10", "this is file 11", "this is file 12",
        "this is file 13", "this is file 14", "this is file 15", "this is file 16"
};
///////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
/// to make env for ncurses and color pairs
/// input : void
/// return : void
////////////////////////////////////////////////////////////
void init_scr()
{
    initscr();
    start_color();

    ///first:index
    ///second:text
    ///color:background
    init_pair(MAIN1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(MAIN2, COLOR_BLACK, COLOR_WHITE);
    init_pair(CLIENTBAR, COLOR_BLACK, COLOR_YELLOW);
    ///insert color pairs you want
}

/////////////////////////////////////////////////////////////
/// to prepare up and down window (for ip insert connection)
/// inputs : upwindow, middlewindow, downWindow
/// return : void
////////////////////////////////////////////////////////////
void init_IP_insert_Page(WINDOW *upWindow, WINDOW *middleWindow, WINDOW *downWindow)
{
    upWindow = subwin(stdscr, 14, FTP_WIDE, 0, 0);
    wbkgd(upWindow, COLOR_PAIR(MAIN1));

    middleWindow = subwin(stdscr, 7, FTP_WIDE, 14, 0);
    wbkgd(middleWindow, COLOR_PAIR(MAIN2));

    downWindow = subwin(stdscr, 3, FTP_WIDE, 21, 0);
    wbkgd(downWindow, COLOR_PAIR(MAIN1));
}

/////////////////////////////////////////////////////////////
/// to show main menu
/// input1 : ip Address space to store
/// return : menunum
////////////////////////////////////////////////////////////
int show_IP_insert_Page(char**ip){
    werase(stdscr); // Clear Window
    curs_set(0); // Not need Cursor pointer
    char key; // User Input
    char ipAddress[IPADDRESSLENGTH] = "";

    int selectingMenu = MENU_BOOKMARKS;

    WINDOW *upMenu, *middleWindow,*downMenu;
    init_IP_insert_Page(upMenu, middleWindow, downMenu);

    attron(COLOR_PAIR(MAIN1));
    mvprintw(3, 34, "FILE DANZI");
    mvprintw(7, 32, "cute FTP Cleint");

    attron(COLOR_PAIR(MAIN2));
    mvprintw(16, 16, "INSERT SERVER'S IP ADDRESS (press enter key)");
    mvprintw(18, 36, " : ");

    while(1){
        attron(COLOR_PAIR(MAIN2));
        mvprintw(18, 26, "IP ADDRESS");
        mvprintw(18, 39, "               ");
        mvprintw(18, 39, ipAddress);
        if (selectingMenu == MENU_IP){
            attron(A_STANDOUT | A_UNDERLINE);
            mvprintw(18, 39+strlen(ipAddress), " ");
            attroff(A_STANDOUT | A_UNDERLINE);
        }

        attron(COLOR_PAIR(MAIN1));
        mvprintw(22, 15, "BOOK MARKS");
        mvprintw(22, 36, "HISTORY");
        mvprintw(22, 58, "EXIT");

        attron(A_STANDOUT | A_UNDERLINE); // selected effect
        switch(selectingMenu){
            case MENU_BOOKMARKS :
                mvprintw(22, 15, "BOOK MARKS");
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
                if (selectingMenu == MENU_BOOKMARKS || selectingMenu == MENU_EXIT || selectingMenu == MENU_HISTORY) {
                    selectingMenu = MENU_IP;
                }
                break;
            case KEYBOARD_DOWN:
                if (selectingMenu == MENU_IP) {
                    selectingMenu = MENU_BOOKMARKS;
                }
                break;
            case KEYBOARD_RIGHT:
                if (selectingMenu == MENU_BOOKMARKS)
                    selectingMenu = MENU_HISTORY;
                else if (selectingMenu == MENU_HISTORY)
                    selectingMenu = MENU_EXIT;
                else if (selectingMenu == MENU_EXIT)
                    selectingMenu = MENU_BOOKMARKS;
                break;
            case KEYBOARD_LEFT :
                if (selectingMenu == MENU_HISTORY)
                    selectingMenu = MENU_BOOKMARKS;
                else if (selectingMenu == MENU_EXIT)
                    selectingMenu = MENU_HISTORY;
                else if (selectingMenu == MENU_BOOKMARKS)
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
                } else if (selectingMenu == MENU_EXIT){
                    *ip=NULL;
                    delwin(upMenu);
                    delwin(middleWindow);
                    delwin(downMenu);
                    return selectingMenu;
                } else if (selectingMenu == MENU_HISTORY){
                    *ip=ipAddress;
                    delwin(upMenu);
                    delwin(middleWindow);
                    delwin(downMenu);
                    return selectingMenu;
                } else if (selectingMenu == MENU_BOOKMARKS){
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

/////////////////////////////////////////////////////////////
/// to prepare FTP main window
/// input : all windows to make FTP main
/// return : void
////////////////////////////////////////////////////////////
void init_FTP_Main_Page(WINDOW*upWindow, WINDOW * downWindow,
                       WINDOW * logWindow, WINDOW * pathWindow, WINDOW * firstWindow,
                       WINDOW * secondWindow, WINDOW * thirdWindow, WINDOW * fourthWindow,
                       WINDOW * xWindow, WINDOW * yWindow, WINDOW * zWindow){

    upWindow = subwin(stdscr, MANUAL_SUBWINDOW_HEIGHT, FTP_WIDE, 0 , 0);
    wbkgd(upWindow, COLOR_PAIR(CLIENTBAR));

    logWindow = subwin(stdscr, LOG_SUBWINDOW_HEIGHT, FTP_WIDE, MANUAL_SUBWINDOW_HEIGHT, 0);
    wbkgd(logWindow, COLOR_PAIR(MAIN2));

    pathWindow = subwin(stdscr, BAR_HEIGHT, FTP_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, 0);
    wbkgd(pathWindow, COLOR_PAIR(CLIENTBAR));

    firstWindow = subwin(stdscr, UPPER_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT, 0);
    wbkgd(firstWindow, COLOR_PAIR(MAIN2));

    xWindow = subwin(stdscr, UPPER_SUBWINDOW_HEIGHT, BAR_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT, LEFT_SUBWINDOW_WIDE);
    wbkgd(xWindow, COLOR_PAIR(CLIENTBAR));

    secondWindow = subwin(stdscr, UPPER_SUBWINDOW_HEIGHT, RIGHT_SUBWINDOW_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT, LEFT_SUBWINDOW_WIDE + BAR_WIDE);
    wbkgd(secondWindow, COLOR_PAIR(MAIN2));

    yWindow = subwin(stdscr, BAR_HEIGHT, FTP_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT, 0);
    wbkgd(yWindow, COLOR_PAIR(CLIENTBAR));

    thirdWindow = subwin(stdscr, DOWN_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT, 0);
    wbkgd(thirdWindow, COLOR_PAIR(MAIN2));

    zWindow = subwin(stdscr, DOWN_SUBWINDOW_HEIGHT, BAR_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT, LEFT_SUBWINDOW_WIDE);
    wbkgd(zWindow, COLOR_PAIR(CLIENTBAR));

    fourthWindow = subwin(stdscr, DOWN_SUBWINDOW_HEIGHT, RIGHT_SUBWINDOW_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT, LEFT_SUBWINDOW_WIDE + BAR_WIDE);
    wbkgd(fourthWindow, COLOR_PAIR(MAIN2));

    downWindow = subwin(stdscr, BAR_HEIGHT, FTP_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT + DOWN_SUBWINDOW_HEIGHT, 0);
    wbkgd(downWindow, COLOR_PAIR(CLIENTBAR));
}

/////////////////////////////////////////////////////////////
/// to show up and down manual bars
/// input : mode (MODE_CLIENT or MODE_SERVER)
/// return : void
////////////////////////////////////////////////////////////
void show_Manual_Bar(int mode){
    ///print
    char * str;
    if (mode == MODE_CLIENT){
        str = "DownloadFile";
    }else if (mode == MODE_SERVER){
        str = " UploadFile";
    }
    mvprintw(0, 2, "CopyFile");
    mvprintw(0, 14, "MoveFile");
    mvprintw(0, 26, "RemoveFile");
    mvprintw(0, 40, "reNameFile");
    mvprintw(0, 54, str);
    mvprintw(0, 70, "IPManage");

    int temp = FTP_HEIGHT-1;
//    mvprintw(temp, 2, "NewDir");
    mvprintw(temp, 12, "MoVeDir");
    mvprintw(temp, 23, "RemovEDir");
    mvprintw(temp, 36, "RenameDir");
    mvprintw(temp, 49, "Help");
    mvprintw(temp, 57, "MakeFolder");
    mvprintw(temp, 71, "EXit");

    ///underline
    attron(A_UNDERLINE);
    mvprintw(0, 2, "C");
    mvprintw(0, 14, "M");
    mvprintw(0, 26, "R");
    mvprintw(0, 42, "N");
    if (mode == MODE_CLIENT){
        mvprintw(0, 62, "F");
    } else if (mode == MODE_SERVER){
        mvprintw(0, 60, "F");
    }
    mvprintw(0, 71, "P");

//    mvprintw(23, 2, "D");
    mvprintw(temp, 14, "V");
    mvprintw(temp, 28, "E");
    mvprintw(temp, 39, "A");
    mvprintw(temp, 49, "H");
    mvprintw(temp, 59, "K");
    mvprintw(temp, 72, "X");

    attroff(A_UNDERLINE);
}

/////////////////////////////////////////////////////////////
/// to print Main Page
/// input : mode MODE_CLIENT or MODE_SERVER
/// return : void
////////////////////////////////////////////////////////////
int FTP_Main_Page(int mode, char * pathOfLeft, char *pathOfRight) {
    werase(stdscr); // Clear Window
    curs_set(0); // Not need Cursor pointer
    char key; // User Input
    int selectingMenu = MENU_FIRSTWINODW;
    int selectedIndex[10];
    int indexOfTab = 0;
    ///
    pathOfLeft = "CLIENT PATH";
    pathOfRight = "SERVER PATH";
    ///
    WINDOW *upMenu;
    WINDOW *downMenu;
    WINDOW *logWindow;
    WINDOW *pathWindow;
    WINDOW *firstWindow;
    WINDOW *secondWindow;
    WINDOW *thirdWindow;
    WINDOW *fourthWindow;
    WINDOW *xWindow;
    WINDOW *yWindow;
    WINDOW *zWindow;

    init_FTP_Main_Page(upMenu, downMenu, logWindow, pathWindow, firstWindow,
                      secondWindow, thirdWindow, fourthWindow,
                      xWindow, yWindow, zWindow);

    attron(COLOR_PAIR(CLIENTBAR));
    show_Manual_Bar(mode);

    while (1) {
        attron(COLOR_PAIR(MAIN1));
        mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, 0, "                                        ");
        mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, 41, "                                       ");
        mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, 2, "LOCAL FILE TREE");
        if (mode == MODE_CLIENT){
            mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, 43, "SERVER FILE TREE");
        } else if (mode == MODE_SERVER){
            mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, 43, "REMOTE FILE TREE");
        }
        mvprintw(13, 0, "                                        ");
        mvprintw(13, 0, pathOfLeft);
        mvprintw(13, 41, "                                       ");
        mvprintw(13, 41, pathOfRight);

        attron(COLOR_PAIR(MAIN2));
        printFiles(0, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT, NULL, selectedIndex,
                   UPPER_SUBWINDOW_HEIGHT);
        printFiles(0, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT,
                   NULL, selectedIndex, DOWN_SUBWINDOW_HEIGHT);
        printFiles(LEFT_SUBWINDOW_WIDE + BAR_WIDE, MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT, NULL,
                   selectedIndex, UPPER_SUBWINDOW_HEIGHT);
        printFiles(LEFT_SUBWINDOW_WIDE + BAR_WIDE,
                   MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT,
                   NULL, selectedIndex, DOWN_SUBWINDOW_HEIGHT);


        attron(A_STANDOUT | A_UNDERLINE); // selected effect
        switch (selectingMenu) {
            case MENU_FIRSTWINODW:
                mvprintw(4, 0, "LOCAL FILE TREE (press enter)           ");
                break;
            case MENU_SECONDWINDOW:
                mvprintw(4, 41, "SERVER FILE TREE (press enter)         ");
                break;
            case MENU_THIRDWINDOW:
                mvprintw(13, 0, "                                        ");
                mvprintw(13, strlen(pathOfLeft), " (press enter)");
                mvprintw(13, 0, pathOfLeft);
                break;
            case MENU_FOURTHWINDOW:
                mvprintw(13, 41, "                                       ");
                mvprintw(13, 41+strlen(pathOfRight), " (press enter)");
                mvprintw(13, 41, pathOfRight);
                break;
        }
        attroff(A_STANDOUT | A_UNDERLINE);

        attron(COLOR_PAIR(MAIN1));
        refresh();

        key = getchar();

        switch (key) {
            case KEYBOARD_TAB:
                if (selectingMenu == MENU_FIRSTWINODW) {
                    selectingMenu = MENU_SECONDWINDOW;
                } else if (selectingMenu == MENU_SECONDWINDOW) {
                    selectingMenu = MENU_THIRDWINDOW;
                } else if (selectingMenu == MENU_THIRDWINDOW) {
                    selectingMenu = MENU_FOURTHWINDOW;
                } else if (selectingMenu == MENU_FOURTHWINDOW) {
                    selectingMenu = MENU_FIRSTWINODW;
                }
                break;
            case KEYBOARD_UP:
                if (selectingMenu == MENU_FIRSTWINODW) {
                    selectingMenu = MENU_SECONDWINDOW;
                } else if (selectingMenu == MENU_SECONDWINDOW) {
                    selectingMenu = MENU_THIRDWINDOW;
                } else if (selectingMenu == MENU_THIRDWINDOW) {
                    selectingMenu = MENU_FOURTHWINDOW;
                } else if (selectingMenu == MENU_FOURTHWINDOW) {
                    selectingMenu = MENU_FIRSTWINODW;
                }
                break;
            case KEYBOARD_DOWN:
                if (selectingMenu == MENU_FIRSTWINODW) {
                    selectingMenu = MENU_SECONDWINDOW;
                } else if (selectingMenu == MENU_SECONDWINDOW) {
                    selectingMenu = MENU_THIRDWINDOW;
                } else if (selectingMenu == MENU_THIRDWINDOW) {
                    selectingMenu = MENU_FOURTHWINDOW;
                } else if (selectingMenu == MENU_FOURTHWINDOW) {
                    selectingMenu = MENU_FIRSTWINODW;
                }
                break;
            case KEYBOARD_LEFT:
                if (selectingMenu == MENU_FIRSTWINODW) {
                    selectingMenu = MENU_SECONDWINDOW;
                } else if (selectingMenu == MENU_SECONDWINDOW) {
                    selectingMenu = MENU_THIRDWINDOW;
                } else if (selectingMenu == MENU_THIRDWINDOW) {
                    selectingMenu = MENU_FOURTHWINDOW;
                } else if (selectingMenu == MENU_FOURTHWINDOW) {
                    selectingMenu = MENU_FIRSTWINODW;
                }
                break;
            case KEYBOARD_RIGHT:
                if (selectingMenu == MENU_FIRSTWINODW) {
                    selectingMenu = MENU_SECONDWINDOW;
                } else if (selectingMenu == MENU_SECONDWINDOW) {
                    selectingMenu = MENU_THIRDWINDOW;
                } else if (selectingMenu == MENU_THIRDWINDOW) {
                    selectingMenu = MENU_FOURTHWINDOW;
                } else if (selectingMenu == MENU_FOURTHWINDOW) {
                    selectingMenu = MENU_FIRSTWINODW;
                }
                break;
            case KEYBOARD_ENTER:
                if (selectingMenu == MENU_FIRSTWINODW) {
                    selectingMenu = MENU_SECONDWINDOW;
                } else if (selectingMenu == MENU_SECONDWINDOW) {
                    selectingMenu = MENU_THIRDWINDOW;
                } else if (selectingMenu == MENU_THIRDWINDOW) {
                    selectingMenu = MENU_FOURTHWINDOW;
                } else if (selectingMenu == MENU_FOURTHWINDOW) {
                    selectingMenu = MENU_FIRSTWINODW;
                }
                break;
            case KEYBOARD_SPACEBAR:
                break;
            case KEYBOARD_BACKSPACE:
                break;
//            case COPY_FILE_KEY1:
            case COPY_FILE_KEY2:
                break;
            case MOVE_FILE_KEY1:
            case MOVE_FILE_KEY2:
                break;
            case REMOVE_FILE_KEY1:
            case REMOVE_FILE_KEY2:
                break;
            case RENAME_FILE_KEY1:
            case RENAME_FILE_KEY2:
                break;
            case UP_AND_DOWN_FILE_KEY1:
            case UP_AND_DOWN_FILE_KEY2:
                break;
            case IP_MANAGE_KEY1:
            case IP_MANAGE_KEY2:
                break;
            case MOVE_DIR_KEY1:
            case MOVE_DIR_KEY2:
                break;
            case REMOVE_DIR_KEY1:
            case REMOVE_DIR_KEY2:
                break;
//            case RENAME_DIR_KEY1:
            case RENAME_DIR_KEY2:
                break;
            case HELP_KEY1:
            case HELP_KEY2:
                break;
            case MAKE_DIR_KEY1:
            case MAKE_DIR_KEY2:
                break;
            case EXIT_KEY1:
            case EXIT_KEY2:
                delwin(upMenu);
                delwin(middleWindow);
                delwin(downMenu);
                delwin(logWindow);
                delwin(pathWindow);
                delwin(firstWindow);
                delwin(secondWindow);
                delwin(thirdWindow);
                delwin(fourthWindow);
                delwin(xWindow);
                delwin(yWindow);
                delwin(zWindow);
                return MENU_EXIT;
        }
    }
}