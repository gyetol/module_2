#include "keyPad.h"

int keyPad(Windows *windows){
	getch();
    mvwprintw(windows->consolewin, 2, 1, ">> keyPad called                                      ");
	refresh();
	wrefresh(windows->consolewin);
	return 0;
}
/*int main(Windows *windows){
	keyPad(windows);
return 0;
}*/
