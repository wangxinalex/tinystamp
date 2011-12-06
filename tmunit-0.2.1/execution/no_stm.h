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


#define TM_INIT(TxDesc)                   
#define TM_EXIT(TxDesc)                   
#define TM_INIT_THREAD(TxDesc)            
#define TM_EXIT_THREAD(TxDesc)            

#define TM_START(TxDesc,Env,ReadOnlyTx)   
#define STM_GET_ENV(TxDesc)               
#define START_TX(TxDesc, ReadOnlyTx)      

#define COMMIT_TX(TxDesc)                 
#define TM_LOAD(TxDesc, AccessedAddress)                   *AccessedAddress 
#define TM_STORE(TxDesc, AccessedAddress ,ValueToStore)    *AccessedAddress = ValueToStore

#define TM_ABORT(tx)                      


// Dummy redefinition for stm_tx_t, just to resolve compilation issues
typedef int stm_tx_t;
