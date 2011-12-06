#!/bin/bash


rm -f c_output/*
rm -f c_output_intermediate/*


./tmunit -g test/listings_in_paper/basic_workload/generate_c/basic_workload.cfg

