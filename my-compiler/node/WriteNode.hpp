#ifndef WHILE_NODE
#define WHILE_NODE

#include "Node.hpp"

class WriteNode : public Node
{
private:
    MemoryLocationNode& writeLocation;
public:
    WriteNode(MemoryLocationNode& writeLocation) : writeLocation(writeLocation) {}
    Register codeGen();
};

#endif