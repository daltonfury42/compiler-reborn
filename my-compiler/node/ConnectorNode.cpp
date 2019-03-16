#include "Node.hpp"

class ConnectorNode : public Node
{
private:
    Node&  next;
    Node& elem;
public:
    ConnectorNode(Node& elem, Node& next) : elem(elem), next(next) {}
    ~ConnectorNode();
    Register codeGen();
};

Register ConnectorNode::codeGen()
{
    elem.codeGen();
    next.codeGen();
}
