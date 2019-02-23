#include "typeCheck.h"
#include "y.tab.h"

#include <stdlib.h>
#include <stdio.h>

extern int lineNumber;

void typeError(char* s)
{
    printf("Type Error near line %d: %s.\n", lineNumber, s);
    exit(-2);
}

int typeOf(tnode* t)
{
    if(t->nodetype == VARIABLE)
    {
        if(t->symbolTableEntry == NULL)
        {
            printf("Error: Undeclared variable %s in line %d.\n", t->varname, lineNumber);
            exit(-1);
        }
        
        return t->symbolTableEntry->type;
    }
    else
    {
        return t->type;
    }
}

void typeCheckRead(tnode* t)
{
    if(typeOf(t->right) != T_NUM)
    {
        typeError("read type mismatch");
    }
}

void typeCheckWrite(tnode* t)
{
    if(typeOf(t->right) != T_NUM && typeOf(t->right) != T_STR)
    {
        typeError("write type mismatch");
    }
}

void typeCheckAssignment(tnode* t)
{
    if(typeOf(t->left) != typeOf(t->right) || typeOf(t->right) == -1)
    {
        typeError("Assignment type mismatch");
    }
}

void typeCheckOperator(tnode* t)
{
    if(typeOf(t->left) != T_NUM || typeOf(t->right) != T_NUM)
    {
        typeError("Left and right expressions of operators should be numer type");
    }

    switch(t->operator)
    {
        case PLUS:
        case MINUS:
        case MUL:
        case DIV:   
            t->type = T_NUM;
            break;
        case GT:
        case GTE:
        case LT:
        case LTE:
        case EQ:
        case NEQ:
            t->type = T_BOOL;
            break;
        default:
            typeError("Operator type check failed");
    }
}

void typeCheckIf(tnode* t)
{
    if(typeOf(t->left) != T_BOOL)
    {
        typeError("If guard should be of type bool.");
    }   

}

void typeCheckWhile(tnode* t)
{
    if(typeOf(t->left) != T_BOOL)
    {
        typeError("While guard should be of type bool.");
    }
}

void typeCheckArray(tnode* t)
{
    if(typeOf(t->right) != T_NUM)
    {
        typeError("The index of arrays should be of type T_INT.");
    }

    t->type = typeOf(t->left);
}