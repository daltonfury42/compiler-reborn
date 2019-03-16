#include "Node.hpp"

class VariableNode : public MemoryLocationNode
{
private:
    std::string variableName;
public:
    VariableNode(std::string variableName): variableName(variableName) {}
    ~VariableNode() {}
    // Register codeGen(); Inderits from MemoryLocationNode codeGen()
    Register getBinding();
};

Register VariableNode::getBinding()
{
    auto symbolTableEntry = gSymbolTable.gLookup(variableName);
    int binding  = symbolTableEntry.getBinding();

    auto reg = getReg();

    writeToFile("MOV R" + reg + ", " + std::to_string(binding));
    
    return reg;
}