#include "main.h"
#include "MemMgr.h"
#include "test.h"
#include "BTree.h"
#include "LHash.h"
#include "EHash.h"

/*
 * Vamos a abrir un archivo binario para manejar la memoria secundaria
 * en este archivo escribiremos y leeremos bloques.
 *
 * Los bloques son arreglos de estructuras.
 * Para recuperar los datos almacenados debemos hacer un cast de dicho arreglo.
 *
 */

int main(int argc, char const *argv[]){
  if (argc >= 2){
    if (argv[1][0]=='-')
    debug = 1;
  }
/*Testing I/O operations*/
  if(debug && argv[1][1]=='w'){
    fprintf(stdout, "Begin testing I/O.\n\n");
    test_io();
    test_bigfile();
    test_structure();
    fprintf(stdout, "I/O is OK.\n");
  }
}
