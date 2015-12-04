#ifndef TREE
#define TREE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct node {
	char *key;
	char *value;
	struct node *left;
	struct node *right;
	int height;
} *TNode;

TNode createTNode(char key[],char value[]){
	TNode node = (TNode) malloc(sizeof(*node));
	node->key = key;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}

void freeTNode(TNode node){
	if (node==NULL) return;
	if (node->left != NULL){
		freeTNode(node->left);
		free(node->left);
	}
	if (node->right != NULL){
		freeTNode(node->right);
		free(node->right);
	}
	/*free(node->key); /* Having serious doubts about erasing here the key. */
}

int height(TNode node){
	if (node == NULL) return 0;
	int sz_l = node->left == NULL ? 0 : node->left->height;
	int sz_r = node->right == NULL ? 0 : node->right->height;
	return MAX(sz_l,sz_r)+1;
}

/* Tree operations */

/**
  * Inserts the value in the tree using the given key.
  */
typedef TNode (*insert_fun)(TNode,char[],char[]);

/**
  * Deletes the node with the given key.
  */
typedef TNode (*delete_fun)(TNode,char[]);

/**
  * Searches the string with the given key.
  */
typedef int (*search_fun)(TNode,char[]);

void preorderprint(TNode node){
	if (node == NULL) return;
	printf("%s %i\n",node->value,node->height);
	preorderprint(node->left);
	preorderprint(node->right);
}

void inorderprint(TNode node){
	if (node == NULL) return;
	inorderprint(node->left);
	printf("%s %i\n",node->value,node->height);
	inorderprint(node->right);
}

void postorderprint(TNode node){
	if (node == NULL) return;
	postorderprint(node->left);
	postorderprint(node->right);
	printf("%s %i\n",node->value,node->height);
}

/*
	we store the pointers to strings not the strings themselves.
	key and value must be allocated before inserting and must be deallocated afterwards.
*/
#endif
