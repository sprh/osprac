#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[]) {
    int fd[2], result;
    size_t size;
    char resstring[14];

    if (pipe(fd) < 0) {
        printf("Can\'t create pipe\n");
        exit(-1);
    }

    result = fork();
    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {
        close(fd[0]);
        printf("Parent execute command pwd and write output to the pipe\n");
        dup2(fd[1], 1);
        (void) execle("/bin/pwd", "pwd", 0, envp);

    } else {
        close(fd[1]);
        dup2(fd[0], 0);
        printf("Children execute command pwd and write output to the pipe\n");
        (void) execle("/bin/pwd", "pwd", 0, envp);
    }
    return 0;
}
