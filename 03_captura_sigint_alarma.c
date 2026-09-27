#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int numcortes = 0; /* Contador de CTRL-C */
int bucle = 1;     /* Controlador de salida del bucle de espera */

void alarma(int sig); /* Captura la señal de alarma SIGALRM */
void cortar(int sig); /* Captura la señal de interrupción SIGINT */

int main()
{
    signal(SIGINT, cortar);
    signal(SIGALRM, alarma);
    printf("Ejemplo de signal.\n");
    printf("Pulsa varias veces CTRL-C durante 15 segundos.\n");
    alarm(15);
    while (bucle)
        ;
    signal(SIGINT, SIG_IGN);
    printf("Has intentado cortar %d veces.\n", numcortes);
    printf("Hasta luego estudiante.\n");
    exit(0);
}

void alarma(int sig)
{
    signal(SIGALRM, SIG_IGN);
    bucle = 0; /* Salir del bucle */
    printf("¡Alarma!\n");
}

void cortar(int sig)
{
    signal(SIGINT, SIG_IGN);
    printf("Has pulsado CTRL-C\n");
    numcortes++;
    signal(SIGINT, cortar);
}
