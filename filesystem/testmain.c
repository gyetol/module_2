//
// Created by linux on 6/30/20.
//
#include "dirmanager.h"
#include "filemanager.h"
#include <stdio.h>

int main(){
    char * msg = ".";
//    cmd_mkdir("test", &msg);
//    printf("%s",msg);
//    cmd_rmdir("test", &msg);
//    printf("%s",msg);
    cmd_fileCp("fileDelete.c", "test.c", &msg);
	printf("%s",msg);
	cmd_fileRm("fileDelete.c",&msg);
    printf("%s",msg);
	cmd_fileMv("test.c","aaaa.c",&msg);
	printf("%s",msg);
    return 0;
}
