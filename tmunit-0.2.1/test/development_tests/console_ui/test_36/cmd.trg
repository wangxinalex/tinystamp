#!/bin/bash

make clean  > temp.compile.log
make > temp.compile.log

./tmunit input.cfg

make clean > temp.compile.log
make test_mode  > temp.compile.log
rm  temp.compile.log