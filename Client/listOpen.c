#include "listOpen.h"

int listOpen(void){
	int chNum=0;
    int fd = open("./list.txt",O_RDONLY,0444);	
	
	//system("/bin/mkdir home");
	chdir("./home");
	chNum++;
	if(fd==-1){
		perror("open");
		return -1;
	}
	char buf[BUFSIZ];
	while(1){
		int nRead=read(fd, buf, sizeof(buf));
		if (nRead<0){
			perror("read");
			return -1;
		}
		else if (nRead==0){
			break;
		}
		//write(fd, buf, nRead);
		//printf("%s", buf);
	}
	char *savePtr;
	char *saveExtract;
	char *saveStr;
	char *ptr=strtok_r(buf, "\n", &savePtr);//while문에는\n단위로 자른 한줄씩 들어감
	while(ptr!=NULL)
	{
//		printf("this ptr[0] is %c\n", ptr[0]);
		//나중에 권한써서 mkdir touch 하는거 반영해야됨
		if(ptr[0]!='d'&&ptr[0]!='-')
		{
		//	printf("d또는 - 아닙니다\n\n");
		
			if(ptr[1]=='/')
			{
				char *str=strtok_r(ptr, ":", &saveStr);
				chdir(str);
				chNum++;
			}
			ptr=strtok_r(NULL, "\n", &savePtr);
		}
		else
		{  
		//	printf("d또는 -이다\n");
			char *authority=" ";
			char *extract=strtok_r(ptr, " ", &saveExtract);
			authority=extract;
		//	printf("0번째 token : %s\n", extract);
			for (int i=0;i<8;i++)
			{
				extract=strtok_r(NULL, " ", &saveExtract);
		//		printf("%d번째 token : %s\n",i, extract);
			}
			if(!strcmp(extract, ".") || !strcmp(extract, ".."))
			{
			//	printf(".또는 ..라 생성하지 않습니다\n\n");
			}
			else
			{
			//	printf("일반 파일입니다\n");
			//	printf("권한 : %s\n", authority);

				char *name=extract;
			//	printf("이름 : %s\n", name);
				char command[100]=" ";
				if(ptr[0]=='d')
				{
					if(access(name, -0)==-1)//일단은 존재하지않는 경우
								//생성하게 했는데 권한달라진거반영하려면
								//권한 달라졌는지도체크하고달라졌을 경우
								//chmod든 뭐든 함수써서권한수정해야할듯
						strcat(command, "/bin/mkdir");
						strcat(command, " ");//나중에수정할때공백뺄까봐
											//그냥 위에명령이랑분리했음
						strcat(command, name);
				//execl("/bin/mkdir", "mkdir", "dirname",(char *)NULL);
				}
				else if(ptr[0]=='-')
				{
					if(access(name, -0)==-1)
					{
						strcat(command, "/usr/bin/touch");
						strcat(command, " ");
						strcat(command, name);
					}
			//execl("/usr/bin/touch","touch","filename", (char *)NULL);
				}
				system(command);
			}
		ptr=strtok_r(NULL, "\n", &savePtr);
		}
		//ptr=strtok_r(NULL, "\n", &savePtr);
	}
	for(int i=0;i<chNum;i++){
		chdir("..");
	}
	chdir("./home");
	system("/bin/ls -alR > list.txt");
	close(fd);
	return 0;
}
