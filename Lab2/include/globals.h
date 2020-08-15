#ifndef GLOBALS_H
#define GLOBALS_H


/* 
    Struct que es utilizado como elemento de un arreglo global en donde se guardan las propiedades parciales.
*/
typedef struct
{
    // parciales
    float realAvarageP;
    float imaginaryAverageP;

    // finales
    float realAvarage;
    float imaginaryAverage;
    float potency;
    float noise;

    // tamaño de datos
    int size;

    // numero de disco
    int numberDisk;

} properties;

/* 
    USO: Función que permite instanciar en 0 el arreglo global de propiedades
    ENTRADA: Cantidad de discos para saber cuantas propiedades hay que instanciar.
    SALIDA: El Struct global properties instanciado en valor 0. (Todas sus componentes).
*/
properties *create_propeerties(int disks);

/* 
    USO: Función que permite liberar la memoria asignada al arreglo de propiedades
    ENTRADA: Cantidad de discos para saber cuantas propiedades hay que liberar y
             el arreglo de propiedades a liberar de memoria.
    SALIDA: El Struct global properties instanciado en valor 0. (Todas sus componentes).
*/
void freeProperties(properties *_current_properties, int disks);


/* 
    Distintas variables que se utilizarán de manera global.
*/
int number;
pthread_mutex_t MutexAcumulador;
properties *global_properties;
int buffer_size;
int flag;

#endif