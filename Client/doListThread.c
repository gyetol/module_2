//doListThread : list 요청을 보내고 받아서 처리하는 스레드의 함수
void * doListThread(void * arg){
	int * sockPtr=(int*)arg;
	listDownload("ls",NULL,NULL,*sockPtr);
	return NULL;
}
