//
// Created by linux on 7/1/20.
//

#include <unistd.h>
#include <pthread.h>

#include "ftp_client.h"


int main(){
    int sock;
    pthread_t tid;
    char * ip;
    char * localPath;
    char * serverPath;

    //function : IP_INSERT_PAGE(&ip)

    //make connection
    int result = clientStart(ip, &sock);
    if (result != 0){
        return -1;
    }
    //mainpage
    //function : listopen()
    //function : do parse .txt -> return char ** srcArray
    //function : FTP_Main_Page(MODE_CLIENT, localPath, serverPath) -> return


    pthread_create(&tid, NULL, localThread, NULL);











    close(sock);
    return 0;
}


