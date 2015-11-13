#include "test.h"

/*
 * This test verifies that we can read and write on a file, and that the
 * rewriting still returns the correct values.
 */
void test_io(){
  fprintf(stdout, "> Testing I/O: writing and reading.\n");
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

    WriteBlock(&sm,b0);blocks_written++;
    WriteBlock(&sm,b1);blocks_written++;
    WriteBlock(&sm,b2);blocks_written++;

    FreeBlock(b0);
    FreeBlock(b1);
    FreeBlock(b2);

    b0 = ReadBlock(&sm,0);blocks_read++;
    b1 = ReadBlock(&sm,1);blocks_read++;
    b2 = ReadBlock(&sm,2);blocks_read++;

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
  fprintf(stdout, "OK. Blocks written: %i\tBlocks read: %i\n\n",blocks_written, blocks_read);
}

/*
 * This test verifies that we can read and write on a large file (1MB)
 * We verify that the elements read are the same we wrote.
 */
void test_bigfile(){
  fprintf(stdout, "> Testing I/O: write a big file then read it.\n");
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
    blocks_written++;
    FreeBlock(b);
  }
  for (i = 0; i < 1000000; i++) {
    b = ReadBlock(&sm,i);
    blocks_read++;
    /*fprintf(stdout, "%i==%i\n",((int)*b->data),i%256);*/
    if (((int)*b->data)!=i%256){fprintf(stdout, "Error I/O should return equal numbers.\n"); exit(1);}
    FreeBlock(b);
  }
  disposeSMemory(&sm);
  fprintf(stdout, "OK. Blocks written: %i\tBlocks read: %i\n\n",blocks_written, blocks_read);
}

/*
 * This test verifies that we can read and write a structure.
 * We write an structure then we read it and the elements stay the same.
 */
void test_structure(){
  fprintf(stdout, "> Testing I/O: write and read a structure.\n\n");
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
    blocks_written++;
    WriteBlock(&sm,b);
    FreeBlock(b);
  }
  for (i = 0; i < 50; i++) {
    b = ReadBlock(&sm,i);
    blocks_read++;
    struct apple *pa = (struct apple*) b->data;
    /*fprintf(stdout, "%f\t%x\t%s\n",pa->freshness,pa->color,pa->name);*/
    if (pa->freshness!=ap.freshness){fprintf(stdout, "Error I/O: wrong apple freshness.\n"); exit(1);}
    if (pa->color!=ap.color){fprintf(stdout, "Error I/O: wrong apple color.\n"); exit(1);}
    if (strcmp(pa->name,ap.name)!=0){fprintf(stdout, "Error I/O: wrong apple name.\n"); exit(1);}
    FreeBlock(b);
  }
  disposeSMemory(&sm);
  fprintf(stdout, "OK. Blocks written: %i\tBlocks read: %i\n\n",blocks_written, blocks_read);
}
