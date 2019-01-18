#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include "exptree.h"
#include "codegen.h"

int freeRegister=0;

int verbose = 1;

void printDebug(const char* msg)
{
	if (verbose)
		printf("DEBUG: %s.\n", msg);
}

int codeGen(struct tnode* t, FILE* target_file);

int getVarAddr(tnode* t)
{
	return t->symbolTableEntry->binding;
}

int getReg()
{
	if(freeRegister > 19)
		{
			printf("Reg overflow");
			exit(-1);
		}
		
	return freeRegister++;
}

void freeReg()
{
	if(freeRegister==0)
		return;
	freeRegister--;

}

int getLabel()
{
	static int label = 0;
	return label++;
}

int codeGenOperator(struct tnode* t, FILE* target_file)
{
	printDebug("Started code generation for Operator");

	int reg1 = codeGen(t->left, target_file);
	int reg2 = codeGen(t->right, target_file);
		
	switch(t->operator)
	{
		case PLUS:	
			fprintf(target_file, "ADD R%d, R%d\n", reg1, reg2);
			break;
			
		case MINUS:	
			fprintf(target_file, "SUB R%d, R%d\n", reg1, reg2);
			break;
			
		case MUL:	
			fprintf(target_file, "MUL R%d, R%d\n", reg1, reg2);
			break;
			
		case DIV:	
			fprintf(target_file, "DIV R%d, R%d\n", reg1, reg2);
			break;
		case GTE:	
				fprintf(target_file, "GE R%d, R%d\n", reg1, reg2);
				break;
		case GT:	
				fprintf(target_file, "GT R%d, R%d\n", reg1, reg2);
				break;
		case LTE:	
				fprintf(target_file, "LE R%d, R%d\n", reg1, reg2);
				break;
		case LT:	
				fprintf(target_file, "LT R%d, R%d\n", reg1, reg2);
				break;
		case EQ:	
				fprintf(target_file, "EQ R%d, R%d\n", reg1, reg2);
				break;
		case NEQ:	
				fprintf(target_file, "NE R%d, R%d\n", reg1, reg2);
				break;
		default: 	
			printf("INVALID OPERATOR\n");
			exit(-1);				
	}
		
	freeReg();
	
	printDebug("Ended code generation for Operator");	
	return reg1;
}

int codeGenNumber(struct tnode* t, FILE* target_file)
{
	printDebug("Started code generation for Number");

	int reg = getReg();
	fprintf(target_file, "MOV R%d, %d\n", reg, t->val);

	printDebug("Ended code generation for Number");

	return reg;
}

int codeGenStr(struct tnode* t, FILE* target_file)
{
	printDebug("Started code generation for String");

	int reg = getReg();
	fprintf(target_file, "MOV R%d, %s\n", reg, t->varname);

	printDebug("Ended code generation for String");

	return reg;
}

int codeGenVar(tnode* t, FILE* target_file)
{
	printDebug("Started code generation for Variable");

	int varPos = getVarAddr(t);	
	int reg0 = getReg();
	fprintf(target_file, "MOV R%d, [%d]\n", reg0, varPos);

	printDebug("Ended code generation for Variable");

	return reg0;
}

int codeGenRead(struct tnode* t, FILE* target_file)
{
	printDebug("Started code generation for Read");

	int varPos = getVarAddr(t->right);

	int tmpreg = getReg();

	fprintf(target_file, "MOV R%d, \"Read\"\n", tmpreg);		
	fprintf(target_file, "PUSH R%d \n", tmpreg);  	
	fprintf(target_file, "MOV R%d, -1 \n", tmpreg);
	fprintf(target_file, "PUSH R%d \n", tmpreg);
	fprintf(target_file, "MOV R%d, %d \n", tmpreg, varPos);
	fprintf(target_file, "PUSH R%d \n", tmpreg);
	fprintf(target_file, "PUSH R%d \n", tmpreg);
	fprintf(target_file, "PUSH R%d \n", tmpreg);
	fprintf(target_file, "CALL 0 \n");
	fprintf(target_file, "POP R%d \n", tmpreg);
	fprintf(target_file, "POP R%d \n", tmpreg);
	fprintf(target_file, "POP R%d \n", tmpreg);
	fprintf(target_file, "POP R%d \n", tmpreg);
	fprintf(target_file, "POP R%d \n", tmpreg);

	freeReg();

	printDebug("Ended code generation for Read");


	return -1;
}

int codeGenWrite(struct tnode* t, FILE* target_file)
{

	printDebug("Started code generation for Write");

	int tmpreg = getReg();

	fprintf(target_file, "MOV R%d, \"Write\"\n", tmpreg);		
	fprintf(target_file, "PUSH R%d \n", tmpreg);  	
	fprintf(target_file, "MOV R%d, -2 \n", tmpreg);
	fprintf(target_file, "PUSH R%d \n", tmpreg);

	int reg1 = codeGen(t->right, target_file);

	fprintf(target_file, "PUSH R%d \n", reg1);
	fprintf(target_file, "PUSH R%d \n", tmpreg);
	fprintf(target_file, "PUSH R%d \n", tmpreg);
	fprintf(target_file, "CALL 0 \n");
	fprintf(target_file, "POP R%d \n", tmpreg);
	fprintf(target_file, "POP R%d \n", tmpreg);
	fprintf(target_file, "POP R%d \n", tmpreg);
	fprintf(target_file, "POP R%d \n", tmpreg);
	fprintf(target_file, "POP R%d \n", tmpreg);
	
	freeReg();
	freeReg();

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

	int varPos = getVarAddr(t->left);
	
	int reg1 = codeGen(t->right, target_file);
	
	fprintf(target_file, "MOV [%d], R%d\n", varPos, reg1);

	freeReg();

	printDebug("Ended code generation for Asgn");


	return -1;
}


int codeGenIf(struct tnode* t, FILE* target_file)
{

	printDebug("Started code generation for If");

	int label_end = getLabel();
	int label_else = getLabel();

	int reg_guard = codeGen(t->left, target_file);

	fprintf(target_file, "JZ R%d, L%d\n", reg_guard, label_else);

	codeGen(t->right, target_file);
	fprintf(target_file, "JMP L%d\n", label_end);

	fprintf(target_file, "L%d:\n", label_else);
	
	if (t->elseTree != NULL)
	{
		codeGen(t->elseTree, target_file);
	}

	fprintf(target_file, "L%d:\n", label_end);

	freeReg();

	printDebug("Ended code generation for If");

	return -1;
}

int codeGenWhile(struct tnode* t, FILE* target_file)
{

	printDebug("Started code generation for While");

	int label_begin = getLabel();
	int label_end = getLabel();

	fprintf(target_file, "L%d:\n", label_begin);
	int reg_guard = codeGen(t->left, target_file);
	fprintf(target_file, "JZ R%d, L%d\n", reg_guard, label_end);
	
	codeGen(t->right, target_file);
	
	fprintf(target_file, "JMP L%d\n", label_begin);
	fprintf(target_file, "L%d:\n", label_end);

	freeReg();

	printDebug("Ended code generation for While");

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
		case STR:
			reg = codeGenStr(t, target_file);
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
		case IF:
			codeGenIf(t, target_file);
			return -1;
		case WHILE:
			codeGenWhile(t, target_file);
			return -1;
		default:
			printf("Invalid nodetype: %d.\n", t->nodetype);
			exit(-1);
	}
}

void codeGenXsm(struct tnode* t, FILE* target_file) 
{
	printDebug("Code genration started");
	/* Header */
	fprintf(target_file, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0); 

	fprintf(target_file, "BRKP\n");
	fprintf(target_file, "MOV SP, 4121\n");	
	//4095 + 26 for storing variables. a is in [4095+1]
	
	int result = codeGen(t, target_file);
	
	fprintf(target_file, "MOV R0, \"Exit\" \n");
   	fprintf(target_file, "PUSH R0 \n");
   	fprintf(target_file, "CALL 0 \n");

	if (freeRegister != 0)
		printDebug("Register Leaks!");

	printDebug("Code generation ended");
}
