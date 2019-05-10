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
    
    int** listPipesIn;
    int** listPipesOut;
    for (int i = 0; i < countDisk; i++)
    {
        listPipesIn[i][2];        
        listPipesOut[i][2];
    }
    
    int pid = fork();
    for (int i = 0; i < countDisk; i++)
    {
        if (getpid() == padre)
        {
            fprintf(stderr,"PipePadreAntes\n");
            /* Soy el padre original*/
            pipe(listPipesIn[i]);
            pipe(listPipesOut[i]);
            fprintf(stderr,"PipePadreDespues\n");
            
            if (i < countDisk-1)
            {
                pid = fork();    
            }
        }
        else if (pid == 0)
        {
            /* Soy el hijo */
            int child = getpid();
            fprintf(stderr,"Hijo Antes del DUP2\n");
            dup2(listPipesIn[i][0],STDIN_FILENO); // Lectura Padre-> Hijo (hijo lee padre)
            dup2(listPipesOut[i][1],STDOUT_FILENO); // Escritura Hijo -> Padre
            fprintf(stderr,"Hijo Despues del DUP2 y antes de cerrar Pipes\n");
            close(listPipesIn[i][1]); // Escritura -> Padre->Hijo
            close(listPipesOut[i][0]); // Lectura Hijo -> Padre (padre lee hijo)
            
            //printf("soy el hijo : %i (%i), y tengo el disco [%i]\n",i+1,child,listDisk[i]);
            fprintf(stderr,"Hijo despues de cerrar el Pipe\n");
            break;
        }
    }
    float dist=-1;

    // Si soy el padre, enviaré la informacion a los pipes
    if (pid > 0){
        for (int i = 0; i < lines; i++)
        {
            fprintf(stderr,"Proceso Padre\n");
            dist = distance(data[i][0],data[i][1]);   
            for (int j = 0; j < countDisk-1; j++)
            {

                if (dist >= listDisk[j] && dist < listDisk[j+1])
                {
                    
                    char text[MAX_CHAR];
                    sprintf(text,"%f,%f,%f",data[i][2],data[i][3],data[i][4]);
                    fprintf(stderr,"1 Proceso Padre antes de WRITE\n");
                    write(listPipesIn[j][1],text,strlen(text));
                    fprintf(stderr,"1 Proceso Padre despues de WRITE\n");
                    // printf("la distancia es : %f, y pertener al disco : %i\n",dist,j);
                }
            }

            if(dist >= listDisk[countDisk-1]){
            
                char text[MAX_CHAR];
                sprintf(text,"%f,%f,%f",data[i][2],data[i][3],data[i][4]);
                fprintf(stderr,"2 Proceso Padre antes de WRITE\n");
                write(listPipesIn[countDisk-1][1],text,strlen(text));
                fprintf(stderr,"2 Proceso Padre despues de WRITE\n");
                //printf("la distancia es : %f, y pertener al disco : %i\n",dist,countDisk-1);
                
            }
                
        
        }
        // Se terminó el envio de datos
    }


    // Si soy algun hijo, ejecutare el archivo vis
    if (pid == 0)
    {
        fprintf(stderr,"Proceso Hijo antes de ejecutar vis\n");
        execl("./vis.out","./vis.out",(const char*)NULL);
        fprintf(stderr,"Proceso Hijo despues de ejecutar vis\n");
        _exit(EXIT_SUCCESS);
    }
    

    // Se le envia un FIN a todos los hijos
    for (int i = 0; i < countDisk; i++)
    {
        if (pid > 0)
        {
            char text[MAX_CHAR];
            fprintf(stderr,"Proceso Padre antes enviar FIN\n");
            write(listPipesIn[i][1],"FIN",3); // Se envia un FIN al hijo para que procese
            fprintf(stderr,"Proceso Padre despues enviar FIN\n");

            // Se espera a que el hijo termine
            wait(&status);

            // Se lee lo que ha escrito el hijo
            fprintf(stderr,"Proceso Padre antes de leer del hijo\n");
            read(listPipesOut[i][0],text,100);
            fprintf(stderr,"Proceso Padre despues de leer del hijo y lei : %f \n",text);
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
        
    }
    return results;

}