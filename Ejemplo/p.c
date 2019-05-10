#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(){
    int pipeIn[2];
    int pipeOut[2];
    int status;
    pipe(pipeIn);
    pipe(pipeOut);
    int pid = fork();
    if(pid == 0){
        dup2(pipeIn[0],STDIN_FILENO); //lectura Padre ->hijo
        dup2(pipeOut[1],STDOUT_FILENO); // escritura Hijo -> padre
        close(pipeIn[1]);
        //close(pipeIn[0]); //escritura Padre -> hijo
        close(pipeOut[0]);
        //close(pipeOut[1]); //lectura Hijo-> padre
        execl("./h","./h",(const char*)NULL);
    }
    char buffer[100];
    char txt[100];
    //write(pipeIn[1], "chao",4);
    sprintf(txt,"%f",120.22);
    write(pipeIn[1],txt,strlen(txt));
    wait(&status);
    read(pipeOut[0], buffer,100);
    printf("%s\n",buffer);
    return 0;
}