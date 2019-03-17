#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <vector>
#include <map>
#include <string>
#include <exception>
#include "Node.hpp"


class SymbolNotFoundException : public std::exception {
private:
    std::string symbolName;
    std::string symbolTableName;
public:
    SymbolNotFoundException(std::string symbolName, std::string symbolTableName) 
        : symbolName(symbolName), symbolTableName(symbolTableName) {}

    virtual const char* what() const throw()
    {
        return (symbolName + " not found in " + symbolTableName).c_str();
    }
};

class VariableDecl
{
private:
    std::string variableName;
    int type;
public:
    VariableDecl(std::string variableName, int type) : variableName(variableName), type(type) {};
    std::string getVariableName() { return variableName; }
    int getVariableType() { return type; }
};

class SymbolTableEntry
{
private:
    bool isVariable;
    std::string symbolName;
	int type;		
	int size;		
	int binding;	

    bool isFunction;
	std::vector<VariableDecl> paramList;
	int flabel;

    SymbolTableEntry(std::string symbolName, int type) : symbolName(symbolName), type(type) {};

public:
    SymbolTableEntry(std::string symbolName, int type, int size, int binding);
    SymbolTableEntry(std::string symbolName, int type, std::vector<VariableDecl> paramList, int flabel);
    
    std::string getSymbolName() { return symbolName; }
    int getBinding() { return binding; }
};

class SymbolTable
{
private:
    std::string symbolTableName;
    std::map<std::string, SymbolTableEntry> entries;
    int nextFreeBindingAddr = 4096;
    static int nextFreeFLabel;
public:
    SymbolTable(std::string symbolTableName) : symbolTableName(symbolTableName) {};
    ~SymbolTable() {};
    SymbolTableEntry lookUp(std::string symbolName);
    void install(IdentifierNode& identifierNode, int type, int size);
    void install(IdentifierNode& identifierNode, int type, std::vector<VariableDecl> paramList);
};

#endif

