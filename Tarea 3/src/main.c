#include "Tree.h"
#include "BST.c"
#include "AVL.c"

int main(int argc, char const *argv[]) {
  BST bst = createBST();
  char *test = "abracadabra";
  bst->root = bst->insert(bst->root,test,test);
  printf("search %i\n", bst->search(bst->root,test));
  bst->root = bst->delete(bst->root,test);
  freeBST(bst);
  return 0;
}
