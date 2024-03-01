#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void cat(const char *filename) {
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error writing to stdout");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    cat(argv[1]);

    return 0;
}
