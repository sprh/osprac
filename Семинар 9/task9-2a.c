#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/sem.h>


int main() {
  int *array;
  int shmid, new = 1, semid;

  char filename[] = "task9-2a.c";
  key_t key;

  struct sembuf buf;

  if ((key = ftok(filename,0)) < 0) {
    printf("Can\'t create key\n");
    exit(-1);
  }

  if ((shmid = shmget(key, 3*sizeof(int), 0666 | IPC_EXCL | IPC_CREAT)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    } else if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-1);
    } else {
      new = 0;
    }
  }

  if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("Can\'t attach shared memory\n");
    exit(-1);
  }

  if ((semid = semget(key, 1, 0666)) < 0) {
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
      printf("Can\'t create semaphore\n");
      exit(-1);
    }

    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    if (semop(semid, &buf, 1) < 0) {
      printf("Can\'t wait\n");
      exit(-1);
    }
  }

  if (new) {
    array[0] =  1;
    array[1] =  0;
    array[2] =  1;

    printf("Spawn 1: %d, spawn2: %d, total - %d\n", array[0], array[1], array[2]);
  } else {
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = 0;

    if (semop(semid, &buf, 1) < 0) {
      printf("Can\'t wait\n");
      exit(-1);
    }

    ++array[0];
    for(long i = 0; i < 2000000000L; ++i);
    ++array[2];

    printf("Spawn 1: %d, spawn2: %d, total - %d\n", array[0], array[1], array[2]);

    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = 0;

    if (semop(semid, &buf, 1) < 0) {
      printf("Can\'t wait\n");
      exit(-1);
    }
  }

  if (shmdt(array) < 0) {
    printf("Can\'t detach shared memory\n");
    exit(-1);
  }

  return 0;
}
