#include  "BinaryOperatorNode.hpp"
#include "../y.tab.h"

Register BinaryOperatorNode::codeGen()
{
	printDebug("Started code generation for Operator");

	Register reg1 = leftExpr.codeGen();
	Register reg2 = rightExpr.codeGen();
		
	switch(operatorCode)
	{
		case PLUS:	
			writeToFile("ADD R" + reg1 + ", R" + reg2);
			break;
			
		case MINUS:	
			writeToFile("SUB R" + reg1 + ", R" + reg2);
			break;
			
		case MUL:	
			writeToFile("MUL R" + reg1 + ", R" + reg2);
			break;
			
		case DIV:	
			writeToFile("DIV R" + reg1 + ", R" + reg2);
			break;
		case GTE:	
				writeToFile("GE R" + reg1 + " R" + reg2);
				break;
		case GT:	
				writeToFile("GT R" + reg1 + " R" + reg2);
				break;
		case LTE:	
				writeToFile("LE R" + reg1 + " R" + reg2);
				break;
		case LT:	
				writeToFile("LT R" + reg1 + " R" + reg2);
				break;
		case EQ:	
				writeToFile("EQ R" + reg1 + " R" + reg2);
				break;
		case NEQ:	
				writeToFile("NE R" + reg1 + " R" + reg2);
				break;
		default: 	
			printf("INVALID OPERATOR\n");
			exit(-1);				
	}
		
	freeReg();
	
	printDebug("Ended code generation for Operator");	
	return reg1;

} 