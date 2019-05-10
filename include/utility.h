#ifndef UTILITY_H
    #define UTILITY_H
    
    /*
    USO: funcion que se utiliza limpiar un string de un caracter en especial (garbage)

    SALIDA: no posee salida, pero como el string es pasado por referencia, se hace 
    el cambio para el string.
    */
    void *removeChar(char *str, char garbage);

    float distance(float u, float v);
#endif