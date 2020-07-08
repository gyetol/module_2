#include "parsing.h"
/*
int myListOpen();
int main(){
	Array* directories;
	Array* files;

	myListOpen();
	parsing("myList.txt",&directories,&files);//server side
	printf("parsing.c의 결과\n");
	printf("%d\n%d",directories->next,files->next);

	free(directories);
	free(files);
	return 0;
}
*/
typedef struct Array{
	char * array[ARR_SIZ];
 	int next;
}Array;

int parsing(const char *path,Array** directories,Array** files){
	Array* dirs=calloc(1,sizeof(Array));
	Array* fs=calloc(1,sizeof(Array));

	int fd=open(path, O_RDONLY| O_CREAT, 444);
	if(fd<0){
		perror("open");
		return -1;
	}
	char buf[BUFSIZ];
	while(1){
		int nRead=read(fd, buf, sizeof(buf));
		if(nRead<0){
			perror("read");
			return -1;
		}
		else if (nRead==0)
			break;
	
		char *savePtr, *saveStr;
		char *ptr=strtok_r(buf, "\n", &savePtr);
		ptr=strtok_r(NULL, "\n", &savePtr);
		ptr=strtok_r(NULL, "\n", &savePtr);
		while(ptr!=NULL)	{
			char *str=strtok_r(ptr, " ", &saveStr);
			char type=str[0];
			for(int i=0;i<8;i++){
				str=strtok_r(NULL, " ", &saveStr);
			}
			if(type=='d'){
				dirs->array[dirs->next]=str;
				printf("%s\n",dirs->array[dirs->next]);
				(dirs->next)++;
			}
			else if(type=='-'){
				fs->array[fs->next]=str;
				fs->next++;
			}
			else
				break;
			ptr=strtok_r(NULL, "\n", &savePtr);
		}
	}
	*directories=dirs;
	*files=fs;
	return 0;
}
