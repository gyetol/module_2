#include<ncurses.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>

// 시스템에 맞게 바꾸면됨 엔터는 보통 10으로 설정되어 있기도 함
#define KEYBOARD_UP 65
#define KEYBOARD_DOWN 66
#define KEYBOARD_LEFT 68
#define KEYBOARD_RIGHT 67
#define KEYBOARD_ENTER 13
#define KEYBOARD_BACKSPACE 127

#define MENU_MAIN 0
#define MENU_LOGIN 1
#define MENU_SIGNIO 2
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


#define MENU_ID 100
#define MENU_PASS 101

#define MENU_WIN 200
#define MENU_LOSE 201

#define IDPASSLENGTH 15

struct loginInformation{
	bool login;
	char id[IDPASSLENGTH];	
	char pass[IDPASSLENGTH];
	int win;
	int lose;
};

int _mainMenu();
int _loginMenu();
int _signioMenu();
int _signinMenu();
int _signoutMenu();
int _playMenu();
int _ingameMenu();
int _statisticsMenu();
int _2ploginMenu();
int _2pmainMenu();
int _gamestartMenu();

void init_updownWindow(WINDOW *upWindow, WINDOW *downWindow);
void init_leftrightWindow(WINDOW *leftMenu,WINDOW *rightMenu);
void init_scr();
void saveInfo();

/* Global Value */

struct loginInformation loginInfo;
struct loginInformation loginInfo2;

/****************/

int main()
{
	init_scr();
	loginInfo.login = false;

	int thisMenu = MENU_MAIN;
	while(thisMenu != MENU_EXIT)
	{
		switch(thisMenu){
			case MENU_MAIN :
				thisMenu = _mainMenu();
				break;
			case MENU_LOGIN : 
				thisMenu = _loginMenu();
				break;
			case MENU_SIGNIO : 
				thisMenu = _signioMenu();
				break;
			case MENU_SIGNIN : 
				thisMenu = _signinMenu();
				break;
			case MENU_SIGNOUT : 
				thisMenu = _signoutMenu();
				break;
			case MENU_PLAY :
				thisMenu = _playMenu();
				break;
			case MENU_INGAME : 
				thisMenu = _ingameMenu();
				break;
			case MENU_STATISTICS :
				thisMenu = _statisticsMenu();
				break;
			case MENU_2PMAIN :
				thisMenu = _2pmainMenu();
				break;
			case MENU_2PLOGIN :
				thisMenu = _2ploginMenu();
				break;
			case MENU_GAMESTART :
				thisMenu = _gamestartMenu();
				break;
		} 	
	}

	endwin();
	return 0;
}

int _mainMenu(){
	werase(stdscr); // Clear Window
	curs_set(0); // Not need Cursor pointer
	char key; // User Input 
	int selectingMenu = MENU_LOGIN; 
	
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);
	
	mvprintw(3, 17, "Software Practice 2");
	mvprintw(5, 23, "OTHELLO");
	mvprintw(7, 35, "2013726011");
	mvprintw(8, 35, "Choi Eun Joo");

	while(1){
		attron(COLOR_PAIR(2));
		mvprintw(11, 4, "1P LOGIN");
		mvprintw(11, 21, "SIGN IN&OUT");
		mvprintw(11, 38, "EXIT");

		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_LOGIN :
				mvprintw(11, 4, "1P LOGIN");
				break;
			case MENU_SIGNIO :
				mvprintw(11, 21, "SIGN IN&OUT");
				break;
			case MENU_EXIT :
				mvprintw(11, 38, "EXIT");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
			
		key = getchar();
		
		switch(key){
			case KEYBOARD_RIGHT :
				if(selectingMenu == MENU_LOGIN)
					selectingMenu = MENU_SIGNIO;
				else if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_EXIT;
				else if(selectingMenu == MENU_EXIT)
					selectingMenu = MENU_LOGIN;			
				break;
			case KEYBOARD_LEFT :
				if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_LOGIN;
				else if(selectingMenu == MENU_EXIT)
					selectingMenu = MENU_SIGNIO;	
				else if(selectingMenu == MENU_LOGIN)
					selectingMenu = MENU_EXIT;			
				break;
			case KEYBOARD_ENTER :
				delwin(upMenu);
				delwin(downMenu);
				return selectingMenu;
		}
	}
}


int _loginMenu(){
	char id[IDPASSLENGTH] = ""; // user input id
	char password[IDPASSLENGTH] = ""; // user input passwd
	int i;
	werase(stdscr); // Clear Window	
	char key; // User Input 
	int selectingMenu = MENU_ID;
	
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);

	mvprintw(2, 25, "1P LOGIN");
	mvprintw(4, 19, " : ");
	mvprintw(6, 19, " : ");
	
	while(1){
		attron(COLOR_PAIR(1));
		mvprintw(4, 17, "ID");
		mvprintw(6, 11, "PASSWORD");
		mvprintw(4, 22, "               ");
		mvprintw(4, 22, id);
		mvprintw(6, 22, "               ");
		for(i=0; i<strlen(password); i++)
			mvprintw(6, 22+i, "*");
		
		attron(COLOR_PAIR(2));
		
		mvprintw(11, 19, "LOGIN");
		mvprintw(11, 28, "MAIN MENU");
		
		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_ID :
				curs_set(1);
				mvprintw(4, 17, "ID");
				move(4, 22 + strlen(id));
				break;
			case MENU_PASS :
				curs_set(1);
				mvprintw(6, 11, "PASSWORD");
				move(6, 22 + strlen(password));
				break;	
			case MENU_2PMAIN :
				curs_set(0);
				mvprintw(11, 19, "LOGIN");
				break;
			case MENU_MAIN :
				curs_set(0);
				mvprintw(11, 28, "MAIN MENU");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
		
		// Input key	
		key = getchar();
		
		switch(key){
			case KEYBOARD_UP :
				if(selectingMenu == MENU_2PMAIN || selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_ID;
				break;
			case KEYBOARD_DOWN :
				if(selectingMenu == MENU_ID) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_2PMAIN;	
				break;
			case KEYBOARD_RIGHT :
				if(selectingMenu == MENU_2PMAIN) 
					selectingMenu = MENU_MAIN;
				else if(selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_2PMAIN;				
				break;
			case KEYBOARD_LEFT :
				if(selectingMenu == MENU_2PMAIN) 
					selectingMenu = MENU_MAIN;
				else if(selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_2PMAIN;				
				break;
			case KEYBOARD_BACKSPACE :
				if(selectingMenu == MENU_ID) 
						id[strlen(id) - 1] = '\0';
				else if(selectingMenu == MENU_PASS)
						password[strlen(password) - 1] = '\0';
				break;
			case KEYBOARD_ENTER :
				if(selectingMenu == MENU_ID) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_2PMAIN;
				else if(selectingMenu == MENU_2PMAIN)
				{
					int fd = open("info", O_RDWR | O_CREAT, 0644);
						
					int bufLength = IDPASSLENGTH + 1 + IDPASSLENGTH + 1 + 3 + 1 + 3 + 1;
					char buf[bufLength]; // ID(15)  PASS(15)  WIN(3)  LOSE(3)   
					char tempID[IDPASSLENGTH], tempPW[IDPASSLENGTH];
					int tempWIN, tempLOSE;
					
					while(read(fd, buf, bufLength) > 0)
					{
						sscanf(buf, "%s %s %d %d", tempID, tempPW, &tempWIN, &tempLOSE);
						if(strcmp(tempID, id) == 0)
						{
							if(strcmp(tempPW, password) == 0) // Login Success!
							{
								mvprintw(LINES - 1, 0, "                                          ");
								mvprintw(LINES - 1, 0, "Hello %s!", id);
								getch();
								loginInfo.login = true;
								strcpy(loginInfo.id, id);
								strcpy(loginInfo.pass, password);
								loginInfo.win = tempWIN;
								loginInfo.lose = tempLOSE;
								close(fd);
								delwin(upMenu);
								delwin(downMenu);
								return selectingMenu;
							}
						}
					}
					close(fd);
					mvprintw(LINES - 1, 0, "                                          ");
					mvprintw(LINES - 1, 0, "Login Failed");
				}
				if(selectingMenu == MENU_MAIN) {
					delwin(upMenu);
					delwin(downMenu);
					return selectingMenu;
				}
				break;
			default :
				if((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z'))
				{
					char tempKey[2];
					tempKey[0] = key;
					tempKey[1] = '\0';
					if(selectingMenu == MENU_ID && strlen(id) < IDPASSLENGTH) 
						strcat(id, tempKey);
					else if(selectingMenu == MENU_PASS && strlen(password) < IDPASSLENGTH)
						strcat(password, tempKey);
				}
				break;
		}
	}
}
int _2pmainMenu(){
	werase(stdscr); // Clear Window
	curs_set(0); // Not need Cursor pointer
	char key; // User Input 
	int selectingMenu = MENU_2PLOGIN; 
	
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);
	
	mvprintw(3, 17, "Software Practice 2");
	mvprintw(5, 23, "OTHELLO");
	mvprintw(7, 35, "2013726011");
	mvprintw(8, 35, "Choi Eun Joo");

	while(1){
		attron(COLOR_PAIR(2));
		mvprintw(11, 4, "2P LOGIN");
		mvprintw(11, 21, "SIGN IN&OUT");
		mvprintw(11, 38, "EXIT");

		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_2PLOGIN :
				mvprintw(11, 4, "2P LOGIN");
				break;
			case MENU_SIGNIO :
				mvprintw(11, 21, "SIGN IN&OUT");
				break;
			case MENU_EXIT :
				mvprintw(11, 38, "EXIT");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
			
		key = getchar();
		
		switch(key){
			case KEYBOARD_RIGHT :
				if(selectingMenu == MENU_2PLOGIN)
					selectingMenu = MENU_SIGNIO;
				else if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_EXIT;
				else if(selectingMenu == MENU_EXIT)
					selectingMenu = MENU_2PLOGIN;			
				break;
			case KEYBOARD_LEFT :
				if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_2PLOGIN;
				else if(selectingMenu == MENU_EXIT)
					selectingMenu = MENU_SIGNIO;	
				else if(selectingMenu == MENU_2PLOGIN)
					selectingMenu = MENU_EXIT;			
				break;
			case KEYBOARD_ENTER :
				delwin(upMenu);
				delwin(downMenu);
				return selectingMenu;
		}
	}
}
int _2ploginMenu(){
	char id[IDPASSLENGTH] = ""; // user input id
	char password[IDPASSLENGTH] = ""; // user input passwd
	int i;
	werase(stdscr); // Clear Window	
	char key; // User Input 
	int selectingMenu = MENU_ID;
	
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);

	mvprintw(2, 25, "2P LOGIN");
	mvprintw(4, 19, " : ");
	mvprintw(6, 19, " : ");
	
	while(1){
		attron(COLOR_PAIR(1));
		mvprintw(4, 17, "ID");
		mvprintw(6, 11, "PASSWORD");
		mvprintw(4, 22, "               ");
		mvprintw(4, 22, id);
		mvprintw(6, 22, "               ");
		for(i=0; i<strlen(password); i++)
			mvprintw(6, 22+i, "*");
		
		attron(COLOR_PAIR(2));
		
		mvprintw(11, 19, "LOGIN");
		mvprintw(11, 28, "MAIN MENU");
		
		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_ID :
				curs_set(1);
				mvprintw(4, 17, "ID");
				move(4, 22 + strlen(id));
				break;
			case MENU_PASS :
				curs_set(1);
				mvprintw(6, 11, "PASSWORD");
				move(6, 22 + strlen(password));
				break;	
			case MENU_GAMESTART :
				curs_set(0);
				mvprintw(11, 19, "LOGIN");
				break;
			case MENU_MAIN :
				curs_set(0);
				mvprintw(11, 28, "MAIN MENU");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
		
		// Input key	
		key = getchar();
		
		switch(key){
			case KEYBOARD_UP :
				if(selectingMenu == MENU_GAMESTART || selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_ID;
				break;
			case KEYBOARD_DOWN :
				if(selectingMenu == MENU_ID) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_GAMESTART;	
				break;
			case KEYBOARD_RIGHT :
				if(selectingMenu == MENU_GAMESTART) 
					selectingMenu = MENU_MAIN;
				else if(selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_GAMESTART;				
				break;
			case KEYBOARD_LEFT :
				if(selectingMenu == MENU_GAMESTART) 
					selectingMenu = MENU_MAIN;
				else if(selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_GAMESTART;				
				break;
			case KEYBOARD_BACKSPACE :
				if(selectingMenu == MENU_ID) 
						id[strlen(id) - 1] = '\0';
				else if(selectingMenu == MENU_PASS)
						password[strlen(password) - 1] = '\0';
				break;
			case KEYBOARD_ENTER :
				if(selectingMenu == MENU_ID) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_GAMESTART;
				else if(selectingMenu == MENU_GAMESTART)
				{
					int fd = open("info", O_RDWR | O_CREAT, 0644);
						
					int bufLength = IDPASSLENGTH + 1 + IDPASSLENGTH + 1 + 3 + 1 + 3 + 1;
					char buf[bufLength]; // ID(15)  PASS(15)  WIN(3)  LOSE(3)   
					char tempID[IDPASSLENGTH], tempPW[IDPASSLENGTH];
					int tempWIN, tempLOSE;
					
					while(read(fd, buf, bufLength) > 0)
					{
						sscanf(buf, "%s %s %d %d", tempID, tempPW, &tempWIN, &tempLOSE);
						if(strcmp(tempID, id) == 0)
						{
						    if(strcmp(loginInfo.id,id)!=0)
						    {
							if(strcmp(tempPW, password) == 0) // Login Success!
							{
								mvprintw(LINES - 1, 0, "                                          ");
								mvprintw(LINES - 1, 0, "Hello %s!", id);
								getch();
								loginInfo2.login = true;
								strcpy(loginInfo2.id, id);
								strcpy(loginInfo2.pass, password);
								loginInfo2.win = tempWIN;
								loginInfo2.lose = tempLOSE;
								close(fd);
								delwin(upMenu);
								delwin(downMenu);
								return selectingMenu;
							}
						     }
						}
					}
					close(fd);
					mvprintw(LINES - 1, 0, "                                          ");
					mvprintw(LINES - 1, 0, "Login Failed");
				}
				if(selectingMenu == MENU_MAIN) {
					delwin(upMenu);
					delwin(downMenu);
					return selectingMenu;
				}
				break;
			default :
				if((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z'))
				{
					char tempKey[2];
					tempKey[0] = key;
					tempKey[1] = '\0';
					if(selectingMenu == MENU_ID && strlen(id) < IDPASSLENGTH) 
						strcat(id, tempKey);
					else if(selectingMenu == MENU_PASS && strlen(password) < IDPASSLENGTH)
						strcat(password, tempKey);
				}
				break;
		}
	}
}
int _gamestartMenu(){
	werase(stdscr); // Clear Window
	curs_set(0); // Not need Cursor pointer
	char key; // User Input 
	int selectingMenu = MENU_PLAY; 
	
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);
	
	mvprintw(3, 17, "Software Practice 2");
	mvprintw(5, 23, "OTHELLO");
	mvprintw(7, 35, "2013726011");
	mvprintw(8, 35, "Choi Eun Joo");

	while(1){
		attron(COLOR_PAIR(2));
		mvprintw(11, 4, "GAME START");
		mvprintw(11, 21, "SIGN IN&OUT");
		mvprintw(11, 38, "EXIT");

		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_PLAY:
				mvprintw(11, 4, "GAME START");
				break;
			case MENU_SIGNIO :
				mvprintw(11, 21, "SIGN IN&OUT");
				break;
			case MENU_EXIT :
				mvprintw(11, 38, "EXIT");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
			
		key = getchar();
		
		switch(key){
			case KEYBOARD_RIGHT :
				if(selectingMenu == MENU_PLAY)
					selectingMenu = MENU_SIGNIO;
				else if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_EXIT;
				else if(selectingMenu == MENU_EXIT)
					selectingMenu = MENU_PLAY;			
				break;
			case KEYBOARD_LEFT :
				if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_PLAY;
				else if(selectingMenu == MENU_EXIT)
					selectingMenu = MENU_SIGNIO;	
				else if(selectingMenu == MENU_PLAY)
					selectingMenu = MENU_EXIT;			
				break;
			case KEYBOARD_ENTER :
				delwin(upMenu);
				delwin(downMenu);
				return selectingMenu;
		}
	}
}

int _signioMenu(){
	werase(stdscr); // Clear Window
	curs_set(0); // Not need Cursor pointer
	char key; // User Input 
	int selectingMenu = MENU_SIGNIN; 
	
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);
	
	mvprintw(4, 20, "SIGN IN/OUT");
	
	while(1){
		attron(COLOR_PAIR(2));
		mvprintw(11, 4, "SIGN IN");
		mvprintw(11, 21, "SIGN OUT");
		mvprintw(11, 38, "BACK(MENU)");
		
		// mvprintw(1, 1, "%d", key);
		
		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_SIGNIN :
				mvprintw(11, 4, "SIGN IN");
				break;
			case MENU_SIGNOUT :
				mvprintw(11, 21, "SIGN OUT");
				break;
			case MENU_MAIN :
				mvprintw(11, 38, "BACK(MENU)");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
			
		key = getchar();
		
		switch(key){
			case KEYBOARD_RIGHT :
				if(selectingMenu == MENU_SIGNIN)
					selectingMenu = MENU_SIGNOUT;
				else if(selectingMenu == MENU_SIGNOUT)
					selectingMenu = MENU_MAIN;	
				else if(selectingMenu == MENU_MAIN)
					selectingMenu = MENU_SIGNIN;
				break;
			case KEYBOARD_LEFT :
				if(selectingMenu == MENU_MAIN)
					selectingMenu = MENU_SIGNOUT;
				else if(selectingMenu == MENU_SIGNOUT)
					selectingMenu = MENU_SIGNIN;
				else if(selectingMenu == MENU_SIGNIN)
					selectingMenu = MENU_MAIN;
				break;
			case KEYBOARD_ENTER :
				delwin(upMenu);
				delwin(downMenu);
				return selectingMenu;
		}
	}
}

int _signinMenu(){
	char id[IDPASSLENGTH] = ""; // user input id
	char password[IDPASSLENGTH] = ""; // user input passwd
	int i;
	werase(stdscr); // Clear Window	
	char key; // User Input 
	int selectingMenu = MENU_ID;
	
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);
	
	mvprintw(2, 23, "SIGN IN");
	mvprintw(4, 19, " : ");
	mvprintw(6, 19, " : ");
	
	while(1){
		attron(COLOR_PAIR(1));
		mvprintw(4, 17, "ID");
		mvprintw(6, 11, "PASSWORD");
		mvprintw(4, 22, "               ");
		mvprintw(4, 22, id);
		mvprintw(6, 22, "               ");
		for(i=0; i<strlen(password); i++)
			mvprintw(6, 22+i, "*");
		
		attron(COLOR_PAIR(2));
		mvprintw(11, 17, "SIGN IN");
		mvprintw(11, 29, "BACK");
		
		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_ID :
				curs_set(1);
				mvprintw(4, 17, "ID");
				move(4, 22 + strlen(id));
				break;
			case MENU_PASS :
				curs_set(1);
				mvprintw(6, 11, "PASSWORD");
				move(6, 22 + strlen(password));
				break;	
			case MENU_MAIN :
				curs_set(0);
				mvprintw(11, 17, "SIGN IN");
				break;
			case MENU_SIGNIO :
				curs_set(0);
				mvprintw(11, 29, "BACK");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
		
		// Input key	
		key = getchar();
		
		switch(key){
			case KEYBOARD_UP :
				if(selectingMenu == MENU_MAIN || selectingMenu == MENU_SIGNIO) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_ID;
				break;
			case KEYBOARD_DOWN :
				if(selectingMenu == MENU_ID) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_MAIN;			
				break;
			case KEYBOARD_RIGHT :
				if(selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_SIGNIO;
				else if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_MAIN;				
				break;
			case KEYBOARD_LEFT :
				if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_MAIN;	
				else if(selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_SIGNIO;		
				break;
			case KEYBOARD_BACKSPACE :
				if(selectingMenu == MENU_ID) 
						id[strlen(id) - 1] = '\0';
				else if(selectingMenu == MENU_PASS)
						password[strlen(password) - 1] = '\0';
				break;
			case KEYBOARD_ENTER :
				if(selectingMenu == MENU_ID)
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_MAIN;	
				else if(selectingMenu == MENU_MAIN)
				{
					int fd = open("info", O_RDWR | O_CREAT, 0644);
						
					int bufLength = IDPASSLENGTH + 1 + IDPASSLENGTH + 1 + 3 + 1 + 3 + 1;
					char buf[bufLength]; // ID(15)  PASS(15)  WIN(3)  LOSE(3)   
					char tempID[IDPASSLENGTH], tempPW[IDPASSLENGTH];
					int tempWIN, tempLOSE;
					bool signInSuccess = true;
					
					while(read(fd, buf, bufLength) > 0)
					{
						sscanf(buf, "%s %s %d %d", tempID, tempPW, &tempWIN, &tempLOSE);
						if(strcmp(tempID, id) == 0)
						{
							mvprintw(LINES - 1, 0, "                                          ");
							mvprintw(LINES - 1, 0, "Sign IN Failed : Already exist duplicated id");
							signInSuccess = false;
							break;
						}
					}
					
					if(signInSuccess == true){
						mvprintw(LINES - 1, 0, "                                            ");
						mvprintw(LINES - 1, 1, "Welcome to OTHELLO world (Press any key)");
						getch();
						
						sprintf(buf, "\n%-15s %-15s %-3d %-3d", id, password, 0, 0);
						write(fd, buf, bufLength);
						
						close(fd);
						delwin(upMenu);
						delwin(downMenu);
						return selectingMenu;
					} else {
						close(fd);
						break;
					}
				}
				if(selectingMenu == MENU_SIGNIO) {
					delwin(upMenu);
					delwin(downMenu);
					return selectingMenu;
				}
			default :
				if((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z'))
				{
					char tempKey[2];
					tempKey[0] = key;
					tempKey[1] = '\0';
					if(selectingMenu == MENU_ID && strlen(id) < IDPASSLENGTH) 
						strcat(id, tempKey);
					else if(selectingMenu == MENU_PASS && strlen(password) < IDPASSLENGTH)
						strcat(password, tempKey);
				}
				break;
		}
	}
}

int _signoutMenu(){
	char id[IDPASSLENGTH] = ""; // user input id
	char password[IDPASSLENGTH] = ""; // user input passwd
	int i;
	werase(stdscr); // Clear Window	
	char key; // User Input 
	int selectingMenu = MENU_ID;
	
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);
	
	mvprintw(2, 23, "SIGN OUT");
	mvprintw(4, 19, " : ");
	mvprintw(6, 19, " : ");
	
	while(1){
		attron(COLOR_PAIR(1));
		mvprintw(4, 17, "ID");
		mvprintw(6, 11, "PASSWORD");
		mvprintw(4, 22, "               ");
		mvprintw(4, 22, id);
		mvprintw(6, 22, "               ");
		for(i=0; i<strlen(password); i++)
			mvprintw(6, 22+i, "*");
		
		attron(COLOR_PAIR(2));
		mvprintw(11, 17, "SIGN OUT");
		mvprintw(11, 29, "BACK");
		
		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_ID :
				curs_set(1);
				mvprintw(4, 17, "ID");
				move(4, 22 + strlen(id));
				break;
			case MENU_PASS :
				curs_set(1);
				mvprintw(6, 11, "PASSWORD");
				move(6, 22 + strlen(password));
				break;	
			case MENU_MAIN :
				curs_set(0);
				mvprintw(11, 17, "SIGN OUT");
				break;
			case MENU_SIGNIO :
				curs_set(0);
				mvprintw(11, 29, "BACK");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
		
		// Input key	
		key = getchar();
		
		switch(key){
			case KEYBOARD_UP :
				if(selectingMenu == MENU_MAIN || selectingMenu == MENU_SIGNIO) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_ID;
				break;
			case KEYBOARD_DOWN :
				if(selectingMenu == MENU_ID) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_MAIN;			
				break;
			case KEYBOARD_RIGHT :
				if(selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_SIGNIO;
				else if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_MAIN;
				break;
			case KEYBOARD_LEFT :
				if(selectingMenu == MENU_SIGNIO)
					selectingMenu = MENU_MAIN;
				else if(selectingMenu == MENU_MAIN) 
					selectingMenu = MENU_SIGNIO;	
				break;
			case KEYBOARD_BACKSPACE :
				if(selectingMenu == MENU_ID) 
						id[strlen(id) - 1] = '\0';
				else if(selectingMenu == MENU_PASS)
						password[strlen(password) - 1] = '\0';
				break;
			case KEYBOARD_ENTER :
				if(selectingMenu == MENU_ID) 
					selectingMenu = MENU_PASS;
				else if(selectingMenu == MENU_PASS)
					selectingMenu = MENU_MAIN;
				else if(selectingMenu == MENU_MAIN)
				{
					int fd = open("info", O_RDWR | O_CREAT, 0644);
						
					int bufLength = IDPASSLENGTH + 1 + IDPASSLENGTH + 1 + 3 + 1 + 3 + 1;
					char buf[bufLength]; // ID(15)  PASS(15)  WIN(3)  LOSE(3)   
					char tempID[IDPASSLENGTH], tempPW[IDPASSLENGTH];
					int tempWIN, tempLOSE;
					bool signInSuccess = true;
					int lineCount = 0;
					
					while(read(fd, buf, bufLength) > 0)
					{
						lineCount++;
						sscanf(buf, "%s %s %d %d", tempID, tempPW, &tempWIN, &tempLOSE);
						if(strcmp(tempID, id) == 0)
						{
							if(strcmp(tempPW, password) == 0) // Login Success!
							{
								mvprintw(LINES - 1, 0, "                                          ");
								mvprintw(LINES - 1, 0, "Goodbye %s", id);
								getch();
								
								while(read(fd, buf, bufLength) > 0){
									lineCount++;
									sscanf(buf, "%s %s %d %d", tempID, tempPW, &tempWIN, &tempLOSE);
									lseek(fd, (off_t)-bufLength*2, SEEK_CUR);
									write(fd, buf, bufLength);	
									lseek(fd, (off_t)+bufLength, SEEK_CUR);
								}
								
								ftruncate(fd, (lineCount-1)*bufLength);
								
								close(fd);
								delwin(upMenu);
								delwin(downMenu);
								return MENU_MAIN;
							}
						}
					}
					
					mvprintw(LINES - 1, 0, "                                            ");
					mvprintw(LINES - 1, 0, "Failed to Sign out");
					close(fd);
					break;
				}
				if(selectingMenu == MENU_SIGNIO) {
					delwin(upMenu);
					delwin(downMenu);
					return selectingMenu;
				}
			default :
				if((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z'))
				{
					char tempKey[2];
					tempKey[0] = key;
					tempKey[1] = '\0';
					if(selectingMenu == MENU_ID && strlen(id) < IDPASSLENGTH) 
						strcat(id, tempKey);
					else if(selectingMenu == MENU_PASS && strlen(password) < IDPASSLENGTH)
						strcat(password, tempKey);
				}
				break;
		}
	}
}

int _playMenu(){
	werase(stdscr); // Clear Window
	curs_set(0); // Not need Cursor pointer
	char key; // User Input 
	int selectingMenu = MENU_INGAME; 
	
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);
	
	mvprintw(5, 3, "1P(o) : %s", loginInfo.id);
	mvprintw(5, 28, "2P(x) : %s", loginInfo2.id);
	
	while(1){
		attron(COLOR_PAIR(2));
		mvprintw(11, 6, "PLAY");
		mvprintw(11, 18, "STATISTICS");
		mvprintw(11, 37, "LOGOUT");

		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_INGAME :
				mvprintw(11, 6, "PLAY");
				break;
			case MENU_STATISTICS :
				mvprintw(11, 18, "STATISTICS");
				break;
			case MENU_MAIN :
				mvprintw(11, 37, "LOGOUT");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
			
		key = getchar();
		
		switch(key){
			case KEYBOARD_RIGHT :
				if(selectingMenu == MENU_INGAME)
					selectingMenu = MENU_STATISTICS;
				else if(selectingMenu == MENU_STATISTICS)
					selectingMenu = MENU_MAIN;
				else if(selectingMenu == MENU_MAIN)
					selectingMenu = MENU_INGAME;	
				break;
			case KEYBOARD_LEFT :
				if(selectingMenu == MENU_STATISTICS)
					selectingMenu = MENU_INGAME;
				else if(selectingMenu == MENU_MAIN)
					selectingMenu = MENU_STATISTICS;
				else if(selectingMenu == MENU_INGAME)
					selectingMenu = MENU_MAIN;			
				break;
			case KEYBOARD_ENTER :
				if(selectingMenu == MENU_MAIN)
					loginInfo.login = false;
				delwin(upMenu);
				delwin(downMenu);
				return selectingMenu;
		}
	}

}
int _ingameMenu(){
	werase(stdscr); // Clear Window
	curs_set(0); // Not need Cursor pointer
	char key, endkey; // User Input
	int cur; 
	int x=15;
	int y=5; //커서위치
	int first = 0;
	int second = 0; // 1P,2P
	int turn = 1;
	int i=0;
	int j=0; //배열찾기
	bool isturn=FALSE;
	char game[12][28];
	for(i=0;i<12;i++)
	{
		for(j=0;j<28;j++)
		{
			game[i][j]=' ';
		}
	}	
	game[5][15]='o';
	game[7][19]='o';
	game[5][19]='x';
	game[7][15]='x';
	for(i=0;i<12;i++)
	{
		for(j=0;j<28;j++)
		{
			if(game[i][j]=='o')
				first+=1;
			else if(game[i][j] == 'x')
				second+=1;
		}
	}
	int selectingMenu = 0;
	int endgameMenu = 0;
	WINDOW *rightWindow, *leftWindow;
	rightWindow = subwin(stdscr,13,18,0,35);
	wbkgd(rightWindow, COLOR_PAIR(2));
	leftWindow = subwin(stdscr,13,35,0,0);
	wbkgd(leftWindow ,COLOR_PAIR(1));
	attron(COLOR_PAIR(1));
	
	while(1){
		attron(COLOR_PAIR(1));
		mvprintw(0, 5, "+---+---+---+---+---+---+");
		mvprintw(1, 5, "| %c | %c | %c | %c | %c | %c |",game[1][7],game[1][11],game[1][15],game[1][19],game[1][23],game[1][27]);
		mvprintw(2, 5, "+---+---+---+---+---+---+");
		mvprintw(3, 5, "| %c | %c | %c | %c | %c | %c |",game[3][7],game[3][11],game[3][15],game[3][19],game[3][23],game[3][27]);
		mvprintw(4, 5, "+---+---+---+---+---+---+");
		mvprintw(5, 5, "| %c | %c | %c | %c | %c | %c |",game[5][7],game[5][11],game[5][15],game[5][19],game[5][23],game[5][27]);
		mvprintw(6, 5, "+---+---+---+---+---+---+");
		mvprintw(7, 5, "| %c | %c | %c | %c | %c | %c |",game[7][7],game[7][11],game[7][15],game[7][19],game[7][23],game[7][27]);
		mvprintw(8, 5, "+---+---+---+---+---+---+");
		mvprintw(9, 5, "| %c | %c | %c | %c | %c | %c |",game[9][7],game[9][11],game[9][15],game[9][19],game[9][23],game[9][27]);
		mvprintw(10, 5, "+---+---+---+---+---+---+");
		mvprintw(11, 5, "| %c | %c | %c | %c | %c | %c |",game[11][7],game[11][11],game[11][15],game[11][19],game[11][23],game[11][27]);
		mvprintw(12, 5, "+---+---+---+---+---+---+");
	first=0;
	second=0;
	for(i=0;i<12;i++)
	{
		for(j=0;j<28;j++)
		{
			if(game[i][j]=='o')
				first+=1;
			else if(game[i][j] == 'x')
				second+=1;
		}
	}

		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(2));
		attron(A_UNDERLINE);
		mvprintw(7,40,"N");
		mvprintw(8,40,"R");
		mvprintw(9,41,"X");
		attroff(A_UNDERLINE);
		mvprintw(7, 41, "EXTTURN");
		mvprintw(8, 41, "EGAME");
		mvprintw(9, 40, "E");
		mvprintw(9, 42, "IT");
		mvprintw(3, 40, "1P(O): %d ",first);
		mvprintw(4, 40, "2P(X): %d ",second);

		if(first+second == 36){
			if(first<second){
				mvprintw(7,40,"2P WIN!!");
				loginInfo2.win++;
				loginInfo.lose++;
				saveInfo();
				endgameMenu = MENU_INGAME;
			}
			if(first>second){
				mvprintw(7,40,"1P WIN!!");
				loginInfo.win++;
				loginInfo2.lose++;
				saveInfo();
				endgameMenu = MENU_INGAME;
			}
			if(first==second){
				mvprintw(7,40,"DRAW!!!!");
				endgameMenu = MENU_INGAME;
			}
			x=39,y=8;
			while(1){
				attron(A_UNDERLINE);
				mvprintw(8,40,"R");
				mvprintw(9,41,"X");
				attroff(A_UNDERLINE);
				mvprintw(8, 41, "EGAME");
				mvprintw(9, 40, "E");
				mvprintw(9, 42, "IT");
				attron(A_STANDOUT|A_UNDERLINE);
				switch(endgameMenu){
					case MENU_INGAME :
						mvprintw(8, 40, "REGAME");
						break;
					case MENU_PLAY :
						mvprintw(9, 40, "EXIT");
						break;
				}
				attroff(A_STANDOUT | A_UNDERLINE);
				move(y,x);
				refresh();
				endkey = getchar();
				switch(endkey){
					case KEYBOARD_DOWN :
						if(endgameMenu == MENU_INGAME){
							endgameMenu = MENU_PLAY;
							y=9;
						}
						else if(endgameMenu == MENU_PLAY){
							endgameMenu = MENU_INGAME;
							y=8;
						}
						break;
					case KEYBOARD_UP :
						if(endgameMenu == MENU_INGAME){
							endgameMenu = MENU_PLAY;
							y=9;
						}
						else if(endgameMenu == MENU_PLAY){
							endgameMenu = MENU_INGAME;
							y=8;
						}
						break;
					case KEYBOARD_ENTER :
						if(endgameMenu == MENU_PLAY){ //EXIT
							selectingMenu = MENU_PLAY;
							delwin(leftWindow);
							delwin(rightWindow);
							return selectingMenu;
						}
						else if(endgameMenu == MENU_INGAME){ //REGAME	
							selectingMenu = MENU_INGAME;
							delwin(leftWindow);
							delwin(rightWindow);
							return selectingMenu;
						}					
				}
			}
		}
		else if(first+second != 36 && first == 0){ //1p말이 하나도 없는 경우
			mvprintw(7,40,"2P WIN!!");
			loginInfo2.win++;
			loginInfo.lose++;
			saveInfo();
			endgameMenu = MENU_INGAME;
			x=39,y=8;
			while(1){
				attron(A_UNDERLINE);
				mvprintw(8,40,"R");
				mvprintw(9,41,"X");
				attroff(A_UNDERLINE);
				mvprintw(8, 41, "EGAME");
				mvprintw(9, 40, "E");
				mvprintw(9, 42, "IT");
				attron(A_STANDOUT|A_UNDERLINE);
				switch(endgameMenu){
					case MENU_INGAME :
						mvprintw(8, 40, "REGAME");
						break;
					case MENU_PLAY :
						mvprintw(9, 40, "EXIT");
						break;
				}
				attroff(A_STANDOUT | A_UNDERLINE);
				move(y,x);
				refresh();
				endkey = getchar();
				switch(endkey){
					case KEYBOARD_DOWN :
						if(endgameMenu == MENU_INGAME){
							endgameMenu = MENU_PLAY;
							y=9;
						}
						else if(endgameMenu == MENU_PLAY){
							endgameMenu = MENU_INGAME;
							y=8;
						}
						break;
					case KEYBOARD_UP :
						if(endgameMenu == MENU_INGAME){
							endgameMenu = MENU_PLAY;
							y=9;
						}
						else if(endgameMenu == MENU_PLAY){
							endgameMenu = MENU_INGAME;
							y=8;
						}
						break;
					case KEYBOARD_ENTER :
						if(endgameMenu == MENU_PLAY){ //EXIT
							selectingMenu = MENU_PLAY;
							delwin(leftWindow);
							delwin(rightWindow);
							return selectingMenu;
						}
						else if(endgameMenu == MENU_INGAME){ //REGAME
							selectingMenu = MENU_INGAME;
							delwin(leftWindow);
							delwin(rightWindow);
							return selectingMenu;
						}
						
			}
		}
		}
		else if(first+second != 36 && second == 0){	//2p 말이 하나도 없는경우
			mvprintw(7,40,"1P WIN!!");
			loginInfo.win++;
			loginInfo2.lose++;
			saveInfo();
			endgameMenu = MENU_INGAME;
			x=39,y=8;
			while(1){
				attron(A_UNDERLINE);
				mvprintw(8,40,"R");
				mvprintw(9,41,"X");
				attroff(A_UNDERLINE);
				mvprintw(8, 41, "EGAME");
				mvprintw(9, 40, "E");
				mvprintw(9, 42, "IT");
				attron(A_STANDOUT|A_UNDERLINE);
				switch(endgameMenu){
					case MENU_INGAME :
						mvprintw(8, 40, "REGAME");
						break;
					case MENU_PLAY :
						mvprintw(9, 40, "EXIT");
						break;
				}
				attroff(A_STANDOUT | A_UNDERLINE);
				move(y,x);
				refresh();
				endkey = getchar();
				switch(endkey){
					case KEYBOARD_DOWN :
						if(endgameMenu == MENU_INGAME){
							endgameMenu = MENU_PLAY;
							y=9;
						}
						else if(endgameMenu == MENU_PLAY){
							endgameMenu = MENU_INGAME;
							y=8;
						}
						break;
					case KEYBOARD_UP :
						if(endgameMenu == MENU_INGAME){
							endgameMenu = MENU_PLAY;
							y=9;
						}
						else if(endgameMenu == MENU_PLAY){
							endgameMenu = MENU_INGAME;
							y=8;
						}
						break;
					case KEYBOARD_ENTER :
						if(endgameMenu == MENU_PLAY){ //EXIT
							selectingMenu = MENU_PLAY;
							delwin(leftWindow);
							delwin(rightWindow);
							return selectingMenu;
						}
						else if(endgameMenu == MENU_INGAME){ //REGAME
							selectingMenu = MENU_INGAME;
							delwin(leftWindow);
							delwin(rightWindow);
							return selectingMenu;
						}
						
			}
		}
		}
		attron(A_STANDOUT|A_UNDERLINE); // selected effect

		if(turn%2 == 1)
			mvprintw(3, 40, "1P(O)");
		else if(turn%2 == 0)
			mvprintw(4, 40, "2P(X)");
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_NEXTTURN :
				mvprintw(7, 40, "NEXTTURN");
				break;
			case MENU_INGAME :
				mvprintw(8, 40, "REGAME");
				break;
			case MENU_PLAY :
				mvprintw(9, 40, "EXIT");
				break;

		}

		attroff(A_STANDOUT | A_UNDERLINE);
		mvprintw(y,x,"%c",game[y][x]);
		refresh();
	
		key = getchar();
		
		switch(key){
			case KEYBOARD_DOWN :
				if(selectingMenu == MENU_NEXTTURN){
					selectingMenu = MENU_INGAME;
					y=8; }
				else if(selectingMenu == MENU_INGAME){
					selectingMenu = MENU_PLAY;
					y=9; }
				else if(selectingMenu == MENU_PLAY){
					selectingMenu = MENU_NEXTTURN;
					y=7; }	
				else{
					y+=2;
					if(y==13)
						y=1;
					else if(y==-1)
						y=11;
				}
				break;
			case KEYBOARD_UP :
				if(selectingMenu == MENU_INGAME){
					selectingMenu = MENU_NEXTTURN;
					y=7; }
				else if(selectingMenu == MENU_NEXTTURN){
					selectingMenu = MENU_PLAY;
					y=9; }
				else if(selectingMenu == MENU_PLAY){
					selectingMenu = MENU_INGAME;
					y=8; }
				else{
					y-=2;
					if(y==13)
						y=1;
					else if(y==-1)
						y=11;
				}	
				break;
			case KEYBOARD_LEFT :
					if(x==39){
						selectingMenu=0;
						x-=8;
						y=5;
					}
					x-=4;
					if(x==31)
						x=7;
					else if(x==3)
						x=27;
					break;
			case KEYBOARD_RIGHT :
					x+=4;
					if(x==31){
						selectingMenu=MENU_NEXTTURN;
						x=39;
						y=7;
					}
					else if(x==3)
						x=27;
				break;
			case 'x' :
				x=39;
				y=9;
				selectingMenu = MENU_PLAY;
				break;
			case 'r' :
				x=39;
				y=8;
				selectingMenu = MENU_INGAME;
				break;
			case 'n' :
				x=39;
				y=7;
				selectingMenu = MENU_NEXTTURN;
				break;
			case KEYBOARD_ENTER :
				if (selectingMenu != MENU_PLAY&&selectingMenu != MENU_INGAME && selectingMenu != MENU_NEXTTURN && turn %2 == 1){
					if(game[y][x] == ' '){
						//if(game[y-2][x] == 'o')//1
						//	break;
						if(game[y-2][x] == 'x'){
							if(game[y-4][x] == 'o'){
								game[y-2][x] = 'o';
								game[y][x] = 'o';
								isturn=TRUE;
							}
							else if(game[y-4][x] == 'x'){
								if(game[y-6][x] == 'o'){
									game[y-4][x] = 'o';
									game[y-2][x] = 'o';
									game[y][x]='o';
									isturn=TRUE;								
								}
								else if(game[y-6][x] == 'x'){
									if(game[y-8][x] == 'o'){
										game[y-6][x] = 'o';
										game[y-4][x] = 'o';
										game[y-2][x] = 'o';
										game[y][x] = 'o';
										isturn=TRUE;
									}
									else if(game [y-8][x] == 'x'){
										if(game [y-10][x] == 'o'){
											game[y-8][x] = 'o';
											game[y-6][x] = 'o';
											game[y-4][x] = 'o';
											game[y-2][x] = 'o';
											game[y][x] = 'o';
											isturn=TRUE;
										}
										//else if(game[y-10][x] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
						}
						//else if(game[y-2][x] == 'o')//2
							//break;
						if(game[y+2][x] == 'x'){
							if(game[y+4][x] == 'o'){
								game[y+2][x] = 'o';
								game[y][x] = 'o';
								isturn=TRUE;
							}
							else if(game[y+4][x] == 'x'){
								if(game[y+6][x] == 'o'){
									game[y+4][x] = 'o';
									game[y+2][x] = 'o';
									game[y][x]='o';
									isturn=TRUE;
								}
								else if(game[y+6][x] == 'x'){
									if(game[y+8][x] == 'o'){
										game[y+6][x] = 'o';
										game[y+4][x] = 'o';
										game[y+2][x] = 'o';
										game[y][x] = 'o';
										isturn=TRUE;
									}
									else if(game [y+8][x] == 'x'){
										if(game [y+10][x] == 'o'){
											game[y+8][x] = 'o';
											game[y+6][x] = 'o';
											game[y+4][x] = 'o';
											game[y+2][x] = 'o';
											game[y][x] = 'o';
											isturn=TRUE;
										}
										//else if(game[y+10][x] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
							//else break;											
						}
						if(game[y][x+4] == 'x'){//3
							if(game[y][x+8] == 'o'){
								game[y][x+4] = 'o';
								game[y][x] = 'o';
								isturn=TRUE;
							}
							else if(game[y][x+8] == 'x'){
								if(game[y][x+12] == 'o'){
									game[y][x+8] = 'o';
									game[y][x+4] = 'o';
									game[y][x]='o';
									isturn=TRUE;
								}
								else if(game[y][x+12] == 'x'){
									if(game[y][x+16] == 'o'){
										game[y][x+12] = 'o';
										game[y][x+8] = 'o';
										game[y][x+4] = 'o';
										game[y][x] = 'o';
										isturn=TRUE;
									}
									else if(game [y][x+16] == 'x'){
										if(game [y][x+20] == 'o'){
											game[y][x+16] = 'o';
											game[y][x+12] = 'o';
											game[y][x+8] = 'o';
											game[y][x+4] = 'o';
											game[y][x] = 'o';
											isturn=TRUE;
										}
										//else if(game[y][x+16] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
						}
						if(game[y][x-4] == 'x'){//4
							if(game[y][x-8] == 'o'){
								game[y][x-4] = 'o';
								game[y][x] = 'o';
								isturn=TRUE;
							}
							else if(game[y][x-8] == 'x'){
								if(game[y][x-12] == 'o'){
									game[y][x-8] = 'o';
									game[y][x-4] = 'o';
									game[y][x]='o';
									isturn=TRUE;
								}
								else if(game[y][x-12] == 'x'){
									if(game[y][x-16] == 'o'){
										game[y][x-12] = 'o';
										game[y][x-8] = 'o';
										game[y][x-4] = 'o';
										game[y][x] = 'o';
										isturn=TRUE;
									}
									else if(game [y][x-16] == 'x'){
										if(game [y][x-20] == 'o'){
											game[y][x-16] = 'o';
											game[y][x-12] = 'o';
											game[y][x-8] = 'o';
											game[y][x-4] = 'o';
											game[y][x] = 'o';
											isturn=TRUE;
										}
									//	else if(game[y][x-20] == 'x')
									//		break;
									}
									//else break;
								}
								//else break;
							}
						}
						if(game[y-2][x-4] == 'x'){//5
							if(game[y-4][x-8] == 'o'){
								game[y-2][x-4] = 'o';
								game[y][x] = 'o';
								isturn=TRUE;
							}
							else if(game[y-4][x-8] == 'x'){
								if(game[y-6][x-12] == 'o'){
									game[y-4][x-8] = 'o';
									game[y-2][x-4] = 'o';
									game[y][x]='o';
									isturn=TRUE;
								}
								else if(game[y-6][x-12] == 'x'){
									if(game[y-8][x-16] == 'o'){
										game[y-6][x-12] = 'o';
										game[y-4][x-8] = 'o';
										game[y-2][x-4] = 'o';
										game[y][x] = 'o';
										isturn=TRUE;
									}
									else if(game [y-8][x-16] == 'x'){
										if(game [y-10][x-20] == 'o'){
											game[y-8][x-16] = 'o';
											game[y-6][x-12] = 'o';
											game[y-4][x-8] = 'o';
											game[y-2][x-4] = 'o';
											game[y][x] = 'o';
											isturn=TRUE;
										}
										//else if(game[y-10][x-20] == 'x')
									//		break;
									}
									//else break;
								}
							//	else break;
							}
						}
						if(game[y+2][x-4] == 'x'){//6
							if(game[y+4][x-8] == 'o'){
								game[y+2][x-4] = 'o';
								game[y][x] = 'o';
								isturn=TRUE;
							}
							else if(game[y+4][x-8] == 'x'){
								if(game[y+6][x-12] == 'o'){
									game[y+4][x-8] = 'o';
									game[y+2][x-4] = 'o';
									game[y][x]='o';
									isturn=TRUE;
								}
								else if(game[y+6][x-12] == 'x'){
									if(game[y+8][x-16] == 'o'){
										game[y+6][x-12] = 'o';
										game[y+4][x-8] = 'o';
										game[y+2][x-4] = 'o';
										game[y][x] = 'o';
										isturn=TRUE;
									}
									else if(game [y+8][x-16] == 'x'){
										if(game [y+10][x-20] == 'o'){
											game[y+8][x-16] = 'o';
											game[y+6][x-12] = 'o';
											game[y+4][x-8] = 'o';
											game[y+2][x-4] = 'o';
											game[y][x] = 'o';
											isturn=TRUE;
										}
										//else if(game[y+10][x-20] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
							//else break;											
						}
						if(game[y-2][x+4] == 'x'){//7
							if(game[y-4][x+8] == 'o'){
								game[y-2][x+4] = 'o';
								game[y][x] = 'o';
								isturn=TRUE;
							}
							else if(game[y+4][x+8] == 'x'){
								if(game[y-6][x+12] == 'o'){
									game[y-4][x+8] = 'o';
									game[y-2][x+4] = 'o';
									game[y][x] = 'o';
									isturn=TRUE;
								}
								else if(game[y-6][x+12] == 'x'){
									if(game[y-8][x+16] == 'o'){
										game[y-6][x+12] = 'o';
										game[y-4][x+8] = 'o';
										game[y-2][x+4] = 'o';
										game[y][x] = 'o';
										isturn=TRUE;
									}
									else if(game [y-8][x+16] == 'x'){
										if(game [y-10][x+20] == 'o'){
											game[y-8][x+16] = 'o';
											game[y-6][x+12] = 'o';
											game[y-4][x+8] = 'o';
											game[y-2][x+4] = 'o';
											game[y][x] = 'o';
											isturn=TRUE;
										}
										//else if(game[y-10][x+20] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
							//else break;											
						}
						if(game[y+2][x+4] == 'x'){//8
							if(game[y+4][x+8] == 'o'){
								game[y+2][x+4] = 'o';
								game[y][x] = 'o';
								isturn=TRUE;
							}
							else if(game[y+4][x+8] == 'x'){
								if(game[y+6][x+12] == 'o'){
									game[y+4][x+8] = 'o';
									game[y+2][x+4] = 'o';
									game[y][x] = 'o';
									isturn=TRUE;
								}
								else if(game[y+6][x+12] == 'x'){
									if(game[y+8][x+16] == 'o'){
										game[y+6][x+12] = 'o';
										game[y+4][x+8] = 'o';
										game[y+2][x+4] = 'o';
										game[y][x] = 'o';
										isturn=TRUE;
									}
									else if(game [y+8][x+16] == 'x'){
										if(game [y+10][x+20] == 'o'){
											game[y+8][x+16] = 'o';
											game[y+6][x+12] = 'o';
											game[y+4][x+8] = 'o';
											game[y+2][x+4] = 'o';
											game[y][x] = 'o';
											isturn=TRUE;
										}
										//else if(game[y+10][x+20] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
							//else break;	
										
						}

						//else break;											
					}
					if(isturn){ turn += 1; isturn=FALSE;}
					if(game[y][x] == 'o' || game[y][x] == 'x')
						break;
				}

				else if(selectingMenu != MENU_PLAY&&selectingMenu != MENU_INGAME && selectingMenu != MENU_NEXTTURN && turn %2 == 0){
					if(game[y][x] == ' '){
						//if(game[y-2][x] == 'o')//1
						//	break;
						if(game[y-2][x] == 'o'){
							if(game[y-4][x] == 'x'){
								game[y-2][x] = 'x';
								game[y][x] = 'x';
								isturn=TRUE;
							}
							else if(game[y-4][x] == 'o'){
								if(game[y-6][x] == 'x'){
									game[y-4][x] = 'x';
									game[y-2][x] = 'x';
									game[y][x]='x';
									isturn=TRUE;
								}
								else if(game[y-6][x] == 'o'){
									if(game[y-8][x] == 'x'){
										game[y-6][x] = 'x';
										game[y-4][x] = 'x';
										game[y-2][x] = 'x';
										game[y][x] = 'x';
										isturn=TRUE;
									}
									else if(game [y-8][x] == 'o'){
										if(game [y-10][x] == 'x'){
											game[y-8][x] = 'x';
											game[y-6][x] = 'x';
											game[y-4][x] = 'x';
											game[y-2][x] = 'x';
											game[y][x] = 'x';
											isturn=TRUE;
										}
										//else if(game[y-10][x] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
						}
						//else if(game[y-2][x] == 'o')//2
							//break;
						if(game[y+2][x] == 'o'){
							if(game[y+4][x] == 'x'){
								game[y+2][x] = 'x';
								game[y][x] = 'x';
								isturn=TRUE;
							}
							else if(game[y+4][x] == 'o'){
								if(game[y+6][x] == 'x'){
									game[y+4][x] = 'x';
									game[y+2][x] = 'x';
									game[y][x]='x';
									isturn=TRUE;
								}
								else if(game[y+6][x] == 'o'){
									if(game[y+8][x] == 'x'){
										game[y+6][x] = 'x';
										game[y+4][x] = 'x';
										game[y+2][x] = 'x';
										game[y][x] = 'x';
										isturn=TRUE;
									}
									else if(game [y+8][x] == 'o'){
										if(game [y+10][x] == 'x'){
											game[y+8][x] = 'x';
											game[y+6][x] = 'x';
											game[y+4][x] = 'x';
											game[y+2][x] = 'x';
											game[y][x] = 'x';
											isturn=TRUE;
										}
										//else if(game[y+10][x] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
							//else break;											
						}
						if(game[y][x+4] == 'o'){//3
							if(game[y][x+8] == 'x'){
								game[y][x+4] = 'x';
								game[y][x] = 'x';
								isturn=TRUE;
							}
							else if(game[y][x+8] == 'o'){
								if(game[y][x+12] == 'x'){
									game[y][x+8] = 'x';
									game[y][x+4] = 'x';
									game[y][x]='x';
									isturn=TRUE;
								}
								else if(game[y][x+12] == 'o'){
									if(game[y][x+16] == 'x'){
										game[y][x+12] = 'x';
										game[y][x+8] = 'x';
										game[y][x+4] = 'x';
										game[y][x] = 'x';
										isturn=TRUE;
									}
									else if(game [y][x+16] == 'o'){
										if(game [y][x+20] == 'x'){
											game[y][x+16] = 'x';
											game[y][x+12] = 'x';
											game[y][x+8] = 'x';
											game[y][x+4] = 'x';
											game[y][x] = 'x';
											isturn=TRUE;
										}
										//else if(game[y][x+16] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
						}
						if(game[y][x-4] == 'o'){//4
							if(game[y][x-8] == 'x'){
								game[y][x-4] = 'x';
								game[y][x] = 'x';
								isturn=TRUE;
							}
							else if(game[y][x-8] == 'o'){
								if(game[y][x-12] == 'x'){
									game[y][x-8] = 'x';
									game[y][x-4] = 'x';
									game[y][x]='x';
									isturn=TRUE;
								}
								else if(game[y][x-12] == 'o'){
									if(game[y][x-16] == 'x'){
										game[y][x-12] = 'x';
										game[y][x-8] = 'x';
										game[y][x-4] = 'x';
										game[y][x] = 'x';
										isturn=TRUE;
									}
									else if(game [y][x-16] == 'o'){
										if(game [y][x-20] == 'x'){
											game[y][x-16] = 'x';
											game[y][x-12] = 'x';
											game[y][x-8] = 'x';
											game[y][x-4] = 'x';
											game[y][x] = 'x';
											isturn=TRUE;
										}
									//	else if(game[y][x-20] == 'x')
									//		break;
									}
									//else break;
								}
								//else break;
							}
						}
						if(game[y-2][x-4] == 'o'){//5
							if(game[y-4][x-8] == 'x'){
								game[y-2][x-4] = 'x';
								game[y][x] = 'x';
								isturn=TRUE;
							}
							else if(game[y-4][x-8] == 'o'){
								if(game[y-6][x-12] == 'x'){
									game[y-4][x-8] = 'x';
									game[y-2][x-4] = 'x';
									game[y][x]='x';
									isturn=TRUE;
								}
								else if(game[y-6][x-12] == 'o'){
									if(game[y-8][x-16] == 'x'){
										game[y-6][x-12] = 'x';
										game[y-4][x-8] = 'x';
										game[y-2][x-4] = 'x';
										game[y][x] = 'x';
										isturn=TRUE;
									}
									else if(game [y-8][x-16] == 'o'){
										if(game [y-10][x-20] == 'x'){
											game[y-8][x-16] = 'x';
											game[y-6][x-12] = 'x';
											game[y-4][x-8] = 'x';
											game[y-2][x-4] = 'x';
											game[y][x] = 'x';
											isturn=TRUE;
										}
										//else if(game[y-10][x-20] == 'x')
									//		break;
									}
									//else break;
								}
							//	else break;
							}
						}
						if(game[y+2][x-4] == 'o'){//6
							if(game[y+4][x-8] == 'x'){
								game[y+2][x-4] = 'x';
								game[y][x] = 'x';
								isturn=TRUE;
							}
							else if(game[y+4][x-8] == 'o'){
								if(game[y+6][x-12] == 'x'){
									game[y+4][x-8] = 'x';
									game[y+2][x-4] = 'x';
									game[y][x]='x';
									isturn=TRUE;
								}
								else if(game[y+6][x-12] == 'o'){
									if(game[y+8][x-16] == 'x'){
										game[y+6][x-12] = 'x';
										game[y+4][x-8] = 'x';
										game[y+2][x-4] = 'x';
										game[y][x] = 'x';
										isturn=TRUE;
									}
									else if(game [y+8][x-16] == 'o'){
										if(game [y+10][x-20] == 'x'){
											game[y+8][x-16] = 'x';
											game[y+6][x-12] = 'x';
											game[y+4][x-8] = 'x';
											game[y+2][x-4] = 'x';
											game[y][x] = 'x';
											isturn=TRUE;
										}
										//else if(game[y+10][x-20] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
							//else break;											
						}
						if(game[y-2][x+4] == 'o'){//7
							if(game[y-4][x+8] == 'x'){
								game[y-2][x+4] = 'x';
								game[y][x] = 'x';
								isturn=TRUE;
							}
							else if(game[y+4][x+8] == 'o'){
								if(game[y-6][x+12] == 'x'){
									game[y-4][x+8] = 'x';
									game[y-2][x+4] = 'x';
									game[y][x] = 'x';
									isturn=TRUE;
								}
								else if(game[y-6][x+12] == 'o'){
									if(game[y-8][x+16] == 'x'){
										game[y-6][x+12] = 'x';
										game[y-4][x+8] = 'x';
										game[y-2][x+4] = 'x';
										game[y][x] = 'x';
										isturn=TRUE;
									}
									else if(game [y-8][x+16] == 'o'){
										if(game [y-10][x+20] == 'x'){
											game[y-8][x+16] = 'x';
											game[y-6][x+12] = 'x';
											game[y-4][x+8] = 'x';
											game[y-2][x+4] = 'x';
											game[y][x] = 'x';
											isturn=TRUE;
										}
										//else if(game[y-10][x+20] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
							//else break;											
						}
						if(game[y+2][x+4] == 'o'){//8
							if(game[y+4][x+8] == 'x'){
								game[y+2][x+4] = 'x';
								game[y][x] = 'x';
								isturn=TRUE;
							}
							else if(game[y+4][x+8] == 'o'){
								if(game[y+6][x+12] == 'x'){
									game[y+4][x+8] = 'x';
									game[y+2][x+4] = 'x';
									game[y][x] = 'x';
									isturn=TRUE;
								}
								else if(game[y+6][x+12] == 'o'){
									if(game[y+8][x+16] == 'x'){
										game[y+6][x+12] = 'x';
										game[y+4][x+8] = 'x';
										game[y+2][x+4] = 'x';
										game[y][x] = 'x';
										isturn=TRUE;
									}
									else if(game [y+8][x+16] == 'o'){
										if(game [y+10][x+20] == 'x'){
											game[y+8][x+16] = 'x';
											game[y+6][x+12] = 'x';
											game[y+4][x+8] = 'x';
											game[y+2][x+4] = 'x';
											game[y][x] = 'x';
											isturn=TRUE;
										}
										//else if(game[y+10][x+20] == 'x')
										//	break;
									}
									//else break;
								}
								//else break;
							}
							//else break;	
										
						}

						//else break;											
					}
					if(isturn){ turn += 1; isturn=FALSE; }
					if(game[y][x] == 'o' || game[y][x] == 'x')
						break;

				}
				//turn은 언제 더해줘야되느거지.... x는 다시 복붙하기 		
				else if(selectingMenu == MENU_NEXTTURN){
					turn+=1;	
					selectingMenu = 0;
					x=15; y=5;
					break;				
				}
				else if(selectingMenu == MENU_PLAY){ //EXIT
					delwin(leftWindow);
					delwin(rightWindow);
					return selectingMenu;
				}
				else if(selectingMenu == MENU_INGAME){ //REGAME
					delwin(leftWindow);
					delwin(rightWindow);
					return selectingMenu;
				}
		}
	}
}


int _statisticsMenu(){
	werase(stdscr); // Clear Window
	curs_set(0); // Not need Cursor pointer
	char key; // User Input 
	int selectingMenu = MENU_PLAY; 
	WINDOW *upMenu, *downMenu;
	init_updownWindow(upMenu, downMenu);

	mvprintw(2, 20, "STATISTICS"); //1P
	mvprintw(4, 5, "ID : %s", loginInfo.id);
	if(loginInfo.win + loginInfo.lose != 0)
	{
		mvprintw(6, 3, "WIN : %d / LOSE : %d", loginInfo.win, loginInfo.lose);
		mvprintw(7,10,"(%d %)", (loginInfo.win * 100) / (loginInfo.win + loginInfo.lose));
	}
	else
	{
		mvprintw(6, 5, "WIN : 0 / LOSE : 0");
		mvprintw(7,7,"(0 %)");
	}
	mvprintw(4, 30, "ID : %s", loginInfo2.id); //2P
	if(loginInfo2.win + loginInfo2.lose != 0)
	{
		mvprintw(6, 28, "WIN : %d / LOSE : %d", loginInfo2.win, loginInfo2.lose);
		mvprintw(7,35,"(%d %)", (loginInfo2.win * 100) / (loginInfo2.win + loginInfo2.lose));
	}
	else
	{
		mvprintw(6, 28, "WIN : 0 / LOSE : 0");
		mvprintw(7,35,"(0 %)");
	}
	
	while(1){
		attron(COLOR_PAIR(2));
		mvprintw(11, 23, "BACK");
		
		attron(A_STANDOUT | A_UNDERLINE); // selected effect
		
		// Overwriting menu font
		switch(selectingMenu){
			case MENU_PLAY :
				mvprintw(11, 23, "BACK");
				break;
		}
		
		attroff(A_STANDOUT | A_UNDERLINE);
		
		refresh();
			
		key = getchar();
		
		switch(key){
			case KEYBOARD_ENTER :
				delwin(upMenu);
				delwin(downMenu);
				return MENU_PLAY;
		}
	}
}

void init_updownWindow(WINDOW *upWindow, WINDOW *downWindow)
{
	upWindow = subwin(stdscr, 10, 53, 0, 0);
	wbkgd(upWindow, COLOR_PAIR(1));
	downWindow = subwin(stdscr, 3, 53, 10, 0);
	wbkgd(downWindow, COLOR_PAIR(2));
	attron(COLOR_PAIR(1));
}

void init_scr()
{
	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_CYAN);
}

void saveInfo()
{
	int fd = open("info", O_RDWR);
				
	int bufLength = IDPASSLENGTH + 1 + IDPASSLENGTH + 1 + 3 + 1 + 3 + 1;
	char buf[bufLength]; // ID(15)  PASS(15)  WIN(3)  LOSE(3)   
	char tempID[IDPASSLENGTH], tempPW[IDPASSLENGTH];
	int tempWIN, tempLOSE;
					
	while(read(fd, buf, bufLength) > 0)
	{
		sscanf(buf, "%s %s %d %d", tempID, tempPW, &tempWIN, &tempLOSE);
		if(strcmp(tempID, loginInfo.id) == 0)
		{
			sprintf(buf, "\n%-15s %-15s %-3d %-3d", loginInfo.id, loginInfo.pass, loginInfo.win, loginInfo.lose);
			lseek(fd, (off_t)-bufLength, SEEK_CUR);
			write(fd, buf, bufLength);	
				
			close(fd);
		}

	}
	int fd2 = open("info", O_RDWR);
				
	int bufLength2 = IDPASSLENGTH + 1 + IDPASSLENGTH + 1 + 3 + 1 + 3 + 1;
	char buf2[bufLength2]; // ID(15)  PASS(15)  WIN(3)  LOSE(3)   
	char tempID2[IDPASSLENGTH], tempPW2[IDPASSLENGTH];
	int tempWIN2, tempLOSE2;
	while(read(fd2,buf2,bufLength2)>0)
	{
		sscanf(buf2, "%s %s %d %d", tempID2, tempPW2, &tempWIN2, &tempLOSE2);
		if(strcmp(tempID2, loginInfo2.id) == 0)
		{
			sprintf(buf2, "\n%-15s %-15s %-3d %-3d", loginInfo2.id, loginInfo2.pass, loginInfo2.win, loginInfo2.lose);
			lseek(fd2, (off_t)-bufLength2, SEEK_CUR);
			write(fd2, buf2, bufLength2);	
				
			close(fd2);
		}
	}
}
