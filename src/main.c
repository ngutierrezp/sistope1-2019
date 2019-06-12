
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "../include/colors.h"
#include "../include/defines.h"
#include "../include/globals.h"
#include "../include/iofunctions.h"
#include "../include/properties.h"

pthread_mutex_t MutexAcumulador;
int number;

properties global_properties;

// Codigo de prueba.
void *prueba()
{
    pthread_mutex_lock(&MutexAcumulador);
    printf("Soy la hebra número : %li y imprimo: %i\n", pthread_self(), number);
    number += 1;
    pthread_mutex_unlock(&MutexAcumulador);
    
}

int main(int argc, char *argv[])
{
    int verify;
    int i;
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * 100);
    int *ancho = (int *)malloc(sizeof(int));
    int *buffer = (int *)malloc(sizeof(int));
    int *discos = (int *)malloc(sizeof(int));
    int *bandera = (int *)malloc(sizeof(int));
    char *salida = (char *)malloc(sizeof(char) * MAX_CHAR);
    char *entrada = (char *)malloc(sizeof(char) * MAX_CHAR);

    global_properties = create_propeerties();

    getArgs(argc,argv,discos,ancho,buffer,entrada,salida,bandera);

    if (verifyFile(entrada) == FALSE)
    {
        exit(EXIT_FAILURE);
    }

    number = 0;
    pthread_mutex_init(&MutexAcumulador, NULL);

    while (i < 100)
    {
        pthread_create(&threads[i], NULL, prueba, NULL);
        i++;
    }
    i = 0;
    while (i < 100)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    //Apartado de Liberación de memoria

    free(ancho);
    free(discos);
    free(bandera);
    free(salida);
    free(buffer);
    free(entrada);

    freeProperties(global_properties);

    return 0;
}
