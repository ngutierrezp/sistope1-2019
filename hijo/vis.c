#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>
#include "../include/child.h"

//Procedimiento Main que da el inicio al programa.
//Entrada: Vacia.
//Salida: Entero 0 que representa que se termino la ejecucion del programa.
int main(int argc, char *argv[]){

    // Estas serán las variables donde se acumularán los distintos datos.
    float sumR;
    float sumI;
    float sumW;
    float n;           

    // Estas serán las variables donde se guardarán el resultado de cada propiedad.
    float realA;
    float imaginaryA;
    float pot = 0;
    
    // Estas serán variables auxiliares para la ejecución del programa.
    char inBuffer[100];
    char outBuffer[100];
    int list[3];
    char* ptr;
   
    // Se lee la primera informaciíon del Pipe.
    read(STDIN_FILENO,inBuffer,100);
    fprintf(stderr,"Soy el proceso : %i y recibo los siguientes datos : %s",getpid(),inBuffer);
    // Mientras lo enviado por el padre no sea el identificador "FIN"
    while (strcmp(inBuffer,"FIN") != 0)
    {
        
        int count = 0;
        ptr = strtok(inBuffer,",");

        while(ptr != NULL){
            list[count] = atof(ptr);
            count++;
            ptr = strtok(NULL,",");
        } 

        // Se acumulan en los contadores las sumatorias de la parte real, imaginaria y el ruido.
        sumR += list[0];
        sumI += list[1];
        sumW += list[2];
        pot += potency(list[0],list[1]);
        n += 1;

        // Se continua leyendo información del Pipe.
        read(STDIN_FILENO,inBuffer,100);
    }
    
    // Cuando se termina el while, se procede a calcular las propiedades.
    realA = realAverage(sumR,n);            // Donde n el el numero de visibilidades del disco
    imaginaryA = imaginaryAverage(sumI,n);  // Donde n el el numero de visibilidades del disco              
    // En el caso de sumW no se calcula ningún procedimiendo adicional ya que es la sumatoria del ruido.
    // Cada vez que llega información , se añade un termino a la sumatoria de la propiedad pot.

    // Se crea nuevo buffer para enviarle la información al padre.
    fprintf(stderr,"Soy el proceso : %i y mi Promedio Real : %f\n",getpid(),realA);
    fprintf(stderr,"Soy el proceso : %i y mi Promedio Imaginario : %f\n",getpid(),imaginaryA);
    fprintf(stderr,"Soy el proceso : %i y mi Potencia : %f\n",getpid(),pot);
    fprintf(stderr,"Soy el proceso : %i y mi Sumatoria Ruido : %f\n",getpid(),sumW);
    sprintf(outBuffer,"%f,%f,%f,%f",realA,imaginaryA,pot,sumW);

    // Se envia la información al padre.
    fprintf(stderr,"Soy el proceso : %i y envio los siguientes datos : %s",getpid(),outBuffer);
    write(STDOUT_FILENO,outBuffer,sizeof(list[5]));
    
    return 0;
}