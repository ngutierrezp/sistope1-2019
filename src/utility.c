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
