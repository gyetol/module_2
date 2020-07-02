#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "commandFunc.h"

int main(){
	char *msg=".";
	char* ary[]={"b.c","bb.c","bbb.c"};
	doRemove(ary,sizeof(ary)/sizeof(ary[0]),&msg);



	return 0;
}
