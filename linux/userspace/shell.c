#include <bits/types/idtype_t.h>
#include <bits/types/siginfo_t.h>
#include <unistd.h>
#include <sys/wait.h>

int asm_waitid(idtype_t idtype, id_t, siginfo_t *infop, int options,void*); //add a 5th arg as raw syscall has one extra argument

#define MAX_COMMAND 255
#define MAX_ARGS 25

//Notes, compile as static with command:
//	gcc -static shell.c -o shell


// properly buffer the input to the shell :)
typedef struct{
	char* cBuffer;
	size_t stInputLen;
	char* cCommand;
	char* cArgs;

}sInputBuffer;

sInputBuffer* sStaticInputBuffer(){
	static sInputBuffer sBufferInstance;
	static char cBuffer[MAX_COMMAND];
	static char cCommand[MAX_COMMAND];
	static char cArgs[MAX_COMMAND];
	
	sBufferInstance.cBuffer = cBuffer;
	sBufferInstance.stInputLen = 0;
	sBufferInstance.cCommand = cCommand;
	sBufferInstance.cArgs = cArgs;

	return &sBufferInstance;
}

int iHandleInput(sInputBuffer *inputBuffer){
	inputBuffer->stInputLen = read(0, inputBuffer->cBuffer, MAX_COMMAND);
	if(inputBuffer->stInputLen < MAX_COMMAND){
		inputBuffer->cBuffer[inputBuffer->stInputLen -1] = 0;
		inputBuffer->cCommand = inputBuffer->cBuffer; //if no args the whole buffer can be assigned 
		inputBuffer->cArgs = inputBuffer->cBuffer;
		return 0;
	}
	else {
		write(1,"Command to long\n", 17);
		return 1;

	}
}



int main(){
	sInputBuffer *inputBuffer = sStaticInputBuffer();
	char cCommand[MAX_COMMAND];
	char *envp[] = {"PATH=/bin:usr/bin","HOME=/home/user",NULL};
	for (;;){
		int iWrittenBytes = write(1, "> ", 2);
		int iSuccess = iHandleInput(inputBuffer);
		if(iSuccess == 0){
			//fork the command run
			pid_t fork_result = fork();
			if (fork_result == 0){
				execve(inputBuffer->cCommand,0, envp);
				break; //stop the child from becoming the shell
			}
			else{
					//TODO, bad practise assume parent for now, fix later
					//wait using waitid as it's in the kernel
						
					siginfo_t info;
					asm_waitid(P_ALL,0,&info, WEXITED, 0);
			}
		}
	}
	
	_exit(0);
}
