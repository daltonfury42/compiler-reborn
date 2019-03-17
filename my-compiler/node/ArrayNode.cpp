#include "ArrayNode.hpp"

Register ArrayNode::getBinding()
{
    auto symbolTableEntry = gSymbolTable.lookUp(arrayName);
    int binding  = symbolTableEntry.getBinding();

    auto reg = index.codeGen();

    writeToFile("ADD R" + reg + ", " + std::to_string(binding));

    return reg;
}