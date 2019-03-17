#include "StringNode.hpp"

Register StringNode::codeGen() 
{
	printDebug("Started code generation for String");

	auto reg = getReg();
	writeToFile("MOV R" + reg + ", " + val);

	printDebug("Ended code generation for String");

	return reg;
}