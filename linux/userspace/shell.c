#include <bits/types/idtype_t.h>
#include <bits/types/siginfo_t.h>
#include <unistd.h>
#include <sys/wait.h>

int asm_waitid(idtype_t idtype, id_t, siginfo_t *infop, int options,void*); //add a 5th arg as raw syscall has one extra argument

#define MAX_COMMAND 255

//Notes, compile as static with command:
//	gcc -static shell.c -o shell

int main(){
	char command[MAX_COMMAND];
	for (;;){
		write(1, "> ", 2);
		int count = read(0, command, MAX_COMMAND);
		command[count -1] = 0;
		//fork the command run
		pid_t fork_result = fork();
		if (fork_result == 0){
			execve(command,0, 0);
			break; //stop the child from becoming the shell
		}
		else{
			//TODO, bad practise assume parent for now, fix later
			//wait using waitid as it's in the kernel
			
			siginfo_t info;
			asm_waitid(P_ALL,0,&info, WEXITED, 0); 
		}
	}
	_exit(0);
}
