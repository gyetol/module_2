#include "myListOpen.h"
 
int myListOpen(WINDOW *leftwin){ //myListOpen();
	char *directories[100];
	char *files[100];
	int dNum=0;
	int fNum=0;
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
                       directories[dNum]=name;
                       dNum++;
                   }
                   else if(ptr[0]=='-')
                   {
                       files[fNum]=name;
                       fNum++;
                   }
           ptr=strtok_r(NULL, "\n", &savePtr);
           }
       }

       for(int i=dNum-1;i>=0;i--)
       {
           wprintw(leftwin, " DIR     %s", directories[i]);
           refresh();
           wrefresh(leftwin);
           winsertln(leftwin);
           wprintw(leftwin,"\r");
       }

       for(int i=fNum-1;i>=0;i--)
       {
           wprintw(leftwin, " FILE    %s",files[i]);
           refresh();
           wrefresh(leftwin);
           winsertln(leftwin);
           wprintw(leftwin,"\r");
       }
}
	close(fd);
	refresh();
	wrefresh(leftwin);
	return 0;
}
