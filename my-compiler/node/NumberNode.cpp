#include "Node.hpp"

class NumberNode : public Node
{
private:
    int val;
public:
    NumberNode(int val) : val(val) {}
    ~NumberNode() {}
    Register codeGen();
};

Register NumberNode::codeGen() 
{
	printDebug("Started code generation for Number");

	auto reg = getReg();
	writeToFile("MOV R" + reg + ", " + std::to_string(val));

	printDebug("Ended code generation for Number");

	return reg;
}