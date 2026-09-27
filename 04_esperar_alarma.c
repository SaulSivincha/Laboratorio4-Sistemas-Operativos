/* cuarto.c - Esperar una alarma */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("Una alarma en 3 segundos.\n");
    alarm(3);
    printf("Esperando...\n");
    while (1)
        ;
    printf("Esta línea no se ejecutará nunca.\n");
    exit(0);
}
