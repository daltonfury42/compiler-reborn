#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include "exptree.h"
#include "codegen.h"

int freeRegister=0;

int codeGen(struct tnode* t, FILE* target_file);

//returns stackPos for variable
int getVarPos(char ch)
{
	int index=ch-'a';
	return 4096+index;
}

int getReg()
{
	if(freeRegister > 19)
		{
			printf("Reg overflow");
			exit(1);
		}
		
	return freeRegister++;
}

void freeReg()
{
	if(freeRegister==0)
		return;
	freeRegister--;

}

int codeGenOperator(struct tnode* t, FILE* target_file)
{
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
			
		default: 	
			printf("INVALID OPERATOR");
			exit(1);				
	}
		
	freeReg();
	return reg1;
}

int codeGenNumber(struct tnode* t, FILE* target_file)
{
	int reg = getReg();
	fprintf(target_file, "MOV R%d, %d\n", reg, t->val);
	return reg;
}

int codeGenVar(tnode* t, FILE* target_file)
{
	int varPos = getVarPos(t->varname);	//returns 4096+0 for a and so on
	int reg0 = getReg();
	fprintf(target_file, "MOV R%d, [%d]\n", reg0, varPos);
	return reg0;
}

int codeGenRead(struct tnode* t, FILE* target_file)
{
	char varname = t->right->varname;
	int varPos = getVarPos(varname);

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

	return -1;
}

int codeGenWrite(struct tnode* t, FILE* target_file)
{
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
	char varname = t->left->varname;
	int varPos = getVarPos(varname);
	
	int reg1 = codeGen(t->right, target_file);
	
	fprintf(target_file, "MOV [%d], R%d\n ", varPos, reg1);

	freeReg();

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
	/* Header */
	fprintf(target_file, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0); 

	int result = codeGen(t, target_file);
	
	fprintf(target_file, "MOV SP, 4096\n");
	fprintf(target_file, "MOV [SP], R%d\n", result);

	
	fprintf(target_file, "MOV R0, \"Write\"\n");		
   	fprintf(target_file, "PUSH R0 \n");  	
   	fprintf(target_file, "MOV R0, -2 \n");
   	fprintf(target_file, "PUSH R0 \n");
   	fprintf(target_file, "MOV R0, [4096] \n");
   	fprintf(target_file, "PUSH R0 \n");
   	fprintf(target_file, "PUSH R0 \n");
   	fprintf(target_file, "PUSH R0 \n");
   	fprintf(target_file, "CALL 0 \n");
   	fprintf(target_file, "POP R0 \n");
   	fprintf(target_file, "POP R1 \n");
   	fprintf(target_file, "POP R1 \n");
   	fprintf(target_file, "POP R1 \n");
   	fprintf(target_file, "POP R1 \n");
   	fprintf(target_file, "MOV R0, \"Exit\" \n");
   	fprintf(target_file, "PUSH R0 \n");
   	fprintf(target_file, "CALL 0 \n");
}
