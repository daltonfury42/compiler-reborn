#include "SymbolTable.hpp"
#include <iostream>

int SymbolTable::nextFreeFLabel = 0;

SymbolTableEntry::SymbolTableEntry(std::string symbolName, int type, int size, int binding) : SymbolTableEntry(symbolName, type)
{
    this->size = size;
    this->binding = binding;
    this->isFunction = false;
    this->isVariable = true;
}

SymbolTableEntry::SymbolTableEntry(std::string symbolName, int type, std::vector<VariableDecl> paramList, int flabel) : SymbolTableEntry(symbolName, type)
{
    this->paramList = paramList;
    this->flabel = flabel;
    this->isFunction = true;
    this->isVariable = false;
}

SymbolTableEntry SymbolTable::lookUp(std::string symbolName)
{
    auto it = entries.find(symbolName);

    if (it == entries.end())
    {
       throw SymbolNotFoundException(symbolName, symbolTableName);
    }
    else
    {
        return it->second;
    }
}

void SymbolTable::install(IdentifierNode& identifierNode, int type, int size)
{
    std::string symbolName = identifierNode.getIdentifier();

    if (entries.find(symbolName) != entries.end())
    {
        std::cout << "Error: Multiple redeclarations of symbol " << symbolName << std::endl;
    }

    int binding = nextFreeBindingAddr;
    nextFreeBindingAddr += size;

    entries.insert(std::pair<std::string, SymbolTableEntry>(symbolName, SymbolTableEntry(symbolName, type, size, binding)));
}

void SymbolTable::install(IdentifierNode& identifierNode, int type, std::vector<VariableDecl> paramList)
{
    std::string symbolName = identifierNode.getIdentifier();
    
    if (entries.find(symbolName) != entries.end())
    {
        std::cout << "Error: Multiple redeclarations of symbol " << symbolName << std::endl;
    }

    entries.insert(std::pair<std::string, SymbolTableEntry>(symbolName, SymbolTableEntry(symbolName, type, paramList, nextFreeFLabel)));

    nextFreeFLabel++;
}