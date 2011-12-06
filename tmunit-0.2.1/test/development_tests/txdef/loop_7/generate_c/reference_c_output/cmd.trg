#!/bin/bash

InitDir=$PWD;

rm -rf reference_c_output 
cp -r  test/development_tests/txdef/loop_7/generate_c/reference_c_output .

cd reference_c_output

make TRACE=ENABLE DEFINES=COMPILE_FOR_TEST STM=TL2 &> compile.log
 rm compile.log

./t_benchrun 

rm -rf reference_c_output
