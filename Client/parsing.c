#include "parsing.h"
#include "myListOpen.h"

typedef struct Array{
	char * array[ARR_SIZ];
 	int next;
}Array;

/*
int main(){	
	Array* directories;
	Array* files;

	//parsing("list.txt",&directories,&files);

	chdir("/home/linux/module2/Client");
	myListOpen();
	printf("chdir success\n");
 	parsing("myList.txt", &directories,&files);
	printf("directories(%d) 출력\n",directories->next);
   	for(int i=0;i<directories->next;i++){
       printf("%s\n", directories->array[i]);
   	}
	printf("files(%d) 출력\n",files->next);
	for(int i=0;i<files->next;i++){
     printf("%s\n", files->array[i]);
 	}
	free(directories);
	free(files);
	
// 	char *directories[DIRECTORY_SIZE];
//  	int dNext=0;
// 	char *files[FILE_SIZE];
// 	int fNext=0;
// 	parsing("list.txt",directories, files, &dNext, &fNext);
//  	parsing("myList.txt", directories, files, &dNext, &fNext);
//   	for(int i=0;i<dNext;i++){
//      printf("%s\n", directories[i]);
//  	}
// 	for(int i=0;i<fNext;i++){
//      printf("%s\n", files[i]);
//  	}
	
	return 0;
}
*/

int parsing(const char *path,Array** directories,Array** files){
//int parsing(char *path,char **directories, char **files, int *dNext, int *fNext){

// 	char * directories[10];
// 	int dNext=0;
// 	char * files[10];
// 	int fNext=0;

// 	Array* dirs=calloc(1,sizeof(Array));
// 	Array* fs=calloc(1,sizeof(Array));

	Array* dirs =calloc(1,sizeof(Array));
	Array* fs = calloc(1,sizeof(Array));


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
				(dirs->next)++;
// 				printf("(parsing)dirs->next=%d\n",dirs->next);
			}
			else if(type=='-'){
				fs->array[fs->next]=str;
				(fs->next)++;
// 				printf("(parsing)fs->next=%d\n",fs->next);
			}
			else
				break;
			ptr=strtok_r(NULL, "\n", &savePtr);

// 			getchar();
		}
	}
	*directories=dirs;
	*files=fs;
	return 0;
}
