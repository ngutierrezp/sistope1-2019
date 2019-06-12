#ifndef IOFUNCTIONS_H

    #define IOFUNCTIONS_H
    /*
    Funcion terrible cuatica.

    @param argc: entero

    */
    void getArgs(int argc, char *argv[], int *n_disk, int* n_whgt, int* buf_size, char* in_file, char* out_file, int *flag);
    int verifyFile(char* _input_file_);
    
#endif