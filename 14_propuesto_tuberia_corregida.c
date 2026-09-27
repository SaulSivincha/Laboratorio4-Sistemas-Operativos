#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEER 0
#define ESCRIBIR 1

int main(void)
{
    int descr[2];
    char mensaje[100];
    const char *frase = "Veremos si la transferencia es buena.";
    if (pipe(descr) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (pid == 0) {
        close(descr[LEER]);
        ssize_t escritos = write(descr[ESCRIBIR], frase, strlen(frase));
        if (escritos < 0)
            perror("write");
        close(descr[ESCRIBIR]);
        return escritos < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }
    close(descr[ESCRIBIR]);
    ssize_t leidos = read(descr[LEER], mensaje, sizeof mensaje - 1);
    if (leidos < 0) {
        perror("read");
        close(descr[LEER]);
        return EXIT_FAILURE;
    }
    mensaje[leidos] = '\0';
    printf("Bytes leídos: %zd\n", leidos);
    printf("Mensaje: %s\n", mensaje);
    close(descr[LEER]);
    waitpid(pid, NULL, 0);
    return EXIT_SUCCESS;
}
