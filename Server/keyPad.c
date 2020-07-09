#include "keyPad.h"

int keyPad(Windows *windows){
	if(windows==NULL){
		perror("windows");
		return -1;
	}
	getch();
    mvwprintw(windows->consolewin, 2, 1, ">> keyPad called                                      ");
	refresh();
	wrefresh(windows->consolewin);

	int ch;
	noecho();
	keypad(stdscr, TRUE);
	while((ch=getch())!='x')
	{
		switch(ch)
		{
			case KEY_LEFT:
				mvwprintw(windows->consolewin, 2, 1, "keyleft");
				break;
			case KEY_RIGHT:
				mvwprintw(windows->consolewin, 2, 1, "keyright");
				break;
			case KEY_UP:	
				mvwprintw(windows->consolewin, 2, 1, "keyup");
				break;
			case KEY_DOWN:
				mvwprintw(windows->consolewin, 2, 1, "keydown");
				break;
			default:
				mvwprintw(windows->consolewin, 2, 1, "nonset key");
				break;
		}
		refresh();
		wrefresh(windows->consolewin);
	}
	delwin(windows->upwin);
	delwin(windows->logwin);
	delwin(windows->leftwin);
	delwin(windows->rightwin);
	delwin(windows->consolewin);
	endwin();
	return 0;
}
/*int main(Windows *windows){
	keyPad(windows);
return 0;
}*/
