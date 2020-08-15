#include <stdio.h>
#include <stdlib.h>
#include "../include/dad.h"
#include "../include/colors.h"
#include "../include/defines.h"
#include "../include/iofuctions.h"

int main(int argc, char *argv[])

{
    float** data_read = NULL;
    float** visibilities = NULL;
    int* ancho = (int*)malloc(sizeof(int));
    int* discos = (int*)malloc(sizeof(int));
    int* bandera = (int*)malloc(sizeof(int));
    char* salida = (char*)malloc(sizeof(char)*MAX_CHAR);
    char* entrada = (char*)malloc(sizeof(char)*MAX_CHAR);

    

    *bandera = NOT_ACTIVE;

    //obtencion de argumentos de entrada
    
    getArgs(argc,argv,discos,ancho,entrada,salida,bandera);

    if (*bandera == ACTIVE)
    {
        printf(ROJO_T"[FLAG ACTIVATED]"RESET_COLOR"\n");
    }
    
    int lines = countLines(entrada);
    
    data_read = readFile(entrada,lines);

    int disks[(*discos)];

    int count = 0;

    //lista de discos
    for (int i = 0; i < (*discos); i++)
    {
        disks[i]=count;
        count = count + *ancho;    
    }

    visibilities = getVisibility(disks,*discos,data_read,lines,bandera);

    writeFile(salida,visibilities,*discos);

    printf(VERDE_T"Programa finalizado!!\n"RESET_COLOR);

    //
    //  ##########################################
    //      Apartado de liberación de Memoria
    //  ##########################################
    //


    // Liberando memoria para los datos leidos del archivo de entrada
    for (int i = 0; i < lines; i++)
    {
        free(data_read[i]);
    }
    free(data_read);

    //Liberando memoria para la data en los discos
    
    for (int i = 0; i < *discos; i++)
    {
        free(visibilities[i]);
    }
    free(visibilities);


    //Liberacion de memoria para datos de entrada
    free(discos);
    free(ancho);
    free(entrada);
    free(salida);
    free(bandera);


    return 0;
}
