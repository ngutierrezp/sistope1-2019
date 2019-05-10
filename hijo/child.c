
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../include/child.h"

// Procedimiento que dado la sumatoria de valores reales de la visibilidad y el número de visibilidad, calcula la media real.
// Entrada: double que representa la sumatoria de valores reales de la visibilidad y el número de visibilidad.
// Salida: double que contiene el resultado de la media real.
double realAverage(double sumR, double n){

    double cte = 1/n;
    return cte * sumR;

}

// Procedimiento que dado la sumatoria de valores imaginarios de la visibilidad y el número de visibilidad, calcula la media real.
// Entrada: double que representa la sumatoria de valores imaginarios de la visibilidad y el número de visibilidad.
// Salida: double que contiene el resultado de la media imaginaria.
double imaginaryAverage(double sumI, double n){

    int cte = 1/n;
    return cte * sumI;

}

// Procedimiento que dado la sumatoria de valores imaginarios y la sumatoria de valores reales de la visibilidad, entrega la potencia de la muestra de visibilidades.
// Entrada: double que representa la sumatoria de valores reales de la visibilidad e double que representa la sumatoria de valores imaginarios.
// Salida: double que contiene el resultado de la potencia de la muestra de visibilidades.
double potency(double sumR, double sumI){

    double sumR2 = pow(sumR,2);
    double sumI2 = pow(sumI,2);
    double sum = sumR2 + sumI2;
    return sqrt(sum);

}
