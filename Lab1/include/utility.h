#ifndef UTILITY_H
    
    #define UTILITY_H
    
    /*
    USO: Funcion que se utiliza limpiar un string de un caracter en especial (garbage)

    ENTRADA: char *str que es el string a limpiar y char que es el caracter que se eliminara del char*.

    SALIDA: No posee salida, pero como el string es pasado por referencia, se hace 
    el cambio para el string.
    */
    void *removeChar(char *str, char garbage);

    /*
    USO: Funcion que dado dos números flotantes, calcula la distancia entre ellos. Tomando u y v como puntos.

    ENTRADA: float u que representa un punto y float v que representa otro punto

    SALIDA: float que representa la distancia entre los dos puntos ingresados como parametros.
    */
    float distance(float u, float v);

#endif