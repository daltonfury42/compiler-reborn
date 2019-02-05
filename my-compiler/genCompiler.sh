#!/bin/sh 
set -e
cd build
yacc -d ../simpleCalculator.y
lex ../simpleCalculator.l
lex -P lt ../labelTranslate.l
gcc -g lex.yy.c lex.lt.c y.tab.c exptree.c codegen.c labelTranslate.c typeCheck.c symbolTable.c

set +e

./a.out < ../bubbleSort.silc

