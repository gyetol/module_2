 //
// Created by linux on 7/1/20.
//

#ifndef MODULE_2_FTP_CLIENT_H
#define MODULE_2_FTP_CLIENT_H


#define PORT_NUM 20629
#define IP_ADDRESS "203.254.163.74"

int clientStart(const char * ip);
void localThread(void * arg);

#endif //MODULE_2_FTP_CLIENT_H
