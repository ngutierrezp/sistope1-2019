#include <stdio.h>
#include <stdlib.h>
#include "../include/globals.h"

properties *create_propeerties(int disks)
{
    properties *newProperties = (properties *)malloc(sizeof(properties) * disks);

    for (int j = 0; j < disks; j++)
    {
        newProperties[j].imaginaryAverage = 0;
        newProperties[j].noise = 0;
        newProperties[j].potency = 0;
        newProperties[j].realAvarage = 0;
        newProperties[j].imaginaryAverageP = 0;
        newProperties[j].numberDisk = j;
        newProperties[j].realAvarageP = 0;
        newProperties[j].size = 0;
    }
    return newProperties;
}

void freeProperties(properties *_current_properties, int disks)
{
    free(_current_properties);
}