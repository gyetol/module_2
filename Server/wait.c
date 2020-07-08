#include<stdio.h>
#include<time.h>

int main(){
	int wait=clock();
	while(wait<=1000)
		;

	printf("wait : %d", wait);
	wait=clock();
	printf("new wait :%d", wait);
	return 0;
}
