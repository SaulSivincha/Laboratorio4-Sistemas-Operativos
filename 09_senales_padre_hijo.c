// Programa en C que implementa las funciones de señales sighup(), sigint()
// y sigquit()
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// declaracion de funcion
void sighup(int sig);
void sigint(int sig);
void sigquit(int sig);

int main()
{
    int pid;

    /* obteniendo el proceso hijo */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { /* hijo */
        signal(SIGHUP, sighup);
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        for (;;)
            ; /* ciclo por un error */
    } else /* padre */
    {         /* pid asegura el id del hijo */
        printf("\nPAdRE: enviando SIGHUP\n\n");
        kill(pid, SIGHUP);

        sleep(3); /* pausa por 3 segundos */
        printf("\nPAdRE: enviando SIGINT\n\n");
        kill(pid, SIGINT);

        sleep(3); /* pausa por 3 segundos */
        printf("\nPAdRe: enviando SIGQUIT\n\n");
        kill(pid, SIGQUIT);
        sleep(3);
    }
    return 0;
}

// definiciendo la función sighup()
void sighup(int sig)
{
    signal(SIGHUP, sighup); /* señal reseteada */
    printf("HIjo: yo he recibido un SIGHUP\n");
}

// definiciendo la función sigint()
void sigint(int sig)
{
    signal(SIGINT, sigint); /* señal reseteada */
    printf("Hijo: Yo he recibido un SIGINT\n");
}

// definiciendo la función sigquit()
void sigquit(int sig)
{
    printf("Mi pApY me mato!!!\n");
    exit(0);
}
