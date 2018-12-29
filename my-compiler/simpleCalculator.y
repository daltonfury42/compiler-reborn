%{
  #include <stdio.h>
  int yyerror();
%}

%token NUM END

%left PLUS MINUS
%left DIV MUL

%%

start 	: expr END  { printf("Expression value = %d",$1); }
	;

expr	: expr PLUS expr		{$$ = $1 + $3;}
	| expr MUL expr		{$$ = $1 * $3;}
	| '(' expr ')'	 	{$$ = $2;}
	| NUM			{$$ = $1;}
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
