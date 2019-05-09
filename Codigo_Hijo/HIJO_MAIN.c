# include "HIJO.c"

//Procedimiento Main que da el inicio al programa.
//Entrada: Vacia.
//Salida: Entero 0 que representa que se termino la ejecucion del programa.
int main(int argc, char *argv[]){

    // Estas serán las variables donde se acumularán los distintos datos.
    double sumR;
    double sumI;
    double sumW;
    double n;           

    // Estas serán las variables donde se guardarán el resultado de cada propiedad.
    double realA;
    double imaginaryA;
    double pot;

    //////////////////////////////////////////////////////////
    // AQUI VA EL WHILE (STRCMP(PALABRA_ENTRADA,"FIN") != 0)
    // read(STRDIN,list[5],sizeof(list[5]))
    // sumR += list[3];
    // sumI += list[4];
    // sumW += list[5];
    // n += 5;
    //////////////////////////////////////////////////////////
    // CUANDO TERMINA EL WHILE, SE LLAMAN A LOS PROCEDIMIENTOS.
    // realA = realAverage(sumR,n);            // Donde n el el numero de visibilidades del disco
    // imaginaryA = imaginaryAverage(sumI,n);  // Donde n el el numero de visibilidades del disco
    // pot = potency(sumR,sumI);               
    // EN EL CASO DE sumW, no hay procedimiento por que la propiedad que lo utiliza es una simple sumatoria.
    //////////////////////////////////////////////////////////
    // Crear nueva list para poder decirle al padre que se termino la ejecución del hijo y entregarle los resultados.
    // write(STDOUT,list[5],sizeof(list[5]))
    //////////////////////////////////////////////////////////
    
    return 0;
}