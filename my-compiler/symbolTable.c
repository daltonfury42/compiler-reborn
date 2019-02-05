#include "symbolTable.h"
#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "exptree.h"

Gsymbol *head = NULL;
Gsymbol *tail = NULL;

int nextFreeBindingAddr = 4096;
int nextFreeFLabel = 0;

Gsymbol* Glookup(char* name)
{
    Gsymbol* temp = head;
    while(temp!=NULL)
    {
        if(strcmp(temp->name, name)==0)
            return temp;
        temp=temp->next;
    }
    
    return NULL;
}

void endIfRedeclared(char* name)
{
    Gsymbol* temp = head;
    while(temp)
    {
        if(strcmp(name, temp->name)==0)
        {
            printf("ERROR : Multiple declaration of variable\n");
            exit(1);
        }
        temp=temp->next;
    }
}

void Ginstall(char* name, int type, int size, int binding, ParamStruct* paramList, int flabel)
{
    endIfRedeclared(name);    

    Gsymbol* newEntry = (Gsymbol*) malloc(sizeof(Gsymbol));
    newEntry->name = (char*) malloc(strlen(name) + 1);

    strcpy(newEntry->name, name); 
    newEntry->type = type;
    newEntry->size = size; 
    newEntry->binding = binding;
    newEntry->paramList = paramList;
    newEntry->flabel = flabel;
    newEntry->next = NULL;

    if(head == NULL)
    {
        head = newEntry;
        tail = newEntry;
    }
    else
    {
        tail->next = newEntry;
        tail = newEntry;
    }
}

void GinstallVariable(char* name, int type, int size) // Creates a symbol table entry.
{
    if(nextFreeBindingAddr>5119)
    {
        printf("ERROR: STACK OVERFLOW\n");
        exit(-1);
    }

    Ginstall(name, type, size, nextFreeBindingAddr, NULL, -1);
    nextFreeBindingAddr += size;
}

void GinstallFunction(char* name, int type, void* paramList)
{
    ParamStruct *phead = NULL;
    tnode *paramListi = (tnode*) paramList;
    if (paramList != NULL)
    {
        phead = malloc(sizeof(ParamStruct));
        ParamStruct *i = phead;

        while(paramListi != NULL){
            i->paramName = paramListi->varname;
            i->type = paramListi->type;
            i->next = NULL;

            paramListi = paramListi->left;
            if (paramListi != NULL)
            {
                i->next = malloc(sizeof(ParamStruct));
                i = i->next;
            }
        }
    }        

    Ginstall(name, type, 0, 0, phead, nextFreeFLabel);
    nextFreeFLabel++;
}