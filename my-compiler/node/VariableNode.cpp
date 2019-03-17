#include "VariableNode.hpp"

Register VariableNode::getBinding()
{
    auto symbolTableEntry = gSymbolTable.lookUp(variableName);
    int binding  = symbolTableEntry.getBinding();

    auto reg = getReg();

    writeToFile("MOV R" + reg + ", " + std::to_string(binding));
    
    return reg;
}