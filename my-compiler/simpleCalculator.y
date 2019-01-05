%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "exptree.h"
  #include "codegen.h"

  int yylex(void);

  void yyerror(const char *s);

  #define YYSTYPE tnode* 

%}


%error-verbose

%token CONNECTOR READ WRITE VARIABLE ASGN BEG END NUM OPERATOR

%left PLUS MINUS
%left DIV MUL

%%

program 	: BEG slist END 	{	 
									FILE* fptr;
									if ( !(fptr = fopen("target_file.xsm", "w")) )
    								{
     								   perror("Opening output xsm file failed");
    								   exit(-1);
    								}
       								
									codeGenXsm($2, fptr);	
									
									fclose(fptr);
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
			;

ReadStmt 	: READ '(' VARIABLE ')' ';'		{ $$ = makeReadNode($3); }
			
WriteStmt 	: WRITE '(' expr ')' ';'		{ $$ = makeWriteNode($3); }

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

void yyerror(const char *s)
{
	printf("Error: %s", s);
}

int main()
{
  	yyparse();
  	return 1;
}
