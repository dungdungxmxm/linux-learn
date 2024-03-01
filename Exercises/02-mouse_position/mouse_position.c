#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define MOUSEFILE "/dev/input/event12"

int main()
{
	int fd;
	struct input_event ie;

	if((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
		perror("opening device");
		exit(EXIT_FAILURE);
	}

	while(read(fd, &ie, sizeof(struct input_event))) {
		if(ie.type == 2) // chi bat su kien mouse movement
		{
			//code = 0 rel_x, code = 1 rel_y
			printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n",ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
		}
	}

	return 0;
}
