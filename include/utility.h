#ifndef UTILITY_H
#define UTILITY_H

/* 
    USO: Función que permite liberar la memoria de las variables en donde se guardaron los parametros ingresados por consola.
    ENTRADA: Las distintas variables en las que se guardan los datos de entrada enviados por consola.
    SALIDA: No posee salida, libera memoria de las variables entregadas por parametro.
*/
void freeArgs(char *in_file, char *out_file, int *disk, int *width, int *flag, int *buffer);

/* 
    USO: Función que permite liberar la memoria de las variables en donde se guardo la información del archivo de entrada.
    ENTRADA: Las distintas variables en las que se guardan los datos del archivo de entrada.
    SALIDA: No posee salida, libera memoria de las variables entregadas por parametro.
*/
void freeDataRead(float** data, int lines);

/* 
    USO: Función genérica que permite eliminar un caracter dentro de un string.
    ENTRADA: El string y el caracter que se eliminará dentro del string entregado.
    SALIDA: No posee salida, cambia el valor del string por paso por referencia.
*/
void *removeChar(char *str, char garbage);

/* 
    USO: Función que dado dos números flotantes, calcula la distancia entre ellos.
    ENTRADA: Ambos números flotantes con los cuales se calculará la distancia.
    SALIDA: Retorna la distancia de los dos numeros flotantes entregados por parametro.
*/
float distance(float u, float v);

#endif