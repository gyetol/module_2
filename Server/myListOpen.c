#include "myListOpen.h"
 
int myListOpen(WINDOW *leftwin){ //myListOpen();
	mvwprintw(leftwin, 1, 1, "leftwin");
	system("/bin/ls -a > ./myList.txt");
	int fd=open("./myList.txt", O_RDONLY, O_CREAT, 0444);
	if(fd<0)
	{
		perror("open");
		return -1;
	}
	char buf[BUFSIZ];
	while(1){
		int nRead=read(fd, buf, sizeof(buf));
		if(nRead<0){
			perror("read");
			close(fd);
			return -1;
		}
		else if(nRead==0){
			break;
		}
		mvwprintw(leftwin, 2, 2, "%s", buf);
	}
	close(fd);
	refresh();
	wrefresh(leftwin);
	return 0;
}
