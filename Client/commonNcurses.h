//
// Created by moosong on 6/30/20.
//

#ifndef MODULE_2_COMMONNUCURSES_H
#define MODULE_2_COMMONNUCURSES_H

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "doCommand.h"

//struct 
#define ARR_SIZ (100)
typedef struct ResInfo ResInfo;//socket&ip information
typedef struct Array Array;



//ip length limit
#define IPADDRESSLENGTH 15

//these are wide and height for windows
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

//these are modse for user(server or client)
#define MODE_CLIENT 40
#define MODE_SERVER 41

//these are modes to print sub windows
//location
//  1   2
//  3   4
#define MODE_FIRST 11
#define MODE_SECOND 12
#define MODE_THIRD 13
#define MODE_FOURTH 14

//these are special keys
#define KEYBOARD_UP 65
#define KEYBOARD_DOWN 66
#define KEYBOARD_LEFT 68
#define KEYBOARD_RIGHT 67
#define KEYBOARD_ENTER 13
#define KEYBOARD_BACKSPACE 127
#define KEYBOARD_SPACEBAR ' '
#define KEYBOARD_TAB 9

//these are page modes
#define MENU_MAIN 0
#define MENU_BOOKMARKS 1
#define MENU_HISTORY 2
#define MENU_EXIT 3
#define MENU_IP_INSERT 4
#define MENU_HELP 5
#define MENU_IP_MANAGE 6
#define MENU_FTP_PAGE 7
#define MENU_INTO_DIR 8
#define MENU_OUT_DIR 9

#define MENU_FIRSTWINODW 21
#define MENU_SECONDWINDOW 22
#define MENU_THIRDWINDOW 23
#define MENU_FOURTHWINDOW 24


//these are for color pairs
//this insert from 1
#define MAIN1 1
#define MAIN2 2
#define CLIENTBAR 3
#define SELECTED 4
#define CHECKED 5

//these are cammand keys
#define COPY_FILE_KEY 'c'
#define MOVE_FILE_KEY 'm'
#define REMOVE_FILE_KEY 'r'
#define RENAME_FILE_KEY 'n'
#define UP_AND_DOWN_FILE_KEY 'f'
#define IP_MANAGE_KEY 'p'
#define MOVE_DIR_KEY 'v'
#define REMOVE_DIR_KEY 'e'
#define RENAME_DIR_KEY 'a'
#define HELP_KEY 'h'
#define MAKE_DIR_KEY 'k'
#define EXIT_KEY 'x'



//function list
void init_scr();    //if you want to use ncurses, please call this first.
int IP_insert_Page(char**ip);   //this is for ip page to insert string, return value is menu_num
void print_Sub_Block(int mode, char** srcArray, int aryCount);
void print_Log_Block(char  ** srcArray, int aryCount);
void print_Path_Block(char * pathOfLeft, char *pathOfRight);    //insert local or server path string
int FTP_Main_Page(int mode, char * pathOfLeft, char *pathOfRight, ResInfo *resInfo,char **msg,Array* myDirectories,Array* myFiles,Array* directories,Array* files);
int print_Selected_Page(int mode, int selectingMenu, char** srcAry, int * selected, int aryCount, char * pathOfLeft, char * pathOfRight, ResInfo *resInfo,char **msg);



#endif //TESTMODULE_COMMONNUCURSES_H
