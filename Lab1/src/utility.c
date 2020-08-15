#include <math.h>
#include <stdio.h>
#include "../include/utility.h"

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