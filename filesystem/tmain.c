#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "commandFunc.h"

int main(){
	char *msg=".";
	char* ary[]={"b.c","bb.c"};
	//doRemove(ary,sizeof(ary)/sizeof(ary[0]),&msg);
	
	//printf("%s\n",msg);
	char *newPath = "folder";
	doMkdir(newPath,&msg);
	//printf("%s\n",msg);
	doMove(ary,sizeof(ary)/sizeof(ary[0]),newPath,&msg);
	printf("%s\n",msg);
	return 0;
}
