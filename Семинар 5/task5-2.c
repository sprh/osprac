#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fd1[2], fd2[2], result;

    size_t size1, size2;
    char resstring1[27], resstring2[26];

    if (pipe(fd1) < 0) {
        printf("Can\'t open first pipe\n");
        exit(-1);
    }

    if (pipe(fd2) < 0) {
        printf("Can\'t open second pipe\n");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {
        if (close(fd1[0]) < 0) {
            printf("Parent: Can\'t close reading side of first pipe\n"); exit(-1);
        }

        size1 = write(fd1[1], "Parent: Hello, world!", 27);

        if (size1 != 27) {
            printf("Can\'t write all string to first pipe\n");
            exit(-1);
        }

        if (close(fd1[1]) < 0) {
            printf("Parent: Can\'t close writing side of first pipe\n"); exit(-1);
        }

        if (close(fd2[1]) < 0) {
            printf("Parent: Can\'t close writing side of second pipe\n"); exit(-1);
        }

        size2 = read(fd2[0], resstring2, 26);

        if (size2 < 0) {
            printf("Can\'t read string from second pipe\n");
            exit(-1);
        }

        printf("Parent:  %s\n", resstring2);

        if (close(fd2[0]) < 0) {
            printf("Parent Can\'t close reading side of first pipe\n");
            exit(-1);
        }
        printf("Parent exit\n");
    } else {
        if (close(fd1[1]) < 0) {
            printf("Child: Can\'t close writing side of first pipe\n"); exit(-1);
        }

        size1 = read(fd1[0], resstring1, 27);

        if (size1 < 0) {
            printf("Can\'t read string from first pipe\n");
            exit(-1);
        }

        printf("Child:  %s\n", resstring1);

        if (close(fd1[0]) < 0) {
            printf("Child: Can\'t close reading side of first pipe\n"); exit(-1);
        }

        if (close(fd2[0]) < 0) {
            printf("Child: Can\'t close reading side of second pipe\n"); exit(-1);
        }

        size2 = write(fd2[1], "Child: Hello, world!", 26);

        if (size2 != 26) {
            printf("Can\'t write all string to second pipe\n");
            exit(-1);
        }

        if (close(fd2[1]) < 0) {
            printf("Child: Can\'t close writing side of second pipe\n"); exit(-1);
        }
        printf("Child exit\n");
    }

    return 0;
}
