#include "ConnectorNode.hpp"

Register ConnectorNode::codeGen()
{
    elem.codeGen();
    next.codeGen();
}
