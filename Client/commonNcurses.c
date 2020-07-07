//
// Created by moosong on 6/30/20.
//
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "commonNcurses.h"


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
    init_pair(SELECTED, COLOR_BLACK, COLOR_YELLOW);
    init_pair(CHECKED, COLOR_BLACK, COLOR_GREEN);
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
int IP_insert_Page(char**ip){
    werase(stdscr); // Clear Window
    curs_set(0); // Not need Cursor pointer
    char key; // User Input
    char ipAddress[IPADDRESSLENGTH] = "";

    int selectingMenu = MENU_BOOKMARKS;

    WINDOW *upMenu = NULL;
    WINDOW *middleWindow = NULL;
    WINDOW *downMenu = NULL;
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
        if (selectingMenu == MENU_IP_INSERT){
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
                    selectingMenu = MENU_IP_INSERT;
                }
                break;
            case KEYBOARD_DOWN:
                if (selectingMenu == MENU_IP_INSERT) {
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
                if (selectingMenu == MENU_IP_INSERT) {
                    ipAddress[strlen(ipAddress) - 1] = '\0';
                }
                break;
            case KEYBOARD_ENTER :
                if (selectingMenu == MENU_IP_INSERT){
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
                //if ((selectingMenu == MENU_IP_INSERT) && ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z') || (key == '.') )) {
                if ((selectingMenu == MENU_IP_INSERT) && ((key >= '0' && key <= '9') || (key == '.') )) {
                    char tempKey[2];
                    tempKey[0] = key;
                    tempKey[1] = '\0';
                    if ((selectingMenu == MENU_IP_INSERT) && (strlen(ipAddress) < IPADDRESSLENGTH)) {
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
/// to destory_FTP_Main_Page
/// input1 : all windows for Main
/// return : void
////////////////////////////////////////////////////////////
void destroy_FTP_Main_Page(WINDOW*upWindow, WINDOW * downWindow,
                        WINDOW * logWindow, WINDOW * pathWindow, WINDOW * firstWindow,
                        WINDOW * secondWindow, WINDOW * thirdWindow, WINDOW * fourthWindow,
                        WINDOW * xWindow, WINDOW * yWindow, WINDOW * zWindow){
    delwin(upWindow);
    delwin(downWindow);
    delwin(logWindow);
    delwin(pathWindow);
    delwin(firstWindow);
    delwin(secondWindow);
    delwin(thirdWindow);
    delwin(fourthWindow);
    delwin(xWindow);
    delwin(yWindow);
    delwin(zWindow);
}

/////////////////////////////////////////////////////////////
/// to show up and down manual bars
/// input : mode (MODE_CLIENT or MODE_SERVER)
/// return : void
////////////////////////////////////////////////////////////
void print_Manual_Bar(int mode){
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

    mvprintw(temp, 14, "V");
    mvprintw(temp, 28, "E");
    mvprintw(temp, 39, "A");
    mvprintw(temp, 49, "H");
    mvprintw(temp, 59, "K");
    mvprintw(temp, 72, "X");

    attroff(A_UNDERLINE);
}

/////////////////////////////////////////////////////////////
/// to print title
/// input : mode (MODE_CLIENT or MODE_SERVER)
/// return : void
////////////////////////////////////////////////////////////
void print_Title_Block(int mode){
    mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, 0, "                                        ");
    mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE+BAR_WIDE, "                                       ");
    mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, 0, "LOCAL FILE TREE");
    if (mode == MODE_CLIENT){
        mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE+BAR_WIDE, "SERVER FILE TREE");
    } else if (mode == MODE_SERVER){
        mvprintw(MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE+BAR_WIDE, "REMOTE FILE TREE");
    }
}

/////////////////////////////////////////////////////////////
/// to print subfiles for up and down window
/// input : mode (MODE_FIRST, MODE_SECOND, MODE_THIRD, MODE_FOURTH), src char* 's ary, a number array
/// return : void
////////////////////////////////////////////////////////////
void print_Sub_Block(int mode, char** srcArray, int aryCount){
    char * nullStr = "                                       ";
    int x;
    int y;
    int totalCount;
    switch (mode) {
        case MODE_FIRST:
            x=0;
            y=MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT;
            totalCount = UPPER_SUBWINDOW_HEIGHT;
            break;
        case MODE_SECOND:
            x=LEFT_SUBWINDOW_WIDE + BAR_WIDE;
            y=MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT;
            totalCount = UPPER_SUBWINDOW_HEIGHT;
            break;
        case MODE_THIRD:
            x=0;
            y=MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT;
            totalCount=DOWN_SUBWINDOW_HEIGHT;
            break;
        case MODE_FOURTH:
            x=LEFT_SUBWINDOW_WIDE + BAR_WIDE;
            y=MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT;
            totalCount = DOWN_SUBWINDOW_HEIGHT;
            break;
        default:
            return;
    }

    //this is reset loop
    for (int i = 0; i < totalCount; ++i) {
        mvprintw(y+i, x, nullStr);
    }
    if (srcArray == NULL){
        return;
    }

    if (aryCount < totalCount){
        totalCount = aryCount;
    }
    //this is print loop
    for (int j = 0; j < totalCount; ++j) {
        mvprintw(y+j, x, srcArray[j]);
    }
    return;
}

/////////////////////////////////////////////////////////////
/// to print Log Block
/// input : log ary and count
/// return : void
////////////////////////////////////////////////////////////
void print_Log_Block(char  ** srcArray, int aryCount){
    int x =0;
    int y = MANUAL_SUBWINDOW_HEIGHT;
    int totalCount = LOG_SUBWINDOW_HEIGHT;
    char * nullStr = "                                                                                ";

    //this is reset loop
    for (int i = 0; i < totalCount; ++i) {
        mvprintw(y+i, x, nullStr);
    }
    if (srcArray == NULL){
        return;
    }

    //this is print loop
    if (aryCount < totalCount){
        for (int i = 0; i < aryCount; ++i) {
            mvprintw(y+i, x, srcArray[i]);
        }
    }else{
        int i = 0;
        for (int j = aryCount - totalCount; j < aryCount; ++j) {
            mvprintw(y+i, x, srcArray[j]);
            i++;
        }
    }
    return;
}

/////////////////////////////////////////////////////////////
/// to print path
/// input : pathOfLeft, pathOfRight
/// return : void
////////////////////////////////////////////////////////////
void print_Path_Block(char * pathOfLeft, char *pathOfRight){
    mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, 0, "                                        ");
    mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, 0, pathOfLeft);
    mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE + BAR_WIDE, "                                       ");
    mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE + BAR_WIDE, pathOfRight);
}

/////////////////////////////////////////////////////////////
/// to print Main Page
/// input : mode MODE_CLIENT or MODE_SERVER, path1, path2
/// return : selectMenu
////////////////////////////////////////////////////////////
int FTP_Main_Page(int mode, char * pathOfLeft, char *pathOfRight) {
    werase(stdscr); // Clear Window
    curs_set(0); // Not need Cursor pointer
    char key; // User Input
    int selectingMenu = MENU_FIRSTWINODW;

    WINDOW *upMenu = NULL;
    WINDOW *downMenu = NULL;
    WINDOW *logWindow = NULL;
    WINDOW *pathWindow = NULL;
    WINDOW *firstWindow = NULL;
    WINDOW *secondWindow =NULL;
    WINDOW *thirdWindow = NULL;
    WINDOW *fourthWindow = NULL;
    WINDOW *xWindow = NULL;
    WINDOW *yWindow = NULL;
    WINDOW *zWindow = NULL;

    init_FTP_Main_Page(upMenu, downMenu, logWindow, pathWindow, firstWindow,
                      secondWindow, thirdWindow, fourthWindow,
                      xWindow, yWindow, zWindow);

    attron(COLOR_PAIR(CLIENTBAR));
    print_Manual_Bar(mode);

    while (1) {
        attron(COLOR_PAIR(MAIN1));
        print_Title_Block(mode);
        print_Path_Block(pathOfLeft, pathOfRight);

        attron(COLOR_PAIR(MAIN2));
        print_Log_Block(sampleFile, 10);
        print_Sub_Block(MODE_FIRST, sampleFile, 10);
        print_Sub_Block(MODE_SECOND, sampleFile, 10);
        print_Sub_Block(MODE_THIRD, sampleFile, 10);
        print_Sub_Block(MODE_FOURTH, sampleFile, 10);

        attron(A_STANDOUT | A_UNDERLINE); // selected effect
        switch (selectingMenu) {
            case MENU_FIRSTWINODW:
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT, 0, "LOCAL FILE TREE (press enter)           ");
                break;
            case MENU_SECONDWINDOW:
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT, 41, "SERVER FILE TREE (press enter)         ");
                break;
            case MENU_THIRDWINDOW:
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, 0, "                                        ");
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, strlen(pathOfLeft), " (press enter)");
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, 0, pathOfLeft);
                break;
            case MENU_FOURTHWINDOW:
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE+BAR_WIDE, "                                       ");
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE+BAR_WIDE+strlen(pathOfRight), " (press enter)");
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE+BAR_WIDE, pathOfRight);
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
            case KEYBOARD_DOWN:
                if (selectingMenu == MENU_FIRSTWINODW) {
                    selectingMenu = MENU_THIRDWINDOW;
                } else if (selectingMenu == MENU_SECONDWINDOW) {
                    selectingMenu = MENU_FOURTHWINDOW;
                } else if (selectingMenu == MENU_THIRDWINDOW) {
                    selectingMenu = MENU_FIRSTWINODW;
                } else if (selectingMenu == MENU_FOURTHWINDOW) {
                    selectingMenu = MENU_SECONDWINDOW;
                }
                break;
            case KEYBOARD_LEFT:
            case KEYBOARD_RIGHT:
                if (selectingMenu == MENU_FIRSTWINODW) {
                    selectingMenu = MENU_SECONDWINDOW;
                } else if (selectingMenu == MENU_SECONDWINDOW) {
                    selectingMenu = MENU_FIRSTWINODW;
                } else if (selectingMenu == MENU_THIRDWINDOW) {
                    selectingMenu = MENU_FOURTHWINDOW;
                } else if (selectingMenu == MENU_FOURTHWINDOW) {
                    selectingMenu = MENU_THIRDWINDOW;
                }
                break;
            case KEYBOARD_ENTER:
                if ( (selectingMenu == MENU_FIRSTWINODW)||(selectingMenu == MENU_SECONDWINDOW)||
                        (selectingMenu == MENU_THIRDWINDOW)||(selectingMenu == MENU_FOURTHWINDOW)){
                    return selectingMenu;
                }
                break;
            case IP_MANAGE_KEY:
                return MENU_IP_MANAGE;
            case HELP_KEY:
                return MENU_HELP;
            case EXIT_KEY:
                destroy_FTP_Main_Page(upMenu, downMenu, logWindow, pathWindow, firstWindow,
                                      secondWindow, thirdWindow, fourthWindow,
                                      xWindow, yWindow, zWindow);
                return MENU_EXIT;
        }
    }
}

/////////////////////////////////////////////////////////////
/// to print selected Page
/// input : mode (MODE_CLIENT or MODE_SERVER), path1, path2
/// return : selectMenu
////////////////////////////////////////////////////////////
int print_Selected_Page(int mode, int selectingMenu, char** srcAry, int * selected, int aryCount, char * pathOfLeft, char * pathOfRight){
    int startPoint = 0;
    int cursor = startPoint;
    char * nullStr;
    int x;
    int y;
    int totalCount;
    selected = malloc(sizeof(int) * aryCount);
    char key;

    switch (selectingMenu) {
        case MENU_FIRSTWINODW:
            x=0;
            y=MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT;
            totalCount = UPPER_SUBWINDOW_HEIGHT;
            nullStr = "                                        ";
            break;
        case MENU_SECONDWINDOW:
            x=LEFT_SUBWINDOW_WIDE + BAR_WIDE;
            y=MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT;
            totalCount = UPPER_SUBWINDOW_HEIGHT;
            nullStr = "                                       ";
            break;
        case MENU_THIRDWINDOW:
            x=0;
            y=MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT;
            totalCount=DOWN_SUBWINDOW_HEIGHT;
            nullStr = "                                        ";
            break;
        case MENU_FOURTHWINDOW:
            x=LEFT_SUBWINDOW_WIDE + BAR_WIDE;
            y=MANUAL_SUBWINDOW_HEIGHT + LOG_SUBWINDOW_HEIGHT + BAR_HEIGHT + UPPER_SUBWINDOW_HEIGHT + BAR_HEIGHT;
            totalCount = DOWN_SUBWINDOW_HEIGHT;
            nullStr = "                                       ";
            break;
        default:
            break;
    }

    attron(COLOR_PAIR(CLIENTBAR));
    attron(A_STANDOUT | A_UNDERLINE); // selected effect
    switch (selectingMenu) {
        case MENU_FIRSTWINODW:
            mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT, 0, "LOCAL FILE TREE (press back space)      ");
            break;
        case MENU_SECONDWINDOW:
            if (mode == MODE_CLIENT){
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT, 41, "SERVER FILE TREE (press back space)    ");
                break;
            } else if (mode == MODE_SERVER){
                mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT, 41, "REMOTE FILE TREE (press back space)    ");
                break;
            }
        case MENU_THIRDWINDOW:
            mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, 0, "                                        ");
            mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, strlen(pathOfLeft), " (press back space)");
            mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, 0, pathOfLeft);
            break;
        case MENU_FOURTHWINDOW:
            mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE+BAR_WIDE, "                                       ");
            mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE+BAR_WIDE+strlen(pathOfRight), " (press back space)");
            mvprintw(MANUAL_SUBWINDOW_HEIGHT+LOG_SUBWINDOW_HEIGHT+BAR_HEIGHT+UPPER_SUBWINDOW_HEIGHT, LEFT_SUBWINDOW_WIDE+BAR_WIDE, pathOfRight);
            break;
    }
    attroff(A_STANDOUT | A_UNDERLINE);

    while (1) {
        attron(COLOR_PAIR(SELECTED));

        //this is reset loop
        for (int i = 0; i < totalCount; ++i) {
            mvprintw(y + i, x, nullStr);
        }
        if (srcAry == NULL) {
            break;
        }

        //print files using loop
        if (aryCount - startPoint < totalCount){
            int k = 0;
            for (int i = startPoint; i < aryCount; ++i) {
                attron(COLOR_PAIR(SELECTED));
                if (selected[i] != 0) {
                    attron(COLOR_PAIR(CHECKED));
                }
                if (cursor == i) {
                    attron(A_STANDOUT | A_UNDERLINE);
                }
                mvprintw(y + k, x, srcAry[i]);
                k++;
                if (cursor == i) {
                    attroff(A_STANDOUT | A_UNDERLINE);
                }
            }
        }else{
            int k=0;
            for (int i = startPoint; i < (startPoint+totalCount); ++i) {
                attron(COLOR_PAIR(SELECTED));
                if (selected[i] != 0) {
                    attron(COLOR_PAIR(CHECKED));
                }
                if (cursor == i) {
                    attron(A_STANDOUT | A_UNDERLINE);
                }
                mvprintw(y + k, x, srcAry[i]);
                k++;
                if (cursor == i) {
                    attroff(A_STANDOUT | A_UNDERLINE);
                }
            }
        }

        refresh();
        key = getchar();

        switch (key) {
            case KEYBOARD_UP:
                if (cursor == startPoint) {
                    if (cursor > 0) {
                        cursor--;
                        startPoint--;
                    }
                } else if ((cursor > startPoint) && (cursor <= startPoint+totalCount)) {
                    cursor--;
                }
                break;
            case KEYBOARD_DOWN:
                if (cursor == startPoint + totalCount -1){
                    if (cursor < aryCount-1){
                        cursor++;
                        startPoint++;
                    }
                }
                else if ((cursor >= startPoint) && (cursor < startPoint+totalCount)) {
                    cursor++;
                }

                break;
            case KEYBOARD_LEFT:
                memset(selected, 0, aryCount);
                selected[0]=cursor;//this is insert
                return MENU_OUT_DIR;
            case KEYBOARD_RIGHT:
                memset(selected, 0, aryCount);
                selected[0]=cursor;//this is insert
                return MENU_INTO_DIR;
            case KEYBOARD_SPACEBAR:
                if (selected[cursor] == 0) {
                    selected[cursor] = 1;
                } else {
                    selected[cursor] = 0;
                }
                break;
            case KEYBOARD_BACKSPACE:
                return MENU_FTP_PAGE;
            case EXIT_KEY:
                return MENU_EXIT;
            case COPY_FILE_KEY:
                return COPY_FILE_KEY;
            case MOVE_FILE_KEY:
                return MOVE_FILE_KEY;
            case REMOVE_FILE_KEY:
                return REMOVE_FILE_KEY;
            case RENAME_FILE_KEY:
                return UP_AND_DOWN_FILE_KEY;
            case IP_MANAGE_KEY:
                return MENU_IP_MANAGE;
            case MOVE_DIR_KEY:
                return MOVE_DIR_KEY;
            case REMOVE_DIR_KEY:
                return REMOVE_DIR_KEY;
            case RENAME_DIR_KEY:
                return RENAME_DIR_KEY;
            case HELP_KEY:
                return MENU_HELP;
            case MAKE_DIR_KEY:
                return MAKE_DIR_KEY;
        }
    }
    return MENU_FTP_PAGE;
}
