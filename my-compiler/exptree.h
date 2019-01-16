#ifndef EXPTREE_H
#define EXPTREE_H

typedef struct tnode 
{
	int val;	// value of a number for NUM nodes.
	int type;	//type of variable
	char varname;	//name of a variable for ID nodes
	int operator;  
	int nodetype;  // information about non-leaf nodes - read/write/connector/operator etc.  
	struct tnode *left,*right; //left and right branches 
	struct tnode *elseTree; // for ifelse  
} tnode;

tnode* makeConnectorNode(tnode* l, tnode* r);
tnode* makeReadNode(tnode* lr);
tnode* makeWriteNode(tnode* lr);
tnode* makeLeafNodeVar(char ch);
tnode* makeLeafNodeNum(int n);
tnode* makeAssignmentNode(tnode* l, tnode* r);
tnode* makeOperatorNode(int operator, tnode *l,tnode *r);
tnode* makeIfNode(tnode* condition, tnode* ifTree, tnode* elseTree);
tnode* makeWhileNode(tnode* condition, tnode* body);

#endif
