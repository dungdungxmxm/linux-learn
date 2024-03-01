#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char* argv[]) 
{
	if(argc != 4)
	{
		perror("Error Syntax!\n");
		return -1;
	}
	int fd;
	char buf[100];
	if((fd = open(argv[1], O_RDONLY)) == -1) 
	{
		perror("Unable to read file!\n");
		return -1;
	}
	printf("Program read character of a file at any point\n");
	lseek(fd, atoi(argv[2]), atoi(argv[3]));
	while(read(fd, buf, 100) != 0) 
	{
		printf("%s", buf);
	}


	return 0;
}

