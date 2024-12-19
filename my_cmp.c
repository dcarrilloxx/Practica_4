#include <stdio.h>    // Llibreria per utilitzar funcions d'entrada/sortida com printf i perror
#include <stdlib.h>   // Llibreria per utilitzar funcions estàndard com exit
#include <fcntl.h>    // Llibreria per gestionar fitxers (open i flags com O_RDONLY)
#include <unistd.h>   // Llibreria per utilitzar funcions de sistema com read, close

int main(int argc, char *argv[]) {
    // Comprovar que el programa rep exactament 2 arguments (a més del nom del programa)
    if (argc != 3) {
        fprintf(stderr, "Has de proporcionar 3 arguments (comptant el nom) d'aquesta manera: %s <arxiu1> <arxiu2>\n", argv[0]);
        return -1; // Retorna -1 en cas d'error
    }

    // Obre el primer fitxer en mode només lectura (O_RDONLY)
    int f1 = open(argv[1], O_RDONLY);
    if (f1 == -1) { // Comprova si la funció open ha fallat
        perror("Error en obrir el primer arxiu"); // Imprimeix un missatge d'error
        return -1; // Retorna -1 en cas d'error
    }

    // Obre el segon fitxer en mode només lectura (O_RDONLY)
    int f2 = open(argv[2], O_RDONLY);
    if (f2 == -1) { // Comprova si la funció open ha fallat
        perror("Error en obrir el segon arxiu"); // Imprimeix un missatge d'error
        close(f1); // Tanca el primer fitxer abans de sortir
        return -1; // Retorna -1 en cas d'error
    }

    char buffer1, buffer2;          // Variables per guardar els caràcters llegits de cada fitxer
    ssize_t bytes_read1, bytes_read2; // Variables per guardar el nombre de bytes llegits
    int byte_position = 1;          // Variable per comptar la posició del byte que s'està comparant
    int line_number = 1;            // Variable per comptar el número de línia actual

    // Bucle per llegir i comparar caràcter a caràcter de tots dos fitxers
    while ((bytes_read1 = read(f1, &buffer1, 1)) > 0 && (bytes_read2 = read(f2, &buffer2, 1)) > 0) {
        // Comprova si els caràcters llegits són diferents
        if (buffer1 != buffer2) {
            // Si són diferents, imprimeix la posició del byte i la línia on es troba la diferència
            printf("Primera diferència al byte %d, línia %d\n", byte_position, line_number);
            close(f1); // Tanca el primer fitxer
            close(f2); // Tanca el segon fitxer
            return 0; // Finalitza el programa amb èxit
        }

        // Si es troba un salt de línia ('\n'), incrementa el comptador de línies
        if (buffer1 == '\n') {
            line_number++;
        }

        // Incrementa el comptador de la posició del byte
        byte_position++;
    }

    // Comprova si un dels fitxers té més bytes que l'altre
    if (bytes_read1 != bytes_read2) {
        printf("Els arxius són diferents: diferent mida\n");
    }

    // Tanca tots dos fitxers
    close(f1);
    close(f2);
    return 0; // Retorna 0 per indicar que el programa ha acabat correctament
}


