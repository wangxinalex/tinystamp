#!/bin/bash

make clean  > temp.compile.log
make > temp.compile.log

./tmunit -d 500000 input.cfg

make clean > temp.compile.log
make test_mode  > temp.compile.log
rm  temp.compile.log