#ifndef QUEUE_H
#define QUEUE_H

/* 
    Struct Nodo para poder realizar la cola.
*/
typedef struct nodo
{
    char* data;
    struct nodo * next;
    
}NODE;


/* 
    Struct cola utilizado para simular un monitor.
*/
typedef struct 
{
    NODE* first;
    int size;
}queue;

/* 
    USO: Función que permite encolar un elemento a la cola.
    ENTRADA: Recibe la cola actual y el elemento que agregará a esta.
    SALIDA: No posee salida, cambia el valor de la cola por paso por referencia.
*/
void EnQueue(queue* current, char *newData);

/* 
    USO: Función que permite desencolar un elemento de la cola.
    ENTRADA: Recibe la cola actual.
    SALIDA: El Nodo que fue desencolado de la cola.
*/
NODE *DeQueue(queue* current);

/* 
    USO: Función que permite imprimir el contenido de la cola.
    ENTRADA: Recibe la cola actual.
    SALIDA: No posee salida, imprime por pantalla el contenido de la pila.
*/
void printQueue(queue* current);

/* 
    USO: Función que permite liberar la memoria utilizada para simular un monitor.
    ENTRADA: Recibe la cola actual y la cantidad de discos.
    SALIDA: No posee salida, sólo libera la memoria.
*/
void freeMonitor(queue** current, int disks);

/* 
    USO: Función que permite encolar contenido al monitor.
    ENTRADA: Recibe la cola actual, los datos a agregar, la cantidad de discos y los discos a utilizar.
    SALIDA: No posee salida, pero actualiza la cola dentro del monitor.
*/
void sendData(float** data,int lines,int* list_disk,queue** monitor,int disks);

/* 
    USO: Función que permite dar el paso a las hebras para escribir en la estructura global.
    ENTRADA: Recibe un número que representa el disco a utilizar.
    SALIDA: No posee salida, inicia el proceso de escritura en la estructura global.
*/
void *monitorData(void *input);

/* 
    USO: Función que permite escribir de manera parcial los resultados dentro de la estructura global.
    ENTRADA: Recibe el buffer en donde tomará los datos, una id que identifica el disco y el tamaño de este.
    SALIDA: No posee salida, modifica los valores de la estructura global.
*/
void writePartialy(char** bufferP,int ID,int current_size);

/* 
    USO: Función que permite encolar el mensaje "FIN" para que las hebras dejen de escribir en la estructura global.
    ENTRADA: Recibe el monitor y el identificador del disco.
    SALIDA: No posee salida, modifica la cola perteneciente al monitor.
*/
void sendEND(queue** monitor, int disk);

/* 
    Distintas variables que se utilizarán de manera global.
*/
queue **monitor;


#endif