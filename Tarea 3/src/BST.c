#include "Tree.h"

typedef struc {
	TNode root;
	insert_fun insert;
	delete_fun delete;
	search_fun search;
} *ABB;

/* Tree operations */
ABB createABB(){
	ABB abb = (ABB) malloc(sizeof(*abb));
	abb->root = NULL;
	abb->insert = &insertABB;
	abb->delete = &deleteABB;
	abb->search = &searchABB;
	return abb;
}

void freeABB(ABB abb){
	freeTNode(abb->root);
	free(abb);
}

TNnode insertABB(TNnode node,char key[],char value[]){
	if (node == NULL) return createTNode(key,value);

	int s = strcmp(node->key,key);
	if (s<0) node->left = insertABB(node->left,key,value);
	else if (s>0) node->right = insertABB(node->right,key,value);
	return node;
}

TNode findPredecessorParent(TNode node){
	if (node->right != NULL && node->right->right == NULL) return node;
	return findPredecessorParent(node->right);
}

void deleteABB(TNnode node,char key[]){
	if (node == NULL) return NULL;

	int s = strcmp(node->key,key);
	if (s<0) node->left = deleteABB(node->left,key);
	else if (s>0) node->right = deleteABB(node->right,key);
	
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
		return l;
	}
	elif(node->right == NULL){
		TNnode r = node->right;
		node->right = NULL;
		freeTNode(node);
		free(node);
		return r;
	}
	TNode p = findPredecessorParent(node->left);
	Tnode l = p->right;
	Tnode k = l->left;
	l->right = node->right;
	l->left = node->left;
	p->right = k;
	node->left =  NULL;
	node->right = NULL;
	freeTNode(node);
	free(node);
	return l;
}

int searchABB(TNnode node,char key[]){
	if (node == NULL) return FALSE;

	int s = strcmp(node->key,key);
	if (s<0) return searchABB(node->left,key);
	else if (s>0) return searchABB(node->right,key);
	return TRUE;
}