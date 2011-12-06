#!/bin/bash

make clean >> temp.compile.log
make test_mode STM=NO_STM >> temp.compile.log

./tmunit -v parser -S S test/listings_in_paper/dirty_read/no_stm/dirty_read.cfg

make clean >> temp.compile.log
make test_mode >> temp.compile.log
rm  temp.compile.log
