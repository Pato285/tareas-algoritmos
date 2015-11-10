#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int debug = 0;
int blocks_written,blocks_read;

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
  FILE *fp;
} SMemory;

void initSMemory(SMemory *sm){
  if (debug) {fprintf(stdout, "Creating working file %s\n",sm->name );}
  FILE *f = fopen(sm->name, "wb+");
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
  Block *block = (Block*) malloc(sizeof(Block));
  block->offset = sm->elem_size * pointer;
  block->data = malloc(sm->elem_size);
  memcpy(block->data,data,sm->elem_size);
  return block;
}

void FreeBlock(Block *block){
  free(block->data);
  free(block);
}

void WriteBlock(SMemory *sm,Block *block){
  /*if (debug) {fprintf(stdout, "Writing block with pointer %zu\n",block->offset/sm->elem_size);}*/

  if (fseek(sm->fp, block->offset, SEEK_SET) != 0){
    printf("Error in seek operation");
    exit(1);
  }
  fwrite(block->data,sm->elem_size,1,sm->fp);
  blocks_written++;
  if (ferror(sm->fp)){
   printf("Error on Write.");
   exit(1);
  }
}

Block *ReadBlock(SMemory *sm,int pointer){
  /*if (debug) {fprintf(stdout, "Reading block with pointer %i\n",pointer );}*/

  Block *block = (Block*) malloc(sizeof(Block));
  block->offset = sm->elem_size * pointer;
  block->data = malloc(sm->elem_size);

  if (fseek(sm->fp, block->offset, SEEK_SET) != 0){
    printf("Error in seek operation");
    exit(1);
  }
  fread(block->data,sm->elem_size,1,sm->fp);
  blocks_read++;
  if (ferror(sm->fp)){
   printf("Error while trying to Read.");
   exit(1);
  }
  return block;
}

/*==============================================*/
/* TESTING I/O */
void test_io(){
  fprintf(stdout, "Testing I/O: writing and reading");
  blocks_written = blocks_read = 0;
  SMemory sm;
  sm.name = "mem_test.bin";
  sm.elem_size = 11;
  initSMemory(&sm);
  const char* const text[] = {"123456789","abcdefghi","!#$¡&/()=" };
  for (size_t i = 0; i < 100; i++) {
    Block *b0 = MakeBlock(&sm,(void*)text[i%3],0);
    Block *b1 = MakeBlock(&sm,(void*)text[(i+1)%3],1);
    Block *b2 = MakeBlock(&sm,(void*)text[(i+2)%3],2);

    // fprintf(stdout, "Block 0 - offset: %i\tdata: %s\n",(int)b0->offset,(char*)b0->data);
    // fprintf(stdout, "Block 1 - offset: %i\tdata: %s\n",(int)b1->offset,(char*)b1->data);
    // fprintf(stdout, "Block 2 - offset: %i\tdata: %s\n",(int)b2->offset,(char*)b2->data);

    WriteBlock(&sm,b0);
    WriteBlock(&sm,b1);
    WriteBlock(&sm,b2);

    FreeBlock(b0);
    FreeBlock(b1);
    FreeBlock(b2);

    b0 = ReadBlock(&sm,0);
    b1 = ReadBlock(&sm,1);
    b2 = ReadBlock(&sm,2);

    if (strcmp((char*)b0->data,text[i%3])!=0){fprintf(stdout, "Error I/O should return equal strings.\n"); exit(1);}
    if (strcmp((char*)b1->data,text[(i+1)%3])!=0){fprintf(stdout, "Error I/O should return equal strings.\n"); exit(1);}
    if (strcmp((char*)b2->data,text[(i+2)%3])!=0){fprintf(stdout, "Error I/O should return equal strings.\n"); exit(1);}

    // fprintf(stdout, "Block 0 has data '%s' and should be '%s'\n",(char*)b0->data,text[i%3]);
    // fprintf(stdout, "Block 1 has data '%s' and should be '%s'\n",(char*)b1->data,text[(i+1)%3]);
    // fprintf(stdout, "Block 2 has data '%s' and should be '%s'\n",(char*)b2->data,text[(i+2)%3]);

    FreeBlock(b0);
    FreeBlock(b1);
    FreeBlock(b2);
  }
  disposeSMemory(&sm);
  fprintf(stdout, "OK. Blocks written: %i\tBlocks read: %i\n",blocks_written, blocks_read);
}

void test_bigfile(){
  fprintf(stdout, "Testing I/O: write a big file then read it.\n");
  blocks_written = blocks_read = 0;
  SMemory sm;
  sm.name = "mem_test.bin";
  sm.elem_size = sizeof(int);
  initSMemory(&sm);
  int i;
  Block *b;
  for (i = 0; i < 1000000; i++) {
    int j = i%256;
    b = MakeBlock(&sm,(void*)&j,i);
    WriteBlock(&sm,b);
    FreeBlock(b);
  }
  for (i = 0; i < 1000000; i++) {
    b = ReadBlock(&sm,i);
    /*fprintf(stdout, "%i==%i\n",((int)*b->data),i%256);*/
    if (((int)*b->data)!=i%256){fprintf(stdout, "Error I/O should return equal numbers.\n"); exit(1);}
    FreeBlock(b);
  }
  disposeSMemory(&sm);
  fprintf(stdout, "OK. Blocks written: %i\tBlocks read: %i\n",blocks_written, blocks_read);
}

void test_structure(){
  fprintf(stdout, "Testing I/O: write and read a structure.\n");
  blocks_written = blocks_read = 0;
  SMemory sm;
  sm.name = "mem_test.bin";

  struct apple {
    float freshness;int color;char* name;
  };

  struct apple ap;

  ap.freshness = 0.783;
  ap.color = 0xff0000;
  ap.name = "Mapple the apple.";

  sm.elem_size = sizeof(struct apple);
  initSMemory(&sm);
  int i;
  Block *b;
  for (i = 0; i < 50; i++) {
    b = MakeBlock(&sm,(void*)&ap,i);
    WriteBlock(&sm,b);
    FreeBlock(b);
  }
  for (i = 0; i < 50; i++) {
    b = ReadBlock(&sm,i);
    struct apple *pa = (struct apple*) b->data;
    /*fprintf(stdout, "%f\t%x\t%s\n",pa->freshness,pa->color,pa->name);*/
    if (pa->freshness!=ap.freshness){fprintf(stdout, "Error I/O: wrong apple freshness.\n"); exit(1);}
    if (pa->color!=ap.color){fprintf(stdout, "Error I/O: wrong apple color.\n"); exit(1);}
    if (strcmp(pa->name,ap.name)!=0){fprintf(stdout, "Error I/O: wrong apple name.\n"); exit(1);}
    FreeBlock(b);
  }
  disposeSMemory(&sm);
  fprintf(stdout, "OK. Blocks written: %i\tBlocks read: %i\n",blocks_written, blocks_read);
}


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
    fprintf(stdout, "Begin testing I/O.\n\n");
    test_io();
    test_bigfile();
    test_structure();
    fprintf(stdout, "I/O is OK.\n");
  }
}
