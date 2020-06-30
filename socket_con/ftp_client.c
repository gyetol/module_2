//myclient.c source file

#include 	<sys/types.h>
#include 	<sys/socket.h>
#include 	<strings.h>
#include	<string.h>
#include 	<arpa/inet.h>
#include 	<unistd.h>
#include 	<stdio.h>
#include    <ctype.h>
#include 	<stdlib.h>
#include 	<netinet/in.h>
#include	<stdbool.h>
#include 	<fcntl.h>
#include	<pthread.h>
#include    <sys/select.h>
#include    <sys/time.h>


#define 	MAXLINE 4096
#define     LISTENQ 1024
#define		TRUE	1
#define		FALSE	0

//function trims leading and trailing whitespaces
void trim(char *str)
{

	int i;
    int begin = 0;

    int end = strlen(str) - 1;

    while (isspace((unsigned char) str[begin]))
        begin++;

    while ((end >= begin) && isspace((unsigned char) str[end]))
        end--;

    // Shift all characters back to the start of the string array.
    for (i = begin; i <= end; i++)
        str[i - begin] = str[i];

    str[i - begin] = '\0'; // Null terminate string.
}



int get_user_input(char *buffer){
//user의 명령어 처리를 해당 함수 안에서 해야한다.
//단축키에 따른 명령어 지정
    memset(buffer, 0, (int)sizeof(buffer));
    printf("> ");
    if(fgets(buffer, 1024, stdin) == NULL){
            return -1;
    }

    return 1;
}

int get_port_string(char *str, char *ip, int n5, int n6){
    int i = 0;
    char ip_temp[1024];
    strcpy(ip_temp, ip);

    for(i = 0; i < strlen(ip); i++){
        if(ip_temp[i] == '.'){
            ip_temp[i] = ',';
        }
    }

    sprintf(str, "PORT %s,%d,%d", ip_temp, n5, n6);
    return 1;
}

int check_command(const char *command){
	int i = 0, space_cnt = 0;
	for(i = 0; i < strlen(command); i++){
		if(isspace(command[i]) != 0){
			space_cnt++;
			continue;
		}
	}
	if(space_cnt <= 1){return 1;}//사용자의 command안에 공백이 존재하지 않음
	else{return -1;}
}

int get_command(const char *command){
	int value=0;
	char copy[1024];	
	while(check == 0){
    	char *str;
		
    	if(get_user_input(command) < 0){
    		fprintf(stderr,"get_command:error in read user command");
			memset(command,0,(int)sizeof(command));
    		continue;
    	}
        if(strlen(command) < 2){
            fprintf(stderr,"get_command:no Input from user");
			memset(command,0,strlen(command));
            continue;
        }
        trim(command);
		

        if(check_command(commadn) < 0){
            	fprintf(stderr,"get_command:command has invalid format\n");
				memset(command,0,strlen(command));
            	continue;
        }
    	
    	char delimit[]=" \t\r\n\v\f";
    	str = strtok(command, delimit);
		switch(str){
			case "ls": value=1;return value;
			case "download": value=2;return value;
			case "upload": value=3;return value;
			case "quit": value=4;return value;
			default:
				fprintf(stderr,"get_command:no available command\n");
				memset(command,0,strlen(command));
				value=0;
		}
    }
	return value;
}

int convert(uint16_t port, int *n5, int *n6){
	//endian 교체 함수
    int i = 0;
    int x = 1;
    *n5 = 0;
    *n6 = 0;
    int temp = 0;
    for(i = 0; i< 8; i++){
        temp = port & x;
        temp = port & x;
        *n6 = (*n6)|(temp);
        x = x << 1; 
    }

    port = port >> 8;
    x = 1;

    for(i = 8; i< 16; i++){
        temp = port & x;
        *n5 = ((*n5)|(temp));
        x = x << 1; 
    }
    return 1;
}

int get_ip_port(int fd, char *ip, int *port){
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    getsockname(fd, (struct sockaddr*) &addr, &len);
    sprintf(ip, inet_ntoa(addr.sin_addr));
    *port = (uint16_t)ntohs(addr.sin_port);
    return 1;
}

int get_filename(char *input, char *fileptr){
    char cpy[1024];
    char *filename = NULL;
    strcpy(cpy, input);
    trim(cpy);
    filename = strtok(cpy, " ");
    filename = strtok(NULL, " ");

    if(filename == NULL){
        fileptr = "\0";
        return -1;
    }else{
        strncpy(fileptr, filename, strlen(filename));
        return 1;
    }
}

int do_ls(int controlfd, int datafd, char *input){
    
    char str[MAXLINE+1], recvline[MAXLINE+1], *temp;
    bzero(filelist, (int)sizeof(filelist));
    bzero(recvline, (int)sizeof(recvline));
    bzero(str, (int)sizeof(str));

    fd_set rdset;
    int maxfdp1, data_finished = FALSE, control_finished = FALSE;

	char filelist[256]={0,};
    if(get_filename(input, filelist) < 0){
        printf("No Filelist Detected...\n");
        sprintf(str, "LIST");
    }else{
        sprintf(str, "LIST %s", filelist);
    }

	memset(filelist,0,strlen(filelist));

    FD_ZERO(&rdset);
    FD_SET(controlfd, &rdset);
    FD_SET(datafd, &rdset);

    if(controlfd > datafd){
        maxfdp1 = controlfd + 1;
    }else{
        maxfdp1 = datafd + 1;
    }

    write(controlfd, str, strlen(str));
    while(1){
        if(control_finished == FALSE){FD_SET(controlfd, &rdset);}
        if(data_finished == FALSE){FD_SET(datafd, &rdset);}
        select(maxfdp1, &rdset, NULL, NULL, NULL);

        if(FD_ISSET(controlfd, &rdset)){
            read(controlfd, recvline, MAXLINE);
            //strtok(recvline, " ");
            //recvline = strtok(NULL, " ");
            printf("%s\n", recvline);
            temp = strtok(recvline, " ");
            if(atoi(temp) != 200){
                printf("Exiting...\n");
                break;
            }
            control_finished = TRUE;
            bzero(recvline, (int)sizeof(recvline));
            FD_CLR(controlfd, &rdset);
        }

        if(FD_ISSET(datafd, &rdset)){
            printf("Server Data Response:\n");
            while(read(datafd, recvline, MAXLINE) > 0){
                printf("%s", recvline); 
                bzero(recvline, (int)sizeof(recvline)); 
            }

            data_finished = TRUE;
            FD_CLR(datafd, &rdset);
        }
        if((control_finished == TRUE) && (data_finished == TRUE)){
            break;
        }

    }
    bzero(filelist, (int)sizeof(filelist));
    bzero(recvline, (int)sizeof(recvline));
    bzero(str, (int)sizeof(str));
    return 1;
}

int do_get(int controlfd, int datafd, char *input){
    char filename[256], str[MAXLINE+1], recvline[MAXLINE+1], *temp, temp1[1024];
    bzero(filename, (int)sizeof(filename));
    bzero(recvline, (int)sizeof(recvline));
    bzero(str, (int)sizeof(str));
    int n = 0, p = 0;

    fd_set rdset;
    int maxfdp1, data_finished = FALSE, control_finished = FALSE;

    

    if(get_filename(input, filename) < 0){
        printf("No filename Detected...\n");
        char send[1024];
        sprintf(send, "SKIP");
        write(controlfd, send, strlen(send));
        bzero(send, (int)sizeof(send));
        read(controlfd, send, 1000);
        printf("Server Response: %s\n", send);
        return -1;
    }else{
        sprintf(str, "RETR %s", filename);
    }   
    printf("File: %s\n", filename);
    sprintf(temp1, "%s-out", filename);
    bzero(filename, (int)sizeof(filename));


    FD_ZERO(&rdset);
    FD_SET(controlfd, &rdset);
    FD_SET(datafd, &rdset);


    if(controlfd > datafd){
        maxfdp1 = controlfd + 1;
    }else{
        maxfdp1 = datafd + 1;
    }

    
    FILE *fp;
    if((fp = fopen(temp1, "w")) == NULL){
        perror("file error");
        return -1;
    }

    write(controlfd, str, strlen(str));
    while(1){
        if(control_finished == FALSE){FD_SET(controlfd, &rdset);}
        if(data_finished == FALSE){FD_SET(datafd, &rdset);}
        select(maxfdp1, &rdset, NULL, NULL, NULL);

        if(FD_ISSET(controlfd, &rdset)){
            bzero(recvline, (int)sizeof(recvline));
            read(controlfd, recvline, MAXLINE);
            printf("Server Control Response: %s\n", recvline);
            temp = strtok(recvline, " ");
            if(atoi(temp) != 200){
                printf("File Error...\nExiting...\n");
                break;
            }
            control_finished = TRUE;
            bzero(recvline, (int)sizeof(recvline));
            FD_CLR(controlfd, &rdset);
        }

        if(FD_ISSET(datafd, &rdset)){
            //printf("Server Data Response:\n");
            bzero(recvline, (int)sizeof(recvline));
            while((n = read(datafd, recvline, MAXLINE)) > 0){
                fseek(fp, p, SEEK_SET);
                fwrite(recvline, 1, n, fp);
                p = p + n;
                //printf("%s", recvline); 
                bzero(recvline, (int)sizeof(recvline)); 
            }
            data_finished = TRUE;
            FD_CLR(datafd, &rdset);
        }
        if((control_finished == TRUE) && (data_finished == TRUE)){
            break;
        }

    }
    bzero(filename, (int)sizeof(filename));
    bzero(recvline, (int)sizeof(recvline));
    bzero(str, (int)sizeof(str));
    fclose(fp);
    return 1;
}

int do_put(int controlfd, int datafd, char *input){
    char filename[256], str[MAXLINE+1], recvline[MAXLINE+1], sendline[MAXLINE+1], *temp, temp1[1024];
    bzero(filename, (int)sizeof(filename));
    bzero(recvline, (int)sizeof(recvline));
    bzero(str, (int)sizeof(str));
    //int n = 0, p = 0;

    fd_set wrset, rdset;
    int maxfdp1, data_finished = FALSE, control_finished = FALSE;

    

    if(get_filename(input, filename) < 0){
        printf("No filename Detected...\n");
        char send[1024];
        sprintf(send, "SKIP");
        write(controlfd, send, strlen(send));
        bzero(send, (int)sizeof(send));
        read(controlfd, send, 1000);
        printf("Server Control Response: %s\n", send);
        return -1;
    }else{
        sprintf(str, "STOR %s", filename);
    }   

    sprintf(temp1, "cat %s", filename);
    bzero(filename, (int)sizeof(filename));


    FD_ZERO(&wrset);
    FD_ZERO(&rdset);
    FD_SET(controlfd, &rdset);
    FD_SET(datafd, &wrset);


    if(controlfd > datafd){
        maxfdp1 = controlfd + 1;
    }else{
        maxfdp1 = datafd + 1;
    }


    FILE *in;
    extern FILE *popen();

    if (!(in = popen(temp1, "r"))) {
        printf("Cannot Run Command\nExiting...\n");
        return -1;
    }


    write(controlfd, str, strlen(str));
    while(1){
        if(control_finished == FALSE){FD_SET(controlfd, &rdset);}
        select(maxfdp1, &rdset, &wrset, NULL, NULL);

        if(FD_ISSET(controlfd, &rdset)){
            bzero(recvline, (int)sizeof(recvline));
            read(controlfd, recvline, MAXLINE);
            printf("Server Control Response: %s\n", recvline);
            temp = strtok(recvline, " ");
            if(atoi(temp) != 200){
                printf("File Error...\nExiting...\n");
                break;
            }
            control_finished = TRUE;
            bzero(recvline, (int)sizeof(recvline));
            FD_CLR(controlfd, &rdset);
        }

        if(FD_ISSET(datafd, &wrset)){
            bzero(sendline, (int)sizeof(sendline));
            //printf("Server Data Response:\n");
            while (fgets(sendline, MAXLINE, in) != NULL) {
                write(datafd, sendline, strlen(sendline));
                //printf("%s", sendline);
                bzero(sendline, (int)sizeof(sendline));
            }

            data_finished = TRUE;
            FD_CLR(datafd, &wrset);
            close(datafd);
        }
        if((control_finished == TRUE) && (data_finished == TRUE)){
            break;
        }
    }
    return 1;
}

void __quit(const char * msg,int line){
	char buf[BUFSIZ];
	sprintf(buf,"%s(%d)",msg,line);
	perror(buf);
	exit(1);
}

#define err_quit(msg) __quit(msg,__LINE__)

#define PORT (20629)
int main(int argc, char **argv){

	int server_port, control_sock, listen_sock, data_sock, code, n5, n6, x;
    uint16_t port=(uint16_t)PORT;
	struct sockaddr_in servaddr, data_addr;
	char command[1024], ip[50], str[MAXLINE+1];


	if(argc != 2){
		fprintf(stderr,"Usage: ./ftpclient SERVER_IP\n");
		exit(1);
	}

    //set up control connection--------------------------------------------------
    if ( (control_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_quit("socket");
                
	struct sockaddr_in servaddr={0,};
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(server_port);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton");
        
    if (connect(control_sock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		err_quit("connect");


    //set up data connection------------------------------------------------------
    if(listen_sock = socket(AF_INET, SOCK_STREAM, 0)==-1)
		err_quit("socke");

	struct sockaddr_in data_addr={0,};
    data_addr.sin_family      = AF_INET;
    data_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    data_addr.sin_port        = htons(0);

    if(bind(listen_sock, (struct sockaddr*) &data_addr, sizeof(data_addr))==-1)
		err_quit("bind");

    if(listen(listen_sock, LISTENQ)==-1)
		err_quit("listen");
    
    //get ip address from control port
    get_ip_port(control_sock, ip, (int *)&x);
    //x = 0;
    printf("x: %d\n", x);
    printf("ip: %s\n", ip);
    //get data connection port from listenfd
    get_ip_port(listen_sock, str, (int *)&port);
    
    printf("Port: %d, str: %s\n",  port, str);
    convert(port, &n5, &n6);

    while(1){

		memset(command,0,strlen(command));
        //get command from user
        code = get_command(command);
        
        //user has entered quit
        if(code == 4){
            char quit[BUFSIZ]={0,};
            sprintf(quit, "QUIT");
            if(write(control_sock, quit, strlen(quit))<=0)
				break;
            read(control_sock,quit, sizeof(quit));
            printf("Server Response: %s\n", quit);
            break;
        }
        printf("command: %s\n", command);

        //send PORT n1,n2,n3,n4,n5,n6
		memset(str,0,(int)sizeof(str));
        get_port_string(str, ip, n5, n6);

        write(control_sock, str, strlen(str));
		memset(str,0,(int)sizeof(str));
        data_sock = accept(listen_sock, (struct sockaddr*)NULL, NULL);

        printf("Data connection Established...\n");

        if(code == 1){
            if(do_ls(control_sock, data_sock, command) < 0){
                close(data_sock);
                continue;
            }
        }else if(code == 2){
            if(do_get(control_sock, data_sock, command) < 0){
                close(data_sock);
                continue;
            }
        }else if(code == 3){
            if(do_put(control_sock, data_sock, command) < 0){
                close(data_sock);
                continue;
            }
        }
        close(data_sock);
    }
    close(control_sock);	
	return TRUE;
}
