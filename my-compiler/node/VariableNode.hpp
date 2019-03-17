#ifndef VARIABLE_NODE
#define VARIABLE_NODE

#include "Node.hpp"

class VariableNode : public MemoryLocationNode
{
private:
    std::string variableName;
public:
    VariableNode(IdentifierNode& identifierNode): variableName(identifierNode.getIdentifier()) {}
    // Register codeGen(); Inderits from MemoryLocationNode codeGen()
    Register getBinding();
};

#endif