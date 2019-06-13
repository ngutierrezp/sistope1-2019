#ifndef UTILITY_H
#define UTILITY_H

void freeArgs(char *in_file, char *out_file, int *disk, int *width, int *flag, int *buffer);
void freeDataRead(float** data, int lines);
void *removeChar(char *str, char garbage);
float distance(float u, float v);

#endif