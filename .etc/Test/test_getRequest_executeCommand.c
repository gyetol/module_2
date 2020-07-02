 #include<stdio.h>
 #include<string.h>
//getRequest, executeCommand 호출 실험입니다
int execute(char **type, char **path, char **ip){
	*type="download";
	printf("%s:%s:%s\n", *type, *path, *ip);
	return 0;
}
 int getRequest(char **type, char **path, char **ip){
     *type="ls";
     *path="sdfwef";
     *ip="123123123";
    printf("%s:%s:%s\n", *type, *path, *ip);
	execute(type, path, ip);
     return 0;
 }
int response(char **type, char **path,char **ip){
	//printf("%s:%s:%s\n", *type, *path, *ip);
	return 0;
}
 int main(void){//getRequest 부를때 이런식으로 불러줘야됨
     char *type="ls";
     char *path="Sdf";
     char *ip="123";
    //printf("%s:%s:%s\n", type, path, ip);
     getRequest(&type, &path, &ip);
    // printf("%s:%s:%s\n", type, path, ip);
     //response(&type, &path, &ip); 
	return 0;
 }

