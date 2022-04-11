#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
  int semid;
  struct sembuf buf;
  key_t key;
  char file_name[] = "task9-1a.c";

  if ((key = ftok(file_name, 0)) < 0) {
    printf("Can\'t create key\n");
    exit(-1);
  }

  if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t create semid\n");
    exit(-1);
  }

  buf.sem_num = 0;
  buf.sem_op  = 1;
  buf.sem_flg = 0;

  if (semop(semid, &buf, 1) < 0) {
    printf("Can\'t increment semaphore\n");
    exit(-1);
  }

  return 0;
}
