#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
  FILE *file = fopen("file.txt","r");
  char *buffer;
  int shmid;
  key_t key;

  if ((key = ftok("task7-1a.c",0)) < 0) {
    printf("Can't generate key\n");
    exit(-1);
  } else if ((shmid = shmget(key, 2000 * sizeof(char), 0666|IPC_CREAT)) < 0) {
    printf("Can't create shared memory\n");
    exit(-1);
  } else if ((buffer = (char*)shmat(shmid, NULL, 0)) == (char*)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }
  
  int current = 0;
  while (!feof(file) && current < 1999) {
    buffer[current] = fgetc(file);
    ++current;
  }

  if (shmdt(buffer) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }

  fclose(file);

  return 0;
}
