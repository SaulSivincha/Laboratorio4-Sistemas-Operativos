// Programa en CPP program para ilustrar un
// Manejador de señal definido por usuario
#include <stdio.h>
#include <signal.h>

// Manejador por SIGINT, causado por
// Ctrl-C en el teclado
void handle_sigint(int sig)
{
    printf("Señal cogida %d\n", sig);
}

int main()
{
    signal(SIGINT, handle_sigint);
    while (1)
        ;
    return 0;
}
