
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MAX 10


//typedef struct{
//	long lMsgType;
//	char* cMsgText;
//	int cMsgLen;

//}sMsgBuf;

struct sMsgBuf{
	long lMsgType;
	char cMsgText[100];

}msg;


int main(){
	//sMsgBuf msg;
	key_t key;
	int msgid;


	key = ftok("progfile",65);

	msgid = msgget(key, 0666 | IPC_CREAT);
	
	msg.lMsgType= 1;
	char* test = "hello";
	strcpy(msg.cMsgText, test);
	//msg.cMsgLen = sizeof(msg.cMsgText);
	
	printf("Sending Data: %s\n", msg.cMsgText);
	
	//fgets(msg.cMsgText, MAX, stdin);
	msgsnd(msgid, &msg, sizeof(msg), 0 );
	
	return 0;
	


}
