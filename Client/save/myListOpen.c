#include "myListOpen.h"
 

int myListOpen(){
//int main(void){ //myListOpen();
	system("/bin/ls -alR > myList.txt");
	return 0;
}
