#!/bin/sh 
set -e
cd build
yacc -d ../simpleCalculator.y
lex ../simpleCalculator.l
gcc -g lex.yy.c y.tab.c exptree.c codegen.c

set +e

./a.out < ../testProgram.silc

retVal=$?
if [ $retVal -ne 0 ]; then
    echo "ERROR: Compilation failed."
    exit
else
    echo "Target xsm file generated."
    cd xsm_expl
    ./xsm -l library.xsm -e ../target_file.xsm --debug
fi