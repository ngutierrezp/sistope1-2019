#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/utility.h"

void freeArgs(char *in_file, char *out_file, int *disk, int *width, int *flag, int *buffer)
{

    free(in_file);
    free(out_file);
    free(disk);
    free(width);
    free(flag);
    free(buffer);
}

void freeDataRead(float** data, int lines){
    for (int i = 0; i < lines; i++)
    {
        free(data[i]);
    }
    free(data);
    
}

void *removeChar(char *str, char garbage)
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++)
    {
        *dst = *src;
        if (*dst != garbage)
        {
            dst++;
        }
    }
    *dst = '\0';
}


float distance(float u, float v){

    return sqrt((u*u)+(v*v));
}

