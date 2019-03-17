#ifndef NUMBER_NODE
#define NUMBER_NODE

#include "Node.hpp"

class NumberNode : public Node
{
private:
    int val;
public:
    NumberNode(int val) : val(val) {}
    ~NumberNode() {}
    Register codeGen();
};

#endif