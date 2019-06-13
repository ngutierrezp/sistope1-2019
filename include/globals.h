#ifndef GLOBALS_H
#define GLOBALS_H

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

properties *create_propeerties(int disks);
void freeProperties(properties *_current_properties, int disks);

int number;
pthread_mutex_t MutexAcumulador;
properties *global_properties;
int buffer_size;
int flag;

#endif