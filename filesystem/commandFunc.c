#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <fcntl.h>
#include "commandFunc.h"

///////////////////////////////////////////////////
//* to move file or directory
// return 0 : exit normally
// return -1: exit abnormally
// srcPath: char* array (files' path to move)
// len: length of array
// msg: we can write message in it
int doMove(char **srcPath, int len,char *destPath, char **msg){
	
	if(srcPath == NULL){
		*msg = "argument is null";
		return -1;
	}
	if(len <=0){
		*msg = "the number of selected files is zero or negative";
		return -1;
	}

	if((strcmp(*srcPath,".")==0) || (strcmp(*srcPath,"..")==0)){
		*msg = "can't move '.' or '..' directory";
		return -1;
	}

	char answer;
	const char *check = "정말로 이동하시겠습니까?(y/n)";

	while(1){
		printf("%s\n",check);
		answer = getchar();
		if(answer == 'y' || answer == 'Y'){
			break;
		}
		else if(answer == 'n' || answer == 'N'){
			return 0;
		}
		else{myflush();}
	}

	pid_t pid[len];
	int childStatus;

	for(int i =0; i<len; i++){
		pid[i]=fork();
		if(pid[i]==0){
			if(execl("/bin/mv","mv",*(srcPath+i),destPath,"-i",NULL)==-1){
				perror("execl");
				*msg = "error occurrence!";
				return -1;
			}
			exit(EXIT_SUCCESS);
		}

	}
	for(int i = 0; i<len; i++){
		pid_t terminatedChild = wait(&childStatus);
		if(WIFEXITED(childStatus)){
			printf("child %d has terminated : %d\n", terminatedChild, WEXITSTATUS(childStatus));
		}
		else{
			printf("child %d has terminated abnormally\n", terminatedChild);
		}
	}

	*msg = "moving is done";
	return 0;

}


////////////////////////////////////////////////////
// *to make new directory*
// return 0 : exit normally
// return -1: exit abnormally
// newPath : directory name to make
// msg : we can write message in it
int doMkdir(char *newPath, char **msg){
    int fd1 = open("news.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    char cmd [BUFSIZ] = "/usr/bin/find -name ";
    strcat(cmd, newPath);
    strcat(cmd, " >> news.txt");
	if(newPath == NULL || msg == NULL){
		*msg = "argument is null";
		return -1;
	}
	
	if((strcmp(newPath,".")==0) || (strcmp(newPath,"..")==0)){
		*msg = "wrong directory name";
		return -1;
	}
    //현재 디렉토리 안에 같은 디렉토리명이 있는지 검사
    system(cmd);


    fd1 = open("news.txt", O_RDONLY);
    char * str[BUFSIZ];
    int result = read(fd1, str, BUFSIZ);
    close(fd1);

    if (result == 0){
        *msg="success make directory";
        pid_t pid;
        pid = fork();
        if (pid == 0){
            //새디렉터리 생성
            if(execl("/bin/mkdir","mkdir",newPath,NULL)==-1){
                perror("execl");
                *msg = "error occurrence!";
                return -1;
            }
        }
    }
    else{
        *msg="there is already exit";
    }


	//디스크 용량 확인
	


	return 0;
}


//////////////////////////////////////////////////////////
// *to remove files and directory*
// return 0 : exit normally
// return -1: exit abnormally
// srcPath: char* array (files' path to remove)
// len: length of array
// msg: we can write message in it
int doRemove(char **srcPath, int len, char **msg){
	
	if(srcPath == NULL){
		*msg = "argument is null";
		return -1;
	}
	if(len <=0){
		*msg = "The number of selected files is zero or negative";
		return -1;
	}
	if((strcmp(*srcPath,".")==0) || (strcmp(*srcPath,"..")==0)){
		*msg = "can't remove '.' or '..' directory";
		return -1;
	}

	char answer;
	const char *check= "정말로 삭제하시겠습니까?(y/n)";

	while(1){
		printf("%s\n",check);
		answer = getchar();
		if(answer == 'y' || answer == 'Y'){
			break;
		}
		else if(answer == 'n' || answer == 'N'){
			return 0;
		}
		else{myflush();}
	}
	
	pid_t pid[len];
	int childStatus;

	for(int i=0; i<len;i++){
		pid[i]=fork();
		if(pid[i]==0){
			if(execl("/bin/rm","rm",*(srcPath+i),"-r",NULL)==-1){
			perror("execl");
			*msg = "error occurrence!";
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
	
	
	*msg = "removing is done";
	return 0;
}

//////////////////////////
// myflush: 버퍼비우기 함수
void myflush(){
	while(getchar()!='\n'){;}
	return;
}
