#ifndef PARSING_H_
#define PARSING_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define ARR_SIZ (100)


typedef struct Array Array;
// typedef struct Array{
// 	char * array[ARR_SIZ];
// 	int next;
// }Array;

int parsing(const char * path,Array** directories,Array** file);

#endif
