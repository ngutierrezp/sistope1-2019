
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/colors.h"
#include "../include/defines.h"
#include "../include/iofunctions.h"
#include "../include/properties.h"


int main(int argc, char *argv[])
{
    int verify;
    int* ancho = (int*)malloc(sizeof(int));
    int* buffer = (int*)malloc(sizeof(int));
    int* discos = (int*)malloc(sizeof(int));
    int* bandera = (int*)malloc(sizeof(int));
    char* salida = (char*)malloc(sizeof(char)*MAX_CHAR);
    char* entrada = (char*)malloc(sizeof(char)*MAX_CHAR);

    getArgs(argc,argv,discos,ancho,buffer,entrada,salida,bandera);

    #ifdef DEBUG
        printf("entrada: %s, salida: %s, discos: %i, ancho : %i, buffer: %i, bandera : %i \n",entrada,salida,*discos,*ancho,*buffer,*bandera);
    #endif

    verify = verifyFile(entrada);

    if (verify == FALSE)
    {
        printf(ROJO_T"[ERROR]"RESET_COLOR" El archivo de entrada '"AMARILLO_T"%s"RESET_COLOR"' no existe.\n",entrada);
    }
    
    
    //Apartado de Liberación de memoria

    free(ancho);
    free(discos);
    free(bandera);
    free(salida);
    free(buffer);
    free(entrada);

    
    return 0;
}
