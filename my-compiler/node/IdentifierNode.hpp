#ifndef IDENTIFIER_NODE
#define IDENTIFIER_NODE

#include "Node.hpp"

class IdentifierNode : public Node
{
private:
    std::string identifier;
public:
    IdentifierNode(std::string identifier) : identifier(identifier) {}
    std::string getIdentifier() { return identifier; }

    /*  
        This node is used only to pass identifiers from Lex to Yacc
        and code generation on this object was not  expected at the 
        time of writing this node.
    */
    Register codeGen() { throw std::exception(); }
};

#endif
