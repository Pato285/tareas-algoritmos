#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int MAX_TESTS = 1;

/*==============================================*/

FILE *openLog(const char* name){
  FILE *f = fopen(name, "w");
  if (f == NULL){
      printf("Error opening file!\n");
      exit(1);
  }
  return f;
}

/*==============================================*/

int comparison_counter, start_time, end_time, iteration, pattern_length;
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
}

void choosePattern(int i){
  pattern_length = 1<<(i-1);
  /*load the pattern to buffer*/
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
  fprintf(log,"%s\t%s\t%i\t%i\t%f\t%i\n",test_algorithm,test_dataset,pattern_length,iteration,time_spent,comparison_counter);
}

typedef void (*TestedFunction)(char*, char*, int*);

void runTest(char *algorithm, char *dataset, FILE *f,TestedFunction test){
  int *answer;
  configureTest(algorithm,dataset);
  for (size_t j = 2; j < 7; j++) {
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
  f = openLog("results.csv");
  fprintf(f, "ALG\tDATA SET\tPLEN\tIT\tEJECTIME\tNCOM\n");
  /*---BINARY---*/
  runTest("BF","BINA.txt",f,&funBF);
  runTest("KMP","BINA.txt",f,&funKMP);
  runTest("BMH","BINA.txt",f,&funBMH);
  /*---REAL DNA---*/
  runTest("BF","RDNA.txt",f,&funBF);
  runTest("KMP","RDNA.txt",f,&funKMP);
  runTest("BMH","RDNA.txt",f,&funBMH);
  /*---SYNTH DNA---*/
  runTest("BF","SDNA.txt",f,&funBF);
  runTest("KMP","SDNA.txt",f,&funKMP);
  runTest("BMH","SDNA.txt",f,&funBMH);
  /*---REAL LNG---*/
  runTest("BF","RLNG.txt",f,&funBF);
  runTest("KMP","RLNG.txt",f,&funKMP);
  runTest("BMH","RLNG.txt",f,&funBMH);
  /*---SYNTH LNG---*/
  runTest("BF","SLNG.txt",f,&funBF);
  runTest("KMP","SLNG.txt",f,&funKMP);
  runTest("BMH","SLNG.txt",f,&funBMH);

  fclose(f);
}
