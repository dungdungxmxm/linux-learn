#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{

  if(argc != 3 || strcmp(argv[1], "--help") == 0) {
    printf("Usage: %s <source> <destination>\n", argv[0]);
    exit(1);
  }

  int source_fd, des_fd;
  void *s_ptr, *d_ptr;

  /*Open source file*/
  source_fd = shm_open(argv[1], O_RDONLY, 0444);
  if(source_fd == -1) {
    printf("Cannot open file %s\n. File not exist", argv[1]);
  }
  /*Get state of file*/
  struct stat source_stat;
  fstat(source_fd, &source_stat);

  /*Open destination file*/
  des_fd = open(argv[2], O_CREAT | O_RDWR, 0666);
  if(des_fd == -1) {
    printf("Cannot open file %s\n", argv[2]);
  }

  /*Truncate destination file*/
  ftruncate(des_fd, source_stat.st_size);

  /*Mapping source file into memory*/
  s_ptr = mmap(0, source_stat.st_size, PROT_READ, MAP_SHARED, source_fd, 0);


  d_ptr = mmap(0, source_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, des_fd, 0);

  memcpy(d_ptr, s_ptr, source_stat.st_size);

  /*Unmapping*/
  munmap(s_ptr, source_stat.st_size);
  munmap(d_ptr, source_stat.st_size);


  close(source_fd);
  close(des_fd);

  return 0;
}