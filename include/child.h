#ifndef CHILD_H
    
    #define CHILD_H

    /*
    USO: Función que dado la sumatoria de valores reales de la visibilidad y el número de visibilidad, calcula la media real.
    
    ENTRADA: float que representa la sumatoria de valores reales de la visibilidad y el número de visibilidad.
    
    SALIDA: float que contiene el resultado de la media real.
    */
    float realAverage(float sumR, float n);

    /*
    USO: Función que dado la sumatoria de valores imaginarios de la visibilidad y el número de visibilidad, calcula la media real.
    
    ENTRADA: float que representa la sumatoria de valores imaginarios de la visibilidad y el número de visibilidad.
    
    SALIDA: float que contiene el resultado de la media imaginaria.
    */
    float imaginaryAverage(float sumI, float n);

    /*
    USO: Función que dado la sumatoria de valores imaginarios y la sumatoria de valores reales de la visibilidad, entrega la potencia de la muestra de visibilidades.
    
    ENTRADA: float que representa la sumatoria de valores reales de la visibilidad e float que representa la sumatoria de valores imaginarios.
    
    SALIDA: float que contiene el resultado de la potencia de la muestra de visibilidades.
    */
    float potency(float sumR, float sumI);

#endif