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
            fprintf(stderr,"soy el hijo : %i, y tengo el disco %i\n",child,i);
            dup2(listPipesIn[i][0],STDIN_FILENO); // Lectura Padre-> Hijo (hijo lee padre)
            dup2(listPipesOut[i][1],STDOUT_FILENO); // Escritura Hijo -> Padre
            
            close(listPipesIn[i][1]); // Escritura -> Padre->Hijo
            close(listPipesOut[i][0]); // Lectura Hijo -> Padre (padre lee hijo)
            
            execl("./vis.out","./vis.out",(const char*)NULL);
            
        }
    }

    // A partir de ahora solo soy el padre
    float dist=-1;

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
                  //  fprintf(stderr,"Proceso Padre antes de WRITE enviando al disco [%i : %f]: %s\n",j,dist,text);
                    write(listPipesIn[j][1],text,MAX_CHAR);
                    //fprintf(stderr,"1 Proceso Padre despues de WRITE\n");
                                
                }
            }

            if(dist >= listDisk[countDisk-1]){
                sprintf(text,"%f,%f,%f",data[i][2],data[i][3],data[i][4]);
               // fprintf(stderr,"2 Proceso Padre antes de WRITE enviando: %s\n",text);
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

            
            fprintf(stderr,"Soy el padre y estoy recibiendo %s\n",text);
            
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
    return results;
    
}