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

#ifndef ______THREAD_H_____
#define ______THREAD_H_____


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "simulation_parameters.h"  // for MainSeed parameter

#include "thread_execution_structure_generator.h"  // for ThreadDefArray array
extern ThreadInfo_t* ThreadDefArray;

#include "invariant_execution_structure_generator.h"  // for ThreadDefArray array


#include "intermediate_representation.h"
#include "tx_op_container.h"

// For random number generator interface
#ifdef COMPILE_FOR_TEST
   #include "test_rng_interface.h"
#else
   #include "system_rng_interface.h"
#endif

#define THREAD_DOT_C_INCLUDING
#include "tm_interface.h"
#include "atomic_ops.h"
#undef THREAD_DOT_C_INCLUDING


typedef struct thread_input_struct 
{
    unsigned short thread_ID;
//    unsigned       MaxTxNumToExecute;
    unsigned       ThreadSeed;
    barrier_t*       ThreadBarrier;
    barrier_t*       SchedulerBarrier;
} 
thread_input_t;



extern barrier_t barrier;
extern barrier_t termination_barrier;

extern unsigned long TerminateRequestedBySignal;
extern unsigned*  ThreadSeed;


void  InitializeThreadSeeds(unsigned ThreadNum);
void* ThreadStart(void *Parameters);
void  ExecuteThread(unsigned ThreadNo);
bool  ExecuteTransaction(stm_tx_t* TxDesc, ThreadInfo_t* CurrentThreadInfo, unsigned CurrentTxID);
unsigned ChooseTransaction(TxContainer_t* CurrentTxContainer, unsigned ThreadNo);






#endif
