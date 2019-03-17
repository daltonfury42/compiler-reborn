#include "Node.hpp"
#include <ios>
#include <fstream>
#include <iostream>
#include <string>

int Node::freeRegister = 0;
int Node::label = 0;
std::string Node::outFileName = "outFile.xsm";
SymbolTable Node::gSymbolTable = SymbolTable("GSymbolTable");


void Node::writeToFile(std::string line)
{
    std::ofstream log(outFileName, std::ios_base::app | std::ios_base::out);
    log << line <<  std::endl;
}

void Node::printDebug(std::string msg)
{
	std::cout << "DEBUG: " << msg << std::endl;
}

void Node::saveAllReg()
{
	for(int i = 0; i < freeRegister; i++)
	{
		this->writeToFile("PUSH R" + std::to_string(i));
	}
}

void Node::restoreAllReg()
{
	for(int i = freeRegister - 1; i >= 0; i--)
	{
		this->writeToFile("POP R" + std::to_string(i));
	}
}

std::string Node::getReg()
{
	if(freeRegister > 15)
		{
			printf("Reg overflow");
			exit(-1);
		}
		
	return std::to_string(freeRegister++);
}

void Node::freeReg()
{
	if(freeRegister==0)
	{
		printf("Too many invocations of freeReg.\n");
		exit(-1);
	}
	freeRegister--;
}

Label Node::getLabel()
{
	return std::to_string(label++);
}

Register MemoryLocationNode::codeGen()
{
	auto reg = getBinding();

	writeToFile("MOV R" + reg + ", R" + reg);

	return reg;
}

void Node::codeGenInit(Node& node) 
{
	printDebug("Code genration started");
	/* Header */
	writeToFile("0");
	writeToFile("2056");
	writeToFile("0");
	writeToFile("0");
	writeToFile("0");
	writeToFile("0");
	writeToFile("0");
	writeToFile("0");

	writeToFile("BRKP");
	writeToFile("MOV SP, 4121");	
	//4095 + 26 for storing variables. a is in [4095+1]
	
	node.codeGen();
	
	writeToFile("MOV R0, \"Exit\"");
   	writeToFile("PUSH R0");
   	writeToFile("CALL 0");

	if (freeRegister != 0)
		printDebug("Register Leaks!");

	printDebug("Code generation ended");
}