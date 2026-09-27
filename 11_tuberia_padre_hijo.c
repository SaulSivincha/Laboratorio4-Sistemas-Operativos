/* onceavo.c - Tubería entre 2 comandos usando pipe */
#include <stdio.h>  // printf, perror
#include <stdlib.h> // exit
#include <unistd.h> // pipe, fork, dup2, execlp, close

#define LEER 0
#define ESCRIBIR 1

int main(int contargs, char *args[])
{
    int descr[2]; /* descriptores extremos de la tubería */

    if (contargs != 3) {
        printf("Formato: %s comando_ent comando_sal.\n", args[0]);
        exit(1);
    }

    if (pipe(descr) == -1) {
        perror("pipe");
        exit(1);
    }

    if (fork() == 0) {
        /* Hijo: ejecuta comando de entrada y escribe en la tubería */
        close(descr[LEER]);
        if (dup2(descr[ESCRIBIR], STDOUT_FILENO) == -1) {
            perror("dup2 hijo");
            exit(1);
        }
        close(descr[ESCRIBIR]);

        execlp(args[1], args[1], (char *)NULL); // sin opciones
        perror(args[1]);                         // solo si execlp falla
        exit(1);
    } else {
        /* Padre: lee de la tubería y ejecuta el comando de salida */
        close(descr[ESCRIBIR]);
        if (dup2(descr[LEER], STDIN_FILENO) == -1) {
            perror("dup2 padre");
            exit(1);
        }
        close(descr[LEER]);

        execlp(args[2], args[2], (char *)NULL); // sin opciones
        perror(args[2]);                         // solo si execlp falla
        exit(1);
    }
}
