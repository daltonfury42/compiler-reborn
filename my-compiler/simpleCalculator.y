%{
  #include <stdio.h>
  int yyerror();
  int yylex(void);
%}

%token NUM END

%left PLUS MINUS
%left DIV MUL

%%

start 	: expr END  { printf("Expression value = %d\n", $1); }
	;

expr	: expr PLUS expr	{ $$ = $1 + $3; }
	| expr MINUS expr	{ $$ = $1 - $3; }
	| expr MUL expr		{ $$ = $1 * $3; }
	| expr DIV expr		{ $$ = $1 / $3; }
	| '(' expr ')'	 	{ $$ = $2; }
	| NUM			{ $$ = $1; }
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
