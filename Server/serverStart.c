#include "serverStart.h"

/////////////////////////////////////////////////////
/// to print errMessage and quit process
/// input : msg(출력할 에러 메세지), line(에러가 발생한 줄 line Number)
/// return : void
//////////////////////////////////////////////////////
void __quit(const char * msg,int line){
	char buf[BUFSIZ];
	sprintf(buf,"%s(%d)",msg,line);
	perror(buf);
	exit(1);
}

///////////////////////////////////////////////////////////////
/// 이벤트가 발생한 클라이언트에게 응답을 하는 thread
/// input : void *
/// return : void
////////////////////////////////////////////////////////////////
/*void* responseThread(void * arg){
	ResponseInfo* resInfo=(ResponseInfo*)arg;
	if(response(resInfo->reqInfo.type,resInfo->reqInfo.path,resInfo->reqInfo.ip,resInfo.sock)==-1)
		pthread_exit(1);
	pthread_exit(0);
}*/

//////////////////////////////////////////////////////////////////
/// 서버소켓을 열고 클라이언트들의 접속을 기다리는 함수
/// input : char * ip (서버의 ip)
/// return : int (오류코드)
////////////////////////////////////////////////////////////////////
int serverStart(char *ip){
	if(ip==NULL){
		perror("serverIp");
		return -1;
	}

	int ssock=socket(PF_INET,SOCK_STREAM,0);
	if(ssock==-1)
		err_quit("socket");

	struct sockaddr_in saddr={0,};
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(PORT); 
	//saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_addr.s_addr=htonl(ip);
	
	int value=1;
	if(setsockopt(ssock,SOL_SOCKET,SO_REUSEADDR,(char*)&value,sizeof(value))==-1)
		err_quit("setsockopt");

	if(bind(ssock,(struct sockaddr *)&saddr,sizeof(saddr))==-1)
		err_quit("bind");

	if(listen(ssock,LISTENQ)==-1)
		err_quit("listen");
	 printf("[server] is running : %s\n\n", ip);
	///////////////////////////////////////////////////////////////////////////////////////
	 //여기까진 디버깅 검증 완료
    ///////////////////////////////////////////////////////////////////////////////////////
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
			if(events[i].data.fd=ssock) {
                struct sockaddr_in caddr = {0,};
                int caddr_len = sizeof(caddr);
                int csock = accept(ssock, (struct sockaddr *) &caddr, &caddr_len);
                if (csock < 0)
                    err_quit("accept");
                printf("[server]%s(client) is  connected...\n", inet_ntoa(caddr.sin_addr));
			}}	}//////////////////////////////////////////////////////////////////////////////////////////////////////////나중에 이괄호 지워야됨		
                /*event.events = EPOLLIN;
                event.data.fd = csock;
                if (epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event) == -1)
                    err_quit("epoll_ctl");
                continue;
            }
			else { //this is for client
				printf("[server] client connected ...\n");
				int cSock=events[i].data.fd;
				int conFlag;
				char * type;
				char * path;
				char * ip;
				ResponseInfo resInfo={0,};

				while(1){
					if(getReqeust(cSock,&conFlag,&type,&path,&ip)==-1)
						continue;
					if(conFlag!=1)
						break;

					resInfo.reqInfo.type=type;
					resInfo.reqInfo.path=path;
					resInfo.reqInfo.ip=ip;
					resInfo.sock=cSock;

					int * tret=0;
					pthread_t tid;
					if(pthread_create(&tid,NULL,responseThread,&resInfo)==EAGAIN)
						err_quit("pthread_create");
					if(pthread_join(tid,(void**)&tret)!=0)
						err_quit("pthread_join");
					if(*tret==0)
						break;	
				}
				if(epoll_ctl(efd,EPOLL_CTL_DEL,cSock,NULL)==-1)
						err_quit("epoll_ctl");
			}
		}
	}
	close(ssock);
	*/
	return 0;
}
