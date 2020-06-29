#include "dirmanager.h"
#include "filemanager.h"
#include <stdio.h>

int main(){
    char * msg = ".";
    cmd_fileCp("fileDelete.c", "test.c", &msg);
	printf("%s",msg);
	cmd_fileRm("fileDelete.c",&msg);
    printf("%s",msg);
	cmd_fileMv("test.c","aaaa.c",&msg);
	printf("%s",msg);

	return 0;
}
