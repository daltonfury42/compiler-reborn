#include "WriteNode.hpp"

Register WriteNode::codeGen()
{
	printDebug("Started code generation for Write");

	saveAllReg();

	Register tempreg = getReg();

	writeToFile("MOV R" + tempreg + ", \"Write\"");		
	writeToFile("PUSH R" + tempreg);  	
	writeToFile("MOV R" + tempreg + ", -2");
	writeToFile("PUSH R" + tempreg);

	Register reg1 = writeLocation.getBinding();

	writeToFile("PUSH R" + reg1);
	writeToFile("PUSH R" + tempreg);
	writeToFile("PUSH R" + tempreg);
	writeToFile("CALL 0");
	writeToFile("POP R" + tempreg);
	writeToFile("POP R" + tempreg);
	writeToFile("POP R" + tempreg);
	writeToFile("POP R" + tempreg);
	writeToFile("POP R" + tempreg);
	
	freeReg();
	freeReg();

	restoreAllReg();

	printDebug("Ended code generation for Write");

}
