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

#include "stm.h"

#define TM_INIT(TxDesc)                   stm_init()
#define TM_EXIT(TxDesc)                   stm_exit()
#define TM_INIT_THREAD(TxDesc)            stm_init_thread()
#define TM_EXIT_THREAD(TxDesc)            stm_exit_thread()

//#define TM_START(TxDesc,Env,ReadOnlyTx)   stm_start(Env,ReadOnlyTx)
#define TM_START(TxDesc,Env,ReadOnlyTx)   START_TX(TxDesc, ReadOnlyTx)
#define STM_GET_ENV(TxDesc)               stm_get_env()
//#define START_TX(TxDesc, ReadOnlyTx)      _a = (stm_tx_attr_t) {0, ReadOnlyTx};
//											_e = stm_start(&_a);
//                                          if (_e != NULL) sigsetjmp(*_e, 0);
#define START_TX(TxDesc, ReadOnlyTx)		stm_tx_attr_t _a = (stm_tx_attr_t) {0, ReadOnlyTx};	\
											sigjmp_buf *_e = stm_start(&_a);					\
											if (_e != NULL) sigsetjmp(*_e, 0);

#define COMMIT_TX(TxDesc)                 stm_commit()
#define TM_LOAD(TxDesc, AccessedAddress)  stm_load(AccessedAddress)
#define TM_STORE(TxDesc, AccessedAddress ,ValueToStore)    stm_store(AccessedAddress ,ValueToStore)

#define TM_ABORT(tx)                      stm_abort(STM_ABORT_IMPLICIT)



/* ################################################################### *
 * TYPES
 * ################################################################### */

typedef int stm_tx_t;  // since stm_tx_t is not actually used, it was defined this way not to cause compilation errors.



#endif /* _STM_INTERFACE_H_ */
