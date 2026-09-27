/* decimo.c - Redirección usando dup2 */
#include <stdio.h>  // printf
#include <stdlib.h> // exit
#include <unistd.h> // dup2, execvp, close
#include <fcntl.h>  // open, O_*

int main(int contargs, char *args[])
{
    int desc_fich;

    if (contargs < 3) {
        printf("Formato: %s fichero comando [opciones].\n", args[0]);
        exit(1);
    }

    printf("Ejemplo de redirección.\n");

    /* abrir/crear el fichero de salida con permisos 0644 */
    desc_fich = open(args[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (desc_fich < 0) {
        perror("open");
        exit(1);
    }

    /* Redirige la salida estándar (fd 1) al fichero */
    if (dup2(desc_fich, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(desc_fich);
        exit(1);
    }
    close(desc_fich);

    /* Ejecuta el comando indicado en args[2] con sus opciones (args[2]..args[n-1]) */
    execvp(args[2], &args[2]);
    perror("execvp"); // solo se ejecuta si exec falla
    exit(1);
}
