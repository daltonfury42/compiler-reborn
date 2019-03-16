#include "Node.hpp"

class AssignmentNode : Node
{
private:
    MemoryLocationNode& lValue;
    Node& rValue;
public:
    AssignmentNode(MemoryLocationNode& lValue, Node& rValue) : lValue(lValue), rValue(rValue) {}
    ~AssignmentNode();
    Register codeGen();
};

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