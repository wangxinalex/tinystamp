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

/*! 
   USAGE OF dynamic_array DATA STRUCTURE.

   The structure  is intended  to be  used as an  extendable array.   In other
   words, the  data structure provides  the required memory allocation  for an
   array of elements. The user only needs to fill up the array elements.

   Before   using  the  data   structure  it   should  be   initialized  using
   Initialize_DynamicArray() function.

   Procedure to add a new element in the array:
   
   1) If  a new  element is  added to  the array  just  use Extend_DynamicArray()
   function to ensure  that space is allocated for this  new element. 

   2 )Then  use GetElement_DynamicArray  function to  get a  pointer to  this new
   element. 
   
   3) Fill up the element as you would fill your data structure.
   
   For  the  moment the  data  structure  only  has Extend_DynamicArray  which
   extends the legally usable size of the array by one (Actually the allocated
   number of elements for the array can be larger, but the legally usable size
   of the indicates the size of the array that has been asked by the user)

   \todo Modify Extend_DynamicArray such that it can extend the legally usable
   size by a desired number of elements.

   \todo Include a function or parametrize  Initialize_DynamicArray such that 
   ArraySizeIncrement of the data structure can be set by the user.   

 */


#ifndef ____DYNAMIC_ARRAY_H______
#define ____DYNAMIC_ARRAY_H______




#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h> // Due to usage of memcpy function


#ifdef __cplusplus
extern "C" {
#endif


#ifdef DYNAMIC_ARRAY_DEBUG
#define DEBUG_PRINT(...)  printf(__VA_ARGS__); fflush(NULL)
#else
#define DEBUG_PRINT(...)
#endif

typedef struct DynamicArrayStruct
{
    void*     ArrayStartAddress;
    unsigned  ArrayElementNum  ,
	      ArraySize ,
	      ArraySizeIncrement;
    
} dyn_arr_t;


void Initialize_DynamicArray(dyn_arr_t*InArray);
void Extend_DynamicArray( dyn_arr_t* Array, unsigned ElementSizeInMemory);
void Chop_DynamicArray(dyn_arr_t* Array);
void Clear_DynamicArray(dyn_arr_t* TargetArray);
void Free_DynamicArray(dyn_arr_t* TargetArray);


unsigned GetSize_DynamicArray(const dyn_arr_t* TargetArray);
void* GetElement_DynamicArray(const dyn_arr_t* TargetArray,unsigned Pos,unsigned ElementSize);

void* MakeStaticCopy_DynamicArray(const dyn_arr_t* SourceArray, unsigned ElementSizeInMemory);


#ifdef __cplusplus
}
#endif



#endif
