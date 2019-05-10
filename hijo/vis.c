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
    float pot;


    //////////////////////////////////////////////////////////
    // AQUI VA EL WHILE (STRCMP(PALABRA_ENTRADA,"FIN") != 0)
    char buffer[100];
   
    /*read(STDIN_FILENO,buffer,100);
    while (strcmp(buffer,"FIN") != 0)
    {
        
    }
    */
    printf("hola soy el archivo hijo \n");
    // read(STRDIN,list[5],sizeof(list[5]))
    // sumR += list[3];
    // sumI += list[4];
    // sumW += list[5];
    // n += 1;
    //////////////////////////////////////////////////////////
    // CUANDO TERMINA EL WHILE, SE LLAMAN A LOS PROCEDIMIENTOS.
    // realA = realAverage(sumR,n);            // Donde n el el numero de visibilidades del disco
    // imaginaryA = imaginaryAverage(sumI,n);  // Donde n el el numero de visibilidades del disco
    // pot = potency(sumR,sumI);               
    // EN EL CASO DE sumW, no hay procedimiento por que la propiedad que lo utiliza es una simple sumatoria.
    //////////////////////////////////////////////////////////
    // Crear nueva list para poder decirle al padre que se termino la ejecución del hijo y entregarle los resultados.
    // write(STDOUT,list[5],sizeof(list[5]))
    //////////////////////////////////////////////////////////
    
    return 0;
}