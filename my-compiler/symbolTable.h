#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

typedef struct Gsymbol 
{
	char *name;		// name of the variable
	int type;		// type of the variable
	int size;		// size of the type of the variable
	int binding;	// stores the static memory address allocated to the variable

	struct ParamStruct *paramList;
	int flabel;

	struct Gsymbol *next;
}Gsymbol; 

typedef struct ParamStruct
{
	char* paramName;
	int type;

	struct ParamStruct *next;
}ParamStruct;


Gsymbol* Glookup(char* name); // Returns a pointer to the symbol table entry for the variable, returns NULL otherwise.

void GinstallFunction(char* name, int type, void* paramList); //actually tnode*

void GinstallVariable(char* name, int type, int size);

#endif