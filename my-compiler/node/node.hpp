#ifndef NODE_HPP
#define NODE_HPP

#include<string>

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
        static std::string getReg();
        static void freeReg();
        static std::string getLabel();

    public:
        virtual int codeGen() = 0;
        static Node makeReadNode(Node& readTarget);
};

int Node::freeRegister = 0;
int Node::label = 0;

class MemoryLocationNode : Node
{
    public:
        virtual std::string getBinding() = 0;
};

#endif