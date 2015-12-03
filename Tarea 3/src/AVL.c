#include "Tree.h"

typedef struct {
	TNode root;
	insert_fun insert;
	delete_fun delete;
	search_fun search;
} *AVL;

/* Tree operations */
AVL createAVL(){
	AVL avl = (AVL) malloc(sizeof(*avl));
	avl->root = NULL;
	avl->insert = &insertAVL;
	avl->delete = &deleteAVL;
	avl->search = &searchAVL;
	return avl;
}

void freeAVL(AVL avl){
	freeTNode(avl->root);
	free(avl);
}

TNode leftRotation(TNode node){
	Tnode q = node->left;
	node->left = q->right;
	q->right = node;
	node->height = height(node);
	return q;
}

TNode rightRotation(TNode node){
	TNode q = node->right;
	node->right = q->left;
	q->left = node;
	node->height = height(node);
	return q;
}

TNode doubleRightRotation(TNode node){
	TNode q = node->right;
	TNode r = q->left;
	node->right = r->left;
	q->left = r->right;
	r->left = node;
	r->right = q;
	node->height = height(node);
	q->height = height(q);
	return r;
}

TNode doubleLeftRotation(TNode node){
	TNode q = node->left;
	TNode r = q->right;
	node->left = r->right;
	q->right = r->left;
	r->left = q;
	r->right = node;
	node->height = height(node);
	q->height = height(q);
	return r;
}

int isAVL(TNnode node){
	if (node->height == 0) return TRUE;
	return abs(node->right->height - node->left->height) <= 1; /* <= 1 may work for the bottom-most cases*/
}

TNnode insertAVL(TNnode node,char key[],char value[]){
	if (node == NULL) return createTNode(key,value);

	int s = strcmp(node->key,key);
	if (s<0) {
		node->left = insertAVL(node->left,key,value);
		if ( !isAvl(node) )
			if ( strcmp(key,node->left->key)>0 )
				node = doubleLeftRotation(node);
			else
				node = leftRotation(node);
	}
	else if (s>0) {
		node->right = insertAVL(node->right,key,value);
		if ( !isAvl(node) )
			if ( strcmp(key,node->right->key)<0 )
				node = doubleRightRotation(node);
			else
				node = rightRotation(node);
	}	
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
/* TODO: DELETE MUST PRESERVE AVL CONDITIONS */
TNnode deleteAVL(TNnode node,char key[]){
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
	else if (s<0) node->left = deleteAVL(node->left,key);
	else node->right = deleteAVL(node->right,key);
	node->height = height(node);
	return node;
}

int searchAVL(TNnode node,char key[]){
	if (node == NULL) return FALSE;

	int s = strcmp(node->key,key);
	if (s<0) return searchAVL(node->left,key);
	else if (s>0) return searchAVL(node->right,key);
	return TRUE;
}
