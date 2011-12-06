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
  
   \todo The printed  output of the test is not very  informative. A user that
   does not read  the test code would not understand  anything.  So modify the
   output to get a reasonable log file (as the reference log of the test).
   
   TEST CONTENTS:

      The test verifies the following functions:

         - Initialize_DynamicArray()
	 - Extend_DynamicArray()
	 - GetElement_DynamicArray()
	 - GetSize_DynamicArray()
	 - Free_DynamicArray()

	 
      for three different data structures. 

         i) The first  data structure is "int". The dynamic  array in which it
            is stored in the program is "TestedArray".

        ii) The  second data structure  is "test_t" (which is  defined below).
            The  dynamic  array  in which  it  is  stored  in the  program  is
            "TestedComplexArray". The "test_t" data  structure was used to see
            whether dynamic array data  structure is capable to store multiple
            field data structures.

       iii)  The third  data structure  is  "array_t" (which  is also  defined
            below).  The dynamic array in which it is stored in the program is
            "TestedArrayWithPointers". The  "array_t" data structure  was used
            to see  whether dynamic array  data structure is capable  to store
            multiple field data structures where some fields are pointers. For
            such data structures the freeing process is somehow more involved.
            First, for each element of the dynamic array, the memory allocated
            for  the   regions  pointed  by  the  pointer   fields  should  be
            freed. Then  the Free_DynamicArray() function is used  to free the
            array. For  this procedure  see the part  of the program  which is
            followed by the comment 

	    // FREEING DATA STRUCTURES WITH POINTERS


 */


#include <stdlib.h>
#include <stdio.h>
#include "dynamic_array.h"
#include "general.h"

typedef struct test_struct
{
    double         Value  ;
    unsigned long  ID;
} test_t; 


typedef struct array_struct
{
    unsigned    Size  ;
    int*        Array ;
} array_t; 




int main()
{
    dyn_arr_t TestedArray;
    Initialize_DynamicArray(&TestedArray);

    Extend_DynamicArray(&TestedArray, sizeof(int));
    Extend_DynamicArray(&TestedArray, sizeof(int));
    Extend_DynamicArray(&TestedArray, sizeof(int));
    int* ReturnedElement = (int *)GetElement_DynamicArray(&TestedArray,0,sizeof(int));
    *ReturnedElement = 9;

    ReturnedElement = (int *)GetElement_DynamicArray(&TestedArray,1,sizeof(int));
    *ReturnedElement = 7;

    ReturnedElement = (int *)GetElement_DynamicArray(&TestedArray,2,sizeof(int));
    *ReturnedElement = 5;

    
    ReturnedElement = (int *)GetElement_DynamicArray(&TestedArray,0,sizeof(int));
    printf("ReturnedElement= %d\n",*ReturnedElement);
    ReturnedElement = (int *)GetElement_DynamicArray(&TestedArray,1,sizeof(int));
    printf("ReturnedElement= %d\n",*ReturnedElement);
    ReturnedElement = (int *)GetElement_DynamicArray(&TestedArray,2,sizeof(int));
    printf("ReturnedElement= %d\n",*ReturnedElement);
  

    dyn_arr_t TestedComplexArray; 
    Initialize_DynamicArray(&TestedComplexArray); 
    Extend_DynamicArray(&TestedComplexArray, sizeof(test_t));
    unsigned LastElement = GetSize_DynamicArray(&TestedComplexArray) -1 ;
    test_t* ReturnedComplexElement = (test_t *)GetElement_DynamicArray(&TestedComplexArray,LastElement,sizeof(test_t));
    ReturnedComplexElement -> ID    = 0;
    ReturnedComplexElement -> Value = 1.23;

    Extend_DynamicArray(&TestedComplexArray, sizeof(test_t));
    LastElement = GetSize_DynamicArray(&TestedComplexArray) -1 ;
    ReturnedComplexElement = (test_t *)GetElement_DynamicArray(&TestedComplexArray,LastElement,sizeof(test_t));
    ReturnedComplexElement -> ID    = 1;
    ReturnedComplexElement -> Value = 4.56;


    Extend_DynamicArray(&TestedComplexArray, sizeof(test_t));
    LastElement = GetSize_DynamicArray(&TestedComplexArray) -1 ;
    ReturnedComplexElement = (test_t *)GetElement_DynamicArray(&TestedComplexArray,LastElement,sizeof(test_t));
    ReturnedComplexElement -> ID    = 2;
    ReturnedComplexElement -> Value = 7.89;
 

    unsigned EleNo;
    for(EleNo=0; EleNo< 3; EleNo++)
    {
	ReturnedComplexElement = (test_t *)GetElement_DynamicArray(&TestedComplexArray,EleNo,sizeof(test_t));
	printf("test_t EleNo[%u]-> ID    = %lu\n",EleNo,ReturnedComplexElement->ID);
	printf("test_t EleNo[%u]-> Value = %lf\n",EleNo,ReturnedComplexElement->Value);
    }


    dyn_arr_t TestedArrayWithPointers; 
    Initialize_DynamicArray(&TestedArrayWithPointers); 

    Extend_DynamicArray(&TestedArrayWithPointers, sizeof(array_t));
    LastElement = GetSize_DynamicArray(&TestedArrayWithPointers) -1 ;
    array_t* CurrentElement = (array_t *)GetElement_DynamicArray(&TestedArrayWithPointers,LastElement,sizeof(test_t));
    CurrentElement -> Size   = 1;
    CurrentElement -> Array = malloc(sizeof(int)*(CurrentElement -> Size));
    for(EleNo=0; EleNo< CurrentElement -> Size; EleNo++)
    {
	CurrentElement -> Array[EleNo] = 5*(EleNo)*(CurrentElement -> Size);
    }    

    Extend_DynamicArray(&TestedArrayWithPointers, sizeof(array_t));
    LastElement = GetSize_DynamicArray(&TestedArrayWithPointers) -1 ;
    CurrentElement = (array_t *)GetElement_DynamicArray(&TestedArrayWithPointers,LastElement,sizeof(test_t));
    CurrentElement -> Size   = 2;
    CurrentElement -> Array = malloc(sizeof(int)*(CurrentElement -> Size));
    for(EleNo=0; EleNo< CurrentElement -> Size; EleNo++)
    {
	CurrentElement -> Array[EleNo] = 5*(EleNo)*(CurrentElement -> Size);
    }    


    Extend_DynamicArray(&TestedArrayWithPointers, sizeof(array_t));
    LastElement = GetSize_DynamicArray(&TestedArrayWithPointers) -1 ;
    CurrentElement = (array_t *)GetElement_DynamicArray(&TestedArrayWithPointers,LastElement,sizeof(test_t));
    CurrentElement -> Size   = 3;
    CurrentElement -> Array = malloc(sizeof(int)*(CurrentElement -> Size));
    for(EleNo=0; EleNo< CurrentElement -> Size; EleNo++)
    {
	CurrentElement -> Array[EleNo] = 5*(EleNo)*(CurrentElement -> Size);
    }    

 

    for(EleNo=0; EleNo< 3; EleNo++)
    {
	CurrentElement = (array_t *)GetElement_DynamicArray(&TestedArrayWithPointers,EleNo,sizeof(test_t));
	printf("array_t EleNo[%u]-> Num    = %d\n",EleNo,CurrentElement->Size);

	char* ArrayContents;
	GenereateIntegerListOutput(CurrentElement->Array, CurrentElement->Size, &ArrayContents);
	printf("array_t EleNo[%u]-> Array: %s\n",EleNo,ArrayContents);
	free(ArrayContents);
    }




    Free_DynamicArray(&TestedArray);
    Free_DynamicArray(&TestedComplexArray);


    // FREEING DATA STRUCTURES WITH POINTERS
    for(EleNo=0; EleNo< 3; EleNo++)
    {
	CurrentElement = (array_t *)GetElement_DynamicArray(&TestedArrayWithPointers,EleNo,sizeof(test_t));
	free(CurrentElement -> Array);
    }
    Free_DynamicArray(&TestedArrayWithPointers);
    
    

  
    return 0;
}
