#include "Tree.h"

typedef struct {
	TNode root;
	insert_fun insert;
	delete_fun delete;
	search_fun search;
} *BST;

TNode insertBST(TNode,char[],char[]);
TNode deleteBST(TNode,char[]);
int searchBST(TNode,char[]);

/* Tree operations */
BST createBST(){
	BST abb = (BST) malloc(sizeof(*abb));
	abb->root = NULL;
	abb->insert = &insertBST;
	abb->delete = &deleteBST;
	abb->search = &searchBST;
	return abb;
}

void freeBST(BST abb){
	freeTNode(abb->root);
	free(abb);
}

TNode insertBST(TNode node,char key[],char value[]){
	if (node == NULL) return createTNode(key,value);

	int s = strcmp(node->key,key);
	if (s>0) node->left = insertBST(node->left,key,value);
	else if (s<0) node->right = insertBST(node->right,key,value);
	node->height = height(node);
	return node;
}

TNode findPredecessorParent(TNode node){
	TNode k;
	if (node->right->right == NULL){
		k = node->right;
		node->right = k->left;
		k->right = NULL;
		k->left = NULL;
	}
	else k = findPredecessorParent(node->right);
	node->height = height(node);
	return k;
}

TNode deleteBST(TNode node,char key[]){
	if (node == NULL) return NULL;
	int s = strcmp(node->key,key);
	if (s==0){
		if (node->left == NULL && node->right == NULL) {
			freeTNode(node);
			free(node);
			return NULL;
		}
		else if(node->right == NULL){
			TNode l = node->left;
			node->left = NULL;
			freeTNode(node);
			free(node);
			l->height = height(l);
			return l;
		}
		else if(node->left == NULL){
			TNode r = node->right;
			node->right = NULL;
			freeTNode(node);
			free(node);
			r->height = height(r);
			return r;
		}
		TNode k;
		if (node->left->right == NULL){
			k = node->left;
			k->right = node->right;
			k->height = height(k);
			node->left =  NULL;
			node->right = NULL;
			freeTNode(node);
			free(node);
			return k;
		}
		k = findPredecessorParent(node->left);
		k->right = node->right;
		k->left = node->left;
		k->height = height(k);
		node->left =  NULL;
		node->right = NULL;
		freeTNode(node);
		free(node);
		return k;
	}
	else if (s>0) node->left = deleteBST(node->left,key);
	else node->right = deleteBST(node->right,key);
	node->height = height(node);
	return node;
}

int searchBST(TNode node,char key[]){
	if (node == NULL) return FALSE;
	int s = strcmp(node->key,key);
	if (s>0) return searchBST(node->left,key);
	else if (s<0) return searchBST(node->right,key);
	return TRUE;
}
