#!/bin/bash

rm -f c_output/*
rm -f c_output_intermediate/*


./tmunit -g -v parser input.cfg
