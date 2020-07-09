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
	WINDOW* win[4];
	win[0]=windows->logwin;
	win[1]=windows->leftwin;
	win[2]=windows->rightwin;
	win[3]=windows->consolewin;
	int now=3;
	WINDOW *currentwin=win[now];
	WINDOW *prevwin=win[2];
	noecho();
	keypad(stdscr, TRUE);
	while((ch=getch())!='x')
	{
		switch(ch)
		{
			case KEY_LEFT:
				prevwin=currentwin;
				if(now==0)
					now=3;
				else
					now--;
				currentwin=win[now];
				if(prevwin==windows->logwin)
					wborder(prevwin, 0, 0, 0, ' ', 0, 0, ' ', ' ');
				else
					wborder(prevwin, 0, 0, 0, 0, 0, 0, 0, 0);
				wborder(currentwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				wbkgd(prevwin, COLOR_PAIR(1));
				wbkgd(currentwin, COLOR_PAIR(2));
				refresh();
				wrefresh(prevwin);
				wrefresh(currentwin);
				break;
			case KEY_RIGHT:
				prevwin=currentwin;
				if(now==3)
					now=0;
				else
					now++;
				currentwin=win[now];
			    if(prevwin==windows->logwin)
					wborder(prevwin, 0, 0, 0, ' ', 0, 0, ' ', ' ');
				else
					wborder(prevwin, 0, 0, 0, 0, 0, 0, 0, 0);
				wborder(currentwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				wbkgd(prevwin, COLOR_PAIR(1));
				wbkgd(currentwin, COLOR_PAIR(2));
				refresh();
				wrefresh(prevwin);
				wrefresh(currentwin);
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
