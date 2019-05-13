#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/wait.h>
#include <sys/types.h> 
#include "../include/dad.h"
#include "../include/defines.h"
#include "../include/utility.h"


float** getVisibility(int* listDisk, int countDisk, float** data, int lines,int* bandera)
{
    char text[MAX_CHAR];
    int status, padre = getpid();
    int** listPipesIn = (int**)malloc(sizeof(int*)*countDisk);
    int** listPipesOut = (int**)malloc(sizeof(int*)*countDisk);
    float** results = (float**)malloc(sizeof(float*)*countDisk);

    if (*bandera == ACTIVE)
    {
        printf("Soy el padre con el PID = %i\n",padre);
    }

    //Reserva de memoria para el arreglo de resultados
    for (int i = 0; i < countDisk; i++)
    {
        results[i] = (float*)malloc(sizeof(float)*4);
    }
    
    //Definicion de los pipes para la comunicacion bilateral.
    for (int i = 0; i < countDisk; i++)
    {
        listPipesIn[i] = (int*)malloc(sizeof(int)*2);        
        listPipesOut[i] = (int*)malloc(sizeof(int)*2);
        pipe(listPipesIn[i]);
        pipe(listPipesOut[i]);
    }
    
    int pid = fork();

    for (int i = 0; i < countDisk; i++)
    {
        //Solo el padre original puede crear mas hijos.
        if (getpid() == padre)
        {
            //Como se creo un hijo fura, el ciclo termina una
            // iteración antes. 
            if (i < countDisk-1)
            {
                pid = fork();    
            }
        }

        //Si es el proceso hijo 
        else if (pid == 0)
        {
            
            dup2(listPipesIn[i][0],STDIN_FILENO); // Lectura Padre-> Hijo (hijo lee padre)
            dup2(listPipesOut[i][1],STDOUT_FILENO); // Escritura Hijo -> Padre
            
            //Se cierran los pipes que tienen relacion con el padre.
            close(listPipesIn[i][1]); // Escritura : Padre-> Hijo
            close(listPipesOut[i][0]); // Lectura Hijo : Padre (padre lee hijo)
            

            //Todos los hijos son enviados a otro proceso
            if (*bandera == ACTIVE)
            {
                execl("./vis.out","./vis.out","-b",(const char*)NULL);    
            }
            else
            {
                execl("./vis.out","./vis.out",(const char*)NULL);
            }
            
            
            
            
        }
    }

    // A partir de ahora solo soy el padre
    float dist=-1;


    // Se cierran los pipes que tienen relacion con el Hijo.
    for (int i = 0; i < countDisk; i++)
    {
        close(listPipesIn[i][0]);
        close(listPipesOut[i][1]);
    }


        for (int i = 0; i < lines; i++)
        {
            
            dist = distance(data[i][0],data[i][1]);   
            
            for (int j = 0; j < countDisk-1; j++)
            {
                
                if (dist >= listDisk[j] && dist < listDisk[j+1])
                {
                    
                    sprintf(text,"%f,%f,%f",data[i][2],data[i][3],data[i][4]);
                    
                    write(listPipesIn[j][1],text,MAX_CHAR);
                    
                                
                }
            }

            if(dist >= listDisk[countDisk-1]){
                
                sprintf(text,"%f,%f,%f",data[i][2],data[i][3],data[i][4]);
                
                write(listPipesIn[countDisk-1][1],text,MAX_CHAR);
                
                                    
            }
            
        }
    

    // Se le envia un FIN a todos los hijos
    for (int i = 0; i < countDisk; i++)
    {
        // Se envia un FIN al hijo para que procese
        write(listPipesIn[i][1],"FIN",MAX_CHAR); 
        
        // Espero a que mis hijos me respondan 
        read(listPipesOut[i][0],text,MAX_CHAR);

        if(text != NULL && strcmp(text,"") != 0){

            float real_avarage;
            float imag_avarage;
            float potency;
            float summatory;

            sscanf(text,"%f,%f,%f,%f",&real_avarage,&imag_avarage,&potency,&summatory);
            
            results[i][0]= real_avarage;
            results[i][1]= imag_avarage;
            results[i][2]= potency;
            results[i][3]= summatory;

        }
    }

    //Liberacion de memoria de los pipes
    for (int i = 0; i < 2; i++)
    {
        free(listPipesIn[i]);
        free(listPipesOut[i]);
    }
    free(listPipesIn);
    free(listPipesOut);
    

    return results;
    
}