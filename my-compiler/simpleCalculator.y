%{
  #include <stdio.h>
  #include <stdlib.h>
	#include "Node.hpp"
  #include "typeCheck.h"
  #include "SymbolTable.hpp"

  int yylex(void);
  int ltlex(void);
  extern FILE* ltin;

  void yyerror(const char *s);

  #define YYSTYPE Node

  extern int lineNumber;

  int currentType;
	int returnType;

%}

%error-verbose

%token BEG END DECL ENDDECL
%token VARIABLE

%token T_NUM T_BOOL T_STR

%token IF THEN ELSE ENDIF WHILE DO ENDWHILE

%token ASGN IDENTIFIER NUM STR READ WRITE

%left GT GTE LT LTE EQ NEQ

%left PLUS MINUS
%left DIV MUL

%%

program		: globalDeclarations code			{}
					;

globalDeclarations 	: DECL DeclList ENDDECL 	{}
					| DECL ENDDECL					{}
					;

DeclList 	: DeclList Decl 				{}
					| Decl									{}
					;

Decl 				: Type VarList ';'		{}
					;

Type 			: T_NUM		 							{ currentType = T_NUM; }
					| T_STR									{ currentType = T_STR; }
					;

VarList 	: VarList ',' VarDecl 	{}
					| VarDecl								{}
					;

VarDecl		: IDENTIFIER 										{ Node::gSymbolTable.install($1, currentType, 1); }
					| IDENTIFIER '[' NUM ']'  			{ Node::gSymbolTable.install($1, currentType, $3); }
					;

code			: BEG slist END 				{	initCompile($2); }
					| BEG END								{ 		
																		printf("Empty program, exiting without generating a target file.\n");
																		exit(0);
																	}
					;

slist 		: stmt slist 						{ $$ = ConnectorNode($1, $2); }
					| stmt									{ $$ = $1; }
					;

stmt 			: ReadStmt
					| WriteStmt		
					| AsgnStmt
					| IfStmt
					| WhileStmt
					;

ReadStmt 	: READ '(' memLoc ')' ';'		{ $$ = ReadNode($3); }
			
WriteStmt : WRITE '(' expr ')' ';'		{ $$ = WriteNode($3); }

AsgnStmt 	: memLoc ASGN expr ';'			{ $$ = AssignmentNode($1, $3) }

expr	: expr PLUS expr	{ $$ = OperatorNode(PLUS, $1, $3); }
			| expr MINUS expr	{ $$ = OperatorNode(MINUS, $1, $3); }
			| expr MUL expr		{ $$ = OperatorNode(MUL, $1, $3); }
			| expr DIV expr		{ $$ = OperatorNode(DIV, $1, $3); }
			| expr GT expr		{ $$ = OperatorNode(GT, $1, $3); }
			| expr GTE expr		{ $$ = OperatorNode(GTE, $1, $3); }
			| expr LT expr		{ $$ = OperatorNode(LT, $1, $3); }
			| expr LTE expr		{ $$ = OperatorNode(LTE, $1, $3); }
			| expr EQ expr		{ $$ = OperatorNode(EQ, $1, $3); }
			| expr NEQ expr		{ $$ = OperatorNode(NEQ, $1, $3); }
			| '(' expr ')'		{ $$ = $2; }
			| NUM							{ $$ = $1; }	
			| STR							{ $$ = $1; }
			| memLoc					{ $$ = $1; }
			;

IfStmt 		: IF '(' expr ')' THEN slist ELSE slist ENDIF 		{ $$ = IfNode($3, $6, $8); }
					| IF '(' expr ')' THEN slist ENDIF								{ $$ = IfNode($3, $6); }
					;

WhileStmt : WHILE '(' expr ')' DO slist ENDWHILE						{ $$ = WhileNode($3, $6); }
					;

memLoc		: IDENTIFIER																			{	$$ = VariableNode($1); }
					| IDENTIFIER '[' expr ']'													{ $$ = ArrayNode($1, $3); }	

%%

void yyerror(const char *s)
{
	printf("Error near line %d: %s", lineNumber, s);
}

int main()
{
  	yyparse();
  	return 1;
}

void initCompile(Node& root)
{
	FILE* fptr;
	if ( !(fptr = fopen("tmp_file.xsm", "w")) )
	{
  	perror("Opening output xsm file failed");
 	  exit(-1);
  }
       								
	// Code Generate
	Node::codeGenInit(root, fptr);	
									
	fclose(fptr);

	// Label Translate
	if ( !(ltin = fopen("tmp_file.xsm", "r")) )
  {
    perror("Opening output xsm file failed");
    exit(-1);
  }

	ltlex();

	exit(0);
}