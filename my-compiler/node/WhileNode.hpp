#ifndef WHILE_NODE
#define WHILE_NODE

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

#endif