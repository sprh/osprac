#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int fd;
  size_t size;
  char resstring[14];

  if ((fd = open("file.fifo", O_WRONLY | O_APPEND | O_CREAT)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  size = read(fd, resstring, 14);

  if (size < 0) {
    printf("Can\'t read file\n");
    exit(-1);
  }

  printf("Reading result: %s\n", resstring);

  if (close(fd) < 0) {
    printf("Can\'t close file\n"); exit(-1);
  }

  return 0;
}
