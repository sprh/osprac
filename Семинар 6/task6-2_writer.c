#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int fd;
  size_t size;

  (void)umask(0);

  if ((fd = open("file.fifo", O_WRONLY | O_APPEND | O_CREAT)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  size = write(fd, "Hi", 2);

  if (size != 2) {
    printf("Can\'t create file\n");
    exit(-1);
  }

  if (close(fd) < 0) {
    printf("Can\'t close file\n");
    exit(-1);
  }
  
  printf("Success\n");

  return 0;
}
