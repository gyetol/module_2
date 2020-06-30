//
// Created by linux on 6/30/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include "dirmanager.h"
#include "common.h"
#include <string.h>

/////////////////////////////////////////////////////////////
/// input : new path name
/// output data : error message
/// return : error
/// -1 : there is no argument
/// -2 : wrong name
/// -3 : mkdir fail
////////////////////////////////////////////////////////////
int cmd_mkdir(char * newPath, char ** errorMsg){
    char str[100] = "./";

    if ( (strcmp(newPath, ".") == 0) || (strcmp(newPath, "..") == 0) ){
        *errorMsg = "wrong directory name";
        return -2;
    }

    if (newPath == NULL){
        *errorMsg = "please insert new directory name.";
        return -1;
    }
    strcat(str, newPath);

    // 디렉토리를 생성한다.
    if(mkdir(str, 0755))
    {
        *errorMsg = "Make directory failed.";
        return -3;
    }

    *errorMsg = "mk dir done";
    return 0;
}

/////////////////////////////////////////////////////////////
/// input : new path name
/// output data : error message
/// return : error
/// -1 : there is no argument
/// -2 : wrong name
/// -3 : mkdir fail
////////////////////////////////////////////////////////////
int cmd_rmdir(char * wannaRemove, char ** errorMsg)
{
    char str[100] = "./";

    if ( (strcmp(wannaRemove, ".") == 0) || (strcmp(wannaRemove, "..") == 0) ){
        *errorMsg = "wrong directory name";
        return -2;
    }

    if (wannaRemove == NULL){
        *errorMsg = "please insert new directory name.";
        return -1;
    }
    strcat(str, wannaRemove);

    // 디렉토리를 삭제한다.
    if(rmdir(wannaRemove))
    {
        fprintf(stderr, "Remove directory failed.\n");
    }

    *errorMsg = "rm dir done";
    return 0;
}

void cmd_cd(int ac, char *av[])
{
    char *path;

    // 인자가 있을 경우 path를 설정
    if(ac > 1)
    {
        path = av[1];
    }

        // 인자가 없을 경우 HOME디렉토리를 설정
    else if((path = (char*)getenv("HOME")) == NULL)
    {
        // 환경 변수가 없을 경우 현재 디렉토리로 설정
        path = ".";
    }

    // 디렉토리를 변경한다.
    if(chdir(path) == ERROR)
    {
        fprintf(stderr, "%s: bad directory.\n", path);
    }
}


void cmd_cp(int ac, char *av[])
{
    FILE *src;
    FILE *dst;
    char ch;

    // 인자가 2개 이하일 경우 에러
    if(ac < 3)
    {
        fprintf(stderr, "Not enough arguments.\n");
        return;
    }

    // 복사할 소스 파일을 연다.
    if((src = fopen(av[1], "r")) == NULL)
    {
        fprintf(stderr, "%s: Can't open file.\n", av[1]);
        return;
    }

    // 쓰기를 할 파일을 연다.
    if((dst = fopen(av[2], "w")) == NULL)
    {
        fprintf(stderr, "%s: Can't open file.\n", av[2]);
        return;
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

    fclose(src);
    fclose(dst);
}