/* Caso curioso: SIGPIPE aparece cuando se escribe en una tubería sin lectores. */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t sigpipe_recibida = 0;

static void manejar_sigpipe(int signal)
{
    const char mensaje[] = "SIGPIPE recibida: ya no existe un proceso lector.\n";

    (void)signal;
    sigpipe_recibida = 1;
    write(STDOUT_FILENO, mensaje, sizeof mensaje - 1);
}

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
    signal(SIGPIPE, manejar_sigpipe);

    printf("El hijo cerró el extremo de lectura, por ello el padre intenta escribir.\n");
    fflush(stdout);

    if (write(tuberia[1], mensaje, sizeof mensaje - 1) == -1 && errno == EPIPE) {
        perror("write");
    }

    close(tuberia[1]);

    if (sigpipe_recibida) {
        printf("Resultado: la escritura no se realizó porque la tubería no tiene lectores.\n");
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "No se recibió SIGPIPE cuando se esperaba.\n");
    return EXIT_FAILURE;
}
