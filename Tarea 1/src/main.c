#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TESTS 1
#define MIN_PAT_EXP 2
#define MAX_PAT_EXP 7
#define MAX_TEXT_SIZE 1000000

#define MAX(a,b) (((a)>(b))?(a):(b))

/*==============================================*/

FILE *openLog(const char* name){
  FILE *f = fopen(name, "w");
  if (f == NULL){
      printf("Error opening file!: %s\n",name);
      exit(1);
  }
  return f;
}

/*==============================================*/

int loadBuffer(char *filename,char* buffer){
  FILE *in;
  size_t read;
  in = fopen(filename, "r");
  if (in == NULL){
    printf("Error opening file!: %s\n",filename);
    exit(1);
  }

  /*copy to buffer*/
  read = fread(buffer, 1, MAX_TEXT_SIZE, in);
  if (ferror(in)){
    printf ("Error reading %s\n",filename);
    fclose(in);
    exit(1);
  }
  if (read!=MAX_TEXT_SIZE) printf("Warning: there are only %zd characters in %s.\n",read,filename);
  for (size_t i = read; i <= MAX_TEXT_SIZE+1; i++) {
    buffer[i] = 0;
  }
  fclose(in);
  return read;
}

/*==============================================*/

int comparison_counter, start_time, end_time, iteration, pattern_length, text_length;
/*filenames and algorithm name*/
char *test_algorithm;
char *test_dataset;

/*actual text and pattern buffers*/
char *text_buffer;
char *pattern_buffer;

void configureTest(char *algorithm,char *dataset){
  iteration = 0;
  test_algorithm = algorithm;
  test_dataset = dataset;
  /*open the dataset and load to memory*/
  text_length = loadBuffer(dataset,text_buffer);
}

void choosePattern(int i){
  int r;
  pattern_length = 1<<i;
  /*load the pattern to buffer*/
  if (text_length<pattern_length){
    printf("Error: Pattern to large for text\n");
    exit(3);
  }
  r = rand() % MAX(1,text_length-pattern_length);
  for (size_t i = 0;  i<(1<<MAX_PAT_EXP)+1; i++) {
    pattern_buffer[i] = i<pattern_length? text_buffer[r+i] : 0;
  }
}

void beginTest(){
  comparison_counter = 0;
  start_time = clock();
}

int compareCharacters(char a, char b){
  comparison_counter++;
  return a==b;
}

void registerTest(FILE *log){
  double time_spent;

  end_time = clock();
  time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

  /*write down the relevant data on log*/
  /* ALGORITHM | DATASET | PATTERN LENGTH | ITERATION | TIME | COMPARISON */
  fprintf(log,"%s\t%s\t%i\t%i\t%f\t%i\n",test_algorithm,test_dataset+8,pattern_length,iteration,time_spent,comparison_counter);
}

typedef void (*TestedFunction)(char*, char*, int*);

void runTest(char *algorithm, char *dataset, FILE *f,TestedFunction test){
  int *answer;
  configureTest(algorithm,dataset);
  for (size_t j = MIN_PAT_EXP; j <= MAX_PAT_EXP; j++) {
    choosePattern(j);
    for (size_t i = 0; i < MAX_TESTS; i++) {
      beginTest();

      /*execute tested algorithm*/
      test(text_buffer,pattern_buffer,answer);

      registerTest(f);
    }
  }
}

/*==============================================*/

/*these are the actual implementations of the algorithms*/
void funBF(char *text, char *pattern, int *answer){
  /*TODO: Confimr its working*/
  for (size_t i = 0; i < text_length+1-pattern_length; i++) {
    for (size_t j = 0; j < pattern_length; j++) {
      if (!compareCharacters(text_buffer[i+j],pattern_buffer[j])) break;
      if (j==pattern_length-1) *answer = i+1;
    }
  }
}

void funKMP(char *text, char *pattern, int *answer){
  /*TODO: REQUIERES CHECKING CAUSES A SEGFAULT AT PATTERN STEP
  char f[pattern_length];
  int j,i;
  f[0] = 0;
  j = 0;
  while (j<pattern_length) {
    i = f[j];
    while (i>0 && !compareCharacters(pattern_buffer[i],pattern_buffer[j])) {
      i = f[i];
    }
    if(compareCharacters(pattern_buffer[i],pattern_buffer[j])) f[j] = i;
    else f[j] = 0;
    j++;
  }
  printf("hello\n");
  i = j = 0;
  while (i<text_length) {
    while (j>0 && !compareCharacters(text_buffer[i],pattern_buffer[j])) {
      j = f[j];
    }
    if (compareCharacters(text_buffer[i],pattern_buffer[j])) j++;
    if (j==pattern_length){
      i = i-j+1;
      *answer = i+1;
      printf("%i,\n",i+1 );
      j = 0;
    }
    i++;
  }
  printf("\n");*/
}

void funBMH(char *text, char *pattern, int *answer){
  /*TODO: Check if it working*/
  int i,j;
  i = j = pattern_length;
  while (i<=text_length) {
    if(j==0){
      *answer = i-pattern_length+1;
      printf("%d,",i-pattern_length+1);
      j = pattern_length;
      i++;
    }
    else if (compareCharacters(text_buffer[i-(pattern_length-j)],pattern_buffer[j])) j--;
    else {
      i = i+(pattern_length- (strrchr(pattern_buffer,text_buffer[i])-pattern_buffer) +1);
      j = pattern_length;
    }
  }
  printf("\n");
}

/*==============================================*/

int main(int argc, char const *argv[]){
  char* file_name, test_name;
  FILE *f;

  /*setting the seed for random*/
  srand(time(NULL));

  /*Allocate ONCE the text working buffer*/
  text_buffer = (char*) malloc(sizeof(char)*(MAX_TEXT_SIZE+1));
  if (text_buffer == NULL) {printf("Failed to allocate text memory!\n");exit(2);}
  pattern_buffer = (char*) malloc(sizeof(char)*((1<<MAX_PAT_EXP)+1));
  if (pattern_buffer == NULL) {printf("Failed to allocate pattern memory!\n");exit(2);}

  f = openLog("results.csv");
  fprintf(f, "ALG\tDATA SET\tPLEN\tIT\tEJECTIME\tNCOM\n");
  /*---BINARY---*//*
  runTest("BF","dataset/BINA.txt",f,&funBF);
  runTest("KMP","dataset/BINA.txt",f,&funKMP);
  runTest("BMH","dataset/BINA.txt",f,&funBMH);*/
  /*---REAL DNA---*//*
  runTest("BF","dataset/RDNA.txt",f,&funBF);
  runTest("KMP","dataset/RDNA.txt",f,&funKMP);
  runTest("BMH","dataset/RDNA.txt",f,&funBMH);*/
  /*---SYNTH DNA---*//*
  runTest("BF","dataset/SDNA.txt",f,&funBF);
  runTest("KMP","dataset/SDNA.txt",f,&funKMP);*/
  runTest("BMH","dataset/SDNA.txt",f,&funBMH);
  /*---REAL LNG---*//*
  runTest("BF","dataset/RLNG.txt",f,&funBF);
  runTest("KMP","dataset/RLNG.txt",f,&funKMP);
  runTest("BMH","dataset/RLNG.txt",f,&funBMH);*/
  /*---SYNTH LNG---*//*
  runTest("BF","dataset/SLNG.txt",f,&funBF);
  runTest("KMP","dataset/SLNG.txt",f,&funKMP);
  runTest("BMH","dataset/SLNG.txt",f,&funBMH);*/

  fclose(f);

  free(text_buffer);
  free(pattern_buffer);
}
