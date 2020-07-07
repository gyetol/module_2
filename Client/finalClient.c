#include "commonNucurses.h"
 #include <unistd.h>
 #include <stdio.h>
 #include <errno.h>
 #include <pthread.h>
 #include <unistd.h>
 #include <stdlib.h>

 #include "myListOpen.h"
 #include "clientStart.h"
 #include "doCommand.h"
 #include "commandFunc.h"


 char * sampleFiles[] = {
         "this is file 1", "this is file 2", "this is file 3", "this is file 4",
         "this is file 5", "this is file 6", "this is file 7", "this is file 8",
         "this is file 9", "this is file 10", "this is file 11", "this is file 12",
         "this is file 13", "this is file 14", "this is file 15", "this is file 16"
 };


 int main(){

     char ip[BUFSIZ];
     ResInfo resInfo={0,};

     init_scr();
     int sock = 0;
     char * ipAddress = "";
     int thisMenu = MENU_MAIN;
     int * selected = NULL;

      while (thisMenu != MENU_EXIT){
      switch (thisMenu) {
          case MENU_MAIN :
              thisMenu = IP_insert_Page(&ipAddress);
              break;
          case MENU_FIRSTWINODW :
          case MENU_SECONDWINDOW :
          case MENU_THIRDWINDOW :
          case MENU_FOURTHWINDOW :
              thisMenu = print_Selected_Page(MODE_CLIENT, thisMenu, sampleFiles, selected, 16, "CLIENT PATH", "SERVER PATH");
              break;
          case MENU_IP_INSERT :
          case MENU_FTP_PAGE:
              thisMenu = FTP_Main_Page(MODE_CLIENT, "CLIENT PATH", "SERVER PATH");
              break;
          case MENU_IP_MANAGE:
              //
              break;
          case MENU_HELP:
              //
break;
          case MENU_HISTORY:
              //
              break;
      }
 }

      //to do when exit
      close(sock);
      endwin();
      return 0;
 }

 int IP_insert_Page(const char **ip){
      if(ip==NULL){
      perror("scanf");
      return -1;
  }


  if(myListOpen()==-1){
      fprintf(stderr,"error in myListOpen\n");
      return -1;
  }


  int sock=0;
  if(clientStart(ip,&sock)==-1||sock==0){
      fprintf(stderr,"error in clientStart\n");
      return -1;
  }
  resInfo.sock=sock;

  //자기 ip뽑아내기-----------------------------------
  char * myIp;
  struct ifaddrs* addrs;
  if(getifaddrs(&addrs)==-1){
      perror("getifaddrs");
      return -1;
  }
  struct ifaddrs* tmp = addrs;

  while (tmp)
  {
      if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
      {
          struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
          myIp=inet_ntoa(pAddr->sin_addr);
      }

      tmp = tmp->ifa_next;
  }
  freeifaddrs(addrs);
INSERT –

resInfo.ip=myIp;//resInfo= {sock,ip};
 printf("(client.c)resInfo.ip==myIp : %s\n",resInfo.ip);


 if(doCommand(&resInfo)==-1){
     fprintf(stderr,"error in doCommand\n");
     return -1;
 }

 close(sock);
 return 0;
}


