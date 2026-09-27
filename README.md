# Laboratorio 4 — Comunicación entre procesos

Práctica de Sistemas Operativos sobre señales, comunicación entre procesos y tuberías en GNU/Linux.

## Contenido

Cada ejercicio se encuentra directamente en esta carpeta mediante dos archivos con el mismo nombre:

- El archivo `.c` o `.cpp` contiene el código fuente.
- El archivo sin extensión es el ejecutable compilado para GNU/Linux.

| N.º | Programa |
| --- | --- |
| 01 | `01_manejador_sigint` |
| 02 | `02_manejador_usuario_sigint` |
| 03 | `03_captura_sigint_alarma` |
| 04 | `04_esperar_alarma` |
| 05 | `05_trampa_senales_pause` |
| 06 | `06_seis_senales_sigint` |
| 07 | `07_comunicacion_sigusr_padre_hijo` |
| 08 | `08_alarma_diez_segundos` |
| 09 | `09_senales_padre_hijo` |
| 10 | `10_redireccion_dup2` |
| 11 | `11_tuberia_padre_hijo` |
| 12 | `12_propuesto_hijo_sigint` |
| 13 | `13_propuesto_sigchld_valor` |
| 14 | `14_propuesto_tuberia_corregida` |

## Compilación

Los archivos C se compilan con GCC y los archivos C++ con G++:

```bash
gcc 03_captura_sigint_alarma.c -o 03_captura_sigint_alarma
g++ 01_manejador_sigint.cpp -o 01_manejador_sigint
```

## Ejecución

Ejemplo de ejecución del primer programa:

```bash
./01_manejador_sigint
```

Para finalizar los programas que esperan una señal, se puede usar `Ctrl+C` o enviar la señal correspondiente desde otra terminal con `kill`.
