
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../include/child.h"

// Procedimiento que dado la sumatoria de valores reales de la visibilidad y el número de visibilidad, calcula la media real.
// Entrada: float que representa la sumatoria de valores reales de la visibilidad y el número de visibilidad.
// Salida: float que contiene el resultado de la media real.
float realAverage(float sumR, float n){

    float cte = 1/n;
    return cte * sumR;

}

// Procedimiento que dado la sumatoria de valores imaginarios de la visibilidad y el número de visibilidad, calcula la media real.
// Entrada: float que representa la sumatoria de valores imaginarios de la visibilidad y el número de visibilidad.
// Salida: float que contiene el resultado de la media imaginaria.
float imaginaryAverage(float sumI, float n){

    int cte = 1/n;
    return cte * sumI;

}

// Procedimiento que dado la sumatoria de valores imaginarios y la sumatoria de valores reales de la visibilidad, entrega la potencia de la muestra de visibilidades.
// Entrada: float que representa la sumatoria de valores reales de la visibilidad e float que representa la sumatoria de valores imaginarios.
// Salida: float que contiene el resultado de la potencia de la muestra de visibilidades.
float potency(float sumR, float sumI){

    float sumR2 = pow(sumR,2);
    float sumI2 = pow(sumI,2);
    float sum = sumR2 + sumI2;
    return sqrt(sum);

}
