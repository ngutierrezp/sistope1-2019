
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include "../include/defines.h"
#include "../include/queue.h"
#include "../include/utility.h"
#include "../include/globals.h"
#include "../include/properties.h"

void EnQueue(queue *current, char *newData)
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    new->data = (char *)malloc(sizeof(char) * MAX_CHAR * 10);
    strcpy(new->data, newData);
    new->next = NULL;
    if (current->size == 0)
    {
        current->first = new;
        current->size++;
    }
    else
    {
        NODE *aux = current->first;

        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = new;
        current->size++;
    }
}

NODE *DeQueue(queue *current)
{
    if (current->size == 0)
    {
        return NULL;
    }
    else
    {
        NODE *aux = current->first;
        current->first = aux->next;
        aux->next = NULL;
        current->size--;
        return aux;
    }
}

void printQueue(queue *current)
{
    printf("-------- \n");
    NODE *aux = current->first;
    while (aux != NULL)
    {
        printf("data : %s\n", aux->data);
        aux = aux->next;
    }
    printf("-------- \n\n\n");
}

void freeMonitor(queue **current, int disks)
{
    for (int i = 0; i < disks; i++)
    {
        free(current[i]);
    }
    free(current);
}

void sendData(float **data, int lines, int *list_disk, queue **monitor, int disks)
{
    float dist;
    char text[MAX_CHAR];
    for (int i = 0; i < lines; i++)
    {

        dist = distance(data[i][0], data[i][1]);
        sprintf(text, "%f,%f,%f,%f,%f", data[i][0], data[i][1], data[i][2], data[i][3], data[i][4]);
        for (int j = 0; j < disks - 1; j++)
        {

            if (dist >= list_disk[j] && dist < list_disk[j + 1])
            {

                EnQueue(monitor[j], text);
            }
        }

        if (dist >= list_disk[disks - 1])
        {

            EnQueue(monitor[disks - 1], text);
        }
    }
}

void sendEND(queue** monitor, int disk){
    for (int i = 0; i < disk; i++)
    {
        EnQueue(monitor[i],"FIN");
    }   
}

void *monitorData(void *input)
{
    pthread_mutex_lock(&MutexAcumulador);
    int currentDisk = *((int *)input);

    pthread_mutex_unlock(&MutexAcumulador);

    NODE *aux = DeQueue(monitor[currentDisk]);

    while (aux == NULL)
    {
        aux = DeQueue(monitor[currentDisk]);

    }

    char **bufferPartial = (char **)malloc(sizeof(char *) * buffer_size);

    for (int i = 0; i < buffer_size; i++)
    {
        bufferPartial[i] = (char *)malloc(sizeof(char) * MAX_CHAR);
    }

    int countBuffer = 0;
    
    while (strcmp(aux->data, "FIN") != 0)
    {
        if (aux != NULL && countBuffer < buffer_size)
        {
            strcpy(bufferPartial[countBuffer], aux->data);
            free(aux->data);
            free(aux);
            countBuffer++;
            // dejamos desencolado otro
            aux = DeQueue(monitor[currentDisk]);

            while (aux == NULL)
            {
                aux = DeQueue(monitor[currentDisk]);
            }
        }
        if (countBuffer == (buffer_size - 1))
        {
            writePartialy(bufferPartial, currentDisk, countBuffer);
            countBuffer = 0;
        }

    }

    if (countBuffer < buffer_size && countBuffer != 0)
    {
        writePartialy(bufferPartial, currentDisk, countBuffer);
    }
    free(aux->data);
    free(aux);

    if (flag == ACTIVE)
    {
        printf("Soy la hebra %i, procesé %i visibilidades.\n",currentDisk,global_properties[currentDisk].size);
    }
}

void writePartialy(char **bufferP, int ID, int current_size)
{
    pthread_mutex_lock(&MutexAcumulador);

    float a = 0; //U
    float b = 0; //V
    float c = 0; //REAL
    float d = 0; //IMAGINARIO
    float e = 0; // RUIDO
    char *p = (char *)malloc(sizeof(char) * MAX_CHAR);

    for (int i = 0; i < current_size; i++)
    {

        sscanf(bufferP[i], "%f,%f,%f,%f,%f", &a, &b, &c, &d, &e);

        global_properties[ID].realAvarageP += c;
        global_properties[ID].imaginaryAverageP += d;
        global_properties[ID].noise += e;
        global_properties[ID].potency += potency(c, d);
        global_properties[ID].size++;

        // printf("%f,%f,%f,%f,%f\n", a, b, c, d, e);
    }

    global_properties[ID].realAvarage = realAverage(global_properties[ID].realAvarageP, global_properties[ID].size);
    global_properties[ID].imaginaryAverage = imaginaryAverage(global_properties[ID].imaginaryAverageP, global_properties[ID].size);    

    pthread_mutex_unlock(&MutexAcumulador);
}