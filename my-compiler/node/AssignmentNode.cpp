#include "AssignmentNode.hpp"

Register AssignmentNode::codeGen()
{
	printDebug("Started code generation for Asgn");

	Register reg0 = lValue.getBinding();
	
	Register reg1 = rValue.codeGen();
	
	writeToFile("MOV [R" + reg0 + "], R" + reg1);

	freeReg();
	freeReg();

	printDebug("Ended code generation for Asgn");

	return "-1";
}