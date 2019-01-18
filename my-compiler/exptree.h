#ifndef EXPTREE_H
#define EXPTREE_H

#include "symbolTable.h"

typedef struct tnode 
{
	int val;	// value of a number for NUM nodes.
	int type;	// type of the expression. type of variables stored in symboltable
	char* varname;	//name of a variable for ID nodes and also doubles up as value of STRCONST
	int operator;  
	int nodetype;  // information about non-leaf nodes - read/write/connector/operator etc.  
	struct tnode *left,*right; //left and right branches 
	struct tnode *elseTree; // for ifelse  
	Gsymbol* symbolTableEntry;
} tnode;

tnode* makeConnectorNode(tnode* l, tnode* r);
tnode* makeReadNode(tnode* lr);
tnode* makeWriteNode(tnode* lr);
tnode* makeLeafNodeVar(char* varname);
tnode* makeLeafNodeNum(int n);
tnode* makeAssignmentNode(tnode* l, tnode* r);
tnode* makeOperatorNode(int operator, tnode *l,tnode *r);
tnode* makeIfNode(tnode* condition, tnode* ifTree, tnode* elseTree);
tnode* makeWhileNode(tnode* condition, tnode* body);
tnode* makeLeafNodeStringConst(char* stringContent);

#endif
