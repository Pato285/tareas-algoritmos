#include "Tree.h"

typedef struct {
	TNode root;
	insert_fun insert;
	delete_fun delete;
	search_fun search;
} *BST;

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

TNnode insertBST(TNnode node,char key[],char value[]){
	if (node == NULL) return createTNode(key,value);

	int s = strcmp(node->key,key);
	if (s<0) node->left = insertBST(node->left,key,value);
	else if (s>0) node->right = insertBST(node->right,key,value);
	node->height = height(node);
	return node;
}

TNode findPredecessorParent(TNode node){
	TNode k;
	if (node->right == NULL){
		return node;
	}
	else if (node->right->right == NULL){
		k = node->right;
		node->right = node->right->left;
	}
	else k = findPredecessorParent(node->right);
	node->height = height(node);
	return k;
}

TNnode deleteBST(TNnode node,char key[]){
	if (node == NULL) return NULL;

	int s = strcmp(node->key,key);
	if (s==0){
		if (node->left == NULL && node->right == NULL) {
			freeTNode(node);
			free(node);
			return NULL;
		}
		elif(node->left == NULL){
			TNnode l = node->left;
			node->left = NULL;
			freeTNode(node);
			free(node);
			l = height(l);
			return l;
		}
		elif(node->right == NULL){
			TNnode r = node->right;
			node->right = NULL;
			freeTNode(node);
			free(node);
			r = height(r);
			return r;
		}
		TNode k = findPredecessorParent(node->left);
		k->right = node->right;
		k->left = node->left;
		k->height = height(k);

		node->left =  NULL;
		node->right = NULL;
		freeTNode(node);
		free(node);
		return k;
	}
	else if (s<0) node->left = deleteBST(node->left,key);
	else node->right = deleteBST(node->right,key);
	node->height = height(node);
	return node;
}

int searchBST(TNnode node,char key[]){
	if (node == NULL) return FALSE;

	int s = strcmp(node->key,key);
	if (s<0) return searchBST(node->left,key);
	else if (s>0) return searchBST(node->right,key);
	return TRUE;
}