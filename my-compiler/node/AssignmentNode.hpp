#ifndef ASSIGNMENT_NODE
#define ASSIGNMENT_NODE
#include "Node.hpp"

class AssignmentNode : public Node
{
private:
    MemoryLocationNode& lValue;
    Node& rValue;
public:
    AssignmentNode(MemoryLocationNode& lValue, Node& rValue) : lValue(lValue), rValue(rValue) {}
    ~AssignmentNode();
    Register codeGen();
};

#endif