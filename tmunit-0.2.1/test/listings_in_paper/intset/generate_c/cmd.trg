#!/bin/bash

rm -f c_output/*
rm -f c_output_intermediate/*

make clean > temp.compile.log
make STM=TL2 STATISTICS_TEST=YES >> temp.compile.log 

./tmunit -g test/listings_in_paper/intset/generate_c/intset.cfg

make clean >> temp.compile.log
make test_mode >> temp.compile.log 
rm  temp.compile.log



