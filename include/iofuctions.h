#ifndef IOFUCTIONS_H
    
    #define IOFUCTIONS_H
    
    float** readFile(char *file,int lines);
    int countLines(char *file);
    void getArgs(int argc, char *argv[], int *n_disk, int* n_whgt, char* in_file, char* out_file, int *flag);
    void writeFile(char* fileName, float** data, int disk);

#endif
