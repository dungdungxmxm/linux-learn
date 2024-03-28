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
	int sock_fd = -1;
	char recv_buf[1024];
	char send_buf[1024];	
	
	memset(recv_buf, 0, sizeof(recv_buf));
	memset(send_buf, 0, sizeof(send_buf));
	/*Create listen socket*/
	sock_fd = socket(AF_INET, SOCK_STREAM, 0); // create IPv4 protocol socket
	
	/*Create socket address struct*/
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	/*Binding created socket with socket addr*/
	bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	
	if(connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Invalid address");
		exit(EXIT_FAILURE);
	}
	while(1) 
	{
		printf("Client: ");
		scanf("%s", send_buf);
		write(sock_fd, send_buf, sizeof(send_buf));		

		read(sock_fd, recv_buf, sizeof(recv_buf)-1);
		printf("Server mesg: %s\n", recv_buf);
	}
	
	close(sock_fd);	
	return 0;
}
