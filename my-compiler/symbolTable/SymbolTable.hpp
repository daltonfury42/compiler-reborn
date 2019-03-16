#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <map>
#include <string>

class VariableDecl
{
private:
    std::string variableName;
    int type;
public:
    VariableDecl(std::string variableName, int type) : variableName(variableName), type(type) {};
    ~VariableDecl();
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
};

class SymbolTable
{
private:
    std::map<std::string, SymbolTableEntry> entries;
public:
    SymbolTable() {};
    ~SymbolTable() {};
    std::optional<SymbolTableEntry> lookUp(std::string symbolName);
    void install(SymbolTableEntry& entry);
};

#endif