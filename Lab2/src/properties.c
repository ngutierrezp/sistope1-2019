#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/properties.h"

float realAverage(float sumR, float n)
{

    float cte = 1/n;
    return cte * sumR;

}

float imaginaryAverage(float sumI, float n)
{

    float cte = 1/n;
    return cte * sumI;

}

float potency(float sumR, float sumI)
{

    float sumR2 = pow(sumR,2);
    float sumI2 = pow(sumI,2);
    float sum = sumR2 + sumI2;
    return sqrt(sum);

}