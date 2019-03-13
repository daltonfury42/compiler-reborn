#include "node.hpp"
#include <ios>
#include <fstream>
#include <iostream>
#include <string>

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

std::string Node::getLabel()
{
	return std::to_string(label++);
}