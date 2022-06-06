#include <signal.h>
#include <stdio.h>

void handler(int nsig) {
  if (nsig == 2)
    printf("ctrl + c pressed");
  else if (nsig == 3)
    printf("ctrl + 4 pressed");
}

int main(void) {
  (void)signal(SIGINT, handler);
  (void)signal(SIGQUIT, handler);

  while(1);

  return 0;
}