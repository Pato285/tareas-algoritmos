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

void deleteABB(TNnode node,char key[]){
	/* */
}

int searchABB(TNnode node,char key[]){
	if (node == NULL) return FALSE;

	int s = strcmp(node->key,key);
	if (s<0) return searchABB(node->left,key);
	else if (s>0) return searchABB(node->right,key);
	return TRUE;
}