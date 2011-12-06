#!/bin/bash

make clean > temp.compile.log
make STM=TL2 STATISTICS_TEST=YES >> temp.compile.log 

./tmunit test/listings_in_paper/intset/intset.cfg

make clean >> temp.compile.log
make test_mode >> temp.compile.log 
rm  temp.compile.log
