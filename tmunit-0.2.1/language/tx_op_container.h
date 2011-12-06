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

#ifndef ____________TX_OP_CONTAINER_H___________
#define ____________TX_OP_CONTAINER_H___________

#include "intermediate_representation.h"


// Adding a new value to the enum requires also the corresponding change in the TX_OP_CONTAINER_Print function 
typedef enum TxOperationEnum { INVALID,
			       START  ,
			       COMMIT ,
			       READ   ,
			       WRITE  ,
			       ABORT  ,
			       LABEL_OP  ,
                               OP_NUM 
                             } TxOpType;




#define  INVALID_DELAY               ((unsigned)-1)
#define  INVALID_CONTAINER_ID        ((unsigned)-1)
#define  INVALID_CONDITION_EXPR_POS  ((unsigned)-1)


typedef struct VarAssignStruct
{
    unsigned AssignedVarID;
    unsigned EvaluatedVarExprID;
} var_assign_t;

typedef struct TransactionOperationContainerStruct
{
    unsigned   ConditionExprPos;
    var_assign_t* VarAssigns;
    unsigned   VarAssignNum;
    DelayType  PrecedingDelay,
      	       DelayBeforeCommit  ;
    bool       LabelEnabled       ;
    char*      Label;
    bool       LoopIteratorContainer;
    bool       LoopExecuting;

    TxOpType   TxOperation;
    unsigned   AccessedAddrGenID[2];
    unsigned   AddrOp;
    unsigned   NextContainerID[2];
    unsigned   RepetitionCount,
	       InitialRepetitionCount;
    int        LoopIteratorAddrGenID;
/*     unsigned      CandidateSeed;  */
/*     unsigned      (*CandidateSelectionFunc)(unsigned, unsigned*); */
} TxOpContainer_t;

void TX_OP_CONTAINER_Initialize(TxOpContainer_t* Target);
void TX_OP_CONTAINER_Finalize(TxOpContainer_t* Target);
void TX_OP_CONTAINER_Copy(const TxOpContainer_t* Source, TxOpContainer_t*Target);
void TX_OP_CONTAINER_Print(const TxOpContainer_t* Target);

#endif
