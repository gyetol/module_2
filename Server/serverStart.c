#include "serverStart.h"
void __quit(const char * msg,int line){
	char buf[BUFSIZ];
	//sprintf(buf,"%s(%d)",msg,line);
	perror(buf);
	exit(1);
}
void* keypadThread(void *arg){
	int *res=calloc(1, sizeof(int));
	Windows* windows=(Windows*)arg;
	mvwprintw(windows->consolewin, 2, 4, "keypadThread create success");
	refresh();
	wrefresh(windows->consolewin);
	if(keyPad(windows)==-1)
	{
		perror("keyPad");
		*res=-1;
		return res;
	}
	*res=0;
	return res;
}
void* responseThread(void * arg){
	int *res=calloc(1, sizeof(int));
	ResponseInfo* resInfo=(ResponseInfo*)arg;
	if(response(resInfo->sock, &(resInfo->reqInfo.type),&(resInfo->reqInfo.path),&(resInfo->reqInfo.ip))==-1)
	{
		*res=1;
		return res;
	}
	//printf("response 함수 갔다오기 성공\n");
	*res=0;
	return res;
}

int serverStart(char *ip){
	if(ip==NULL){
		perror("serverIp");
		return -1;
	}

////////////////////////////////////     color init start    ///////////////////////////////////////////////////////////////

  initscr();
  cbreak();

  start_color();

  if(can_change_color())
  {
      init_color(COLOR_WHITE, 999, 999, 893);
      init_color(COLOR_YELLOW, 999,999,400);
      init_color(COLOR_RED, 756, 537, 415);
      //    init_color(COLOR_YELLOW, 999, 999, 980);
      //내가 원하던 색깔 편집기능 되는지 확인+편집 동시에
  }
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_BLACK, COLOR_YELLOW);
  init_pair(3, COLOR_BLACK, COLOR_RED);
  wbkgd(stdscr,COLOR_PAIR(1));
  

///////////////////////////////////    color init finish     ///////////////////////////////////////////////////////////////

///////////////////////////////////		screen	init start   	///////////////////////////////////////////////////////////

  WINDOW *front=newwin(24, 80, 0, 0);
  wbkgd(front, COLOR_PAIR(2));
  mvwprintw(front,9,30, "%s","           v");
  mvwprintw(front,10,30,"%s","fileDanzi (ll):");
  refresh();
  wrefresh(front); 
  getch();

 WINDOW *upwin = newwin(3, 80, 0, 0);
 wbkgd(upwin,COLOR_PAIR(1));
 wborder(upwin, 0, 0, 0, 0, 0, 0, 0, 0);
 mvwprintw(upwin,1, 1, "fileDanzi");
 mvwprintw(upwin, 1, 64, "%s", ip);
 refresh();
 wrefresh(upwin);

 WINDOW *logwin=newwin(5, 80, 3, 0);
 wbkgd(logwin,COLOR_PAIR(1));
 wborder(logwin, 0, 0, 0, ' ', 0, 0, ' ', ' ');
 mvwprintw(logwin,1, 1, "[server] is running : %s...", ip);
 refresh();
 wrefresh(logwin);

 WINDOW *leftwin=newwin(11, 40, 8, 0);
 wbkgd(leftwin,COLOR_PAIR(1));
 scrollok(leftwin, TRUE);
 myListOpen(leftwin);
 wborder(leftwin, 0, 0, 0, 0, 0, 0, 0, 0);
 refresh(); 
 wrefresh(leftwin);

 WINDOW *rightwin=newwin(11, 40, 8, 40);
 wbkgd(rightwin,COLOR_PAIR(1));
 scrollok(rightwin, TRUE);
 listOpen(rightwin);
 wborder(rightwin, 0, 0, 0, 0, 0, 0, 0, 0); 
 refresh();
 wrefresh(rightwin);

 
 WINDOW *consolewin=newwin(5, 80, 19, 0);
 wbkgd(consolewin,COLOR_PAIR(1));
 wborder(consolewin, 0, 0, 0, 0, 0, 0, 0, 0);
 mvwprintw(consolewin, 1, 1,"console");
 mvwprintw(consolewin, 2, 1, ">>");
 refresh();
 wrefresh(consolewin);
////////////////////////////////////	 screen init finish	 /////////////////////////////////////////////////////////

	int ssock=socket(PF_INET,SOCK_STREAM,0);
	if(ssock==-1)
		err_quit("socket");
	struct sockaddr_in saddr={0,};
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(DATA_PORT); 
	saddr.sin_addr.s_addr=inet_addr(ip);	
	
	int value=1;
	if(setsockopt(ssock,SOL_SOCKET,SO_REUSEADDR,(char*)&value,sizeof(value))==-1)
		err_quit("setsockopt");

	if(bind(ssock,(struct sockaddr *)&saddr,sizeof(saddr))==-1)
		err_quit("bind");

	if(listen(ssock,LISTENQ)==-1)
		err_quit("listen");

    ////////////log파일 기록
	char buf[100]="echo '[server] is running :";
    strcat(buf, ip);
    strcat(buf, " ' >>./log/");
	strcat(buf, "2020_07_09");
	strcat(buf, ".txt");
    system(buf);
    ////////////log파일 기록
/*	time_t tt;
	time(&tt);
	struct tm *tm;
	tm = gmtime(&tt);
	printf("%d년 / %d월 / %d일 ",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
*/

 // 1. 하드코딩으로 53라인 날짜 해놓은거 실제 그날 날짜로 바꿔야됨
//	 (그러기위해 함수 얻는 중이었음 이떄 7월 말고 07월로 나오는 형식 지정자 찾아야됨)
//  2. 완료되면 더 추가해야할 로그들 찾아서 위와 같이 시스템 함수로 추가	

//printf("[server] is running : %s\n\n", ip);
	int efd=epoll_create(1); 
	if(efd==-1)
		err_quit("epoll_create");

	struct epoll_event event; 
	event.events=EPOLLIN||EPOLLOUT;
	event.data.fd=ssock;
	if(epoll_ctl(efd,EPOLL_CTL_ADD,ssock,&event)==-1)
		err_quit("epoll_ctl");

	struct epoll_event events[EPOLL_SIZ];
//////////////////////////////////////////////////////////////////////////////////////////////////////
        //keypad thread create for console window
        Windows windows;
        windows.upwin=upwin;
        windows.logwin=logwin;
        windows.leftwin=leftwin;
        windows.rightwin=rightwin;
        windows.consolewin=consolewin;

        int *tret_s=0;
        pthread_t tid_s;
        if(pthread_create(&tid_s,NULL,keypadThread, &windows)==EAGAIN)
            err_quit("pthread_create");
///////////////////////////////////////////////////////////////////////////////////////////////////////
	while(1){
		int nEvent=epoll_wait(efd,events,128,-1);
		if(nEvent<0){
			if(errno==EINTR) //키패드 쓰레드에서 system함수 사용시 커널같이써서인지 epoll wait interrupt 에러나므로 
				continue;	//방해 들어왔을 경우 다시 위로 가서 기다린다는 의미로 사용
			else 
				err_quit("epoll_wait");
		}

		else if(nEvent==0)
			continue;

		for(int i=0;i<nEvent;i++){
			if(events[i].data.fd==ssock) {
				struct sockaddr_in caddr = {0,};
                int caddr_len = sizeof(caddr);
                int csock = accept(ssock, (struct sockaddr *) &caddr, &caddr_len);
                if (csock < 0)
                    err_quit("accept");
 				mvwprintw(logwin,2, 1, "[server] %s(client) is connected...", inet_ntoa(caddr.sin_addr));
 				refresh();
 				wrefresh(logwin);

              // printf("[server]%s(client) is  connected... and cSock is %d\n", inet_ntoa(caddr.sin_addr), csock);	
			  // printf("connect당시의 cSock : %d\n", csock);
				event.events = EPOLLIN;
				event.data.fd = csock;
				int epollRes=epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event);
				if(epollRes==-1){
					clock_t start;
					clock_t now;
					for(int i=0;i<10;i++){
						start=clock();
						while(1){
							now=clock();
							if((now-start)>=5000000L)
								break;
						}
					    epollRes=epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event);
						if(i==9&&epollRes==-1){
							perror("epoll_ctl_add");
							return -1;
						}
					}
				}
				//printf("wait success\n");
            }
			else{
				if(events[i].events==EPOLLIN){
				    //this is for client
					mvwprintw(logwin,3,1,"[server] client send request ...\n");
					refresh();
					wrefresh(logwin);
					int cSock=events[i].data.fd; 
					//printf("cSock=%d", cSock);
					char * type;
					char * path;
					char * ip;
					ResponseInfo resInfo={0,};
					while(1){
						if(getRequest(cSock,&type,&path,&ip)==-1)
							continue;
						resInfo.reqInfo.type=type;
						resInfo.reqInfo.path=path;
						resInfo.reqInfo.ip=ip;
						resInfo.sock=cSock;
						//mvwprintw(logwin,3,1,"type : %s, path : %s, ip : %s\n", type, path, ip);
						//refresh();
						//wrefresh(logwin);
						if(strcmp(type,"quit")==0)
						{
							if(epoll_ctl(efd,EPOLL_CTL_DEL,events[i].data.fd,NULL)==-1)
							  	err_quit("epoll_ctl");
							mvwprintw(logwin,3,1,"[ client ] : %s disconnected", *ip);
							refresh();
							wrefresh(logwin);
							break;
						}
					   int * tret=0;
						pthread_t tid;
						if(pthread_create(&tid,NULL,responseThread,&resInfo)==EAGAIN)
							err_quit("pthread_create");
						if(pthread_join(tid,(void**)&tret)!=0)
							err_quit("pthread_join");
						if(*tret==0)
						{
							free(tret);
							break;
						}

	//////////////////////////////////////////////				//keypad 쓰레드 기다리기
						if(pthread_join(tid_s, (void**)&tret_s)!=0)
							err_quit("pthread_join");
							if(*tret_s==0)
						{
							free(tret_s);
							break;
						}
///////////////////////////////////////////////////////////////////////////////////////////
					}
					//printf("도달");
				}
				else{
					if(epoll_ctl(efd,EPOLL_CTL_DEL,events[i].data.fd,NULL)==-1)
					  err_quit("epoll_ctl");
				}
			}
		}//for문 괄호
	}//while1괄호
	delwin(upwin);
	delwin(logwin);
	delwin(leftwin);
	delwin(rightwin);
	delwin(consolewin);
	endwin();
	close(ssock);
	return 0;
}
