#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(){
    char buffer[100];
    read(STDIN_FILENO,buffer,100);
    write(STDOUT_FILENO, "hola",4);
    return 0;
}