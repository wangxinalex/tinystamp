#!/bin/bash

make clean >> temp.compile.log
make test_mode STM=NO_STM >> temp.compile.log

./tmunit -v parser -S S test/development_tests/schedules/dirty_read_2_no_stm/dirty_read_2.cfg

make clean >> temp.compile.log
make test_mode >> temp.compile.log
rm  temp.compile.log


