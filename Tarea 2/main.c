#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*==============================================*/

typedef struct {
  char *buffer;
  int length;
  int offset;
} Block;

FILE* openfile(const char* name){
  FILE *f = fopen(name, "w");
  if (f == NULL){
      printf("Error opening file!: %s\n",name);
      exit(1);
  }
  return f;
}

void closefile(FILE *f){
  fclose(f);
}

void writeBlock(){}

void readBlock(){}

/*==============================================*/

/*B-TREES*/

/*HASHING LINEAL*/

/*HASHING EXTENDIBLE*/

/*==============================================*/

int main(int argc, char const *argv[]){
}
