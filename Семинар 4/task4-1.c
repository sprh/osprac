#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
  for(int i = 0; i < argc; ++i) {
    printf("argv: %s\n", argv[i]);
  }
  
  for (int i = 0; envp[i] != NULL; ++i) {
    printf("envp: %s\n", envp[i]);
  }
  return 0;
}
