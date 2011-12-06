
#ifndef _STM_INTERFACE_H_
#define _STM_INTERFACE_H_

#include "stm.h"


/* ################################################################### *
 * TYPES
 * ################################################################### */

typedef wlpdstm::Transaction stm_tx_t;  // since stm_tx_t is not actually used, it was defined this way not to cause compilation errors.
#ifdef THREAD_DOT_C_INCLUDING
#error "Hello, there"
#endif 

#ifndef THREAD_DOT_C_INCLUDING
   extern __thread stm_tx_t* TxDesc; 
#endif 

/* ################################################################### *
 * FUNCTIONS
 * ################################################################### */


#define TM_INIT(TxDesc)                   wlpdstm::global_init()
#define TM_EXIT(TxDesc)                   wlpdstm::print_stats() 
#define TM_INIT_THREAD(TX_DESCR)          wlpdstm::thread_init(); \
                                          TxDesc = wlpdstm::CurrentTransaction::Get()
#define TM_EXIT_THREAD(TxDesc)            

#define TM_START(TxDesc,Env,ReadOnlyTx)   BEGIN_TRANSACTION
#define STM_GET_ENV(TxDesc)               // wlpdstm::CurrentTransaction::Get();


#define START_TX(TxDesc, ReadOnlyTx)      BEGIN_TRANSACTION
#define COMMIT_TX(TxDesc)                 END_TRANSACTION

#define TM_LOAD(TxDesc, AccessedAddress)                   wlpdstm::read_word(TxDesc, (void *)AccessedAddress)
#define TM_STORE(TxDesc, AccessedAddress ,ValueToStore)    wlpdstm::write_word(TxDesc, (void *)AccessedAddress, (void *)ValueToStore)


#define TM_ABORT(tx)                     wlpdstm::abort_tx(tx)





#endif
