#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // Comprovar que es rep el nom del fitxer com a argument
    if (argc != 2) {
        fprintf(stderr, "Ús: %s <nom fitxer>\n", argv[0]);
        return -1;
    }

    // Crear el fitxer amb permisos de lectura/escriptura per al propietari i només lectura per als altres
    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("Error al crear el fitxer");
        return -1;
    }

    char buffer;
    ssize_t bytes_read;

    // Llegir caràcter a caràcter de l'entrada estàndard
    while ((bytes_read = read(STDIN_FILENO, &buffer, 1)) > 0) {
        // Escriure a la sortida estàndard
        if (write(STDOUT_FILENO, &buffer, 1) == -1) {
            perror("Error en escriure a la sortida estàndard");
            close(fd);
            return -1;
        }

        // Escriure al fitxer
        if (write(fd, &buffer, 1) == -1) {
            perror("Error en escriure al fitxer");
            close(fd);
            return -1;
        }
    }

    // Comprovar si la lectura ha fallat
    if (bytes_read == -1) {
        perror("Error en llegir de l'entrada estàndard");
        close(fd);
        return -1;
    }

    // Tancar el fitxer
    close(fd);
    return 0;
}
