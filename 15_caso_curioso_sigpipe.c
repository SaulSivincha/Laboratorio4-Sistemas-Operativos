/* Caso curioso: SIGPIPE aparece cuando se escribe en una tubería sin lectores. */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int tuberia[2];
    const char mensaje[] = "mensaje para una tuberia sin lectores";
    pid_t hijo;

    if (pipe(tuberia) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    hijo = fork();
    if (hijo == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (hijo == 0) {
        close(tuberia[0]);
        close(tuberia[1]);
        _exit(EXIT_SUCCESS);
    }

    close(tuberia[0]);
    waitpid(hijo, NULL, 0);
    /* Se ignora SIGPIPE para que write() devuelva EPIPE y se pueda mostrar el error. */
    signal(SIGPIPE, SIG_IGN);

    fprintf(stderr, "El hijo cerró el extremo de lectura, por ello el padre intenta escribir.\n");

    if (write(tuberia[1], mensaje, sizeof mensaje - 1) == -1) {
        if (errno == EPIPE) {
            perror("Error al escribir en la tuberia");
        } else {
            perror("write");
        }
        close(tuberia[1]);
        return EXIT_FAILURE;
    }

    close(tuberia[1]);
    return EXIT_SUCCESS;
}
