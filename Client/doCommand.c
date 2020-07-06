
#include "doCommand.h"

void * doListThread(void * arg){
	if(arg==NULL){
		fprintf(stderr, "doListThread: argument is null\n");
		return NULL;
	}
	int * retVal=calloc(1,sizeof(int));
	if(retVal==NULL){
		perror("calloc");
		return NULL;
	}
	ResInfo* resInfo =(ResInfo*)arg;
	if(listDownload(resInfo->sock,resInfo->ip)==-1){
		*retVal=-1;
		return retVal;
	}
	*retVal=0;
	return retVal;
}

void * doDownloadThread(void *arg){
	if(arg==NULL){
		fprintf(stderr, "doDownloadThread: argument is null\n");
		return NULL;
	}
	int * retVal=calloc(1,sizeof(int));
	if(retVal==NULL){
		perror("calloc");
		return NULL;
	}
	ResInfo* resInfo =(ResInfo*)arg;
	char fName[255];
	printf("다운받을 파일명을 입력해주세요:");
	fgets(fName,sizeof(fName),stdin);

	if(fileDownload(resInfo->sock,resInfo->ip,fName)==-1){
		*retVal=-1;
		return retVal;
	}
	*retVal=0;
	return retVal;
}

void * doQuitThread(void * arg){
	if(arg==NULL){
		fprintf(stderr, "doQuitThread: argument is null\n");
		return NULL;
	}
	int * retVal=calloc(1,sizeof(int));
	if(retVal==NULL){
		perror("calloc");
		return NULL;
	}
	ResInfo* resInfo =(ResInfo*)arg;
	if(clientQuit(resInfo->sock, resInfo->ip)==-1){
		*retVal=-1;
		return retVal;
	}

	*retVal=0;
	return retVal;
}


int  doCommand(ResInfo *resInfo){
	char cmd;
	char *srcPath[100]={"b.c","bb.c"}; //하드코딩함
	char *destPath="folder";
	char *msg=".";
	int flag = 0; // doCommand의 while문 계속: 0 , 탈출: 1
	int len = sizeof(srcPath)/sizeof(srcPath[0]);
	pthread_t tid;



	while(1){
		if(flag==1){break;}
		
	cmd=getchar();
	
	switch(cmd){
		case ' ' : putSrcPath(srcPath, &msg);
				   break;

		case '\n': if(pthread_create(&tid,NULL,doListThread, resInfo)!=0){
					   perror("pthread_create");
					   return -1;
				   } //서버쪽의 디렉토리 경로 요청시 list 쓰레드 생성
					break;

		case 'c' : getDestPath(destPath, &msg, "복사할 경로를 입력하세요:"); 
				   doCopy(srcPath,len,destPath,&msg);
				   freeDestPath(destPath,&msg);
				   break;

		case 'm' : getDestPath(destPath, &msg, "이동할 경로를 입력하세요:");
				   doMove(srcPath,len,destPath,&msg);
				   freeDestPath(destPath,&msg);
				   break;

		case 'r' : doRemove(srcPath,len,&msg);
				   break;

		case 'n' : getDestPath(destPath,&msg, "바꿀 이름을 입력하세요:");
				   doRename(srcPath,len,destPath,&msg);
				   freeDestPath(destPath,&msg);
				   break;

		case 'f' : if(pthread_create(&tid,NULL,doDownloadThread,resInfo)!=0){
					   perror("pthread_create");
					   return -1;
				   } //download 요청시 download 쓰레드 생성
				   break;

		case 'p' : break;
		case 'h' : break;
		case 'k' : getDestPath(destPath, &msg, "생성할 디렉토리명을 입력하세요:");
				   doMkdir(destPath,&msg);
				   freeDestPath(destPath,&msg);
				   break;

		case 'x' : if(pthread_create(&tid,NULL,doQuitThread, resInfo)!=0){
					   perror("phread_create");
					   return -1;
				   } //quit 요청시 quit 쓰레드 생성
				   flag=1;
				   break;
		}

	}
//}


/*
void * fileDownloadThread(void * arg){
	printf("(doCommand)fileDownloadThread 진입\n");
	ResInfo * resInfo=(ResInfo*)arg;
	fileDownload(resInfo->sock,resInfo->ip,"fileDanzi.txt");
	return NULL;
}
*/
/*
int doCommand(ResInfo* resInfo){
	printf("(doCommand)doCommand 들어옴\n");
	//listDownload(resInfo->sock,resInfo->ip);
	//printf("(doCommand)listDownload성공\n");

	//pthread_t tid;
	//pthread_create(&tid,NULL,fileDownloadThread,resInfo);
	//pthread_join(tid,NULL);
	//printf("(doCommand)fileDownload성공\n");*/
	clientQuit(resInfo->sock,resInfo->ip);	printf("clientQuit성공\n");
	return 0;
}
