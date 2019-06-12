#include <stdio.h>
#include <stdlib.h>
#include "../include/globals.h"


properties create_propeerties()
{
    properties newProperties;

    newProperties.imaginaryAverage = (float*)malloc(sizeof(float));
    newProperties.noise = (float*)malloc(sizeof(float));
    newProperties.potency = (float*)malloc(sizeof(float));
    newProperties.realAvarage = (float*)malloc(sizeof(float));

    return newProperties;
}


void freeProperties(properties _current_properties){

    free(_current_properties.imaginaryAverage);
    free(_current_properties.noise);
    free(_current_properties.potency);
    free(_current_properties.realAvarage);
}