
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../incl/colors.h"
#include "../incl/defines.h"


int verifyFile(char* _input_file_)
{

    FILE* file = fopen(_input_file_,"r");

    if( file == NULL){
         printf(ROJO_T"[ERROR]"RESET_COLOR" El archivo de entrada '"AMARILLO_T"%s"RESET_COLOR"' no existe.\n",_input_file_);
        return FALSE;
    }
    fclose(file);
    return TRUE;
    
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

void getArgs(int argc, char *argv[], int *n_floors, int* n_elevators, char* up_file, char* down_file, char* other_file, int *flag)
{
    /*
     • -u:  nombre de archivo de subida
     • -d:  nombre de archivo de bajada
     • -o:  nombre de archivo de normal
     • -n:  cantidad de pisos
     • -e:  cantidad de asensores
     • -b:  bandera o flag 
     */
    int opt;
	char *aux3[AUX_CHAR];
	if(argc < 11){
		printf(ROJO_T"[ERROR]"RESET_COLOR" FALTAN argumentos en la linea de comandos\n");
		printf(AMARILLO_T"[USE]"RESET_COLOR" %s -u [nombre archivo subida] -d [nombre archivo bajada] -o [nombre archivo otro] -n [numero de pisos] -e [numero de elevadores] [-b]\n", argv[0]);
        exit(FAIL);
	}
    if(argc > 12){
		printf(ROJO_T"[ERROR]"RESET_COLOR" DEMASIADOS argumentos en la linea de comandos\n");
		printf(AMARILLO_T"[USE]"RESET_COLOR" %s -u [nombre archivo subida] -d [nombre archivo bajada] -o [nombre archivo otro] -n [numero de pisos] -e [numero de elevadores] [-b]\n", argv[0]);
        exit(FAIL);
	}
	int floors = NOT_ACTIVE;
    int elevators = NOT_ACTIVE;

	while((opt = getopt(argc, argv, "u:d:o:n:e:b")) != -1) {
	   switch(opt) {
	   case 'b':
		   (*flag) = ACTIVE;
		   break;
	   case 'n': 
		   floors = strtol(optarg, aux3, 10);
		   if(optarg!=0 && floors==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-n] no puede quedar vacia");
                exit(EXIT_FAILURE);
			}
            else if(floors < 0) 
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-n] no puede tener numeros negativos");
                exit(EXIT_FAILURE);
            }
            else
            {
                (*n_floors) = floors;
            }
            
		   break;
        case 'e': 
		   elevators = strtol(optarg, aux3, 10);
		   if(optarg!=0 && elevators==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-e] no puede quedar vacia");
                exit(EXIT_FAILURE);
			}
            else if(elevators < 0) 
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-e] no puede tener numeros negativos");
                exit(EXIT_FAILURE);
            }
            else
            {
                (*n_elevators) = elevators;
            }
		   break;
        case 'u': 
		   if(strcmp(optarg,"-b")==0 || 
              strcmp(optarg,"-d")==0 || 
              strcmp(optarg,"-o")==0 ||
              strcmp(optarg,"-n")==0 ||
              strcmp(optarg,"-e")==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-u] no puede quedar vacia\n");
                exit(EXIT_FAILURE);
			}
            else if (strcmp(down_file,optarg)==0)
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-u] no puede tener el mismo nombre que la salida.\n");
                exit(EXIT_FAILURE);
            }
            else {
                strcpy(up_file,optarg);   
            }
		   break;
        case 'd': 
		   if(strcmp(optarg,"-u")==0 || 
              strcmp(optarg,"-o")==0 || 
              strcmp(optarg,"-n")==0 ||
              strcmp(optarg,"-e")==0 ||
              strcmp(optarg,"-b")==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-b] no puede quedar vacia\n");
                exit(EXIT_FAILURE);
			}
            else if (strcmp(up_file,optarg)==0)
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-b] no puede tener el mismo nombre que la entrada.\n");
                exit(EXIT_FAILURE);
            }
            else{
                strcpy(down_file,optarg);
            }
		   break;
        case 'o': 
		   if(strcmp(optarg,"-u")==0 || 
              strcmp(optarg,"-d")==0 || 
              strcmp(optarg,"-n")==0 ||
              strcmp(optarg,"-e")==0 ||
              strcmp(optarg,"-b")==0){
				printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-o] no puede quedar vacia\n");
                exit(EXIT_FAILURE);
			}
            else if (strcmp(up_file,optarg)==0)
            {
                printf(AMARILLO_T"[WARN]"RESET_COLOR " la opcion [-o] no puede tener el mismo nombre que la entrada.\n");
                exit(EXIT_FAILURE);
            }
            else{
                strcpy(other_file,optarg);
            }
		   break;
	   default: 
		   printf(AMARILLO_T"[USE]"RESET_COLOR" %s -u [nombre archivo subida] -d [nombre archivo bajada] -o [nombre archivo otro] -n [numero de pisos] -e [numero de elevadores] [-b]\n", argv[0]);
		   exit(EXIT_FAILURE);
	   }
	}
}

