%{

	#include "labelTranslate.h"
	int lineCount = 1;
	int pass = 1;	//1st or second pass;
	FILE* fp;
%}

%%

[L][0-9]+:\n 	{	
					if(pass == 1)
					{
						int label;
						sscanf(yytext, "L%d", &label);
						storeLabel(label, lineCount);	
					}
				}
[L][0-9]+		{ 
					if(pass == 2)
					{	int label;
						
						sscanf(yytext, "L%d", &label);
						fprintf(fp, "%d", getLabelAddr(label));
						
					}
				}

[\n]		{
			if(pass == 1)
			{
				lineCount++;
			}
			else
				fprintf(fp, "\n");
		}

.		{ 	
			if(pass == 2)
				fprintf(fp, "%s", yytext);
		}

%%

int ltwrap()
{
	if(pass == 1)
	{
		pass = 2;

		fseek(ltin, 0, SEEK_SET);

		fp = fopen("target_file.out", "w");
		
		return 0;
	}
	else if(pass == 2)
	{ 
		fclose(ltin);
		fclose(fp);
		return 1;
	}
}
