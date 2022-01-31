// Меняется, потому что при создании нового процесса ОС присваивает ему свободный номер больший, чем у предыдущего процесса
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("uid = %d, gid = %d.\n", getuid(), getgid());
    return 0;
}
