#ifndef IOFUNCTIONS_H

    #define IOFUNCTIONS_H
   
    /* 
    USO: Función que permite calcular la propiedad de imaginaryAverage.
    ENTRADA: La sumatoria de los valores imaginarios y la cantidad de datos leidos en el disco.
    SALIDA: Flotante que representa el calculo de la propiedad correspondiente.
    */
    float imaginaryAverage(float sumI, float n);

    /* 
    USO: Función que permite calcular la propiedad potency.
    ENTRADA: La sumatoria de los valores reales e imaginarios en el disco.
    SALIDA: Flotante que representa el calculo de la propiedad correspondiente.
    */
    float potency(float sumR, float sumI);

    /* 
    USO: Función que permite calcular la propiedad realAverage.
    ENTRADA: La sumatoria de los valores reales y la cantidad de datos leidos en el disco.
    SALIDA: Flotante que representa el calculo de la propiedad correspondiente.
    */
    float realAverage(float sumR, float n);
    
    
#endif