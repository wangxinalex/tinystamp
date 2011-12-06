
all:
	$(CC) -g -Wall -DDYNAMIC_ARRAY_DEBUG -I../ dynamic_array_test_1.c ../dynamic_array.c ../general.c -o test_dynamic_array_element_add
	./run_test test_dynamic_array_element_add
	$(CC) -g -Wall  -I../ dynamic_array_test_2.c ../dynamic_array.c ../general.c  -o test_dynamic_array_size_1
	./run_test test_dynamic_array_size_1
	$(CC) -g -Wall -DOUT_OF_LOWER_BOUND_ERROR -I../ dynamic_array_test_2.c ../dynamic_array.c ../general.c  -o test_dynamic_array_size_2
	./run_test test_dynamic_array_size_2
	$(CC) -g -Wall -DOUT_OF_UPPER_BOUND_ERROR -I../ dynamic_array_test_2.c ../dynamic_array.c ../general.c  -o test_dynamic_array_size_3
	./run_test test_dynamic_array_size_3


clean:
	rm -f *.o *~
	rm -f test_dynamic_array_element_add
	rm -f test_dynamic_array_size_1  test_dynamic_array_size_2  test_dynamic_array_size_3
