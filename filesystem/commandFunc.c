#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "commandFunc.h"



// return 0 : 정상종료
// return -1: 비정상종료

int doRemove(char **srcPath, int len, char **msg){
	char answer;
	
	if(srcPath == NULL){
		*msg = "argument is null";
		return -1;
	}
	if(len <=0){
		*msg = "The number of selected files is zero or negative";
		return -1;
	}

	while(1){
		printf("정말로 삭제하시겠습니까?\n");
		answer = getchar();
		if(answer == 'y' || answer == 'Y'){
			break;
		}
		else if(answer == 'n' || answer == 'N'){
			return 0;
		}
		else{;}
	}
	
	pid_t pid[len];
	int childStatus;

	for(int i=0; i<len;i++){
		pid[i]=fork();
		if(pid[i]==0){
			if(execl("/bin/rm","rm",*(srcPath+i),"-r",NULL)==-1){
			perror("execl");
			return -1;
			}
			exit(EXIT_SUCCESS);
		}
	}

	for(int i=0; i<len; i++){
		pid_t terminatedChild = wait(&childStatus);
		if(WIFEXITED(childStatus)){
			printf("child %d has terminated : %d\n",terminatedChild,WEXITSTATUS(childStatus));
		}
		else{
			printf("child %d has terminated abnormally\n",terminatedChild);
		}
	}
	
	
	
	return 0;
}
