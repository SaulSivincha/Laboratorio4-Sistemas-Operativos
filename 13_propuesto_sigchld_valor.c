#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t val = 10;

static void handler(int sig)
{
    (void)sig;
    val += 5;
}

int main(void)
{
    signal(SIGCHLD, handler);
    pid_t pid = fork();
    if (pid == 0) {
        val -= 3;
        printf("Hijo: su copia de val = %d\n", (int)val);
        fflush(stdout);
        _exit(EXIT_SUCCESS);
    }
    waitpid(pid, NULL, 0);
    printf("Padre: valor final de val = %d\n", (int)val);
    return EXIT_SUCCESS;
}
