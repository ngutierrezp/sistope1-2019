
### Instalación
Se asume que se tienen el compilador gcc y make.

```sh
$ make
```
Este comando genera dos archivos ejecutables, el primero es 'lab1.out' el cual es le principal, el segundo es 'vis.out'
lab1.out ejecuta a vis.out.

El Archivo Makefile hace una limpieza de los archivos residuales de la ultima compilación por lo que no es necesario hacer un ''' make clean ''' (aun que de todas formas es posible hacerlo).

Con esto el código se encuentra listo para su utilización.

### Ejecución

```sh
$ ./lab1.out -i <Archivo de entrada> -o <Archivo de salida> -d <Radio de Disco> -n <Cantidad de Discos> [-b]
```
El parametro de entrada -b, representa una bandera la cual dice si esta activado o no el modo de debug. 

No se debe olvidar hacer un "make clean" antes de un "make"
