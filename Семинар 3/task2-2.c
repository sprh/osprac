#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == -1) {
        printf("Error");
    } else if (pid == 0) {
        printf("Child: pid = %d, ppid = %d.\n", getpid(), getppid());
    } else {
        printf("Parent: pid = %d, ppid = %d.\n", getpid(), getppid());
    }
    return 0;
}
