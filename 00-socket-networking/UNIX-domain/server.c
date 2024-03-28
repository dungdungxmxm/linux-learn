#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>
#define SV_SOCK_PATH "/tmp/mysock"
#define BUF_SIZE 100
#define BACK_LOG 10


int main(int argc, char *argv[])
{
	int sfd, cfd;
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
	
	listen(sfd, BACK_LOG);


	/*When connecting successfully -> Comunication*/
	while(1)
	{
		if(cfd = accept(sfd, NULL, NULL) == -1)        
		{
			perror("error connect");
			exit(EXIT_FAILURE);      
		}
		
		scanf("%s", buf);
		write(cfd, buf, BUF_SIZE);
	}
	close(cfd);
	close(sfd);
	return 0;
}


