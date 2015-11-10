#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int debug = 0;

/*==============================================*/

/*
 * Vamos a abrir un archivo binario para manejar la memoria secundaria
 * en este archivo escribiremos y leeremos bloques.
 *
 * Los bloques son arreglos de estructuras.
 * Para recuperar los datos almacenados debemos hacer un cast de dicho arreglo.
 *
 */

typedef struct {
  const char* name;
  size_t elem_size;
  File *fp;
} SMemory;

void initSMemory(SMemory *sm){
  if (debug) {fprintf(stdout, "Creating working file %s\n",sm->name );}
  FILE *f = fopen(sm->name, "rb+");
  if (f == NULL){
      printf("Error opening binary file: %s\n",sm->name);
      exit(1);
  }
  sm->fp = f;
}

void disposeSMemory(SMemory *sm){
  fclose(sm->fp);
}

typedef struct {
  size_t offset;
  unsigned char *data;
} Block;

Block *MakeBlock(SMemory *sm,void *data, int pointer){
  Block *block = (Block) malloc(sizeof(Block));
  block->offset = sm->elem_size * pointer;
  block->data = malloc(sm->elem_size);
  memcpy(block->data,data,sizeof(*data));
}

void FreeBlock(Block *block){
  free(block->data);
  free(block);
}

void WriteBlock(SMemory *sm,Block *block){
  if (debug) {fprintf(stdout, "Writing block with pointer %i\n",block->offset/sm->elem_size );}

  if (fseek(sm->fp, block->offset, SEEK_SET) != 0){
    printf("Error in seek operation");
    exit(1);
  }
  fwrite(block->data,sm->elem_size,1,sm->fp);
  if (ferror()){
   printf("Error on Write.");
   exit(1);
  }
}

Block *ReadBlock(SMemory *sm,int pointer){
  if (debug) {fprintf(stdout, "Reading block with pointer %i\n",pointer );}

  Block *block = (Block) malloc(sizeof(Block));
  block->offset = sm->elem_size * pointer;
  block->data = malloc(sm->elem_size);

  if (fseek(sm->fp, block->offset, SEEK_SET) != 0){
    printf("Error in seek operation");
    exit(1);
  }
  fread(block->data,sm->elem_size,1,fp);
  if (ferror()){
   printf("Error while trying to Read.");
   exit(1);
  }
}

/*==============================================*/

/*==============================================*/

/*B-TREES*/

/*HASHING LINEAL*/

/*HASHING EXTENDIBLE*/

/*==============================================*/

int main(int argc, char const *argv[]){
  if (argc >= 2){
    if (argv[1][0]=='-')
    debug = 1;
  }

  /*Testing I/O operations*/
  if(debug && argv[1][1]=='w'){
    SMemory sm;

    sm.name = "sec_mem.bin";
    sn.elem_size = sizeof(char)*10;
    initSMemory(&sm);

    Block *b0 = MakeBlock(&sm,"0123456789",0);
    Block *b1 = MakeBlock(&sm,"abcdefghij",0);
    Block *b2 = MakeBlock(&sm,"!#$¡&/()=?",0);

    WriteBlock(&sm,b0);
    WriteBlock(&sm,b1);
    WriteBlock(&sm,b2);

    FreeBlock(b0);
    FreeBlock(b1);
    FreeBlock(b2);

    b0 = ReadBlock(&sm,0);
    b1 = ReadBlock(&sm,1);
    b2 = ReadBlock(&sm,2);

    fprintf(stdout, "Block 0 has data '%s' and should be '0123456789'\n",(char*)b0->data);
    fprintf(stdout, "Block 1 has data '%s' and should be 'abcdefghij'\n",(char*)b0->data);
    fprintf(stdout, "Block 2 has data '%s' and should be '!#$¡&/()=?'\n",(char*)b0->data);

    FreeBlock(b0);
    FreeBlock(b1);
    FreeBlock(b2);

    disposeSMemory(&sm);
  }
}