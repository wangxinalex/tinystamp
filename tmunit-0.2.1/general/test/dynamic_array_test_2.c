/*
 * 
 * Author(s):
 *   Derin Harmanci <derin.harmanci@unine.ch>
 *
 * Copyright (c) 2008.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/**
   AUTHOR: Derin Harmanci
   GOAL  : TO VERIFY WHETHER THE DYNAMIC TEST ARRAY SIZE IS CORRECTLY HANDLED

   TEST CONTENTS:

      The test verifies the following functions:

         - GetSize_DynamicArray()
         - Chop_DynamicArray()
	 - Clear_DynamicArray()
	 - GetElement_DynamicArray()

	 
      with  the  simplest  data  structure  (the elements  of  the  array  are
      integers).  The test first fills  the array with 3 elements then removes
      one   element  from   the  end.   Then   the  array   is  emptied   with
      Clear_DynamicArray()  function.  Between   all  this  actions  the  test
      verifies whether  the size  of the array  is correctly  maintained. This
      check is done  using the GetSize_DynamicArray() function and  thus it is
      also validated using the test.

      The file  can also be compiled in  two more different ways  so that some
      out of array bound accesses can be  injected in the code. In such a case
      the program  stops due to an  failure to fulfil the  an assertion.  Each
      compile variation  corresponds to  a different out  of bound  error.


      \todo  Change the name  of the  field" ArraySize"  in dynamic  array. It
      confuses the user  reading the test output. Actually  the "ArraySize" of
      the data structure  shows the size of memory allocated  for the array in
      terms of  "number of elements that  could fit in  that allocated memory"
      The value stored  by the current ArraySize is  generally larger than the
      number of elements stored in the array by the user of the array.

 */


#include <stdlib.h>
#include <stdio.h>
#include "dynamic_array.h"
#include "general.h"




#define REPORT_SIZE_INFO(...)     TestedArraySize = GetSize_DynamicArray(&TestedArray); \
                          GenereateIntegerListOutput(TestedArray.ArrayStartAddress, TestedArray.ArrayElementNum, &ArrayContents); \
                          printf(__VA_ARGS__); fflush(NULL);		\
                          free(ArrayContents)



int main()
{

    dyn_arr_t TestedArray;
    unsigned  TestedArraySize;
    char* ArrayContents;


    Initialize_DynamicArray(&TestedArray);
    REPORT_SIZE_INFO("TestedArraySize= %u (after INITIALIZATION)\tArrayContents: %s\n",TestedArraySize, ArrayContents);

    Extend_DynamicArray(&TestedArray, sizeof(int));
    int* ReturnedElement = (int *)GetElement_DynamicArray(&TestedArray,0,sizeof(int));
    *ReturnedElement = 10;
    REPORT_SIZE_INFO("TestedArraySize= %u (after ADD of element \"10\")\tArrayContents: %s\n",TestedArraySize, ArrayContents);

 
    Extend_DynamicArray(&TestedArray, sizeof(int));
    ReturnedElement = (int *)GetElement_DynamicArray(&TestedArray,1,sizeof(int));
    *ReturnedElement = 20;
    REPORT_SIZE_INFO("TestedArraySize= %u (after ADD of element \"20\")\tArrayContents: %s\n",TestedArraySize, ArrayContents);

    Extend_DynamicArray(&TestedArray, sizeof(int));
    ReturnedElement = (int *)GetElement_DynamicArray(&TestedArray,2,sizeof(int));
    *ReturnedElement = 30;
    REPORT_SIZE_INFO("TestedArraySize= %u (after ADD of element \"30\")\tArrayContents: %s\n",TestedArraySize, ArrayContents);

#ifdef OUT_OF_LOWER_BOUND_ERROR
    printf("Trial to access the element right before the beginning of the array:\n"); fflush(NULL);
    GetElement_DynamicArray(&TestedArray,-1,sizeof(int));
#endif

#ifdef OUT_OF_UPPER_BOUND_ERROR
    printf("Accessing the element right after the end of the array:\n"); fflush(NULL);
    TestedArraySize = GetSize_DynamicArray(&TestedArray);
    GetElement_DynamicArray(&TestedArray,TestedArraySize,sizeof(int));
#endif


    Chop_DynamicArray(&TestedArray);
    REPORT_SIZE_INFO("TestedArraySize= %u (after CHOP)\t\t\tArrayContents: %s\n",TestedArraySize, ArrayContents);
    

    Clear_DynamicArray(&TestedArray);
    REPORT_SIZE_INFO("TestedArraySize= %u (after CLEAR)\t\tArrayContents: %s\n",TestedArraySize, ArrayContents);

    Free_DynamicArray(&TestedArray);
  
    return 0;
}



