#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


void main(){
	int pipfds[2];
	char buffer[256] = { 0 };
	pipe(pipfds);
	write(pipfds[1], "msg", 3);
	if (fork() > 0){
		return;
	}

	read(pipfds[0],buffer,3);
	printf("pipe: %s\n");
	printf("pid: %d\n");
}
