//Echo Client
#include <sys/types.h>       
#include <sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
	int sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock==-1){
		perror("socket");
		return -1;
	}


	struct sockaddr_in addr={0,};
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8080);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");


	if(connect(sock,(struct sockaddr*)&addr,sizeof(addr))==-1){
		perror("connect");
		return -1;
	}

	char buf[BUFSIZ];
	int nRead=read(0,buf,sizeof(buf));
	if(nRead<0){
		perror("read");
		return -1;
	}
	else if(nRead==0){
		return -1;
	}

	//buf[nRead]='\0';
	write(sock,buf,nRead);

	nRead=read(sock,buf,sizeof(buf));
	if(nRead<0){
		perror("read");
		return -1;
	}
	else if(nRead==0){
		return -1;
	} //서버가 끊겨서 아무것도 못함

	buf[nRead]='\0';
	fputs(buf,stdout);

	close(sock);
	return 0;
}

	
