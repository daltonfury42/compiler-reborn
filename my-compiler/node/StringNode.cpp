#include "Node.hpp"

class StringNode : Node
{
private:
    std::string val;
public:
    StringNode(std::string val) : val(val) {}
    ~StringNode() {}
    Register codeGen();
};

Register StringNode::codeGen() 
{
	printDebug("Started code generation for String");

	auto reg = getReg();
	writeToFile("MOV R" + reg + ", " + val);

	printDebug("Ended code generation for String");

	return reg;
}