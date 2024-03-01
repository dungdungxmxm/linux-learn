#include <sys/types.h>
#include <aio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int SIZE_TO_READ = 100;

int main()
{
	// Open the file
	int file = open("test_aoi.txt", O_RDONLY, 0);

	if(file == -1) 
	{
		printf("Unable to open file!\n");
		return -1;
	}

	// Create the buffer
	char* buffer = (char*)calloc(SIZE_TO_READ, 1);

	// Create the control block structure
	struct aiocb cb;
	
	memset(&cb, 0, sizeof(struct aiocb));
	cb.aio_nbytes = SIZE_TO_READ;
	cb.aio_fildes = file;
	cb.aio_offset = 0;
	cb.aio_buf = buffer;

	// Asynchronous read
	if (aio_read(&cb) == -1)
	{
		printf("Unable to create request!\n");
		close(file);
	}
	printf("Request enqueued!\n");

	// TESTING::wait until the request has finished
	while(aio_error(&cb) == EINPROGRESS) 
	{
		printf("Working....\n");
	}

	//Succes ?
	int numBytes = aio_return(&cb);
	
	if(numBytes != -1)
		printf("Success!\n");
	else 
		printf("Error!\n");

	// Now clean up
	free(buffer);
	close(file);
	return 0;
}