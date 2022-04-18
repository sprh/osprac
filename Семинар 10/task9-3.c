#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main() {
  char pathname[] = "task9-3.c";
  key_t key;
  struct sembuf mybuf;
  int semid, N;
  int fd[2], result;

  scanf("%d", &N);
  
  if (N < 2) {
      printf("Incorrect number: should be >= 2");
  }

  if (pipe(fd) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }
  if ((key = ftok(pathname, 0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
  if ((semid = semget(key, 1, IPC_CREAT | 0666)) < 0) {
    printf("Can\'t get semaphore set\n");
    exit(-1);
  }
  result = fork();
  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  }
  
  for (int i = 1; i <= N; ++i) {
    char message[16];
    if (result > 0) {
      // Write
      write(fd[1], "Message", 7);
      //  A(S, 0)
      mybuf.sem_num = 0;
      mybuf.sem_flg = 0;
      mybuf.sem_op = 2;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Parent: can\'t wait for condition\n");
        exit(-1);
      }
      
      // Z(S)
      mybuf.sem_num = 0;
      mybuf.sem_op = 0;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Parent: can\'t wait for condition\n");
        exit(-1);
      }
      // Read
      read(fd[0], message, 7);

      printf("Parent %d: read from pipe: %s\n", i, message);
    } else {
      // D(S,1)
      mybuf.sem_num = 0;
      mybuf.sem_op = -1;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Child: can\'t wait for condition\n");
        exit(-1);
      }
      // Read
      read(fd[0], message, 7);

      printf("Child %d: read from pipe: %s\n", i, message);
      // Write
      write(fd[1], "Message", 7);
      //   D(S, 1)
      mybuf.sem_num = 0;
      mybuf.sem_flg = 0;
      mybuf.sem_op = -1;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Child: can\'t wait\n");
        exit(-1);
      }
    }
  }

  if (close(fd[0]) < 0) {
    printf("Can\'t close reading side of pipe\n");
    exit(-1);
  } else if (close(fd[1]) < 0) {
    printf("Can\'t close writing side of pipe\n");
    exit(-1);
  }

  return 0;
}
