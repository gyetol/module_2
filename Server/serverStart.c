#include "serverStart.h"
void __quit(const char * msg,int line){
	char buf[BUFSIZ];
	sprintf(buf,"%s(%d)",msg,line);
	perror(buf);
	exit(1);
}

void* responseThread(void * arg){
	int *res=calloc(1, sizeof(int));
	ResponseInfo* resInfo=(ResponseInfo*)arg;
	if(response(resInfo->sock, &(resInfo->reqInfo.type),&(resInfo->reqInfo.path),&(resInfo->reqInfo.ip))==-1)
	{
		*res=1;
		return res;
	}
	printf("response 함수 갔다오기 성공\n");
	*res=0;
	return res;
}

void *serverStart(void *arg){
	int *res;
	if(arg==NULL){
		perror("serverIp");
		*res=-1;
		return res;
	}
	char* ip=(char *)arg;
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
	strcat(buf, "2020_07_08");
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

printf("[server] is running : %s\n\n", ip);
	int efd=epoll_create(1); 
	if(efd==-1)
		err_quit("epoll_create");

	struct epoll_event event; 
	event.events=EPOLLIN; 
	event.data.fd=ssock;
	if(epoll_ctl(efd,EPOLL_CTL_ADD,ssock,&event)==-1)
		err_quit("epoll_ctl");

	struct epoll_event events[EPOLL_SIZ];
	while(1){
		getchar();
		int nEvent=epoll_wait(efd,events,128,-1);
		if(nEvent<0)
			err_quit("epoll_wait");
		else if(nEvent==0)
			continue;
		for(int i=0;i<nEvent;i++){
			if(events[i].data.fd==ssock) {
                getchar();
				struct sockaddr_in caddr = {0,};
                int caddr_len = sizeof(caddr);
                int csock = accept(ssock, (struct sockaddr *) &caddr, &caddr_len);
				printf("accept당시의 cSock : %d\n", csock);
                if (csock < 0)
                    err_quit("accept");
                printf("[server]%s(client) is  connected... and cSock is %d\n", inet_ntoa(caddr.sin_addr), csock);	
				printf("connect당시의 cSock : %d\n", csock);
				getchar();
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
						    *res=-1;
							return res;
						}
					}
				}
				printf("wait success\n");
            }
			else{
			   //this is for client
				printf("[server] client send request ...\n");
				int cSock=events[i].data.fd; 
				printf("cSock=%d", cSock);
				getchar();
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
					printf("type : %s, path : %s, ip : %s\n", type, path, ip);
					if(strcmp(type,"quit")==0)
					{
			   			if(epoll_ctl(efd,EPOLL_CTL_DEL,cSock,NULL)==-1)
      	 	 			  err_quit("epoll_ctl");
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
					getchar();	
				}
				printf("도달");
				getchar();
			}
		}//for문 괄호
	
	}//while1괄호
	close(ssock);
	*res=0;
	return res;
}
