#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>
#define SV_SOCK_PATH "/tmp/mysock"
#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	int sfd;
	struct sockaddr_un s_addr;
	ssize_t numRead;
	char buf[BUF_SIZE];

	/*Create socket*/
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1)
	{
		perror("Error initalize socket");
		exit(EXIT_FAILURE);
	}
	
	/*Create socket addr*/
	s_addr.sun_family = AF_UNIX;
	strncpy(s_addr.sun_path, SV_SOCK_PATH, sizeof(SV_SOCK_PATH)-1);
	
	/*Binding address to socket*/
	if(bind(sfd, (struct sockaddr*)&s_addr, sizeof(struct sockaddr_un)) == -1)
	{
		perror("Error binding address");
		exit(EXIT_FAILURE);
	}
	
	/*Connec to server*/
	if(connect(sfd, (struct sockaddr*)&s_addr, sizeof(struct sockaddr_un) == -1))
	{
		perror("Erro connect to server");
		exit(EXIT_FAILURE);
	}
	
	/*When connecting successfully -> Comunication*/
	while(1)
	{
		while(numRead = read(sfd, buf, BUF_SIZE) > 0)
			printf("Server msg: %s\n", buf);
	}
	close(sfd);
	return 0;
}


