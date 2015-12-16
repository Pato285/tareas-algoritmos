#include "Tree.h"
#include "BST.c"
#include "AVL.c"
#include <time.h>

typedef struct {
  int n;
  int byten; /* SIZE OF THE ARRAY IN BYTES */
  int off_idx;
  int off_str;
  int *idx;
  char *str;
} *Data;

Data readFile(const char *name){
  FILE *f = fopen(name, "r");
  if (f == NULL){
    printf("Error opening file!: %s\n",name);
    exit(1);
  }

  Data dt = (Data) malloc(sizeof(*dt));
  int magic;
  fread(&magic,4,1,f);
  if (magic!=1214793300){
    printf ("Not a potato file %s\n",name);
    fclose(f);
    exit(1);
  }
  fread(&(dt->n), 4, 1, f);
  fread(&(dt->byten), 4, 1, f);
  fread(&(dt->off_idx), 4, 1, f);
  fread(&(dt->off_str), 4, 1, f);

  dt->idx = (int*) malloc(sizeof(int)*dt->n);
  dt->str = (char*) malloc(dt->byten);

  fseek(f,dt->off_idx,SEEK_SET);
  fread(dt->idx, sizeof(int), dt->n, f);
  fseek(f,dt->off_str,SEEK_SET);
  fread(dt->str, 1, dt->byten, f);

  if (ferror(f)){
    printf ("Error reading %s\n",name);
    fclose(f);
    exit(1);
  }
  fclose(f);
  return dt;
}

void test(void *p,Data dt){
  double start, end;
  double total;
  int s;

  BST bst = (BST) p;

  printf("INSERTION\n");
  total = s = 0;
  for (size_t i = 4; i < 15; i++) {
    for (;s<(2<<i);s++) {
      start = clock();
      bst->root = bst->insert(bst->root,dt->str+dt->idx[s],dt->str+dt->idx[s]);
      end = clock();
      total += end-start;
    }
    printf("Size of Structure with 2^%i data is %i, index %i\n",i,size(bst->root),s);
    printf("Mean Time spent INSERTING with 2^%i data is %f ms.\n",i,total/(2<<i));
  }

  printf("SEARCH\n");
  total = s = 0;
  for (size_t i = 4; i < 15; i++) {
    for (;s<(2<<i);s++) {
      int r = rand() % dt->n;

      start = clock();
      bst->search(bst->root,dt->str+dt->idx[r]);
      end = clock();

      total += end-start;
    }
    printf("Mean Time spent SEARCHING with 2^%i data is %f ms.\n",i,total/(2<<i));
  }

  printf("DELETION\n");
  total = s = 0;
  for (size_t i = 4; i < 15; i++) {
    for (;s<(2<<i);s++) {
      int r = rand() % dt->n;
      
      start = clock();
      bst->root = bst->delete(bst->root,dt->str+dt->idx[r]);
      end = clock();

      total += end-start;
    }
    printf("Size of Structure with 2^%i data is %i, index %i\n",i,size(bst->root),s);
    printf("Mean Time spent DELETING with 2^%i data is %f ms.\n",i,total/(2<<i));
  }

}

int main(int argc, char const *argv[]) {
  char *filename = malloc(14);
  strcpy(filename,"word_0_15.pto");

  for (size_t i = 4; i < 9; i++) {

    filename[5] = '0' + i;
    printf("WORKING ON %s\n",filename);
    Data dt = readFile(filename);

    printf("TESTING BST\n");
    BST bst = createBST();
    test(bst,dt);
    freeBST(bst);

    printf("TESTING AVL\n");
    AVL avl = createAVL();
    test(avl,dt);
    freeAVL(avl);

    free(dt->idx);
    free(dt->str);
    free(dt);
  }
  /*
  char *test = "K\0A\0Q\0L\0B\0S";
  int index[] = {0,2,4,6,8,10};

  printf("BST\n");
  BST bst = createBST();
  for (size_t i = 0; i < 6; i++) {
    bst->root = bst->insert(bst->root,test+index[i],test+index[i]);
  }
  for (size_t i = 0; i < 6; i++) {
    printf("search %s: %i\n",test+index[i], bst->search(bst->root,test+index[i]));
  }
  printf("search %s: %i\n","H", bst->search(bst->root,"H"));
  printf("search %s: %i\n","O", bst->search(bst->root,"O"));
  printf("search %s: %i\n","RF", bst->search(bst->root,"RF"));
  inorderprint(bst->root);
  printf("delete A\n");
  bst->root = bst->delete(bst->root,"A");
  inorderprint(bst->root);
  printf("delete Q\n");
  bst->root = bst->delete(bst->root,"Q");
  inorderprint(bst->root);
  printf("insert C\n");
  bst->root = bst->insert(bst->root,"C","C");
  printf("insert E\n");
  bst->root = bst->insert(bst->root,"E","E");
  printf("insert D\n");
  bst->root = bst->insert(bst->root,"D","D");
  inorderprint(bst->root);
  printf("delete K\n");
  bst->root = bst->delete(bst->root,"K");
  inorderprint(bst->root);
  printf("ENDING\n");
  freeBST(bst);

  printf("AVL\n");
  AVL avl = createAVL();
  inorderprint(avl->root);
  printf("insert H\n");avl->root = avl->insert(avl->root,"H","H");inorderprint(avl->root);
  printf("insert K\n");avl->root = avl->insert(avl->root,"K","K");inorderprint(avl->root);
  printf("insert O\n");avl->root = avl->insert(avl->root,"O","O");inorderprint(avl->root);
  printf("insert P\n");avl->root = avl->insert(avl->root,"P","P");inorderprint(avl->root);
  printf("insert D\n");avl->root = avl->insert(avl->root,"D","D");inorderprint(avl->root);
  printf("insert I\n");avl->root = avl->insert(avl->root,"I","I");inorderprint(avl->root);
  printf("insert J\n");avl->root = avl->insert(avl->root,"J","J");inorderprint(avl->root);
  printf("insert OA\n");avl->root = avl->insert(avl->root,"OA","OA");inorderprint(avl->root);

  printf("search %s: %i\n","H", avl->search(avl->root,"H"));
  printf("search %s: %i\n","P", avl->search(avl->root,"P"));
  printf("search %s: %i\n","J", avl->search(avl->root,"J"));
  printf("search %s: %i\n","S", avl->search(avl->root,"S"));
  printf("search %s: %i\n","L", avl->search(avl->root,"L"));
  printf("search %s: %i\n","Kappa", avl->search(avl->root,"Kappa"));

  printf("delete H\n");avl->root = avl->delete(avl->root,"H");inorderprint(avl->root);
  printf("delete OA\n");avl->root = avl->delete(avl->root,"OA");inorderprint(avl->root);
  printf("delete O\n");avl->root = avl->delete(avl->root,"O");inorderprint(avl->root);
  printf("delete P\n");avl->root = avl->delete(avl->root,"P");inorderprint(avl->root);

  printf("ENDING\n");
  freeAVL(avl);

  Data dt = readFile("out.pto");
  printf("%i\n", dt->n);
  printf("%i\n", dt->byten);
  printf("%i\n", dt->off_idx);
  printf("%i\n", dt->off_str);
  printf("%s\n", dt->str);

  for (size_t i = 0; i < dt->n; i++) {
    printf("%s\n", dt->str+dt->idx[i] );
  }

  free(dt->idx);
  free(dt->str);
  free(dt);*/

  return 0;
}
