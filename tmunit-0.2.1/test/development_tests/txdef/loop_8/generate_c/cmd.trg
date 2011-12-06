#!/bin/bash

rm -f c_output/*
rm -f c_output_intermediate/*

./tmunit -g test/development_tests/txdef/loop_8/generate_c/input.cfg 
