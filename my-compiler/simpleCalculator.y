%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "exptree.h"
  #include "codegen.h"

  int yyerror();
  int yylex(void);

  #define YYSTYPE tnode* 

%}

%token CONNECTOR READ WRITE VARIABLE ASGN BEG END NUM

%left PLUS MINUS
%left DIV MUL

%%

program 	: BEG slist END 	{	 
       								FILE* fptr=fopen("target_file1.xsm","w");
									codeGenXsm($1, fptr);	
									fclose(fptr);
	
									exit(0);
								}
			| BEG END
			;

slist 		: slist stmt 		{
									$$ = makeConnectorNode($1, $2);
								}
			| stmt				{ $$ = $1; }
			;

stmt 		: ReadStmt
			| WriteStmt		
			| AsgnStmt
			;

ReadStmt 	: READ '(' VARIABLE ')' ';'		{ $$ = makeReadNode($1); }
			
WriteStmt 	: WRITE '(' expr ')' ';'		{ $$ = makeWriteNode($1); }

AsgnStmt 	: VARIABLE ASGN expr ';'		{ $$ = makeAssignmentNode($1, $3); }

expr	: expr PLUS expr		{ $$ = makeOperatorNode(PLUS, $1, $3); }
	| expr MINUS expr			{ $$ = makeOperatorNode(MINUS, $1, $3); }
	| expr MUL expr				{ $$ = makeOperatorNode(MUL, $1, $3); }
	| expr DIV expr				{ $$ = makeOperatorNode(DIV, $1, $3); }
	| '(' expr ')'	 			{ $$ = $2; }
	| NUM						{ $$ = $1; }	// Node made in .l file
	| VARIABLE						{ $$ = $1; }
	;

%%

int yyerror()
{
	printf("Error");
}

int main()
{
  	yyparse();
  	return 1;
}
