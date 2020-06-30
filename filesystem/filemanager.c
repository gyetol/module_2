//
// Created by linux on 6/30/20.
//
#include <stdio.h>
#include <string.h>
#include "filemanager.h"

/////////////////////////////////////////////////////////////
/// to copy file function
/// input : src file, dest file
/// output data : error message
/// return : error
/// -1 : there is no argument
/// -2 : can't open file
/// 0 : done
////////////////////////////////////////////////////////////
int cmd_fileCp(char * srcStr, char * destStr, char ** errorMsg)
{
    if (srcStr == NULL || destStr == NULL || errorMsg == NULL){
        *errorMsg = "there is no argument";
        return -1;
    }
    FILE *src;
    FILE *dst;
    char ch;

    // open src
    if((src = fopen(srcStr, "r")) == NULL)
    {
        *errorMsg = "Can't open file.";
        return -2;
    }

    // 쓰기를 할 파일을 연다.
    if((dst = fopen(destStr, "w")) == NULL)
    {
        *errorMsg = "Can't open file.";
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
    *errorMsg="copy is done";
    fclose(src);
    fclose(dst);
    return 0;
}

