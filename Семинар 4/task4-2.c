#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
  pid_t process_id = fork();
  if (process_id < 0) {
    printf("Error!");
    exit(1);
  }
  else if (process_id == 0) {
    printf("Child, calling task4-1.c\n");
    (void) execle("/bin/cat", "/bin/cat", "task4-1.c", 0, envp);
    printf("Error start\n");
    exit(1);
  }
  else {
    printf("Parent\n");
  }
  return 0;
}
