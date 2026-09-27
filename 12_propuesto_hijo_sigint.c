#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int estado = 0;
    pid_t pid = fork();
    if (pid == 0) {
        printf("Hijo PID=%d esperando una señal\n", getpid());
        fflush(stdout);
        for (;;)
            pause();
    } else if (pid > 0) {
        sleep(1);
        printf("Padre: enviando SIGINT al hijo %d\n", pid);
        fflush(stdout);
        kill(pid, SIGINT);
        waitpid(pid, &estado, 0);
        if (WIFSIGNALED(estado))
            psignal(WTERMSIG(estado), "El hijo terminó debido a");
    } else {
        perror("fork");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
