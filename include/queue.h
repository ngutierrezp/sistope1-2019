#ifndef QUEUE_H
    #define QUEUE_H

    typedef struct nodo
    {
        float* listVisivility;
        struct nodo* next;

    }node;


    typedef struct 
    {
        int size;
        node* first;
    }queue;
    
    
#endif