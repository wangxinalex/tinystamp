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

#ifndef _____TxInfo_T_H_____
#define _____TxInfo_T_H_____

#include <string.h>
#include "tx_op_container.h"
#include "general.h"


typedef struct TransactionDefinitionStruct
{
    char* Name;

    unsigned TxDefOptionNum;
    TxOpContainer_t** TxOpList;
    unsigned* TxOpNum; 
    int* OptionConditionID;
    int* OutputVariableList;
    int* OutputCalculationList;


    unsigned* VarListToUpdate;
    unsigned  VarToUpdateNum;
    unsigned* LoopIteratorAddrGenList; 
    unsigned  LoopIteratorNum;         
//    unsigned* LoopIterationCountArray;
    unsigned* LoopEndTxOpList;
    unsigned  LoopEndTxOpNum;          

    int      ReadOnly;
    unsigned long CommitNum;
    unsigned long AbortNum;
    unsigned long CurrentRetryNum;
    unsigned long MaxRetryNum;
    unsigned long InherentDelay;
} TxInfo_t;


void TX_INFO_Initialize(TxInfo_t* Target);
void TX_INFO_Finalize(TxInfo_t* Target);
void TX_INFO_Copy(const TxInfo_t* Source, TxInfo_t*Target);
void TX_INFO_Print(const TxInfo_t* Target);



#endif
