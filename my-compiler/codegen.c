#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include "exptree.h"
#include "codegen.h"

int varMem[26];

int verbose = 1;

void printDebug(const char* msg)
{
	if (verbose)
		printf("DEBUG: %s.\n", msg);
}

int codeGen(struct tnode* t, FILE* target_file);

//returns stackPos for variable
int getVarPos(char ch)
{
	int index=ch-'a';
	return index;
}

int codeGenOperator(struct tnode* t, FILE* target_file)
{
	printDebug("Started code generation for Operator");

	int reg1 = codeGen(t->left, target_file);
	int reg2 = codeGen(t->right, target_file);
		
	switch(t->operator)
	{
		case PLUS:	
			return reg1 + reg2;
			break;
			
		case MINUS:	
			return reg1 - reg2;
			break;
			
		case MUL:	
			return reg1 * reg2;
			break;
			
		case DIV:	
			return reg1 / reg2;
			break;
			
		default: 	
			printf("INVALID OPERATOR");
			exit(1);				
	}
		
	freeReg();
	
	printDebug("Ended code generation for Operator");	
	return reg1;
}

int codeGenNumber(struct tnode* t, FILE* target_file)
{
	printDebug("Started code generation for Number");

	int reg = t->val;

	printDebug("Ended code generation for Number");

	return reg;
}

int codeGenVar(tnode* t, FILE* target_file)
{
	printDebug("Started code generation for Variable");

	int varPos = getVarPos(t->varname);	//returns 4096+0 for a and so on
	int reg0 = varMem[varPos];
	
	printDebug("Ended code generation for Variable");

	return reg0;
}

int codeGenRead(struct tnode* t, FILE* target_file)
{
	printDebug("Started code generation for Read");

	char varname = t->right->varname;
	int varPos = getVarPos(varname);

	int temp;
	scanf("%d", &temp);
	varMem[varPos] = temp;

	printDebug("Ended code generation for Read");

	return -1;
}

int codeGenWrite(struct tnode* t, FILE* target_file)
{

	printDebug("Started code generation for Write");


	int reg1 = codeGen(t->right, target_file);

	printf("%d", reg1);

	printDebug("Ended code generation for Write");


	return -1;
}

int codeGenConnector(struct tnode* t, FILE* target_file)
{

	codeGen(t->left, target_file);
	codeGen(t->right, target_file);
	
	return -1;
}

int codeGenAsgn(struct tnode* t, FILE* target_file)
{

	printDebug("Started code generation for Asgn");

	char varname = t->left->varname;
	int varPos = getVarPos(varname);
	
	int reg1 = codeGen(t->right, target_file);
	
	varMem[varPos] = reg1;

	printDebug("Ended code generation for Asgn");

	return -1;
}

int codeGen(struct tnode* t, FILE* target_file)
{
	int reg;

	switch (t->nodetype)
	{	
		case NUM:
			reg = codeGenNumber(t, target_file);
			return reg;
		case OPERATOR:
			reg = codeGenOperator(t, target_file);
			return reg;
		case VARIABLE:
			reg = codeGenVar(t, target_file);
			return reg;
		case READ:
			codeGenRead(t, target_file);
			return -1;
		case WRITE:
			codeGenWrite(t, target_file);
			return -1;
		case CONNECTOR:
			codeGenConnector(t, target_file);
			return -1;
		case ASGN:
			codeGenAsgn(t, target_file);
			return -1;
		default:
			printf("Invalid nodetype.\n");
			exit(-1);
	}
}

void codeGenXsm(struct tnode* t, FILE* target_file) 
{
	printDebug("Code genration started");
	/* Header */
	int result = codeGen(t, target_file);
	
	printDebug("Code generation ended");
}
