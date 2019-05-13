#ifndef DAD_H
    
    #define DAD_H

    /*
    USO: Función que se encarga de la mayoria de la logica del programa.
    Esta función crea los hijos necesarios para resolver la problematica, tambien crea los pipes necesarios para poder comunicar al padre con sus hijos.
    Una vez creados los hijos y realizada toda la conección (PIPE, DUP2) realiza distintos procedimientos.
    En caso de ser un hijo, se ejecuta el archivo "vis.out".
    En caso de ser el padre, este (Mediante WRITE) le envia la información necesaria a cada hijo para que sea procesada.
    Luego de enviar toda la información, el padre esperara a cada hijo y cuando un hijo determinado termine este leera el resultado entregado por el hijo.
    Una vez se lee el resultado enviado por el hijo el padre procede a guardarlo en la matriz de resultado.
    
    ENTRADA: int* listDisk que es una lista que contiene los distintos discos,
        int countDisk que contiene la cantidad de discos, 
        float** data que contiene la información leida del archivo de entrada 
        int lines que contiene la cantidad de lineas presentes en el archivo de entrada.
        int* bandera es la flag para activar el modo DEBUG
        
    SALIDA: float** que representa la matriz de resultados luego de que cada hijo procesa la información.
    */
    float** getVisibility(int* listDisk, int countDisk, float** data, int lines,int* bandera);

#endif    