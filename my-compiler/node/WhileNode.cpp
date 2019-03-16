#include "Node.hpp"

class WhileNode : public Node
{
private:
    Node& condition;
    Node& body;
public:
    WhileNode(Node& condition, Node& body) : condition(condition), body(body) {}
    Register codeGen();
};

Register WhileNode::codeGen()
{
    printDebug("Started code generation for While");

	Label label_begin = getLabel();
	Label label_end = getLabel();

	writeToFile("L" + label_begin + ":");
	Register reg_guard = condition.codeGen();
	writeToFile("JZ R" + reg_guard + ", L" + label_end);
	
    body.codeGen();
	
	writeToFile("JMP L" + label_begin);
	writeToFile("L" + label_end + ":");

	freeReg();

	printDebug("Ended code generation for While");

	return "-1";
}