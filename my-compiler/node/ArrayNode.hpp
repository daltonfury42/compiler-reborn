#ifndef ARRAY_NODE
#define ARRAY_NODE
#include "Node.hpp"
class ArrayNode : public MemoryLocationNode
{
private:
    std::string arrayName;
    Node& index;
public:
    ArrayNode(IdentifierNode& identifier, Node& index) : arrayName(identifier.getIdentifier()), index(index) {}
    Register getBinding();
};

#endif