#ifndef NODE_HPP
#define NODE_HPP

#include<string>
#include "SymbolTable.hpp"

typedef std::string Register;
typedef std::string Label;

class Node
{
    private:
        std::string outFileName = "outFile.xsm";
        static int freeRegister;
        static int label;

    protected:
        void writeToFile(std::string line);
        void restoreAllReg();
        void saveAllReg();
        void printDebug(std::string msg);
        static Register getReg();
        static void freeReg();
        static std::string getLabel();
        static SymbolTable gSymbolTable;

    public:
        virtual Register codeGen() = 0;
        static void codeGenInit(Node& node);
};

int Node::freeRegister = 0;
int Node::label = 0;

class MemoryLocationNode : public Node
{
    public:
        virtual Register getBinding() = 0;
        Register codeGen();
};

#include "ArrayNode.cpp"
#include "AssignmentNode.cpp"
#include "BinaryOperatorNode.cpp"
#include "ConnectorNode.cpp"
#include "IfNode.cpp"
#include "NumberNode.cpp"
#include "ReadNode.cpp"
#include "StringNode.cpp"
#include "VariableNode.cpp"
#include "WhileNode.cpp"
#include "WriteNode.cpp"

#endif