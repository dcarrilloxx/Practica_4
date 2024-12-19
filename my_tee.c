#include <stdio.h>    // Llibreria per utilitzar funcions d'entrada/sortida com printf i perror
#include <stdlib.h>   // Llibreria per utilitzar funcions estàndard com exit
#include <fcntl.h>    // Llibreria per gestionar fitxers (open, flags com O_CREAT, etc.)
#include <unistd.h>   // Llibreria per utilitzar funcions de sistema com read, write i close
#include <sys/stat.h> // Llibreria per definir permisos dels fitxers


int main(int argc, char *argv[]) {
    // Comprovar que el programa rep exactament un argument (a part del nom del programa)
    if (argc != 2) {
        fprintf(stderr, "Has de proporcionar exactament dos arguments (comptant el nom) d'aquesta manera: %s <nom fitxer>\n", argv[0]);
        return -1; // Retorna -1 en cas d'error
    }


    // Crear o obrir el fitxer amb els permisos adequats
    // O_CREAT: crea el fitxer si no existeix
    // O_WRONLY: obre el fitxer en mode escriptura
    // O_TRUNC: si el fitxer ja existeix, elimina el contingut anterior
    // S_IRUSR | S_IWUSR: permisos de lectura i escriptura per al propietari
    // S_IRGRP | S_IROTH: permisos de només lectura per al grup i altres usuaris
    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) { // Comprovar si la funció open ha fallat
        perror("Error al crear el fitxer"); // Imprimeix un missatge d'error
        return -1; // Retorna -1 en cas d'error
    }


    char buffer;       // Variable per guardar caràcters llegits
    ssize_t bytes_read; // Variable per guardar el nombre de bytes llegits


    // Bucle per llegir caràcter a caràcter de l'entrada estàndard (teclat)
    while ((bytes_read = read(STDIN_FILENO, &buffer, 1)) > 0) {
        // Escriure el caràcter llegit a la sortida estàndard (pantalla)
        if (write(STDOUT_FILENO, &buffer, 1) == -1) { // Comprovar si la funció write ha fallat
            perror("Error en escriure a la sortida estàndard");
            close(fd); // Tancar el fitxer abans de sortir
            return -1; // Retorna -1 en cas d'error
        }


        // Escriure el mateix caràcter al fitxer
        if (write(fd, &buffer, 1) == -1) { // Comprovar si la funció write ha fallat
            perror("Error en escriure al fitxer");
            close(fd); // Tancar el fitxer abans de sortir
            return -1; // Retorna -1 en cas d'error
        }
    }


    // Comprovar si la funció read ha fallat (si bytes_read és -1)
    if (bytes_read == -1) {
        perror("Error en llegir de l'entrada estàndard");
        close(fd); // Tancar el fitxer abans de sortir
        return -1; // Retorna -1 en cas d'error
    }


    // Tancar el fitxer quan el bucle ha acabat
    close(fd);
    return 0; // Retorna 0 per indicar que el programa ha acabat correctament
}



