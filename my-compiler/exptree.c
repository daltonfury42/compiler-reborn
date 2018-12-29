#include "exptree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

tnode* makeLeafNode(int n)
{
	tnode* temp = (tnode*)malloc(sizeof(tnode));
	memset(temp, 0, sizeof(tnode));

	temp->val = n;

	return temp;
}
	
struct tnode* makeOperatorNode(int op,struct tnode *l,struct tnode *r){
	tnode* temp = (struct tnode*)malloc(sizeof(struct tnode));
	memset(temp, 0, sizeof(tnode));

	temp->op = op;
	temp->isOperator = 1;
	temp->left = l;
	temp->right = r;

	return temp;
}
