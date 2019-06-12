#ifndef GLOBALS_H
#define GLOBALS_H

typedef struct
{

    float *realAvarage;
    float *imaginaryAverage;
    float *potency;
    float *noise;

} properties;


properties create_propeerties();
void freeProperties(properties _current_properties);

#endif