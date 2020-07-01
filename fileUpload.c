#include "fileUpload.h"

//한개업로드 성공
/*int main(int argc, char **argv){
     if(argc!=2){
         fprintf(stderr, "./upLoad [filePath]");
         return -1;
     }

     if(access(argv[1], 0)!=-1&&access(argv[1], 0)!=0){
         perror("access");
         return -1;
     }
     else if(access(argv[1], 0)==-1){
         fprintf(stderr, "no such file\n\n");
         return -1;
     }
         char command[200]=" ";
         strcat(command, "/bin/cp");
         strcat(command, " ");//나중에 누가 편집하다가 공백 빼먹을까봐 굳이 따로 빼서 썼음
         strcat(command, argv[1]);
         strcat(command, " ");
         strcat(command, "./home");
         system(command);

 return 0;
 }
*/

//다중업로드 성공
int main(int argc, char **argv){
	if(argc<2){
		fprintf(stderr, "./upLoad [filePath].. ");
		return -1;
	}
	for(int i=1;i<argc;i++){
	if(access(argv[i], 0)!=-1&&access(argv[i], 0)!=0){
		perror("access");
		return -1;
	}
	else if(access(argv[i], 0)==-1){
		fprintf(stderr, "no such file\n\n");
		continue;
	}
		char command[200]=" ";
		strcat(command, "/bin/cp");
		strcat(command, " ");//나중에 누가 편집하다가 공백 빼먹을까봐 굳이 따로 빼서 썼음
		strcat(command, argv[i]);
		strcat(command, " ");
		strcat(command, "./home");
		system(command);
	}
return 0;
}
