#include<stdio.h>
#include<time.h>
int main(void){
	int a, b, i;
	a=clock();
	while(1){
		b=clock();
		if(b>=50000)
			break;
		printf("b:%d\n", b);
	}
	printf("\n%d========================\n;", a);
return 0;
}
