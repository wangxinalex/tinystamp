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

#ifndef _TL2_INTERFACE_H_
#define _TL2_INTERFACE_H_

#include "tl2.h"
#include "util.h"
#include "atomic_ops.h"  // For AO_t  and  AO_fetch_and_add1

typedef  Thread stm_tx_t;

#ifndef THREAD_DOT_C_INCLUDING
   extern __thread stm_tx_t* TxDesc; 
   extern AO_t tx_id_counter; 
   extern __thread sigjmp_buf* envPtr; 
#endif 

#define TM_INIT(TxDescr)                  TxOnce()
#define TM_EXIT(TxDescr)                  TxShutdown()

#define TM_INIT_THREAD(TxDescr)           TxDesc = TxNewThread();	\
                                          TxInitThread(TxDesc, AO_fetch_and_add1(&tx_id_counter));     \
                                          envPtr  = (sigjmp_buf*)malloc(sizeof(sigjmp_buf))            
                                          

#define TM_EXIT_THREAD(TxDescr)           TxFreeThread(TxDesc); \
                                          free(envPtr)

#define TM_START(TxDescr,Env,ReadOnlyTx)  TxStart(TxDesc, Env,ReadOnlyTx)

#define STM_GET_ENV(TxDescr)              envPtr 
#define START_TX(TxDescr, ReadOnlyTx)     sigjmp_buf *_env = envPtr ;       \
                                          sigsetjmp(*_env, 0);              \
                                          TxStart(TxDesc, _env, ReadOnlyTx)

#define COMMIT_TX(TxDescr)                TxCommit(TxDesc)
#define TM_LOAD(TxDescr, AccessedAddress) (uintptr_t)TxLoad(TxDesc, (intptr_t*) AccessedAddress)  
#define TM_STORE(TxDescr, AccessedAddress ,ValueToStore)    TxStore(TxDesc, (intptr_t*) AccessedAddress ,ValueToStore )
#define TM_ABORT(TxDescr)                  TxAbort(TxDesc)

#define STM_GET_PARAMETER(tx,name,val)    *val =  TxNbAborts(TxDesc)
                                          






#endif /* _TL2_INTERFACE_H_ */
