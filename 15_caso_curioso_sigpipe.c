#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int tuberia[2];
    const char mensaje[] = "mensaje";
    pid_t hijo;

    if (pipe(tuberia) == -1)
        return EXIT_FAILURE;

    hijo = fork();
    if (hijo == -1)
        return EXIT_FAILURE;

    if (hijo == 0) {
        close(tuberia[0]);
        close(tuberia[1]);
        _exit(EXIT_SUCCESS);
    }

    close(tuberia[0]);
    waitpid(hijo, NULL, 0);
    signal(SIGPIPE, SIG_DFL);
    write(tuberia[1], mensaje, sizeof mensaje - 1);
    close(tuberia[1]);

    return EXIT_SUCCESS;
}
