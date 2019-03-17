#ifndef STRING_NODE
#define STRING_NODE

#include "Node.hpp"

class StringNode : public Node
{
private:
    std::string val;
public:
    StringNode(std::string val) : val(val) {}
    ~StringNode() {}
    Register codeGen();
};

#endif