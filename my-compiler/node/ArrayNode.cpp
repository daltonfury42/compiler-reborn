#include "ArrayNode.hpp"

Register ArrayNode::getBinding()
{
    auto symbolTableEntry = gSymbolTable.lookUp(arrayName);
    int binding  = symbolTableEntry.getBinding();

    auto reg = getReg();

    writeToFile("MOV R" + reg + ", " + std::to_string(binding));
    writeToFile("ADD R" + reg + ", " + std::to_string(index));
    
    return reg;
}


