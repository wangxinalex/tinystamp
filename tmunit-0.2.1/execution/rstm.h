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

#ifndef _STM_INTERFACE_H_
#define _STM_INTERFACE_H_


#define STM_LIB_LLT
#include "stm.hpp"
#include <setjmp.h>


#define TM_INIT(TxDesc)                   stm::init("", "", 1 ) 
#define TM_EXIT(TxDesc)                    
#define TM_INIT_THREAD(TxDesc)            stm::init("", "", 1 )
#define TM_EXIT_THREAD(TxDesc)            // stm::shutdown(ThreadNo)

#define START_TX(TxDesc, ReadOnlyTx)      BEGIN_TRANSACTION
#define COMMIT_TX(TxDesc)                 END_TRANSACTION 
#define TM_START(TxDesc,Env,ReadOnlyTx)   START_TX(TxDesc, ReadOnlyTx)
#define STM_GET_ENV(TxDesc)               


#define TM_LOAD(TxDesc, AccessedAddress)  llt::currentDescriptor.get() ->stm_read((unsigned long*)AccessedAddress) 
#define TM_STORE(TxDesc, AccessedAddress ,ValueToStore)  llt::currentDescriptor.get() ->stm_write((unsigned long*)AccessedAddress , (unsigned long)ValueToStore)

#define TM_ABORT(tx)                      llt::currentDescriptor.get() -> abort(true)




/* ################################################################### *
 * TYPES
 * ################################################################### */

typedef int stm_tx_t;  // since stm_tx_t is not actually used, it was defined this way not to cause compilation errors.

#endif
