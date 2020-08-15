
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "../incl/defines.h"
#include "../incl/iofunctions.h"
#include "../incl/colors.h"


int main(int argc, char *argv[])
{
    int i = 0;
    int verify;
    int *elevadores = (int *)malloc(sizeof(int));
    int *pisos = (int *)malloc(sizeof(int));
    int *bandera = (int *)malloc(sizeof(int));
    char *subida = (char *)malloc(sizeof(char) * MAX_CHAR);
    char *bajada = (char *)malloc(sizeof(char) * MAX_CHAR);
	char *otro = (char *)malloc(sizeof(char) * MAX_CHAR);

    //Lectura de argumentos
    getArgs(argc, argv,pisos,elevadores,subida,bajada,otro,bandera);

    if (verifyFile(subida) == FALSE || 
		verifyFile(bajada) == FALSE ||
		verifyFile(otro) == FALSE )
    {
        exit(EXIT_FAILURE);
    }

    /*
        ###############################################################

                    Sentencia de inicialización de varibales

        ###############################################################
    */
   
    free(elevadores);
    free(pisos);
    free(bandera);
    free(subida);
    free(bajada);
	free(otro);

    //Fin del programa
    printf(VERDE_T "Programa finalizado!!\n" RESET_COLOR);

    return 0;
}
