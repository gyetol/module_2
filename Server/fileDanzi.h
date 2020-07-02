#ifndef MODULE_2_FILEDANZI_H
#define MODULE_2_FILEDANZI_H

 #include<stdio.h>
 #include<string.h>
 #include<sys/stat.h>
 #include<sys/types.h>
 #include<fcntl.h>
 #include<unistd.h>
 #include<stdlib.h>
 #include<pthread.h>
 #include"localCommand.h"
 #include"serverStart.h"
int ipTest(char *ip); 
int inputIp(char *ip);
int notExist(char *ip,char *pwd);
int exist(char *ip, char *pwd);
int inputPassword(char *pwd);
int pwdTest(char *ip, char *pwd);
#endif
