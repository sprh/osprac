#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sendpid;
int number = 0b11111111111111111111111111111111;
int step = 0;

void on_updated_step(int bit) {
  ++step;
  if (step == 32) {
    printf("Number = %d\n", number);
    exit(0);
  } else {
    printf("Step %d, bit %d\n", step, bit);
    kill(sendpid, SIGUSR1);
  }
}

void first() {
  number = number ^ (1 << step);
  on_updated_step(0);
}

void second() {
  on_updated_step(1);
}

int main(void) {
  (void)signal(SIGUSR1, first);
  (void)signal(SIGUSR2, second);

  printf("PID: %d\n", getpid());

  printf("Sender\'s PID: ");
  scanf("%d", &sendpid);

  while(1) {};
}