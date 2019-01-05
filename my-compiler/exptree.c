#include "exptree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

tnode* createTree(int val, int type, char c, int operator, int nodetype, tnode* l, tnode* r )
{
	tnode* temp = (tnode*)malloc(sizeof(tnode));
	temp->val = val;
	temp->type = type;
	temp->varname = c;
	temp->operator = operator;
	temp->nodetype = nodetype;
	temp->left=l;
	temp->right=r;
}

tnode* makeConnectorNode(tnode* l, tnode* r)
{
	return createTree(-1, -1, -1, -1, CONNECTOR, l, r);
}

tnode* makeReadNode(tnode* lr)
{
	return createTree(-1, -1, -1, -1, READ, NULL, lr);
}

tnode* makeWriteNode(tnode* lr)
{
		return createTree(-1, -1, -1, -1, WRITE, NULL, lr);
}

tnode* makeLeafNodeVar(char ch)
{
	return createTree(-1, -1, ch, -1, VARIABLE, NULL, NULL);
}


tnode* makeLeafNodeNum(int n)
{
	return createTree(n, -1, -1, -1, NUM, NULL, NULL);
}

tnode* makeAssignmentNode(tnode* l, tnode* r)
{
	return createTree(-1, -1, -1, -1, ASGN, l, r);
}

tnode* makeOperatorNode(int operator, tnode *l,tnode *r)
{
	return createTree(-1, -1, -1, operator, OPERATOR, l, r);
}