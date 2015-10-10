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
char *test_algorithm;
char *test_dataset;

void configureTest(char *algorithm,char *dataset){
  iteration = 0;
  test_algorithm = algorithm;
  test_dataset = dataset;
  /*open the dataset and load to memory*/
}

void choosePattern(int i){
  pattern_length = 1<<(i-1);
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
  fprintf(log,"%s, %s, %i, %i, %f, %i\n",test_algorithm,test_dataset,pattern_length,iteration,time_spent,comparison_counter);
}

/*==============================================*/

void runTest(char *algorithm, char *dataset, FILE *f){
  configureTest(algorithm,dataset);
  for (size_t j = 2; j < 7; j++) {
    choosePattern(j);
    for (size_t i = 0; i < MAX_TESTS; i++) {
      beginTest();

      /*execute tested algorithm*/

      registerTest(f);
    }
  }
}

int main(int argc, char const *argv[]){
  char* file_name, test_name;
  FILE *f;
  f = openLog("results.csv");

  /*---BINARY---*/
  runTest("Naive","BIN.txt",f);
  runTest("KMP","BIN.txt",f);
  runTest("BMH","BIN.txt",f);
  /*---REAL DNA---*/
  runTest("Naive","RDNA.txt",f);
  runTest("KMP","RDNA.txt",f);
  runTest("BMH","RDNA.txt",f);
  /*---SYNTH DNA---*/
  runTest("Naive","SDNA.txt",f);
  runTest("KMP","SDNA.txt",f);
  runTest("BMH","SDNA.txt",f);
  /*---REAL LNG---*/
  runTest("Naive","RLNG.txt",f);
  runTest("KMP","RLNG.txt",f);
  runTest("BMH","RLNG.txt",f);
  /*---SYNTH LNG---*/
  runTest("Naive","SLNG.txt",f);
  runTest("KMP","SLNG.txt",f);
  runTest("BMH","SLNG.txt",f);

  fclose(f);
}
