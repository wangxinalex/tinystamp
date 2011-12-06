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

#ifndef ____INVARIANT_EXECUTION_STRUCTURE_GENERATOR_H___
#define ____INVARIANT_EXECUTION_STRUCTURE_GENERATOR_H___

#include "dynamic_array.h"


extern dyn_arr_t Dyn_InvariantArray;
extern unsigned  InvariantNum;

typedef struct Invariant_struct
{
    char*    Name;
    unsigned VarExprID;
} Invariant;


#endif
