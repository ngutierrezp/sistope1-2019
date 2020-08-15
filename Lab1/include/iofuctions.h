#ifndef IOFUCTIONS_H
    
    #define IOFUCTIONS_H
    
    /*
    USO: Función que permite leer un archivo de entrada y guardar su información en un matriz de números flotantes.

    ENTRADA: char* file que representa el nombre del archivo de entrada y int lines, entero que contiene la cantidad de lineas dentro del archivo de entrada.

    SALIDA: Matriz de float que contiene toda la información del archivo de entrada.
    */
    float** readFile(char *file,int lines);

    /*
    USO: Función que dado un archivo de entrada, retorna la cantidad de lineas existentes en este.

    ENTRADA: char* file que representa el nombre del archivo de entrada.

    SALIDA: int que representa la cantidad de lineas en el archivo de entrada.
    */
    int countLines(char *file);

    /*
    USO: Funcion que permite obtener los parametros pasados por consola al ejecutar el programa.

    ENTRADA: int* n_disk que representa la cantidad de discos, int* n_whgt que representa el ancho del disco, char* in_file con el nombre de archivo de entrada, char* out_file con el nombre del archivo de salida y un int* flag que representa la bandera utilizada en el programa.

    SALIDA: No posee salida, pero como todos los parametros son pasados por referencia, estos se actualizan.
    */
    void getArgs(int argc, char *argv[], int *n_disk, int* n_whgt, char* in_file, char* out_file, int *flag);

    /*
    USO: Funcion que permite escribir la información procesada en un archivo de salida.

    ENTRADA: char* fileName que representa el nombre del archivo de salida, float** data que representa la matriz en donde se guardaroón los resultados luego de aplicar las distintas propiedades y int disk que contiene la cantidad de discos con los que se trabajaron.

    SALIDA: No posee salida dentro de programa, pero genera un archivo de salida en la carpeta donde se encuentra el codigo fuente.
    */
    void writeFile(char* fileName, float** data, int disk);

#endif
