#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Declaramos los prototipos de funciones
void manejador(int signum);
// Variable global
int bandera = 1;

// Función principal
int main(int argc, char **argv)
{
    // Capturamos la señal SIGALRM
    signal(SIGALRM, manejador);
    printf("EN 10 segundos se creara una alarma\n");
    // Crear alarma en segundos
    alarm(10);

    // Mientras bandera sea 1, no finalizar el programa
    while (bandera)
        ;
}

// Funcion manejador
void manejador(int signum)
{
    printf("\nRecibi una alarma\n");
    // signal(SIGINT,SIG_DFL);
    bandera = 0;
}
