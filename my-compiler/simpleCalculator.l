%{
  #include <stdio.h>
  #include "y.tab.h"
  #include <stdlib.h>
  #include "exptree.h"

  void yyerror(const char *s);

  int lineNumber = 1;	// Lex keeps track of line numbers for error reporting
%}
	
%%

"begin" 	{ return BEG; }
"end"		{ return END; }
"read" 		{ return READ; }
"write" 	{ return WRITE; }
	
[0-9]+ 		{
				int number = atoi(yytext); 
				yylval = makeLeafNodeNum(number);	
				return NUM;
			}

[a-zA-Z] 	{
				yylval = makeLeafNodeVar(*yytext);
				return VARIABLE;
			}

"+" 		{ return PLUS; }

"-" 		{ return MINUS; }

"*" 		{ return MUL; }

"/" 		{ return DIV; }

"="			{ return ASGN; }

">"			{ return GT; }

">="		{ return GTE; }

"<"			{ return LT; }

"<="		{ return LTE; }

"=="		{ return EQ; }

"!="		{ return NEQ; }

"if"		{ return IF; }

"then"		{ return THEN; }

"else"		{ return ELSE; }

"endif"		{ return ENDIF; }

"while"		{ return WHILE; }

"do"		{ return DO; }

"endwhile"	{ return ENDWHILE; }

[ \t] 		{ }

[\n]		{ lineNumber++; }

[();] 		{ return *yytext; }

		. 	{ 
				yyerror("unknown character\n");
				exit(1);
			}
	
%%
	
int yywrap(void) 
{
	return 1;
}
