#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "commandFunc.h"

int main(){
	char *msg=".";
	char* ary[]={"b.c"};
	doRemove(ary,sizeof(ary)/sizeof(ary[0]),&msg);
	
	printf("%s\n",msg);
	char *newPath = "folder";
	doMkdir(newPath,&msg);
	printf("%s\n",msg);

	return 0;
}
