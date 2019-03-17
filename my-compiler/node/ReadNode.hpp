#ifndef READ_NODE
#define READ_NODE

#include  "Node.hpp"

class ReadNode : public Node
{
private:
    MemoryLocationNode& readTarget;
public:
    ReadNode(MemoryLocationNode& readTarget) : readTarget(readTarget) {}
    ~ReadNode() {}

    Register codeGen();
};

#endif