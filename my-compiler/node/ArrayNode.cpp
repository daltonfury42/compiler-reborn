#include "node.hpp"

class ArrayNode : public MemoryLocationNode
{
private:
    std::string arrayName;
    int index;
public:
    ArrayNode(std::string arrayName, int index) : arrayName(arrayName), index(index) {}
    Register getBinding();
};

Register ArrayNode::getBinding()
{
    auto symbolTableEntry = gSymbolTable.lookup(arrayName);
    int binding  = symbolTableEntry.getBinding();

    auto reg = getReg();

    writeToFile("MOV R" + reg + ", " + std::to_string(binding));
    writeToFile("ADD R" + reg + ", " + std::to_string(index));
    
    return reg;
}


