#!/bin/bash

InitDir=$PWD;

cp -r  test/listings_in_paper/intset/generate_c/reference_c_output .

cd reference_c_output

make STM=TL2  > compile.log
 rm compile.log

./benchrun 

cd $InitDir;
rm -rf reference_c_output




