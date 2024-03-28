#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_BUFFER_LENGTH 4096


int main(int argc, char *argv[])
{
  int input_fd, output_fd;

  if(argc != 3 || strcmp(argv[1], "--help") == 0)
  {
    printf("Usage: %s <source-file> <destination-file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  input_fd = open(argv[1], O_RDONLY);

  if(input_fd == -1)
  {
    perror("open input file fail !!!");
    exit(EXIT_FAILURE);
  }

  output_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // rw-rw-rw-


  if(output_fd == -1)
  {
    perror("open output file fail !!!");
    exit(EXIT_FAILURE);
  }


  char buffer[MAX_BUFFER_LENGTH];

  ssize_t numRead;
  numRead = read(input_fd, buffer, MAX_BUFFER_LENGTH);

  if(numRead < 0) {
    perror("read error");
    exit(EXIT_FAILURE);
  }

  lseek(output_fd, 0, SEEK_SET);

  if(write(output_fd, buffer, numRead) != numRead)
  {
    perror("write error");
    exit(EXIT_FAILURE);
  }

  close(input_fd);
  close(output_fd);

  return 0;
}
