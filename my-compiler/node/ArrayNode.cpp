#include "Node.hpp"

class ArrayNode : public MemoryLocationNode
{
private:
    std::string arrayName;
    int index;
    SymbolTableEntry symbolTableEntry;
public:
    ArrayNode(std::string arrayName, int index);
    Register getBinding();
};

Register ArrayNode::getBinding()
{
    auto symbolTableEntry = 
    int binding  = symbolTableEntry.getBinding();

    auto reg = getReg();

    writeToFile("MOV R" + reg + ", " + std::to_string(binding));
    writeToFile("ADD R" + reg + ", " + std::to_string(index));
    
    return reg;
}


