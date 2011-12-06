#!/bin/bash


make clean >> temp.compile.log
make test_mode STM=TL2 >> temp.compile.log

./tmunit -v parser -S S test/listings_in_paper/dirty_read/tl2/dirty_read.cfg

make clean >> temp.compile.log
make test_mode >> temp.compile.log
rm  temp.compile.log

