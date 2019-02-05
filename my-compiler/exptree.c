#include "exptree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#include "symbolTable.h"

tnode* createTree(int val, int type, char* varname, int operator, int nodetype, tnode* l, tnode* r, tnode* elseTree)
{

	tnode* temp = (tnode*)malloc(sizeof(tnode));
	temp->val = val;
	temp->type = type;
	temp->varname = varname;
	temp->operator = operator;
	temp->nodetype = nodetype;
	temp->left=l;
	temp->right=r;
	temp->elseTree = elseTree;

	if(varname != NULL && nodetype == VARIABLE)
	{
		temp->varname = malloc(strlen(varname) + 1);
		strcpy(temp->varname, varname);
		temp->symbolTableEntry = Glookup(varname);
	}

	return temp;
}

tnode* makeConnectorNode(tnode* l, tnode* r)
{
	return createTree(-1, -1, NULL, -1, CONNECTOR, l, r, NULL);
}

tnode* makeReadNode(tnode* lr)
{
	return createTree(-1, -1, NULL, -1, READ, NULL, lr, NULL);
}

tnode* makeWriteNode(tnode* lr)
{
		return createTree(-1, -1, NULL, -1, WRITE, NULL, lr, NULL);
}

tnode* makeLeafNodeVar(char* varname)
{
	return createTree(-1, -1, varname, -1, VARIABLE, NULL, NULL, NULL);
}


tnode* makeLeafNodeNum(int n)
{
	return createTree(n, T_NUM, NULL, -1, NUM, NULL, NULL, NULL);
}

tnode* makeAssignmentNode(tnode* l, tnode* r)
{
	return createTree(-1, -1, NULL, -1, ASGN, l, r, NULL);
}

tnode* makeOperatorNode(int operator, tnode *l,tnode *r)
{
	return createTree(-1, -1, NULL, operator, OPERATOR, l, r, NULL);
}

tnode* makeIfNode(tnode* condition, tnode* ifTree, tnode* elseTree)
{
	return createTree(-1, -1, NULL, -1, IF, condition, ifTree, elseTree);
}

tnode* makeWhileNode(tnode* condition, tnode* body) 
{
	return createTree(-1, -1, NULL, -1, WHILE, condition, body, NULL);
}

tnode* makeLeafNodeStringConst(char* stringContent)
{
	char* stringVal = malloc(strlen(stringContent));

	//stripping yytext of the quotes while copying
	strncpy(stringVal, stringContent, strlen(stringContent) + 1);

	return createTree(-1, T_STR, stringVal, -1, STR, NULL, NULL, NULL);
}


tnode* makeArrayNode(tnode* l, tnode* r) 
{
	return createTree(-1, -1, NULL, -1, ARRAY, l, r, NULL);
}
