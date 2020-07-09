#include "keyPad.h"

int keyPad(Windows *windows){
	if(windows==NULL){
		perror("windows");
		return -1;
	}
    mvwprintw(windows->consolewin, 2, 1, ">>                                            ");
	wmove(windows->consolewin, 2, 4);
	refresh();
	wrefresh(windows->consolewin);

	int ch;
    noecho();
	WINDOW* win[4];
	win[0]=windows->logwin;
	win[1]=windows->leftwin;
	win[2]=windows->rightwin;
	win[3]=windows->consolewin;
	int now=3;
	int cursor=4;
	int cursor2=4;
	int line=1;
	WINDOW *currentwin=win[now];
	WINDOW *prevwin=win[2];
	wborder(windows->upwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wbkgd(windows->upwin, COLOR_PAIR(3));
	refresh();
	wrefresh(windows->upwin);

	wborder(currentwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wbkgd(currentwin, COLOR_PAIR(2));
	refresh();
	wrefresh(currentwin);
	keypad(stdscr, TRUE);
	char command[80]={0, };
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
				mvwprintw(windows->consolewin, 2, 4, "keyup");
				break;
			case KEY_DOWN:
				mvwprintw(windows->consolewin, 2, 4, "keydown");
				break;
			case KEY_BACKSPACE: //delete문자 했을 경우 (backspace)
				 prevwin=currentwin;
				 now=3;
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
				
				if(line==1){
					if(cursor!=4)
							cursor--;

					mvwprintw(windows->consolewin, 2, cursor, " "); 
					wmove(windows->consolewin, 2, cursor);
				}
				else if(line==2){
					if(cursor2!=4)
						{
							if(cursor2==76)
								mvwprintw(windows->consolewin, 3, 76," ");
							cursor2--;
					  		mvwprintw(windows->consolewin, 3, cursor2, " ");
							wmove(windows->consolewin, 3, cursor2);
						}
					else
						{
							mvwprintw(windows->consolewin, 3, 2, " ");
							mvwprintw(windows->consolewin, 3, 1, " ");
							mvwprintw(windows->consolewin, 2, 76," ");
							line=1;
							wmove(windows->consolewin, 2, cursor);
						}				
				}
				break;
			default:  //add문자 했을 경우
				 prevwin=currentwin;
     			 now=3;
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
			 	
				 if(line==1){
					mvwprintw(windows->consolewin, 2, cursor, "%c", (char)ch);
	
						if(cursor!=76)
							{
								cursor++;
							    wmove(windows->consolewin, 2, cursor);
							}
						else{
								line=2;
								mvwprintw(windows->consolewin, 3, 1, ">>");
								wmove(windows->consolewin, 3, cursor2);
							}
	            }				
				else if(line==2){
					mvwprintw(windows->consolewin, 3, cursor2, "%c", (char)ch);
						if(cursor2!=76)
							{
								cursor2++;
								wmove(windows->consolewin, 3, cursor2);
							}
				}
				break;
		}
		//noecho();
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
