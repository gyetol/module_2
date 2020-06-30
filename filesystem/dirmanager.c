//
// Created by linux on 6/30/20.
//
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

#include "dirmanager.h"
#include <string.h>

/////////////////////////////////////////////////////////////
/// to make directory function
/// input : new path name
/// output data : error message
/// return : error
/// -1 : there is no argument
/// -2 : wrong name
/// -3 : mkdir fail
/// 0 : done
////////////////////////////////////////////////////////////
int cmd_mkdir(char * newPath, char ** errorMsg){
    char str[100] = "./";

    if ( (strcmp(newPath, ".") == 0) || (strcmp(newPath, "..") == 0) ){
        *errorMsg = "wrong directory name";
        return -2;
    }

    if (newPath == NULL || errorMsg == NULL){
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
/// to remove directory function
/// input : new path name
/// output data : error message
/// return : error
/// -1 : there is no argument
/// -2 : wrong name
/// -3 : rmdir fail
/// 0 : done
////////////////////////////////////////////////////////////
int cmd_rmdir(char * wannaRemove, char ** errorMsg)
{
    char str[100] = "./";

    if ( (strcmp(wannaRemove, ".") == 0) || (strcmp(wannaRemove, "..") == 0) ){
        *errorMsg = "wrong directory name";
        return -2;
    }

    if (wannaRemove == NULL || errorMsg == NULL){
        *errorMsg = "please insert new directory name.";
        return -1;
    }
    strcat(str, wannaRemove);

    // 디렉토리를 삭제한다.
    if(rmdir(wannaRemove))
    {
        int ret = cmd_rmdirs(wannaRemove, 1);
        if (ret != 0){
            *errorMsg = "Remove directory failed.";
            return -3;
        }
    }

    *errorMsg = "rm dir done";
    return 0;
}

/////////////////////////////////////////////////////////////
/// to remove directory function force
/// input1 : new path name
/// input2 : force
/// return : error
/// -1 : fail
/// 0 : done
////////////////////////////////////////////////////////////
int cmd_rmdirs(const char *path, int force) {
    DIR * dir_ptr = NULL;
    struct dirent *file = NULL;
    struct stat buf;
    char filename[1024];
    /* 목록을 읽을 디렉토리명으로 DIR *를 return 받습니다. */
    if((dir_ptr = opendir(path)) == NULL) {
        /* path가 디렉토리가 아니라면 삭제하고 종료합니다. */
        return unlink(path);
    }
    /* 디렉토리의 처음부터 파일 또는 디렉토리명을 순서대로 한개씩 읽습니다. */
    while((file = readdir(dir_ptr)) != NULL) {
        // readdir 읽혀진 파일명 중에 현재 디렉토리를 나타네는 . 도 포함되어 있으므로
        // 무한 반복에 빠지지 않으려면 파일명이 . 이면 skip 해야 함
        if(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            continue;
        }
        sprintf(filename, "%s/%s", path, file->d_name);
        /* 파일의 속성(파일의 유형, 크기, 생성/변경 시간 등을 얻기 위하여 */
        if(lstat(filename, &buf) == -1) {
            continue;
        }
        if(S_ISDIR(buf.st_mode)) {
            // 검색된 이름의 속성이 디렉토리이면
            // /* 검색된 파일이 directory이면 재귀호출로 하위 디렉토리를 다시 검색 */
            if(cmd_rmdirs(filename, force) == -1 && !force) {
                return -1;
            }
        } else if(S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode)) {
            // 일반파일 또는 symbolic link 이면
            if(unlink(filename) == -1 && !force) {
                return -1;
            }
        }
    }
    closedir(dir_ptr);
    return rmdir(path);
}

