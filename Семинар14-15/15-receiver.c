#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int received = 1;
int recpid; 
int number;

void waiting() {
  received = 1;
}

int main(void) {
  (void)signal(SIGUSR1, waiting);

  printf("PID: %d\n", getpid());
  printf("Receiver\'s PID: ");
  scanf("%d", &recpid);

  printf("Enter number: ");
  scanf("%d", &number);

  for (int i = 0; i < 32; ++i) {
    kill(recpid, (number & (1 << i)) != 0 ? SIGUSR2 : SIGUSR1);
    received = 0;
    while (i != 31 && received == 0) {}
  }

  printf("Sent number: %d\n", number);
  return 0;
}