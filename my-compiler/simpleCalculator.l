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
"number"	{ return T_NUM; }
"string"	{ return T_STR; }
"decl"		{ return DECL; }
"enddecl"	{ return ENDDECL; }
	
[0-9]+ 		{
				int number = atoi(yytext); 
				yylval = makeLeafNodeNum(number);	
				return NUM;
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

["][^"]*["]	{
				yylval = makeLeafNodeStringConst(yytext);
				return STR;
			}

[ \t] 		{ }

[\n]		{ lineNumber++; }

[(),;\[\]]	{ return *yytext; }

[a-zA-Z_][a-zA-Z0-9_]* 	{
							yylval = makeLeafNodeVar(yytext);
							return VARIABLE;
						}

. 			{ 
				yyerror("Unknown character. Please add any new characters to the lex file\n");
				exit(1);
			}
	
%%
	
int yywrap(void) 
{
	return 1;
}
