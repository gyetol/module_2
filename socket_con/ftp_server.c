
//Echo_server
#include <sys/types.h>       
#include <sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <fcntl.h>
#include <sys/times.h>
#include<stdlib.h>
#include<string.h>
#include <signal.h>
#include <sys/epoll.h>

void __quit(const char * msg,int line){
	char buf[BUFSIZ];
	sprintf(buf,"%s(%d)",msg,line);
	perror(buf);
	exit(1);
}

#define err_quit(msg) __quit(msg,__LINE__)
#define LISTENQ (10)
#define EPOLL_SIZ (128)

int main(){
	int ssock=socket(PF_INET,SOCK_STREAM,0);
	if(ssock==-1)
		err_quit("socket");

	struct sockaddr_in saddr={0,};
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(8080); 
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	int value=1;
	if(setsockopt(ssock,SOL_SOCKET,SO_REUSEADDR,(char*)&value,sizeof(value))==-1)
		err_quit("setsockopt");

	if(bind(ssock,(struct sockaddr *)&saddr,sizeof(saddr))==-1)
		err_quit("bind");

	if(listen(ssock,LISTENQ)==-1)
		err_quit("listen");
	printf("[server] running...\n");

	int efd=epoll_create(1); 
	if(efd==-1)
		err_quit("epoll_create");

	struct epoll_event event; 
	event.events=EPOLLIN; 
	event.data.fd=ssock;
	if(epoll_ctl(efd,EPOLL_CTL_ADD,ssock,&event)==-1)
		err_quit("epoll_ctl");

	struct epoll_event events[EPOLL_SIZ];
	char buf[BUFSIZ];
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

                event.events = EPOLLIN;
                event.data.fd = csock;
                if (epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event) == -1)
                    err_quit("epoll_ctl");
                continue;
            }
			else { //this is for client

				
				if(get_command(csock)==-1)
					err_quit("get_command");


			}
		}
	}
	close(ssock);
	return 0;
}
#endif	

