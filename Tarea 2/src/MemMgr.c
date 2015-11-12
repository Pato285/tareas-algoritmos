#include "MemMgr.h"

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
