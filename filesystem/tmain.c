#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "commandFunc.h"

int main(){
	char *msg=".";
	char* ary[]={"b.c"};
	//char *paths = "fo";
	//doRemove(ary,sizeof(ary)/sizeof(ary[0]),&msg);
	//doCopy(ary,sizeof(ary)/sizeof(ary[0]),paths,&msg);	
	//printf("%s\n",msg);
	//char *newPath = "folder";
	//doMkdir(newPath,&msg);
	//printf("%s\n",msg);
	char *newPath ="a.c";
	doRename(ary,sizeof(ary)/sizeof(ary[0]),newPath,&msg);
	printf("%s\n",msg);

	return 0;
}
