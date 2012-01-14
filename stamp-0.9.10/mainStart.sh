#!/bin/sh
cd ..
./compile
./compile
cd stamp-0.9.10
cp benchmarks stilltodolist
#./mem &
uname -a > unameInfo
./singbench
