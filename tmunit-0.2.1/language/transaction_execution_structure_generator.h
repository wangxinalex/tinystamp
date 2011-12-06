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

#ifndef ___TRANSACTION_EXECUTION_STRUCTURE_GENERATOR_H_____
#define ___TRANSACTION_EXECUTION_STRUCTURE_GENERATOR_H_____

#ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION

    #include "dynamic_array.h"
    #include "txdef.h"
    #include "tx_op_container.h"
    #include "intermediate_representation.h"


typedef struct TransactionOpInfoStruct
{
    DelayType Delay;
    TxOpType  Op;
//    Address_t Addr;   HARMANCI ADDR-->ID  AFTER CHANGE
    unsigned AddrGenIDList[2];
//    unsigned  AddrGenIDNum;
    unsigned AddrOp;
} TxOpInfo_t ;
void TxOp_SetInfo(TxOpContainer_t* TargetOpContainer, TxOpInfo_t* GivenOpInfo);


extern dyn_arr_t CurrentTxOpList;
extern dyn_arr_t ConditionTerminationTxOpList ;
extern bool EndOfIfElseBlock;
extern dyn_arr_t Dyn_VarAssignList;
extern dyn_arr_t Dyn_VarExprToUpdateList;

int InitializeTempTransactionStructuresUsedInParsing();


void MakeTxOpContainerDefault(TxOpContainer_t* TargetOpContainer);
unsigned AddNewContainerToTransaction(dyn_arr_t* TargetTxOpContainerList);
void InsertTxOpContainerToTransaction(dyn_arr_t* CurrentTxOpContainerList, TxOpInfo_t* OperationInfo, ConnectionInfo_t* ConnectionInfo, unsigned ConnectionNum);
void InsertBranchAmongTxOpContainers(dyn_arr_t* CurrentTxOpContainerList, unsigned FromContainerPos,unsigned ToContainerPos,Branch_t BranchType, int IterationNum);
void GenerateAndAttachNewContainerForSingleTxOp(dyn_arr_t* CurrentTxOpContainerList,TxOpInfo_t* GivenOpInfo);


void ExtendVarExprToUpdate(const char* VarExprString);


#endif

#endif
