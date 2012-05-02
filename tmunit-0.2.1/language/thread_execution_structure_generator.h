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

#ifndef ___THREAD_EXECUTION_STRUCTURE_GENERATOR_H_____
#define ___THREAD_EXECUTION_STRUCTURE_GENERATOR_H_____

#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

#ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION

#include <sys/time.h> // for timeval structure and nanosleep function
#include <string.h>   // for the FindTxByName() function which uses strcmp()
#include "general.h"  // for bool definition
#include "semantic_error.h" // For REPORT_SEMANTIC_ERROR macro
#include "float.h"    // For DBL_MIN constant
#include "transaction_execution_structure_generator.h"
#include "invariant_execution_structure_generator.h"
#include "intermediate_representation.h"
#include <pthread.h>  // For barrier_t structure and pthread functions used in barrier_init and barrier_cross functions.

#ifdef COMPILE_FOR_TEST
   #define  ITERATION_NUM_OF_INFINITE_LOOPS_FOR_TESTS 100
   #include "test_rng_interface.h"
#else
   #include "system_rng_interface.h"
#endif



typedef struct barrier {
  pthread_cond_t complete;
  pthread_mutex_t mutex;
  int count;
  int crossing;
} barrier_t;

void barrier_init(barrier_t *b, int n);
void barrier_cross(barrier_t *b);



           // Unspecified percentage will be indicated with -1
           #define UNSPECIFIED_PERCENTAGE -1.0

           typedef struct  TransactionCandidateStruct
	   {
	       unsigned  TxID       ;
	       double    Percentage ;  
	   } TxCandidate_t;



     typedef struct TransactionContainerStruct
     {
         //    TxCandidate_t* ListOfTxCandidates;

	 //HARMANCI: CODE ADDED FOR VARIABLE EXPR WITHIN THREAD DEF
	 bool           LoopEndNodeWithVarExpr;
	 unsigned       LoopLimitExprPos;
	 // END OF CODE ADDED FOR VARIABLE EXPR WITHIN THREAD DEF

	 TxCandidate_t* TxCandidateList;
	 unsigned       CandidateTxNum;
	 
	 unsigned      NextContainerID[2];
	 unsigned      RepetitionCount,
	     InitialRepetitionCount;
	 unsigned      CandidateSeed; 
	 unsigned      (*CandidateSelectionFunc)(struct TransactionContainerStruct* CurrentTxContainer);
	 DelayType     PrecedingDelay[2]   ;
	 bool          LoopStartNode;
     } TxContainer_t;



      // Dummy TxInfo_t structure
/*       typedef struct TransactionDefinitionStruct */
/*       { */
/* 	  char* Name; */

/*       } TxInfo_t; */



      // Dummy AddrGen_t
      typedef struct AddressGeneratorStruct
      {
	  char* Name;

      } AddrGen_t;


// MAJOR STRUCTURE TO GENERATE
typedef struct ThreadInfoStruct
{
    char*     Name;
    unsigned  ID  ;
    bool      Active;
    TxContainer_t*  TxContainerList;
    unsigned        TxContainerNum;     
    TxInfo_t*  TxDefArray;
    unsigned   TxDefNum; 
    VarExpr*   VarExprList;
    unsigned   VarExprNum;

    unsigned   WriteValue;

    char*      ConsoleDisplayOffset;
    barrier_t* BarrierSelf;
    barrier_t* SchedulerBarrier;
    
    unsigned long CommitNum;
    unsigned long AbortNum;

    unsigned      UnfinishedTxNum;

    struct timeval start_time; 
    struct timeval end_time  ; 
    
} ThreadInfo_t;


typedef struct TxContainerInfoStruct
{
    char* TxName;
    unsigned PrecedingDelay[2];  //  PrecedingDelay[0] is the delay preceding the transaction 
                                 //  PrecedingDelay[1] is the delay preceding a loop

} TxContainerInfo_t;


extern dyn_arr_t  Dyn_TxDefArray;
extern TxInfo_t*  TxDefArray;
extern unsigned   TxDefNum; 


extern dyn_arr_t Dyn_ThreadDefArray;
extern ThreadInfo_t* ThreadDefArray; 

extern unsigned   ThreadDefArraySize ;
extern unsigned   ThreadDefNum       ;
extern unsigned   ThreadTypeNum      ;
extern dyn_arr_t  Dyn_CurrentThreadDefList;

extern unsigned short CurrentTxContainerNo   ;
extern unsigned short TxBlockStartContainerNo;


extern dyn_arr_t  CurrentTxContainerList; 
extern dyn_arr_t  CurrentTxList;
extern dyn_arr_t  CurrentTxCandidateList;


extern dyn_arr_t Dyn_VariableExpressionArray;

extern unsigned CurrentDelayVal;
extern bool DelayOpEncountered;




int InitializeTempThreadStructuresUsedInParsing();


// Taken from thread.h of benchgen-0.1 version
void AddNewThreadDef(char* ThreadName);


// Taken from transaction.h of benchgen-0.1 version
unsigned UniformDistNextTx(TxContainer_t* CurrentTxContainer);
unsigned PercentageDistNextTx(TxContainer_t* CurrentTxContainer);








void AddNewThreadDef(char* ThreadName);
void Duplicate_ThreadDef(char* SourceThreadName);
void AddNewTxCanidate(dyn_arr_t* CurrentTxCandidateList, const char* CurrentTransactionName, double Percentage);
unsigned AddNewContainerToThread(dyn_arr_t* TargetTxContainerList);
void GenerateAndAttachContainersForForwardTxList(dyn_arr_t* CurrentTxList, unsigned RepetitionCount);

void GenerateAndAttachNewContainerForSimpleTxBlock(const char* CurrentTransactionName, bool* DelayOpEncountered,  unsigned CurrentDelayVal);

//void GenerateAndAttachNewContainerForTxChoiceList(const dyn_arr_t* CurrentTxCandidateList, unsigned RepetitionCount, unsigned* PrecedingDelayPair);
void GenerateAndAttachNewContainerForTxChoiceList(const dyn_arr_t* CurrentTxCandidateList, unsigned RepetitionCount, bool* DelayOpEncountered,  unsigned CurrentDelayVal);

unsigned FindTxByName(const char* SearchedTransactionName, const TxInfo_t* TxDefArray, unsigned TxDefNum);
unsigned FindThreadByName(const char* SearchedThreadName, const ThreadInfo_t* ThreadDefArray, unsigned ThreadDefNum);
void InsertTxContainerToThread(dyn_arr_t* CurrentTxContainerList, const dyn_arr_t* CurrentTxCandidateList, ConnectionInfo_t* ConnectionInfo, unsigned ConnectionNum, unsigned* PrecedingDelayPair);
void InsertTxCandidateListInContainer(const dyn_arr_t* CurrentTxCandidateList, TxContainer_t* CurrentTxContainer);
void InsertBranchAmongTxContainers(dyn_arr_t* CurrentTxContainerList, unsigned FromContainerPos,unsigned ToContainerPos,Branch_t BranchType, int IterationNum);
void InsertVarExprBranchAmongTxContainers(dyn_arr_t* CurrentTxContainerList, unsigned FromContainerPos,unsigned ToContainerPos,Branch_t BranchType, int LoopLimitExprPos);
void MakeTxContainerDefault(TxContainer_t* TargetContainer);



#endif  // END OF   #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION 


#endif
