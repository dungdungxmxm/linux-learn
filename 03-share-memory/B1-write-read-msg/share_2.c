#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define SHARE_MEM_SIZE 4096
void main()
{
  char read_buf[4096];
  void *ptr;
  int shm_fd = shm_open("Dung_share", O_RDONLY, 0666);
  if (shm_fd == -1)
  {
    printf("Shared memory failed\n");
    exit(-1);
  }

  ptr = mmap(0, SHARE_MEM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
  strcpy(read_buf, ptr);
  printf("%s\n", read_buf);

  munmap(ptr, SHARE_MEM_SIZE);
  shm_unlink("Dung_share");

  close(shm_fd);
  printf("Done free shared memory\n");
}