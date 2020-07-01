//
// Created by linux on 7/1/20.
//

#include <unistd.h>
#include <pthread.h>

#include "ftp_client.h"


int main(){
    int sock;
    pthread_t tid;
    //make connection
    int result = clientStart(IP_ADDRESS, &sock);
    if (result != 0){
        return -1;
    }
    //mainpage;
    pthread_create(&tid, NULL, localThread, NULL);











    close(sock);
    return 0;
}


