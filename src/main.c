
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "../include/queue.h"
#include "../include/colors.h"
#include "../include/defines.h"
#include "../include/globals.h"
#include "../include/iofunctions.h"
#include "../include/properties.h"
#include "../include/utility.h"

int main(int argc, char *argv[])
{
    int i = 0;
    int verify;
    int *ancho = (int *)malloc(sizeof(int));
    int *buffer = (int *)malloc(sizeof(int));
    int *discos = (int *)malloc(sizeof(int));
    int *bandera = (int *)malloc(sizeof(int));
    char *salida = (char *)malloc(sizeof(char) * MAX_CHAR);
    char *entrada = (char *)malloc(sizeof(char) * MAX_CHAR);

    //Lectura de argumentos
    getArgs(argc, argv, discos, ancho, buffer, entrada, salida, bandera);

    if (verifyFile(entrada) == FALSE)
    {
        exit(EXIT_FAILURE);
    }

    /*
        ###############################################################

                    Sentencia de inicialización de varibales

        ###############################################################
    */

    number = 0;
    if (*bandera == ACTIVE)
    {
        flag = ACTIVE;
        printf(ROJO_T "[FLAG ACTIVATED]" RESET_COLOR "\n");
    }

    // definicion de mutex hilos y monitores que seran ocupados por los discos
    pthread_mutex_init(&MutexAcumulador, NULL);

    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * (*discos));

    // asignación de variables globales
    global_properties = create_propeerties(*discos);

    monitor = (queue **)malloc(sizeof(queue *) * (*discos));

    int *listNumberDisks = (int *)malloc(sizeof(int) * (*discos));

    buffer_size = *buffer;

    int *disks = (int *)malloc(sizeof(int) * (*discos));

    int count_disk = 0;

    //lista de discos
    for (int k = 0; k < (*discos); k++)
    {
        listNumberDisks[k] = k;
        monitor[k] = (queue *)malloc(sizeof(queue));
        disks[k] = count_disk;
        count_disk = count_disk + *ancho;
    }

    int lines = countLines(entrada);
    float **dataRead = readFile(entrada, lines);

    //entrada al monitor
    sendData(dataRead, lines, disks, monitor, *discos);

    /*
        ###############################################################

                Fin de Sentencia de inicialización de varibales

        ###############################################################
    */

    for (int i = 0; i < *discos; i++)
    {
        //llamado a crear la hebra
        pthread_create(&threads[i], NULL, monitorData, &listNumberDisks[i]);
    }

    // se envia el FIN a los monitores
    sendEND(monitor, *discos);

    // se esperand a las hebras que terminen
    i = 0;
    while (i < *discos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    //Escritrua deñ archivo

    writeFile(salida, *discos);

    //Apartado de Liberación de memoria

    freeMonitor(monitor, *discos);
    freeProperties(global_properties, *discos);
    freeArgs(entrada, salida, discos, ancho, bandera, buffer);
    free(listNumberDisks);
    free(threads);
    free(disks);
    freeDataRead(dataRead, lines);

    //Fin del programa
    printf(VERDE_T "Programa finalizado!!\n" RESET_COLOR);

    return 0;
}
