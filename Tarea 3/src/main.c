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

  printf("AVL\n");
  AVL avl = createAVL();
  for (size_t i = 0; i < 6; i++) {
    avl->root = avl->insert(avl->root,test+index[i],test+index[i]);
  }
  for (size_t i = 0; i < 6; i++) {
    printf("search %s: %i\n",test+index[i], avl->search(avl->root,test+index[i]));
  }
  printf("search %s: %i\n","H", avl->search(avl->root,"H"));
  printf("search %s: %i\n","O", avl->search(avl->root,"O"));
  printf("search %s: %i\n","RF", avl->search(avl->root,"RF"));
  inorderprint(avl->root);
  printf("delete A\n");
  avl->root = avl->delete(avl->root,"A");
  inorderprint(avl->root);
  printf("delete Q\n");
  avl->root = avl->delete(avl->root,"Q");
  inorderprint(avl->root);
  printf("insert C E D\n");
  bst->root = bst->insert(bst->root,"C","C");
  bst->root = bst->insert(bst->root,"E","E");
  bst->root = bst->insert(bst->root,"D","D");
  printf("delete K\n");
  avl->root = avl->delete(avl->root,"K");
  printf("insert M\n");
  avl->root = avl->insert(avl->root,"M","M");
  inorderprint(avl->root);
  printf("delete K\n");
  avl->root = avl->delete(avl->root,"K");
  inorderprint(avl->root);
  printf("ENDING\n");
  freeAVL(avl);
  return 0;
}
