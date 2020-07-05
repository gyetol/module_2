#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void){

	char *fName="serverStart.c";

char str[100];
strcat(str,"grep");
strcat(str, " ");
strcat(str, fName);
strcat(str, " ");
strcat(str, "list.txt");
strcat(str, " ");
strcat(str, ">");
strcat(str, "ho.txt");
system(str);
return 0;
}
