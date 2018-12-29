%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "exptree.h"
  #include "codegen.h"

  int yyerror();
  int yylex(void);

  #define YYSTYPE tnode* 

%}

%token NUM END

%left PLUS MINUS
%left DIV MUL

%%

start 	: expr END		{	 
       					FILE* fptr=fopen("target_file1.xsm","w");
					codeGenXsm($1, fptr);	
					fclose(fptr);
	
					exit(0);
				}
	;

expr	: expr PLUS expr	{ $$ = makeOperatorNode(PLUS, $1, $3); }
	| expr MINUS expr	{ $$ = makeOperatorNode(MINUS, $1, $3); }
	| expr MUL expr		{ $$ = makeOperatorNode(MUL, $1, $3); }
	| expr DIV expr		{ $$ = makeOperatorNode(DIV, $1, $3); }
	| '(' expr ')'	 	{ $$ = $2; }
	| NUM			{ $$ = $1; }	// Node made in .l file
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
