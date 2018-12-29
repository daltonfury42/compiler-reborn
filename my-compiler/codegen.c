#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include "exptree.h"

int evaluate(struct tnode *t){
	if(!t->isOperator)
	{
		return t->val;
	}
	else
	{
		switch(t->op)
		{
			case PLUS: 	return evaluate(t->left) + evaluate(t->right);
					break;
			case MINUS: 
					return evaluate(t->left) - evaluate(t->right);
					break;
			case MUL: 
					return evaluate(t->left) * evaluate(t->right);
					break;
			case DIV: 
					return evaluate(t->left) / evaluate(t->right);
					break;
			default:
					printf("Invalid Operator.\n");
		}
	}
}
