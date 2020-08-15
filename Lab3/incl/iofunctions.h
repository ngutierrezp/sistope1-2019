#ifndef IOFUCTIONS_H
#define IOFUCTIONS_H

void getArgs(int argc, char *argv[], int *n_floors, int* n_elevators, char* up_file, char* down_file, char* other_file, int *flag);
int countLines(char *file);
int verifyFile(char* _input_file_);


#endif