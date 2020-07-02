//
// Created by linux on 6/28/20.
//
#include <ncurses.h>

#ifndef MODULE_2_CONSOLE_H
#define MODULE_2_CONSOLE_H

#define FTP_WIDE 80
#define FTP_HEIGHT 24
#define MANUAL_SUBWINDOW_HEIGHT 1
#define LOG_SUBWINDOW_HEIGHT 3
#define BAR_WIDE 1
#define BAR_HEIGHT 1
#define LEFT_SUBWINDOW_WIDE (FTP_WIDE/2)
#define RIGHT_SUBWINDOW_WIDE (FTP_WIDE - LEFT_SUBWINDOW_WIDE - BAR_WIDE)
#define INNER_SUBWINDOW_HEIGHT (FTP_HEIGHT - MANUAL_SUBWINDOW_HEIGHT - LOG_SUBWINDOW_HEIGHT - BAR_HEIGHT - BAR_HEIGHT - MANUAL_SUBWINDOW_HEIGHT)
#define UPPER_SUBWINDOW_HEIGHT (INNER_SUBWINDOW_HEIGHT/2)
#define DOWN_SUBWINDOW_HEIGHT (INNER_SUBWINDOW_HEIGHT -UPPER_SUBWINDOW_HEIGHT)

#define MODE_CLIENT 40
#define MODE_SERVER 41

#define MODE_FIRST 11
#define MODE_SECOND 12
#define MODE_THIRD 13
#define MODE_FOURTH 14

#define KEYBOARD_UP 65
#define KEYBOARD_DOWN 66
#define KEYBOARD_LEFT 68
#define KEYBOARD_RIGHT 67

#define KEYBOARD_ENTER 13
#define KEYBOARD_BACKSPACE 127
#define KEYBOARD_SPACEBAR ' '
#define KEYBOARD_TAB 9

#define MENU_MAIN 0
#define MENU_BOOKMARKS 1
#define MENU_HISTORY 2
#define MENU_EXIT 3
#define MENU_IP 4


#define MENU_FIRSTWINODW 21
#define MENU_SECONDWINDOW 22
#define MENU_THIRDWINDOW 23
#define MENU_FOURTHWINDOW 24

#define IPADDRESSLENGTH 15

#define MAIN1 1
#define MAIN2 2
#define CLIENTBAR 3

//#define COPY_FILE_KEY1 'C'
#define COPY_FILE_KEY2 'c'
#define MOVE_FILE_KEY1 'M'
#define MOVE_FILE_KEY2 'm'
#define REMOVE_FILE_KEY1 'R'
#define REMOVE_FILE_KEY2 'r'
#define RENAME_FILE_KEY1 'N'
#define RENAME_FILE_KEY2 'n'
#define UP_AND_DOWN_FILE_KEY1 'F'
#define UP_AND_DOWN_FILE_KEY2 'f'
#define IP_MANAGE_KEY1 'P'
#define IP_MANAGE_KEY2 'p'
#define MOVE_DIR_KEY1 'V'
#define MOVE_DIR_KEY2 'v'
#define REMOVE_DIR_KEY1 'E'
#define REMOVE_DIR_KEY2 'e'
//#define RENAME_DIR_KEY1 'A'
#define RENAME_DIR_KEY2 'a'
#define HELP_KEY1 'H'
#define HELP_KEY2 'h'
#define MAKE_DIR_KEY1 'K'
#define MAKE_DIR_KEY2 'k'
#define EXIT_KEY1 'X'
#define EXIT_KEY2 'x'


void init_scr();
void init_updownWindow(WINDOW *upWindow, WINDOW *middleWindow, WINDOW *downWindow);
int mainMenu(char**ip);
int printMonitor(int mode, char * pathOfLeft, char *pathOfRight);
void showManualBar(int mode);

#endif //MODULE_2_CONSOLE_H
