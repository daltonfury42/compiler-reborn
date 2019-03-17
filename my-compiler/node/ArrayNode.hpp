#ifndef ARRAY_NODE
#define ARRAY_NODE
#include "Node.hpp"

class ArrayNode : public MemoryLocationNode
{
private:
    std::string arrayName;
    Node& index;
public:
    ArrayNode(std::string arrayName, Node& index) : arrayName(arrayName), index(index) {}
    Register getBinding();
};

#endif