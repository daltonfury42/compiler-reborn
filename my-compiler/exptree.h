#ifndef EXPTREE_H
#define EXPTREE_H

typedef struct tnode 
{
	int isOperator;
	int val;
	int op; 			//indicates the name of the operator for a non leaf node
	struct tnode *left,*right; 	//left and right branches
} tnode;


/*Make a leaf tnode and set the value of val field*/
struct tnode* makeLeafNode(int n);
	
/*Make a tnode with opertor, left and right branches set*/
struct tnode* makeOperatorNode(int op,struct tnode *l,struct tnode *r);

#endif
