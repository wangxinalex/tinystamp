#!/bin/bash

make clean > temp.compilation.log
make >>  temp.compilation.log

./tmunit -S S2  -v all input.cfg

make clean >>  temp.compilation.log
make test_mode >>  temp.compilation.log
rm  temp.compilation.log


