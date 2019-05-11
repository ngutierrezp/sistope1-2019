#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>
#include "../include/defines.h"
#include "../include/utility.h"
#include "../include/dad.h"


float** getVisibility(int* listDisk, int countDisk, float** data, int lines)
{
    
    float** results = (float**)malloc(sizeof(float*)*countDisk);
    for (int i = 0; i < countDisk; i++)
    {
        results[i] = (float*)malloc(sizeof(float)*4);
    }
    
    int padre = getpid();
    int status;
    char* ptr;
    char text[MAX_CHAR];
    int** listPipesIn = (int**)malloc(sizeof(int*)*countDisk);
    int** listPipesOut = (int**)malloc(sizeof(int*)*countDisk);
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
        if (getpid() == padre)
        {
            
            if (i < countDisk-1)
            {
                pid = fork();    
            }
        }
        else if (pid == 0)
        {
            // Soy el hijo
            int child = getpid();
            
            dup2(listPipesIn[i][0],STDIN_FILENO); // Lectura Padre-> Hijo (hijo lee padre)
            dup2(listPipesOut[i][1],STDOUT_FILENO); // Escritura Hijo -> Padre
            
            close(listPipesIn[i][1]); // Escritura -> Padre->Hijo
            close(listPipesOut[i][0]); // Lectura Hijo -> Padre (padre lee hijo)
            
            execl("./vis.out","./vis.out",(const char*)NULL);
            
        }
    }
    float dist=-1;

    // Si soy el padre, enviaré la informacion a los pipes
    if (pid > 0){
        for (int i = 0; i < lines; i++)
        {
            
            
            dist = distance(data[i][0],data[i][1]);   
            for (int j = 0; j < countDisk-1; j++)
            {
                
                if (dist >= listDisk[j] && dist < listDisk[j+1])
                {
                    
                    sprintf(text,"%f,%f,%f",data[i][2],data[i][3],data[i][4]);
                    fprintf(stderr,"Proceso Padre antes de WRITE enviando: %s\n",text);
                    write(listPipesIn[j][1],text,MAX_CHAR);
                    //fprintf(stderr,"1 Proceso Padre despues de WRITE\n");
                                
                }
            }

            if(dist >= listDisk[countDisk-1]){
                sprintf(text,"%f,%f,%f",data[i][2],data[i][3],data[i][4]);
                fprintf(stderr,"2 Proceso Padre antes de WRITE enviando: %s\n",text);
                write(listPipesIn[countDisk-1][1],text,MAX_CHAR);
                
                                    
            }
            
                
        
        }
    }
    

    // Se le envia un FIN a todos los hijos
    for (int i = 0; i < countDisk; i++)
    {
        if (pid > 0)
        {
            
            //fprintf(stderr,"Proceso Padre antes enviar FIN\n");
            write(listPipesIn[i][1],"FIN",MAX_CHAR); // Se envia un FIN al hijo para que procese
            //fprintf(stderr,"Proceso Padre despues enviar FIN\n");

            // Se espera a que el hijo termine
            

            // Se lee lo que ha escrito el hijo
            //fprintf(stderr,"Proceso Padre antes de leer del hijo\n");
            read(listPipesOut[i][0],text,MAX_CHAR);
            //fprintf(stderr,"Proceso Padre despues de leer del hijo y lei : %s \n",text);
            int count = 0;
            ptr = strtok(text,",");

            while(ptr != NULL){
                results[i][count] = atof(ptr);
                count++;
                ptr = strtok(NULL,",");
            }

            if (count != 3)
            {
                exit(EXIT_FAILURE);
            }

        }
        wait(&status);
        
    }
    return results;
    
}