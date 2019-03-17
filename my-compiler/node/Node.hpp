#ifndef NODE_HPP
#define NODE_HPP

#include<string>
#include "SymbolTable.hpp"

typedef std::string Register;
typedef std::string Label;
typedef int Type;

class Node
{
    private:
        static std::string outFileName;
        static int freeRegister;
        static int label;

    protected:
        static void writeToFile(std::string line);
        void restoreAllReg();
        void saveAllReg();
        static void printDebug(std::string msg);
        static Register getReg();
        static void freeReg();
        static std::string getLabel();

    public:
        virtual Register codeGen() = 0;
        static void codeGenInit(Node& node);
        static SymbolTable gSymbolTable;
};

class MemoryLocationNode : public Node
{
    public:
        virtual Register getBinding() = 0;
        Register codeGen();
};

#include "ArrayNode.hpp"
#include "AssignmentNode.hpp"
#include "BinaryOperatorNode.hpp"
#include "ConnectorNode.hpp"
#include "IfNode.hpp"
#include "NumberNode.hpp"
#include "ReadNode.hpp"
#include "StringNode.hpp"
#include "VariableNode.hpp"
#include "WhileNode.hpp"
#include "WriteNode.hpp"
#include "IdentifierNode.hpp"

#endif