#!/bin/bash


make clean >> temp.compile.log
make test_mode STM=TL2 >> temp.compile.log

./tmunit -v parser -S S test/listings_in_paper/zombie_transactions/tl2/zombie_transactions.cfg

make clean >> temp.compile.log
make test_mode >> temp.compile.log
rm  temp.compile.log

