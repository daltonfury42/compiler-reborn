#include "exptree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

tnode* createTree(int val, char varname, int operator, int nodetype, tnode* l, tnode* r, tnode* elseTree)
{
	tnode* temp = (tnode*)malloc(sizeof(tnode));
	temp->val = val;
	temp->type = -1;
	temp->varname = varname;
	temp->operator = operator;
	temp->nodetype = nodetype;
	temp->left=l;
	temp->right=r;
	temp->elseTree = elseTree;
}

tnode* makeConnectorNode(tnode* l, tnode* r)
{
	return createTree(-1, -1, -1, CONNECTOR, l, r, NULL);
}

tnode* makeReadNode(tnode* lr)
{
	return createTree(-1, -1, -1, READ, NULL, lr, NULL);
}

tnode* makeWriteNode(tnode* lr)
{
		return createTree(-1, -1, -1, WRITE, NULL, lr, NULL);
}

tnode* makeLeafNodeVar(char ch)
{
	return createTree(-1, ch, -1, VARIABLE, NULL, NULL, NULL);
}


tnode* makeLeafNodeNum(int n)
{
	return createTree(n, -1, -1, NUM, NULL, NULL, NULL);
}

tnode* makeAssignmentNode(tnode* l, tnode* r)
{
	return createTree(-1, -1, -1, ASGN, l, r, NULL);
}

tnode* makeOperatorNode(int operator, tnode *l,tnode *r)
{
	return createTree(-1, -1, operator, OPERATOR, l, r, NULL);
}

tnode* makeIfNode(tnode* condition, tnode* ifTree, tnode* elseTree)
{
	return createTree(-1, -1, -1, IF, condition, ifTree, elseTree);
}

tnode* makeWhileNode(tnode* condition, tnode* body) 
{
	return createTree(-1, -1, -1, WHILE, condition, body, NULL);
}