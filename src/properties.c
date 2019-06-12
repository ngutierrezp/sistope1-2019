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

float* partialProperties(int argc, char *argv[])
{
    
    // Variable en donde se guardara el resultado de calculo parcial de las propiedades.
    float* partialCalc[4];

    // Estas serán las variables donde se acumularán los distintos datos.
    int cont_vis=0;
    float sumR = 0;
    float sumI = 0;
    float sumW = 0;
    float n = 0;        

    // Estas serán las variables donde se guardarán el resultado de cada propiedad.
    // Se inicializan con argv ya que calcularán parcialmente las propiedades.
    float realA = atof(argv[0]);
    float imaginaryA = atof(argv[1]);
    float pot = atof(argv[2]);

    // CALCULO DE LAS PROPIEDADES.

    // SE AGREGAN LAS PROPIEDADES A LA VARIABLE A RETORNAR.

    return partialCalc;
}

void* prueba(void* number)
{
    int number2 = (int) number;
    printf("Soy la hebra número : %i\n",number2);

}