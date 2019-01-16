#ifndef H_TYPECHECK
#define H_TYPECHECK

#include "exptree.h"

void typeCheckRead(tnode* t);
void typeCheckWrite(tnode* t);
void typeCheckAssignment(tnode* t);
void typeCheckOperator(tnode* t);
void typeCheckIf(tnode* t);
void typeCheckWhile(tnode* t);


#endif