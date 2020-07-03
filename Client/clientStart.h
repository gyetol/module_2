 //
// Created by linux on 7/1/20.
//

#ifndef MODULE_2_FTP_CLIENT_H
#define MODULE_2_FTP_CLIENT_H

#include <sys/types.h>       
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT_NUM 20629

int clientStart(const char * ip);

#endif //MODULE_2_FTP_CLIENT_H
