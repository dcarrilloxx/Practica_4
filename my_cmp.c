#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Ús: %s <arxiu1> <arxiu2>\n", argv[0]);
        return -1;
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("Error en obrir el primer arxiu");
        return -1;
    }

    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1) {
        perror("Error en obrir el segon arxiu");
        close(fd1);
        return -1;
    }

    char buffer1, buffer2;
    ssize_t bytes_read1, bytes_read2;
    int byte_position = 1;
    int line_number = 1;

    while ((bytes_read1 = read(fd1, &buffer1, 1)) > 0 && (bytes_read2 = read(fd2, &buffer2, 1)) > 0) {
        if (buffer1 != buffer2) {
            printf("Primera diferència al byte %d, línia %d\n", byte_position, line_number);
            close(fd1);
            close(fd2);
            return 0;
        }

        if (buffer1 == '\n') {
            line_number++;
        }
        byte_position++;
    }

    if (bytes_read1 != bytes_read2) {
        printf("Els arxius són diferents: diferent mida\n");
    } else {
        printf("Els arxius són idèntics\n");
    }

    close(fd1);
    close(fd2);
    return 0;
}

