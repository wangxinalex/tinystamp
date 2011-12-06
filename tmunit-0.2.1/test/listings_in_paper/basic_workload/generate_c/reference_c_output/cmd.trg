#!/bin/bash

InitDir=$PWD;

cp -r  test/listings_in_paper/basic_workload/generate_c/reference_c_output .

cd reference_c_output

make TRACE=ENABLE DEFINES=COMPILE_FOR_TEST  &> compile.log
 rm compile.log

./t_benchrun 

cd $InitDir;
rm -rf reference_c_output




