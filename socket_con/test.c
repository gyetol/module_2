#include<stdio.h>
#include<string.h>
#include<ctype.h>


int main(){
	char * str="ab c";
	for(int i=0;i<strlen(str);i++){
		if(isspace(str[i]!=0)){
				printf("it's whitespace char\n");
		}
		else{
			printf("it's not whitespace char \n");
		}
		
	}
	return 0;
}


