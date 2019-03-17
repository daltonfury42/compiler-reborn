#ifndef IF_NODE
#define IF_NODE

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

#endif