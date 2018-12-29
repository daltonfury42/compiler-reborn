#!/bin/sh 
set -e
yacc -d simpleCalculator.y
lex simpleCalculator.l
gcc -g lex.yy.c y.tab.c 
./a.out 

