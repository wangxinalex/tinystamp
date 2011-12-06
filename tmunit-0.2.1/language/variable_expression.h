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

#ifndef ____VARIABLE_EXPRESSION_______
#define ____VARIABLE_EXPRESSION_______

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "general.h"  // For printing unsigned integer list.
#include "grammar.h"  // For operation name definitions (as in an enum)
#include "dynamic_array.h" // For Dyn_VariableExpressionArray definition

#ifdef COMPILE_FOR_TEST
   #include "test_rng_interface.h"
#else
   #include "system_rng_interface.h"
#endif

#include "simulation_parameters.h" // for VerboseParserOutput variable

typedef unsigned long Word;
#include "tm_interface.h"

typedef enum VarExprTypeEnum
{
   VAR_SHARED_UNMANAGED,
   VAR_SHARED_CONSTANT_UNMANAGED,
   VAR_SHARED_MANAGED,
   VAR_SHARED_CONSTANT_MANAGED,
   VAR_SHARED_ARRAY,
   VAR_SHARED_ARRAY_CONSTANT,
   VAR_LOCAL_SIMPLE,
   VAR_LOCAL_ARRAY,
   VAR_LOCAL_SIMPLE_CONSTANT,
   VAR_LOCAL_ARRAY_CONSTANT,
//
   OP_ARITH_UNARY,
   OP_RELATIONAL_UNARY,
   OP_BOOLEAN_UNARY,
   OP_MEMORY_READ,
   OP_MEMORY_WRITE,
//
   OP_ARITH,
   OP_RELATIONAL,
   OP_BOOLEAN,
   OP_MANAGED_ARRAY_ACCESS,
   OP_UNMANAGED_ARRAY_ACCESS,
//
   OP_RANDOM_DIST,
   OP_RANDOM_DIST_CONSTANT,
   VAR_EXPR_TYPE_NUM
}  VarExprType;

extern const VarExprType INVALID_VAR_EXPR_TYPE;
#define  INVALID_OPERATION  0   



typedef struct VariableExpressionStruct
{
    char*         Name;
    VarExprType   Type;
    unsigned      Operation;
    unsigned      OperandID[5];
    void*         Addr ;
    unsigned long Value;
} VarExpr;


extern dyn_arr_t Dyn_VariableExpressionArray;

void VAR_EXPR_Initialize(VarExpr* Target);
void VAR_EXPR_Finalize(VarExpr* Target);
void VAR_EXPR_Copy(const VarExpr* Source, VarExpr*Target);
void VAR_EXPR_Print(const VarExpr* Target);

unsigned VAR_EXPR_FindPos(const char* SearchedVarExprName, const VarExpr* VarExprList, unsigned VarExprListSize);

signed long VAR_EXPR_Evaluate(VarExpr* Target, VarExpr* VarExprList, unsigned VarExprListSize);

signed long VAR_EXPR_ComputeArithmetic(unsigned Operation, signed long LeftValue, signed long RightValue);
unsigned long VAR_EXPR_ComputeRelational(unsigned Operation, unsigned long LeftValue, unsigned long RightValue);
unsigned long VAR_EXPR_ComputeBoolean(unsigned Operation, unsigned long LeftValue, unsigned long RightValue);
unsigned ChooseFromUniformDist(unsigned CandidateNum, unsigned* Seed);



#endif
