#include "fileDanzi.h"
   
 int ipTest(char *ip){
	if(ip==NULL){
		perror("ipTest");
		return -1;
	}
	inputIp(ip);
	//파일열고
	int fd=open("./account.txt", O_RDONLY, O_CREAT, 0444);
		if(fd==-1){
			perror("open");
			return -1;
		}
		char buf[BUFSIZ];
		while(1){
			int nRead=read(fd, buf, sizeof(buf));
			if(nRead<0){
				perror("read");
				return -1;
			}
			else if(nRead==0){
				break;
			}
		char *savePtr;
		char *ptr=strtok_r(buf, "\n", &savePtr);
			while(ptr!=NULL){
			char *saveIp;
			char *existIp=strtok_r(ptr, ":", &saveIp);
			if(strcmp(ip, existIp)==0)
			{	
				close(fd);
				return 0; //Exist 호출
			}
			ptr=strtok_r(NULL, "\n", &savePtr);
			}
		}
close(fd);
return -1;//notExist 호출
}
int inputIp(char *ip){
	if(ip==NULL){
		perror("inputIp");
		return -1;
	}
	printf("\n-----Login-----\n");
	printf("input your ip : ");
 	if(fgets(ip, 20, stdin)==NULL)
 	{
   	  perror("fgets");
   	  return -1;
 	}		
	 ip[strlen(ip)-1]='\0';

	return 0;
}


int notExist(char *ip,char *pwd){
	if(ip==NULL || pwd==NULL)
	{
		perror("notExist");
		return -1;
	}
	char pwdSet[20];
	char pwdConfirm[20];

	while(1){
		printf("\n----new account----\n");
		printf("set your password : ");
		if(fgets(pwdSet, 20, stdin)==NULL)
		{
			perror("fgets");
			return -1;
		}
		pwdSet[strlen(pwdSet)-1]='\0';	

		printf("confirm your password : ");
		if(fgets(pwdConfirm, 20, stdin)==NULL)
		{
			perror("fgets");
			return -1;
		}
		 pwdConfirm[strlen(pwdConfirm)-1]='\0';
		if(strcmp(pwdSet, pwdConfirm)!=0)
			fprintf(stderr, "passwords do not match\n");
		else{
			pwd=pwdConfirm;
			break;
		}
	}

	char homePath[100]=" ";
	while(1){
		printf("set your home path : ");
		if(fgets(homePath, 100, stdin)==NULL)
		{
			perror("homePath");
			return -1;
		}
		homePath[strlen(homePath)-1]='\0';

		if(0) //경로가 존재하지 않을경우 다시입력시켜야하는데 그냥
			//항상 존재하는 경로라 치고 하겠음
			fprintf(stderr, "wrong path\n");
		else{
			//홈경로를 자료구조에 등록한다
			system("/bin/mkdir home");
			break;
		}
	}
	strcpy(homePath,"./home");
	FILE* fp=fopen("./account.txt", "a");//O_RDWR, O_CREAT, O_APPEND, 0666);
		if(fp==NULL)
		{
			perror("fopen");
	 		return -1;
		}
		//fprintf(fp, "\n");
		rewind(fp);
  	    fprintf(fp, "%s:%s:%s", ip, pwd, homePath);
	fclose(fp);
	printf("Registration success\n\n");
	return 0;
}


int exist(char *ip, char *pwd){
	if(ip==NULL||pwd==NULL)
	{
		perror("exist");
		return -1;
	}
	while(1){
	  //비밀번호 입력시키기
      inputPassword(pwd);
      //비밀번호 대조하기
      if(pwdTest(ip, pwd)==-1)
		  fprintf(stderr, "passwords do not match\n\n");
	  else{
		  printf("login success\n\n");
          break;
	  }
      }

  return 0;
}

//1-2-1
int inputPassword(char *pwd){
	if(pwd==NULL){
		perror("inputPassword");
		return -1;
	}
	printf("input password : "); //등록되어있는 ip라면 비밀번호 입력시키기
	if(fgets(pwd, 20, stdin)==NULL)
	{
		perror("fgets");
		return -1;
	}
	pwd[strlen(pwd)-1]='\0';
	return 0;
}

int pwdTest(char *ip, char *pwd){
	if(ip==NULL || pwd==NULL){
		perror("pwdTest");
		return -1;
	}
	int fd=open("./account.txt", O_RDONLY, 0444);
	if(fd==-1)
	{
		perror("open");
		return -1;
	}
	char buf[BUFSIZ];
	while(1){
		int nRead=read(fd, buf, sizeof(buf));
		if(nRead<0){
			perror("read");
			return -1;
		}
		else if(nRead==0){
			break;
		}
		char *savePtr;
		char *saveThings;
		char *ptr=strtok_r(buf, "\n", &savePtr);
		while(ptr!=NULL){
			char *existIp=strtok_r(ptr, ":", &saveThings);
			if(strcmp(ip,existIp)==0){
				char *existPwd=strtok_r(NULL, ":", &saveThings);
					if(strcmp(pwd, existPwd)==0)
					{
						close(fd);
						return 0;
					}
			}		
			ptr=strtok_r(NULL, "\n", &savePtr);
		}
	}
	close(fd);
	return -1;
}

int main(int argc, char **argv){
	if(argc!=2||(strcmp(argv[1],"start")!=0)){
		fprintf(stderr, "usage : ./fileDanzi start\n");
		return -1;
	}
	char ip[20]=" ";
	char pwd[20]=" ";
	//서버 등록 되어있는 ip인지 확인
	if(ipTest(ip)==-1){

		//등록되어있지 않을 경우 등록시키기
		if(notExist(ip,pwd)==-1){
			perror("notExist");
			return -1;
		}

	}

	//등록되어있는 ip일 경우 비번 입력시키기
	if(exist(ip, pwd)==-1){
		perror("exist");
		return -1;
	}

	//존재하는 사용자임이 확인되었으면 쓰레드 분리 후
	//한쪽에선 로컬 명령어 받고 한쪽에선 서버 가동시키기
	pthread_t tid;
	if(pthread_create(&tid, NULL, serverStart, ip)==-1)
	{
		perror("pthread_create");
		return -1;
	}
/*	if(serverMain()==-1){
		perror("serverMain");
		return -1;
	}*/
	if(pthread_join(tid, NULL)==-1)
	{
		perror("thread join failed");
		return -1;
	}
	return 0;
}

