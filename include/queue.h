#ifndef QUEUE_H
#define QUEUE_H

typedef struct nodo
{
    char* data;
    struct nodo * next;
    
}NODE;

typedef struct 
{
    NODE* first;
    int size;
}queue;

void EnQueue(queue* current, char *newData);
NODE *DeQueue(queue* current);
void printQueue(queue* current);
void freeMonitor(queue** current, int disks);

void sendData(float** data,int lines,int* list_disk,queue** monitor,int disks);
void *monitorData(void *input);
void writePartialy(char** bufferP,int ID,int current_size);
void sendEND(queue** monitor, int disk);
queue **monitor;


#endif