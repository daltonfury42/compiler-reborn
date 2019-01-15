%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "exptree.h"
  #include "codegen.h"

  int yylex(void);
  int ltlex(void);
  extern FILE* ltin;

  void yyerror(const char *s);

  #define YYSTYPE tnode* 

%}

%error-verbose

%token CONNECTOR READ WRITE VARIABLE ASGN BEG END NUM OPERATOR 

%token IF THEN ELSE ENDIF WHILE DO ENDWHILE

%left GT GTE LT LTE EQ NEQ

%left PLUS MINUS
%left DIV MUL

%%

program 	: BEG slist END 	{	 
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

ReadStmt 	: READ '(' VARIABLE ')' ';'		{ $$ = makeReadNode($3); }
			
WriteStmt 	: WRITE '(' expr ')' ';'		{ $$ = makeWriteNode($3); }

AsgnStmt 	: VARIABLE ASGN expr ';'		{ $$ = makeAssignmentNode($1, $3); }

expr		: expr PLUS expr				{ $$ = makeOperatorNode(PLUS, $1, $3); }
			| expr MINUS expr				{ $$ = makeOperatorNode(MINUS, $1, $3); }
			| expr MUL expr					{ $$ = makeOperatorNode(MUL, $1, $3); }
			| expr DIV expr					{ $$ = makeOperatorNode(DIV, $1, $3); }
			| expr GT expr					{ $$ = makeOperatorNode(GT, $1, $3); }
			| expr GTE expr					{ $$ = makeOperatorNode(GTE, $1, $3); }
			| expr LT expr					{ $$ = makeOperatorNode(LT, $1, $3); }
			| expr LTE expr					{ $$ = makeOperatorNode(LTE, $1, $3); }
			| expr EQ expr					{ $$ = makeOperatorNode(EQ, $1, $3); }
			| expr NEQ expr					{ $$ = makeOperatorNode(NEQ, $1, $3); }
			| '(' expr ')'	 				{ $$ = $2; }
			| NUM							{ $$ = $1; }	// Node made in .l file
			| VARIABLE						{ $$ = $1; }
			;

IfStmt 		: IF '(' expr ')' THEN slist ELSE slist ENDIF 	{ $$ = makeIfNode($3, $6, $8); }
			| IF '(' expr ')' THEN slist ENDIF				{ $$ = makeIfNode($3, $6, NULL); }
			;

WhileStmt 	: WHILE '(' expr ')' DO slist ENDWHILE			{ $$ = makeWhileNode($3, $6); }
			;

%%

void yyerror(const char *s)
{
	printf("Error: %s", s);
}

int main()
{
  	yyparse();
  	return 1;
}
