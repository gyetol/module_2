//doDownloadThread : fileDownload하는 thread
void * doDownloadThread(void *arg){
	//char * path=(char*)arg;
	int * sockPtr=(int*)arg;
	fileDownload("download",NULL,NULL,*sockPtr);
	return NULL;
}
