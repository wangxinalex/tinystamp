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

#include <stdlib.h>
#include "general.h"
#include "thread_execution_structure_generator.h"
extern unsigned ThreadDefNum;
extern unsigned TxDefNum;
// extern ThreadInfo_t* ThreadDefArray;


#include "syntax_debug.h" // For MAX_RETURN_STRING_SIZE constant (it is actually a define)
#include <unistd.h>       // For chdir() function

void Generate_C_Code();
void Generate_C_CodeForThread(unsigned ThreadID);

void GenerateVariableDefsBeforeSwitchStatement();

bool  IsConsantValue(const VarExpr* Target);
char* GenerateOperationString(unsigned Operation);
void  GenerateVarExprString(unsigned TargetVarExprID, const  VarExpr* VarExprList, unsigned VarExprListSize, char** ExpressionString);

void  Generate_Transaction_C_Code();


void  GenerateCodeInitializingGlobalOptions();
void  Generate_Thread_Local_Variables();
void  Generate_ThreadSeedInitializations();
void  Generate_ThreadLocalVariableInitializations();

void GenerateSharedVariableDefinitions();
void GenerateSharedVariableInitializations();

