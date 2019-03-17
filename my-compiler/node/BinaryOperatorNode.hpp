#ifndef BINARYOP_NODE
#define BINARYOP_NODE

#include "Node.hpp"
class BinaryOperatorNode : public Node
{
private:
    int operatorCode;
    Node& leftExpr;
    Node& rightExpr;
public:
    BinaryOperatorNode(int operatorCode, Node& leftExpr, Node& rightExpr) : 
        operatorCode(operatorCode), leftExpr(leftExpr), rightExpr(rightExpr) {}
    ~BinaryOperatorNode();

    Register codeGen();
};

#endif