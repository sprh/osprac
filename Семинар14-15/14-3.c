#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int nsig) {
  int status;
  pid_t pid = waitpid(-1, &status, WNOHANG);

  while (pid != 0) {
    if (pid < 0) {
      if (errno == 10) {
        printf("No process to close\n");
      } else {
        printf("Errno = %d\n", errno);
      }
      return;
    } else {
      if ((status & 0xff) == 0) {
        printf("Process %d exited with status %d\n", pid, status >> 8);
      } else if ((status & 0xff00) == 0) {
        printf("Process %d killed by signal %d\n", pid, status &0x7f);
      }
      pid = waitpid(-1, &status, WNOHANG);
    }
  }
}

int main(void) {
  (void) signal(SIGCHLD, handler);

  pid_t pid;

  for (int i=0; i<10; i++) {
    if ((pid = fork()) < 0) {
      printf("Can\'t fork child 1\n");
      exit(1);
    } else if (pid == 0) {
      exit(200 + i);
    }
  }

  while(1);
  return 0;
}