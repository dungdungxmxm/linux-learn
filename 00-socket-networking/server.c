#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>


int main()
{
	int listenfd = -1;
	int connfd = -1;
	char recv_buf[1024];
	char send_buf[1024];
	time_t ticks;
	
	memset(send_buf, 0, sizeof(send_buf));
	memset(recv_buf, 0, sizeof(recv_buf));
	/* Create Socket fd */
	listenfd = socket(AF_INET, SOCK_STREAM, 0); // Create socket IPv4 protocol
	
	/*Create Socket address struct*/
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/*Bind socket address with created socket*/
	bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	/*Setting connection - Client connect server*/
	// Server listen - Create waiting queue size = 10
	listen(listenfd, 10);
 	if(connfd = accept(listenfd, (struct sockaddr*)NULL, NULL) < 0) 
	{
		perror("Invalid address");
		exit(EXIT_FAILURE);
	}	
	while(1)
	{	
		read(connfd, recv_buf, sizeof(recv_buf)-1);
		printf("Client mesg: %s\n", recv_buf);

		/*Write send buffer*/
		printf("Server: ");
		scanf("%s", send_buf);
		
		/*Write operation*/
		write(connfd, send_buf, sizeof(send_buf));
		
	}	
	close(connfd);
	close(listenfd);

	return 0;
}
