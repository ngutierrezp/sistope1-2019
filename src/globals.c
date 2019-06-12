#include <stdio.h>
#include <stdlib.h>
#include "../include/globals.h"

properties *create_propeerties(int disks)
{
    properties newProperties[disks];

    for (int j = 0; j < disks; j++)
    {
        newProperties[j].imaginaryAverage = (float *)malloc(sizeof(float));
        newProperties[j].noise = (float *)malloc(sizeof(float));
        newProperties[j].potency = (float *)malloc(sizeof(float));
        newProperties[j].realAvarage = (float *)malloc(sizeof(float));
    }
    return newProperties;
}

void freeProperties(properties *_current_properties, int disks)
{
    for (int j = 0; j < disks; j++)
    {
        free(_current_properties[j].imaginaryAverage);
        free(_current_properties[j].noise);
        free(_current_properties[j].potency);
        free(_current_properties[j].realAvarage);
    }
}