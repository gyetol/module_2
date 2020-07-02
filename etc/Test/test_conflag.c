#include<stdio.h>
//conflag 실험입니다
void execute(int *conFlag){
	printf("conFlag1 : %d\n", *conFlag);
	*conFlag=0;
}
int mains(int *conFlag){
	execute(conFlag);
	return 0;
}
int main(void){
	int conFlag=1;
	mains(&conFlag);
	printf("conFlag2 : %d\n", conFlag);
	return 0;
}
