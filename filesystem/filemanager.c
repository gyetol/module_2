/// input : src file, dest file
/// output data : error message
/// return : error
/// -1 : there is no argument
/// -2 : can't open file
/// 0 : done
////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "filemanager.h"

int cmd_fileCp(char * srcStr, char * destDir, char ** msg)
{
    if (srcStr == NULL || destDir == NULL || msg == NULL){
        *msg = "there is no argument";
        return -1;
    }
    FILE *src;
    FILE *dst;
    char ch;

    // open src
    if((src = fopen(srcStr, "r")) == NULL)
    {
        *msg = "Can't open file.";
        return -2;
    }

    // 쓰기를 할 파일을 연다.
    if((dst = fopen(destStr, "w")) == NULL)
    {
        *msg = "Can't open file.";
        return -2;
    }

     // 복사
    while(!feof(src))
    {
        ch = (char) fgetc(src);

        if(ch != EOF)
        {
            fputc((int)ch, dst);
        }
    }
    *msg="copy is done\n";
    fclose(src);
    fclose(dst);
    return 0;
}

int cmd_fileRm(char *srcStr, char **msg){
	if(srcStr == NULL || msg == NULL){
		*msg = "there is no argument";
		return -1;
	}
	if(remove(srcStr)==0){
		*msg="removing is done\n";
		return 0;
	}
	return -1;
}

int cmd_fileMv(char *srcStr, char *destStr, char **msg){
	if(srcStr == NULL || destStr == NULL || msg == NULL){
		*msg = "there is no argument";
		return -1;
	}
	if(cmd_fileCp(srcStr,destStr,msg)<0){
		return -1;
	}
	if(cmd_fileRm(srcStr,msg)==0){
		*msg = "moving file is succeeded\n";
		return 0;
	}
	return -1;
}

int cmd_fileRn(char *srcStr, char *destStr, char **msg){
	if(srcStr == NULL || destStr == NULL || msg == NULL){
		*msg = "there is no argument";
		return -1;
	}
	if(rename(srcStr, destStr) == 0){
		*msg = "renaming is done\n";
		return 0;
	}
	return -1;
}


