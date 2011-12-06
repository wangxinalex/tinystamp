#!/bin/bash

InitDir=$PWD;

rm -rf reference_c_output 
cp -r  test/development_tests/conditions/if_else_block_1/generate_c/reference_c_output .

cd reference_c_output

make TRACE=ENABLE DEFINES=COMPILE_FOR_TEST &> compile.log
 rm compile.log

./t_benchrun 

rm -rf reference_c_output
