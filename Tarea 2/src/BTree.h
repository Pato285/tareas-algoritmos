#ifndef BTREE
#define BTREE

#include "MemMgr.h"

extern int debug;
extern int blocks_written, blocks_read;

typedef struct btnode {
  int n; /*numero de llaves que contiene*/
  int key[]; /*llaves [n]*/
  int LEAF; /*valor booleano is_LEAF?*/
  int pointers[]; /*si es falso que LEAF, entonces guardo punteros [n+1]*/
} *BTNode;

typedef struct {
  BTNode root;
} *BTree;

BTree CreateBTree();

int insert(BTree T,char *str);
void split_child(BTree T,BTNode s,int i,BTNode k);
void insert_nonfull(BTree T,BTNode x,int k);

#endif
