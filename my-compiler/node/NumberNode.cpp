#include "NumberNode.hpp"

Register NumberNode::codeGen() 
{
	printDebug("Started code generation for Number");

	auto reg = getReg();
	writeToFile("MOV R" + reg + ", " + std::to_string(val));

	printDebug("Ended code generation for Number");

	return reg;
}