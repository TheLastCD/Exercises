
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>



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
	

	msgrcv(msgid, &msg,sizeof(msg),1,0);
	printf("Received: %s\n", msg.cMsgText);

	msgctl(msgid,IPC_RMID,NULL);

	return 0;
	


}
