#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>   // fork, getpid, getppid, sleep
#include <sys/wait.h> // wait

void manejador(int signum);

// variable global modificada por el manejador
static volatile sig_atomic_t bandera = 1;

int main(int argc, char **argv)
{
    int status;
    pid_t pid;

    if ((pid = fork()) == 0) {
        // Proceso hijo
        printf("Soy hijo y estoy esperando una señal de mi padre, mi pid es: %d\n", (int)getpid());
        signal(SIGUSR1, manejador);
        while (bandera)
            ; // espera a que el manejador cambie la bandera
        kill(getppid(), SIGUSR2); // avisar al padre
    } else {
        // Proceso padre
        signal(SIGUSR2, manejador);
        printf("Soy Padre, mi pid es: %d\n", (int)getpid());
        sleep(3);
        kill(pid, SIGUSR1); // avisar al hijo
        wait(&status);      // esperar al hijo
        printf("Mi hijo termino con un estado: %d\n", status);
    }
    return 0;
}

void manejador(int signum)
{
    if (signum == SIGUSR1) {
        printf("Recibi una senal de mi padre %d\n", signum);
    } else {
        printf("Recibi una senal de mi hijo %d\n", signum);
    }
    bandera = 0; // dejar de esperar
}
