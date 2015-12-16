#include <math.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

typedef struct vebn {
  int size;
  int min;
  int max;
  int n;
  struct vebn *top;
  struct vebn *bottom;
} *VEBNode;

typedef VEBNode (*insert_vebfun)(VEBNode,char[],char[]);
typedef VEBNode (*delete_vebfun)(VEBNode,char[]);
typedef int (*search_vebfun)(VEBNode,char[]);

typedef struct {
	VEBNode root;
	insert_vebfun insert;
	delete_vebfun delete;
	search_vebfun search;
} *VEB;

VEBNode insertVEB(VEBNode,char[],char[]);
VEBNode deleteVEB(VEBNode,char[]);
int searchVEB(VEBNode,char[]);

VEB createVEB(){
	VEB veb = (VEB) malloc(sizeof(*veb));
	veb->root = NULL;
	veb->insert = &insertVEB;
	veb->delete = &deleteVEB;
	veb->search = &searchVEB;
	return veb;
}

void freeVEB(VEB veb){
	freeVEBNode(veb->root);
	free(veb);
}

VEBNode createVEBNode(char key[],char value[]){
	VEBNode node = (VEBNode) malloc(sizeof(*node));
	return node;
}

void freeVEBNode(VEBNode node){
	if (node==NULL) return;
}

void getAB(int i, int n, int *a, int *b){
  int rn = (int) floor(sqrt(n));
  *b = i%rn;
  *a = i/rn;
}

VEBNode insertVEB(VEBNode node,int key,char value[]){
  int a,b;
  getAB(key,node->n,&a,&b);
  /*actualizar size, min y max*/
  if (node->bottom[a]->size == 0)
    node->top = insertVEB(node->top,a,NULL);
  node->bottom[a] = insertVEB(node->bottom[a],b,value);
}

VEBNode deleteVEB(VEBNode,int key){
  int a,b;
  getAB(key,node->n,&a,&b);

  node->bottom[a] = deleteVEB(node->bottom[a],b,value);
  if (node->bottom[a]->size == 0)
    node->top = deleteVEB(node->top,a);
  /*actualizar size,min,max*/
}

int searchVEB(VEBNode,int key){

}
