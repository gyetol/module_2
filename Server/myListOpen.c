#include "myListOpen.h"
 
int myListOpen(WINDOW *leftwin){ //myListOpen();
	system("/bin/ls -alR > ./myList.txt");
	int fd=open("./myList.txt", O_RDONLY, O_CREAT, 0444);
	if(fd<0)
	{
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
                        wprintw(leftwin, " DIR    %s",name);
                        refresh();
                        wrefresh(leftwin);
                        winsertln(leftwin);
                        wprintw(leftwin,"\r");

                    }
                    else if(ptr[0]=='-')
                    {
                        wprintw(leftwin, " FILE    %s",name);
                        refresh();
                        wrefresh(leftwin);
                        winsertln(leftwin);
                        wprintw(leftwin, "\r");
                    }
            ptr=strtok_r(NULL, "\n", &savePtr);
            }
        }
}
	close(fd);
	refresh();
	wrefresh(leftwin);
	return 0;
}
