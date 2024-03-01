#include <unistd.h>
#include <stdio.h>

int main() {
    int pid;
    pid = fork();

    if(0 == pid) {
        printf("Child\n");
        execl("/bin/ls", "ls", "-l", NULL);
        exit(0);
    } else {
        printf("Parent\n");
    }
    exit(0);

    return 0;
}