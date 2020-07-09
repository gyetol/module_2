#include "listOpen.h"

int listOpen(WINDOW *rightwin){
	mvwprintw(rightwin, 1, 1, "rightwin");
	int chNum=0;
    int fd = open("./list.txt",O_RDONLY,0444);	
	if(access("./home", -0)==-1)
		system("/bin/mkdir home");
	chdir("./home");
	chNum++;
	if(fd==-1){
		perror("open");
		return -1;
	}
	char buf[BUFSIZ];
	while(1){
		int nRead=read(fd, buf, sizeof(buf));
		if (nRead<0){
			perror("read");
			return -1;
		}
		else if (nRead==0){
			break;
		}
	}
		char *savePtr;
		char *saveExtract;
		char *saveStr;
		char *ptr=strtok_r(buf, "\n", &savePtr);//while문에는\n단위로 자른 한줄씩 들어감
		while(ptr!=NULL)
		{
			if(ptr[0]!='d'&&ptr[0]!='-')
				ptr=strtok_r(NULL, "\n", &savePtr);
			else
			{  
				char *extract=strtok_r(ptr, " ", &saveExtract);
				for (int i=0;i<8;i++)
					extract=strtok_r(NULL, " ", &saveExtract);
					char *name=extract;
					if(ptr[0]=='d')
					{
						wprintw(rightwin, "+%s",name);
						refresh();
						wrefresh(rightwin);
					}
					else if(ptr[0]=='-')
					{
						wprintw(rightwin, "-%s",name);
						refresh();
						wrefresh(rightwin);
					}
			ptr=strtok_r(NULL, "\n", &savePtr);
			}
		}
		chdir("..");
		close(fd);
		return 0;
	}
