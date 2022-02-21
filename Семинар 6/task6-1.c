#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int fd[2];
  int result = 0;
  if (pipe(fd) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }
  
  char *b =  malloc(1 * sizeof(char));
  while (1) {
    if (write(fd[1], b, 1) > 0) {
        ++result;
    }
    else {
        break;
    }
  }

  printf("%d\n", result);

  if (close(fd[0]) < 0) {
    printf("Can'\t close reading side of pipe\n");
    exit(-1);
  } else if (close(fd[1]) < 0) {
    printf("Can'\t close writing side of  pipe\n");
    exit(-1);
  }

  return 0;
}
