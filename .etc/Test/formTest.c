#include "getRequest.h"
void test(struct RequestForm* requestForm);
void test(struct RequestForm* requestForm){
	;
	/*strcpy(requestForm->type,"ls");
	strcpy(requestForm->path,"./home");
	strcpy(requestForm->ip, "192.168.301.212");
*/}
int main(void){
	struct RequestForm* rForm;
	test(rForm);
	//printf("type : %s\n",requestForm.type);
	//printf("path : %s\n",requestForm.path);
 	//printf("ip : %s\n",requestForm.ip);
	
	return 0;
}
