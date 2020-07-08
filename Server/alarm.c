#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int signalbone();
void func();
void func(){
	printf("func\n");
}

void sigHandler(int signo){
	printf("SIGALRM!\n");
	func();
	alarm(1);
}

int signalbone(){
	if(signal(SIGALRM, sigHandler)==SIG_ERR) {
				perror("signal");
				return -1;
	}
	alarm(1);
	while(1);
	return 0;
}

int main(){
	if(signalbone()==-1)
	{
		perror("signalbone");
		return -1;
	}
	return 0;
}
