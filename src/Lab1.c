#include <stdio.h>
#include <stdlib.h>
#include "../include/defines.h"
#include "../include/iofuctions.h"
#include "../include/dad.h"

int main(int argc, char  *argv[])

{
    int* discos = (int*)malloc(sizeof(int));
    int* ancho = (int*)malloc(sizeof(int));
    char* entrada = (char*)malloc(sizeof(char)*MAX_CHAR);
    char* salida = (char*)malloc(sizeof(char)*MAX_CHAR);
    int* bandera = (int*)malloc(sizeof(int));
    float** visibilities = NULL;

    getArgs(argc,argv,discos,ancho,entrada,salida,bandera);
    #define DEBUG
    #ifdef DEBUG
        printf("Imprimiendo...\n");
        printf("Entrada: %s\n",entrada);
        printf("Salida: %s\n",salida);
        printf("Discos: %i\n",*discos);
        printf("Ancho : %i\n",*ancho);
        printf("Bandera : %i\n",*bandera);
        printf("\n");
    #endif

    int lines = countLines(entrada);
    
    visibilities = readFile(entrada,lines);

    int disks[(*discos)];

    int count = 0;

    //lista de discos
    for (int i = 0; i < (*discos); i++)
    {
        disks[i]=count;
        count = count + *ancho;    
    }

    float** visibi = getVisibility(disks,*discos,visibilities,lines);

    writeFile(salida,visibi,*discos);
    printf("\nEscritura Correcta.\n");

    // liberación de memoria
    for (int i = 0; i < lines; i++)
    {
        free(visibilities[i]);
    }
    free(visibilities);

    free(discos);
    free(ancho);
    free(entrada);
    free(salida);
    free(bandera);

    

    
   
    

    return 0;
}
