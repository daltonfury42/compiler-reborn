%{
  #include <stdio.h>
  #include "y.tab.h"
  #include <stdlib.h>
  #include "exptree.h"
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

[ \t\n] 	{ }

[();] 	{ return *yytext; }

. 	{ 
		yyerror("unknown character\n");
		exit(1);
	}
	
%%
	
int yywrap(void) 
{
	return 1;
}
