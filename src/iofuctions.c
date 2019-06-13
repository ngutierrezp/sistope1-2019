
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/colors.h"
#include "../include/defines.h"
#include "../include/utility.h"
#include "../include/globals.h"


int verifyFile(char* _input_file_)
{

    FILE* file = fopen(_input_file_,"r");

    if( file == NULL){
         printf(ROJO_T"[ERROR]"RESET_COLOR" El archivo de entrada '"AMARILLO_T"%s"RESET_COLOR"' no existe.\n",_input_file_);
        fclose(file);
        return FALSE;
    }
    fclose(file);
    return TRUE;
    
}

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

void getArgs(int argc, char *argv[], int *n_disk, int* n_whgt, int* buf_size, char* in_file, char* out_file, int *flag)
{
    /*
     • -i:  nombre de archivo con visibilidades
     • -o:  nombre de archivo de salida
     • -n:  cantidad de discos
     • -d:  ancho de cada disco
     • -s:  tamaño del buffer de cada monitor
     • -b:  bandera o flag 
     */
    int opt;
	char *aux3[AUX_CHAR];
	if(argc < 11){
		printf(ROJO_T"[ERROR]"RESET_COLOR" FALTAN argumentos en la linea de comandos\n");
		printf(AMARILLO_T"[USE]"RESET_COLOR" %s -i [nombre archivo entrada] -o [nombre archivo de salida] -d [ancho] -n [numero de discos] -s [tamaño del buffer] [-b]\n", argv[0]);
        exit(FAIL);
	}
    if(argc > 12){
		printf(ROJO_T"[ERROR]"RESET_COLOR" DEMASIADOS argumentos en la linea de comandos\n");
		printf(AMARILLO_T"[USE]"RESET_COLOR" %s -i [nombre archivo entrada] -o [nombre archivo de salida] -d [ancho] -n [numero de discos] -s [tamaño del buffer] [-b]\n", argv[0]);
        exit(FAIL);
	}
	int disks = NOT_ACTIVE;
    int whtg = NOT_ACTIVE;
    int buffer = NOT_ACTIVE;

	while((opt = getopt(argc, argv, "i:o:d:n:s:b")) != -1) {
	   switch(opt) {
	   case 'b':
		   (*flag) = ACTIVE;
		   break;
	   case 'n': 
		   disks = strtol(optarg, aux3, 10);
		   if(optarg!=0 && disks==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-n] no puede quedar vacia");
                exit(EXIT_FAILURE);
			}
            else if(disks < 0) 
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-n] no puede tener numeros negativos");
                exit(EXIT_FAILURE);
            }
            else
            {
                (*n_disk) = disks;
            }
            
		   break;
        case 's': 
		   buffer = strtol(optarg, aux3, 10);
		   if(optarg!=0 && buffer==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-s] no puede quedar vacia");
                exit(EXIT_FAILURE);
			}
            else if(buffer < 0) 
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-s] no puede tener numeros negativos");
                exit(EXIT_FAILURE);
            }
            else
            {
                (*buf_size) = buffer;
            }
		   break;
        case 'd': 
		   whtg = strtol(optarg, aux3, 10); 
		   if(optarg!=0 && whtg==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-d] no puede quedar vacia\n");
                exit(EXIT_FAILURE);
			}
            else if(whtg < 0) 
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-d] no puede tener numeros negativos");
                exit(EXIT_FAILURE);
            }
            else
            {
                (*n_whgt) = whtg;
            }
		   break;
        case 'i': 
		   if(strcmp(optarg,"-i")==0 || 
              strcmp(optarg,"-o")==0 || 
              strcmp(optarg,"-d")==0 ||
              strcmp(optarg,"-n")==0 ||
              strcmp(optarg,"-b")==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-i] no puede quedar vacia\n");
                exit(EXIT_FAILURE);
			}
            else if (strcmp(out_file,optarg)==0)
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-i] no puede tener el mismo nombre que la salida.\n");
                exit(EXIT_FAILURE);
            }
            else {
                strcpy(in_file,optarg);   
            }
		   break;
        case 'o': 
		   if(strcmp(optarg,"-i")==0 || 
              strcmp(optarg,"-o")==0 || 
              strcmp(optarg,"-d")==0 ||
              strcmp(optarg,"-n")==0 ||
              strcmp(optarg,"-b")==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-o] no puede quedar vacia\n");
                exit(EXIT_FAILURE);
			}
            else if (strcmp(in_file,optarg)==0)
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-o] no puede tener el mismo nombre que la entrada.\n");
                exit(EXIT_FAILURE);
            }
            else{
                strcpy(out_file,optarg);
                
            }
            
		   break;
	   default: 
		   printf(AMARILLO_T"[WARN]"RESET_COLOR" use: %s -i [nombre archivo entrada] -o [nombre archivo de salida] -d [ancho] -n [numero de discos] [-b]\n", argv[0]);
		   exit(EXIT_FAILURE);
	   }
	}
}

void writeFile(char* fileName, int disk)
{

    FILE* _file = fopen(fileName ,"w");

    for (int i = 0; i < disk; i++)
    {
        fprintf(_file,"Disco : %i\n",i+1);
        fprintf(_file,"Media Real: %f\n",global_properties[i].realAvarage);
        fprintf(_file,"Media imaginaria: %f\n",global_properties[i].imaginaryAverage);
        fprintf(_file,"Potencia: %f\n",global_properties[i].potency);
        fprintf(_file,"Ruido total: %f\n",global_properties[i].noise);
    }
    fclose(_file);
}