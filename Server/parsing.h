#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>
#define DIRECTORY_SIZE (50)
#define FILE_SIZE (100)
int parsing(char **directories, char **files, int *dNext, int *fNext);
