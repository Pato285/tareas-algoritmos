#include <string.h>

typedef struct node {
	char *key;
	char *value;
	struct node *left;
	struct node *right;
	int height;
} *TNode;

TNode createTNode(char key[],char value[]){
	TNode node = (TNode) malloc(sizeof(*node));
	node->key = NULL;
	node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	node->height = 0;
	return node;
}

void freeTNode(TNode node){
	if (node->left != NULL)
		freeTNode(node->left);
	if (node->right != NULL)
		freeTNode(node->right);
	free(node->left);
	free(node->right);
	/*free(node->key); /* Having serious doubts about erasing here the key. */
}

int height(TNode node){
	int sz_l = node->left == NULL ? -1 : node->left.height;
	int sz_r = node->right == NULL ? -1 : node->right.height;
	return MAX(sz_l,sz_r)+1
}

/* Tree operations */

/**
  * Inserts the value in the tree using the given key.
  */
typedef TNnode (*insert_fun)(TNode,char[],char[]);

/**
  * Deletes the node with the given key.
  */
typedef TNnode (*delete_fun)(TNode,char[]);

/**
  * Searches the string with the given key.
  */
typedef int (*search_fun)(TNode,char[]);

/*
	we store the pointers to strings not the strings themselves.
	key and value must be allocated before inserting and must be deallocated afterwards.
*/