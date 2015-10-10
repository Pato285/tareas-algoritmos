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
void funBF(char *text, char *pattern, int *answer){}
void funKMP(char *text, char *pattern, int *answer){}
void funBMH(char *text, char *pattern, int *answer){}

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
  /*---SYNTH DNA---*/
  runTest("BF","dataset/SDNA.txt",f,&funBF);/*
  runTest("KMP","dataset/SDNA.txt",f,&funKMP);
  runTest("BMH","dataset/SDNA.txt",f,&funBMH);*/
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
