%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "exptree.h"
  #include "codegen.h"
  #include "typeCheck.h"
  #include "symbolTable.h"

  int yylex(void);
  int ltlex(void);
  extern FILE* ltin;

  void yyerror(const char *s);

  #define YYSTYPE tnode* 

  extern int lineNumber;

  int currentType;

%}

%error-verbose

%token CONNECTOR READ WRITE VARIABLE ASGN BEG END DECL ENDDECL NUM STR OPERATOR 

%token T_NUM T_BOOL T_STR

%token IF THEN ELSE ENDIF WHILE DO ENDWHILE

%left GT GTE LT LTE EQ NEQ

%left PLUS MINUS
%left DIV MUL

%%

program		: globalDeclarations code			{}
			;

globalDeclarations 	: DECL DeclList ENDDECL 	{}
					| DECL ENDDECL				{}
					;

DeclList 			: DeclList Decl 			{}
					| Decl						{}
					;

Decl 				: Type VarList ';'			{}
					;

Type 				: T_NUM 					{ currentType = T_NUM; }
					| T_STR						{ currentType = T_STR; }
					;

VarList 			: VarList ',' VARIABLE 			{ Ginstall($3->varname, currentType, 1); }
					| VARIABLE						{ Ginstall($1->varname, currentType, 1); }
					;

code 				: BEG slist END {	 
									FILE* fptr;
									if ( !(fptr = fopen("tmp_file.xsm", "w")) )
    								{
     								   perror("Opening output xsm file failed");
    								   exit(-1);
    								}
       								
									// Code Generate
									codeGenXsm($2, fptr);	
									
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
			| BEG END			{ 	printf("Empty program, exiting without generating a target file.\n");
									exit(0);
								}
			;

slist 		: slist stmt 		{
									$$ = makeConnectorNode($1, $2);
								}
			| stmt				{ $$ = $1; }
			;

stmt 		: ReadStmt
			| WriteStmt		
			| AsgnStmt
			| IfStmt
			| WhileStmt
			;

ReadStmt 	: READ '(' VARIABLE ')' ';'		{ 
											  $3->type = T_NUM;
											  $$ = makeReadNode($3);
											  typeCheckRead($$);
					 						}
			
WriteStmt 	: WRITE '(' expr ')' ';'		{ $$ = makeWriteNode($3); 
											  typeCheckWrite($$);
											}

AsgnStmt 	: VARIABLE ASGN expr ';'		{
	 										  $1->type = T_NUM;
											  $$ = makeAssignmentNode($1, $3); 
											  typeCheckAssignment($$);
											}

expr		: expr PLUS expr				{ $$ = makeOperatorNode(PLUS, $1, $3); 
											  typeCheckOperator($$);
											}
			| expr MINUS expr				{ $$ = makeOperatorNode(MINUS, $1, $3); 
											  typeCheckOperator($$);
											}
			| expr MUL expr					{ $$ = makeOperatorNode(MUL, $1, $3); 
											  typeCheckOperator($$);
											}
			| expr DIV expr					{ $$ = makeOperatorNode(DIV, $1, $3); 
											  typeCheckOperator($$);
											}
			| expr GT expr					{ $$ = makeOperatorNode(GT, $1, $3); 
											  typeCheckOperator($$);
											}
			| expr GTE expr					{ $$ = makeOperatorNode(GTE, $1, $3); 
											  typeCheckOperator($$);
											}
			| expr LT expr					{ $$ = makeOperatorNode(LT, $1, $3); 
											  typeCheckOperator($$);
											}
			| expr LTE expr					{ $$ = makeOperatorNode(LTE, $1, $3); 
											  typeCheckOperator($$);
											}
			| expr EQ expr					{ $$ = makeOperatorNode(EQ, $1, $3); 
											  typeCheckOperator($$);
											}
			| expr NEQ expr					{ $$ = makeOperatorNode(NEQ, $1, $3); 
											  typeCheckOperator($$);
											}
			| '(' expr ')'	 				{ $$ = $2; }
			| NUM							{ $$ = $1; // Node made in .l file
											  $$->type = T_NUM;
											}	
			| STR							{
											  $$ = $1;
											  $$->type = T_STR;
											}
			| VARIABLE						{ $$ = $1; 
											}
			;

IfStmt 		: IF '(' expr ')' THEN slist ELSE slist ENDIF 	{ $$ = makeIfNode($3, $6, $8); 
															  typeCheckIf($$);
															}
			| IF '(' expr ')' THEN slist ENDIF				{ $$ = makeIfNode($3, $6, NULL); 
															  typeCheckIf($$);
															}
			;

WhileStmt 	: WHILE '(' expr ')' DO slist ENDWHILE			{ $$ = makeWhileNode($3, $6); 
															  typeCheckWhile($$);
															}
			;

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
