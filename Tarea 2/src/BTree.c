#include "BTree.h"

BTree CreateBTree(){
  Btree T = (BTree) malloc(sizeof(*T));
  BTNode x = (BTNode) malloc(sizeof(*x));
  x->LEAF = 1;
  x->n = 0;
  /*diskwrite(x)*/
  T->root = x;
  return T;
}

int insert(BTree T,int k){
  BTNode r = T->root;
  if (r->n == 2*t-1){/*TODO: define t*/
    BTNode s = (BTNode) malloc(sizeof(*s));
    T->root = s;
    s->LEAF = 0;
    s->n = 0;
    s->pointers[0] = r;
    split_child(T,s,1,r);
    insert_nonfull(T,s,k);
  }
  else insert_nonfull(T,r,k);
}

void split_child(BTree T,BTNode x,int i,BTNode y){
}

void insert_nonfull(BTree T,BTNode x,int k){
  int i = x->n;/*n-1?*/
  if (x->LEAF){
    while (i>=0 && k < x->key[i]){
      x->key[i+1]=x->key[i];
      i--;
    }
    x->key[i+1]=k;
    x->n++;
    /*diskwrite(x)*/
  }
  else {
    while (i>=0 && k < x->key[i]) i--;
    i++
    /*y = diskread(x->pointers[i])*/
    if (y->n==2*t-1){
      split_child(x,i,y);
      if (k>x->key[i]) i++;
      insert_nonfull(y,k);
    }
  }
}
