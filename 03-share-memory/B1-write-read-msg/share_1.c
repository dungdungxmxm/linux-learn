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
  const char *name = "Dung_share";
  const char *message = "Hello, World! chao cac ban";
  int shm_fd;
  void *ptr;
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  if (shm_fd == -1)
  {
    printf("Shared memory failed\n");
    exit(-1);
  }

  ftruncate(shm_fd, SHARE_MEM_SIZE);

  ptr = mmap(0, SHARE_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  strcpy(ptr, message);

}