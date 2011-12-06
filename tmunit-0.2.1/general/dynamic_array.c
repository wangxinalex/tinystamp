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

#include "dynamic_array.h"


void Initialize_DynamicArray(dyn_arr_t* InArray)
{
    InArray -> ArrayStartAddress = NULL; 
    InArray -> ArrayElementNum   = 0;
    InArray -> ArraySize         = 0;
    InArray -> ArraySizeIncrement = 2 ;
}

void Extend_DynamicArray( dyn_arr_t* Array, unsigned ElementSizeInMemory)
{
    if(Array -> ArrayElementNum >= Array-> ArraySize )
    {
	Array -> ArraySize = Array -> ArraySize + Array -> ArraySizeIncrement;
        DEBUG_PRINT("Array -> AllocatedArraySize=%u,Array -> ArrayElementNum = %u\n",Array -> ArraySize,Array -> ArrayElementNum);
	unsigned NewArraySize = Array -> ArraySize*ElementSizeInMemory;
	if(Array -> ArrayStartAddress == NULL)
	{
	    DEBUG_PRINT("Allocating space for the first time for dynamic array. AllocatedArraySize= %u\n",Array -> ArraySize);
	    Array -> ArrayStartAddress= malloc(NewArraySize);
	}
	else
	{
	    DEBUG_PRINT("Reallocating space for dynamic array. AllocatedArraySize= %u\n",Array -> ArraySize);
	    Array -> ArrayStartAddress = realloc(Array -> ArrayStartAddress,NewArraySize);
	    assert(Array -> ArrayStartAddress != NULL);
	}
    }

    Array -> ArrayElementNum++;
    DEBUG_PRINT("Array size is now %u.\n",Array -> ArrayElementNum);
}

void Chop_DynamicArray( dyn_arr_t* Array)
{
    assert( Array != NULL);
    assert( Array -> ArrayElementNum > 0);
    Array -> ArrayElementNum --;
}



void Clear_DynamicArray(dyn_arr_t* TargetArray)
{
    assert( TargetArray != NULL);
    TargetArray -> ArrayElementNum =0;
}

unsigned GetSize_DynamicArray(const dyn_arr_t* TargetArray)
{
    return TargetArray -> ArrayElementNum;
}

void* GetElement_DynamicArray(const dyn_arr_t* TargetArray,unsigned Pos,unsigned ElementSize)
{
    assert(Pos < TargetArray -> ArrayElementNum);
    return  (void *)(TargetArray->ArrayStartAddress + ElementSize*Pos);
}


void* MakeStaticCopy_DynamicArray(const dyn_arr_t* SourceArray, unsigned ElementSizeInMemory)
{
    assert(SourceArray != NULL);
    unsigned StaticArraySize = (SourceArray -> ArrayElementNum) * ElementSizeInMemory;
    void* StaticArrayPtr = malloc(StaticArraySize);
    memcpy(StaticArrayPtr, SourceArray -> ArrayStartAddress, StaticArraySize);
    return StaticArrayPtr; 
}

void Free_DynamicArray(dyn_arr_t* TargetArray)
{
    free(TargetArray->ArrayStartAddress);
    Initialize_DynamicArray(TargetArray);
}
