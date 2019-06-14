#ifndef IOFUNCTIONS_H

    #define IOFUNCTIONS_H

    /* 
    USO: Función que permite obtener los parametros ingresados por consola.
    ENTRADA: Las distintas variablers en donde se guardaran dichos parametros.
    SALIDA: No posee salida, pero cambia el valor de los parametros de entrada por paso por referencia.
    */
    void getArgs(int argc, char *argv[], int *n_disk, int* n_whgt, int* buf_size, char* in_file, char* out_file, int *flag);
    
    /* 
    USO: Función que verifica si el archivo de entrada es el correspondiente con la problematica.
    ENTRADA: Nombre del arhcivo de entrada.
    SALIDA: Entero que representa si el archivo de entrada respeta el formato.
    */
    int verifyFile(char* _input_file_);
    
    /* 
    USO: Función que permite leer el archivo de entrada.
    ENTRADA: Nombre del achivo de entrada a leer y la cantidad de lineas que contiene este.
    SALIDA: Matriz de flotantes que contiene la información del archivo de entrada.
    */
    float** readFile(char *file,int lines);

    /* 
    USO: Función que permite contar las lineas existentes en el archivo de entrada.
    ENTRADA: Nombre del archivo de entrada.
    SALIDA: Entero que representa la cantidad de lineas existentes en el archivo.
    */
    int countLines(char *file);

    /* 
    USO: Función que permite escribir el resultado en un archivo de salida pasado por parametro.
    ENTRADA: Nombre del archivo de salida.
    SALIDA: No posee salida, pero crea el archivo de salida en el directorio que se encuentra el programa.
    */
    void writeFile(char* fileName, int disk);
    
#endif