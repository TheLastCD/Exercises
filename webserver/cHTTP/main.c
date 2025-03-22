#include <stdio.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
int main(){

	int s = socket(AF_INET, SOCK_STREAM,0);
	if (s <0){
		perror("Socket Declaration Failed");
		return 1;
	}

	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(15081), // Use htons to convert to network byte order
		.sin_addr.s_addr = INADDR_ANY // Bind to all interfaces
	};

	int b = bind(s, (struct sockaddr *)&addr, sizeof(addr));
	if (b <0){
		perror("Binding Failed");
		return 1;
	}

	int l = listen(s, 100);
	if (l <0){
		perror("Listening Failed");
		return 1;
	}

	int client_fd = accept(s, 0,0);
	
	char buffer[256] = {0};
	recv(client_fd,buffer,256,0);

	char* f = buffer +5;
	*strchr(f, ' ') = 0; // null byte at the end
	int opened_fd = open(f, O_RDONLY);
	sendfile(client_fd, opened_fd,0,256);

	close(opened_fd);
	close(client_fd);
	close(b);
	close(s);
	return 0;

}
