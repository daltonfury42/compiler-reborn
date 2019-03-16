#include "SymbolTable.hpp"
#include <iostream>

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

std::optional<SymbolTableEntry> SymbolTable::lookUp(std::string symbolName)
{
    auto it = entries.find(symbolName);

    if (it == entries.end())
    {
        return {};
    }
    else
    {
        return it->second;
    }
}

void SymbolTable::install(SymbolTableEntry& entry)
{
    if (entries.find(entry.getSymbolName()) != entries.end())
    {
        std::cout << "Error: Multiple redeclarations of symbol " << entry.getSymbolName() << std::endl;
    }

    entries.insert(std::pair<std::string, SymbolTableEntry>(entry.getSymbolName(), entry));
}