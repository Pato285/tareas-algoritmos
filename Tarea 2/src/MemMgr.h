#ifndef MEMMGR
#define MEMMGR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int debug;
extern int blocks_written, blocks_read;

typedef struct {
  const char* name;
  size_t elem_size;
  FILE *fp;
} SMemory;

void initSMemory(SMemory *sm);

void disposeSMemory(SMemory *sm);

typedef struct {
  size_t offset;
  unsigned char *data;
} Block;

Block *MakeBlock(SMemory *sm,void *data, int pointer);

void FreeBlock(Block *block);

void WriteBlock(SMemory *sm,Block *block);

Block *ReadBlock(SMemory *sm,int pointer);
#endif
