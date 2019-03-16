#include "Node.hpp"

class IfElseNode : public Node
{
private:
    bool hasElse;
    Node& guard;
    Node& ifPart;
    Node& elsePart;
public:
    IfElseNode(Node& guard, Node& ifPart, Node& elsePart) : 
        guard(guard), ifPart(ifPart), elsePart(elsePart), hasElse(true) {}

    IfElseNode(Node& guard, Node& ifPart) : 
        guard(guard), ifPart(ifPart), elsePart(elsePart), hasElse(false) {}

    ~IfElseNode();
    Register codeGen();
};

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
