#include "Node.hpp"

Register IfElseNode::codeGen()
{
	printDebug("Started code generation for If");

	Label label_end = getLabel();
	Label label_else = getLabel();

	Register reg_guard = guard.codeGen();

	writeToFile("JZ R" + reg_guard + ", L" + label_else);

	ifPart.codeGen();
	writeToFile("JMP L" + label_end);

	writeToFile("L" + label_else + ":");
	
    if(hasElse)
    {
	    elsePart.codeGen();
    }

	writeToFile("L" + label_end + ":");

	freeReg();

	printDebug("Ended code generation for If");

	return "-1";  
}
