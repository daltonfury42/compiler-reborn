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

void typeCheckRead(tnode* t)
{
    if(t->right->type != T_NUM)
    {
        typeError("read type mismatch");
    }
}

void typeCheckWrite(tnode* t)
{
    if(t->right->type != T_NUM)
    {
        typeError("write type mismatch");
    }
}

void typeCheckAssignment(tnode* t)
{
    if(t->left->type != t->right->type || t->right->type == -1)
    {
        typeError("Assignment type mismatch");
    }
}

void typeCheckOperator(tnode* t)
{
    if(t->left->type != T_NUM || t->right->type != T_NUM)
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
    if(t->left->type != T_BOOL)
    {
        typeError("If guard should be of type bool.");
    }   

}

void typeCheckWhile(tnode* t)
{
    if(t->left->type != T_BOOL)
    {
        typeError("While guard should be of type bool.");
    }
}

