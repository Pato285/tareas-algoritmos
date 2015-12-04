#include "Tree.h"
#include "BST.c"
#include "AVL.c"

int main(int argc, char const *argv[]) {
  BST bst = createBST();
  char *test = "K\0A\0Q\0L\0B\0S";
  int index[] = {0,2,4,6,8,10};
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
  printf("insert C E D\n");
  bst->root = bst->insert(bst->root,"C","C");
  bst->root = bst->insert(bst->root,"E","E");
  bst->root = bst->insert(bst->root,"D","D");
  inorderprint(bst->root);
  printf("delete K\n");
  bst->root = bst->delete(bst->root,"K");
  inorderprint(bst->root);
  printf("ENDING\n");
  freeBST(bst);
  return 0;
}
