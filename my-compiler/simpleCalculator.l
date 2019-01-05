%{
  #include <stdio.h>
  #include "y.tab.h"
  #include <stdlib.h>
  #include "exptree.h"
%}
	
%%

"begin" { return BEG; }
"end"	{ return END; }
"read" 	{ return READ; }
"write" { return WRITE; }
	
[0-9]+ 	{
				int number = atoi(yytext); 
				yylval = makeLeafNodeNum(number);	
				return NUM;
			}

[a-zA-Z] 	{
				yylval = makeLeafNodeVar(*yytext);
				return VARIABLE;
			}

"+" 	{ return PLUS; }

"-" 	{ return MINUS; }

"*" 	{ return MUL; }

"/" 	{ return DIV; }

"="		{ return ASGN; }

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
