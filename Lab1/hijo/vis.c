#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h> 
#include <sys/wait.h>
#include <sys/types.h> 
#include "../include/child.h"
#include "../include/defines.h"


int main(int argc, char *argv[]){

    // Estas serán las variables donde se acumularán los distintos datos.
    int cont_vis=0;
    float sumR = 0;
    float sumI = 0;
    float sumW = 0;
    float n = 0;        

    // Estas serán las variables donde se guardarán el resultado de cada propiedad.
    float realA = 0;
    float imaginaryA = 0;
    float pot = 0;
    
    // Estas serán variables auxiliares para la ejecución del programa.
    char inBuffer[50];
    char outBuffer[50];
    float list[3];

    // Se lee la primera informaciíon del Pipe.
    read(STDIN_FILENO,inBuffer,sizeof(inBuffer));

    // Si lo primero ingresado en la tuberia es vacio.
    if(strcmp(inBuffer,"FIN") == 0){

        sprintf(outBuffer,"%f,%f,%f,%f",realA,imaginaryA,pot,sumW);

        // Se envia la información al padre.
       
        write(STDOUT_FILENO,outBuffer,MAX_CHAR);
    
    return 0;

    }
    
    // Mientras lo enviado por el padre no sea el identificador "FIN"
    
    while (strcmp(inBuffer,"FIN") != 0)
    {
        

        if(inBuffer != NULL && strcmp(inBuffer, "") != 0){

            list[0]=0;
            list[1]=0;
            list[2]=0;
                
            sscanf(inBuffer,"%f,%f,%f",&list[0],&list[1],&list[2]);

            if (list[0] != 0 && list[1] != 0 && list[2] != 0)
            {
                // Se acumulan en los contadores las sumatorias de la parte real, imaginaria y el ruido.
                sumR += list[0];
                sumI += list[1];
                sumW += list[2];
                pot += potency(list[0],list[1]);
                n += 1;
                cont_vis++;
                // Se continua leyendo información del Pipe.
                
            }
            
            
        }
        read(STDIN_FILENO,inBuffer,sizeof(inBuffer));
        
    }
    
    // Cuando se termina el while, se procede a calcular las propiedades.
    realA = realAverage(sumR,n);            // Donde n el el numero de visibilidades del disco
    imaginaryA = imaginaryAverage(sumI,n);  // Donde n el el numero de visibilidades del disco              
    
    sprintf(outBuffer,"%f,%f,%f,%f",realA,imaginaryA,pot,sumW);

    
    if (argc > 1)
    {
        fprintf(stderr,"Soy el Hijo con PID %i, y procesé %d visibilidades\n",getpid(),cont_vis);
    }
    
    // Se envia la información al padre.
    write(STDOUT_FILENO,outBuffer,MAX_CHAR);
    
    return 0;
}