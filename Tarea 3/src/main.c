#include "Tree.h"
#include "BST.c"
#include "AVL.c"

int main(int argc, char const *argv[]) {
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
  return 0;
}
