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

#ifndef ____INTERMEDIATE_REPRESENTATION___
#define ____INTERMEDIATE_REPRESENTATION___

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simulation_parameters.h"
#include "grammar.h"
#include "variable_expression.h"
#include <ctype.h> // for isupper function
#include "syntax_error.h"
#include "syntax_debug.h"


#define INVALID_ADDR_GEN_ID  ((unsigned)-1)
#define INVALID_ADDR_OP      ((unsigned)-1)



typedef unsigned DelayType;


// Typedefs for functions of interface.h of benchgen-0.1 version
typedef enum BranchTypeEnum {NEXT, LOOP_BACK} Branch_t ;
typedef struct ConnectionInfoType 
{
    Branch_t Type;
    int      BranchOffset;
    unsigned IterationNum;
} ConnectionInfo_t ;




// int InitializeTempDataStructuresUsedInParsing();
bool CheckAndSetSimulationParameter(const char* VariableName, unsigned Value);



unsigned FindVarExpr(const char* SearchedVarExprName, VarExpr** FoundVarExpr);
unsigned AllocVarExpr(const char* SearchedVarExprName, VarExpr** AllocatedTargetVarExpr );
unsigned FindOrAllocVarExpr(const char* SearchedVarExprName, VarExpr** FoundVarExpr);
VarExpr* GetVarExprPtr(unsigned VarExprID);

signed long EvaluateVarExpr(VarExpr* TargetVarExpr);

unsigned ResolveOperationType(const char* OperationString);

void AddSharedVariableToVarExprList(const char* VarExprString, const char* ValueToAssignString);
void AddLocalVariableToVarExprList(const char* VarExprString, const char* ValueToAssignString);

unsigned GetMemAccessOpAddressParameter(const char* AddressParamString);
unsigned GetReadAccessTargetParameter(const char* AddressParamString);
unsigned GetWriteAccessTargetParameter(const char* AddressParamString);



#endif
