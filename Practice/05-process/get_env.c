#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main() {
    printf("home = %s\n", getenv("HOME"));
    printf("user = %s\n", getenv("USER"));
    printf("pwd = %s\n", getenv("PWD"));
    return 0;
}