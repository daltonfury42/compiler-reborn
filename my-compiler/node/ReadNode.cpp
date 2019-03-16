#include  "Node.hpp"

class ReadNode : Node
{
private:
    MemoryLocationNode& readTarget;
public:
    ReadNode(MemoryLocationNode& readTarget) : readTarget(readTarget) {}
    ~ReadNode() {}

    Register codeGen();
};

Register ReadNode::codeGen()
{
    printDebug("Started code generation for Read");

	saveAllReg();

	Register reg0 = readTarget.getBinding();

	Register tmpreg = getReg();

	writeToFile("MOV R" + tmpreg + ", \"Read\"");		
	writeToFile("PUSH R" + tmpreg);  	
	writeToFile("MOV R" + tmpreg + ", -1");
	writeToFile("PUSH R" + tmpreg);
	writeToFile("PUSH R" + reg0);
	writeToFile("PUSH R" + tmpreg);
	writeToFile("PUSH R" + tmpreg);
	writeToFile("CALL 0");
	writeToFile("POP R" + tmpreg);
	writeToFile("POP R" + tmpreg);
	writeToFile("POP R" + tmpreg);
	writeToFile("POP R" + tmpreg);
	writeToFile("POP R" + tmpreg);

	freeReg();
	freeReg();

	restoreAllReg();

	printDebug("Ended code generation for Read");


	return "None";
}
