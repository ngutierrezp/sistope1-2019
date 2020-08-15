
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/colors.h"
#include "../include/utility.h"
#include "../include/defines.h"
#include "../include/iofuctions.h"

float** readFile(char *file,int lines)
{
    // se cuentan las lineas del archivo    
    int  i, security_chain;
    float current_distance;
    char buffer[MAX_CHAR],*ptr;
    
    // 5 dada la cantidad de columnas 
    float** listVisibility = (float**)malloc(sizeof(float*)*lines);
    for (int j = 0; j < lines; j++)
    {
        listVisibility[j] = (float*)malloc(sizeof(float)*5);
    }
   
    

    // se abre el archivo a leer 
    FILE *_file_pointer = fopen(file, "r");

    // se hace un ciclo la lectura de lineas
    for (i = 0; i < lines; i++)
    {
        // esta parte realiza la lectura de solo una linea
        // Es importante dejar el espacio en " %[^\n]" 
        fscanf(_file_pointer, " %[^\n]", buffer);
        
        
        //se limpian los espacios en caso de que hayan.
        while (strchr(buffer, ' ') != NULL)
        {
            removeChar(buffer, ' ');
        }
        
        ptr = strtok(buffer,",");
        security_chain = 0;
        while (ptr != NULL)
        {
            listVisibility[i][security_chain] = atof(ptr);
            security_chain++;
            ptr = strtok(NULL,",");
        }
        

    }
    fclose(_file_pointer);
    return listVisibility;
}


int countLines(char *file)
{
    int lines = 1, flag = 0;
    char ch;
    FILE *_file_pointer = fopen(file, "r");

    //ciclo que va rescatando cada caracter del archivo
    while ((ch = fgetc(_file_pointer)) != EOF)
    {
        // para cualquier caracter distinto de un salto de linea
        // la bandera sera 1 = hay caracteres en una linea
        if (ch != '\n')
        {
            flag = 1;
        }
        // si se lee un caracter y la bandera sigue en 1, se suma 1 a las 
        // lineas
        if (ch == '\n' && flag == 1)
        {
            lines++;
            flag = 0;
        }
    }

    // Si la bandera es 0 quiere decir que no hay caracteres en la linea
    if (flag == 0)
    {
        lines--;
    }

    fclose(_file_pointer);
    return lines;
}


void getArgs(int argc, char *argv[], int *n_disk, int* n_whgt, char* in_file, char* out_file, int *flag){
	int opt;
	char *aux3[AUX_CHAR];
	if(argc < 9){
		printf(ROJO_T"[ERROR]"RESET_COLOR" Faltan argumentos en la linea de comandos\n");
		printf(AMARILLO_T"[USE]"RESET_COLOR" %s -i [nombre archivo entrada] -o [nombre archivo de salida] -d [ancho] -n [numero de discos] [-b]\n", argv[0]);
        exit(FAIL);
	}
	int disks = NOT_ACTIVE;
    int whtg = NOT_ACTIVE;
	while((opt = getopt(argc, argv, "i:o:d:n:b")) != -1) { 
	   switch(opt) {
	   case 'b':
		   *flag = ACTIVE;
		   break;
	   case 'n': 
		   disks = strtol(optarg, aux3, 10);
		   if(optarg!=0 && disks==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-n] no puede quedar vacia");
			}
		   break;
        case 'd': 
		   whtg = strtol(optarg, aux3, 10); 
		   if(optarg!=0 && whtg==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-d] no puede quedar vacia\n");
			}
		   break;
        case 'i': 
		   if(optarg==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-i] no puede quedar vacia\n");
			}
            else {
                strcpy(in_file,optarg);   
            }
		   break;
        case 'o': 

		   if(optarg==0 ){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-o] no puede quedar vacia\n");
			}
            else{
                strcpy(out_file,optarg);
                
            }
            
		   break;
	   default: 
		   printf(AMARILLO_T"[WARN]"RESET_COLOR" use: %s -i [nombre archivo entrada] -o [nombre archivo de salida] -d [ancho] -n [numero de discos] [-b]\n", argv[0]);
		   exit(FAIL);
	   }
	}
    
	(*n_disk) = disks;
    (*n_whgt) = whtg;
}

void writeFile(char* fileName, float** data, int disk){

    FILE* _file = fopen(fileName ,"w");

    for (int i = 0; i < disk; i++)
    {
        fprintf(_file,"Disco : %i\n",i+1);
        fprintf(_file,"Media Real: %f\n",data[i][0]);
        fprintf(_file,"Media imaginaria: %f\n",data[i][1]);
        fprintf(_file,"Potencia: %f\n",data[i][2]);
        fprintf(_file,"Ruido total: %f\n",data[i][3]);
    }
    fclose(_file);
}