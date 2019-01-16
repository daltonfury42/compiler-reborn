#include <stdio.h>
#include "labelTranslate.h"

int LabelTable[1024];

void storeLabel(int label, int lineNumber)
{
	if (LabelTable[label] != 0)
		printf("Warning: overwriting labels.\n");

	LabelTable[label] = lineNumber;
}

int getLabelAddr(int label)
{
	if (LabelTable[label] == 0)
		printf("Warning: Attempted to lookup a label that doesnot exist..\n");

	return(2056 + 2*(LabelTable[label] - 9));
}
