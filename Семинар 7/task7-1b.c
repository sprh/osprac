#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
  char *buffer;
  int shmid;
  key_t key;

  if ((key = ftok("task7-1a.c", 0)) < 0) {
    printf("Can't generate key\n");
    exit(-1);
  } else if ((shmid = shmget(key, 2000 * sizeof(char), 0666|IPC_CREAT)) < 0) {
    printf("Can't find shared memory\n");
    exit(-1);
  } else if ((buffer = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }
  
  int current = 0;
  while(buffer[current] != '\0') {
    printf("%c", buffer[current]);
    ++current;
  }

  if (shmdt(buffer) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }

  if (shmctl(shmid, 0, NULL) < 0) {
    printf("Can't free shared memory\n");
    exit(-1);
  }

  return 0;
}
