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
		int nEvent=epoll_wait(efd,events,128,-1);
		if(nEvent<0)
			err_quit("epoll_wait");
		else if(nEvent==0)
			continue;
		for(int i=0;i<nEvent;i++){
			if(events[i].data.fd==ssock) {
                struct sockaddr_in caddr = {0,};
                int caddr_len = sizeof(caddr);
                int csock = accept(ssock, (struct sockaddr *) &caddr, &caddr_len);
                if (csock < 0)
                    err_quit("accept");
                printf("[server]%s(client) is  connected...\n", inet_ntoa(caddr.sin_addr));	
				event.events = EPOLLIN;
				event.data.fd = csock;
				printf("c\n");
                if(epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event)==-1)
					err_quit("epoll_ctl");
            }
			else{
			   //this is for client
				printf("[server] client send request ...\n");
				int cSock=events[i].data.fd; 
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
     ///////////////////////////////////////////////////////////////////////////////////////
    //여기까진 디버깅 검증 완료
   ///////////////////////////////////////////////////////////////////////////////////////		
				    int * tret=0;
					pthread_t tid;
					if(pthread_create(&tid,NULL,responseThread,&resInfo)==EAGAIN)
						err_quit("pthread_create");
					if(pthread_join(tid,(void**)&tret)!=0)
						err_quit("pthread_join");
					if(*tret!=0)
						break;
				getchar();	
				}
				if(epoll_ctl(efd,EPOLL_CTL_DEL,cSock,NULL)==-1)
						err_quit("epoll_ctl");
			printf("도달");
			getchar();
			}
		}//for문 괄호
	}//while1괄호
	close(ssock);
	*res=0;
	return res;
}
