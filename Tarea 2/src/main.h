#ifndef MAIN
#define MAIN

int debug = 0;
int blocks_written,blocks_read;

/*Returns the hash of a 15-long DNA sequence*/
int MakeHashGCAT(char *str){
  int mask,result;
  result = 0;
  for (size_t i = 0; i < 15; i++) {
    switch (str[i]) {
      case "C": mask = 0; break;
      case "G": mask = 1; break;
      case "A": mask = 2; break;
      case "T": mask = 3; break;
    }
    result |= mask<<i;
  }
  return result;
}

#endif
