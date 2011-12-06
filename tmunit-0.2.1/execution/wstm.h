#ifndef _STM_INTERFACE_H_
#define _STM_INTERFACE_H_

#include "stm0.h"
typedef void*  stm_tx_t;  // since stm_tx_t is not actually used, it was defined this way not to cause compilation errors.

#ifndef THREAD_DOT_C_INCLUDING
   extern __thread stm_tx_t* TxDesc; 
#endif 


#define TM_INIT(TxDescr)                   STMInit()
#define TM_EXIT(TxDescr)                   STMDone() 
#define TM_INIT_THREAD(TxDescr)            TxDesc = (stm_tx_t*)malloc(sizeof(stm_tx_t)); \
                                           STMAddThread(TxDesc)

#define TM_EXIT_THREAD(TxDescr)            STMRemoveThread (TxDesc)

#define TM_START(TxDescr,Env,ReadOnlyTx)   STMStartTransaction (TxDesc)
#define STM_GET_ENV(TxDescr)               
#define START_TX(TxDescr, ReadOnlyTx)      do { \
                                           TM_START(TxDescr,NULL,ReadOnlyTx)  

#define COMMIT_TX(TxDescr)                 } \
                                           while( ! STMCommitTransaction (TxDesc) )

#define TM_LOAD(TxDescr, AccessedAddress)  STMReadValue (TxDesc, (addr_t) AccessedAddress)
#define TM_STORE(TxDescr, AccessedAddress ,ValueToStore)    STMWriteValue (TxDesc, (addr_t)AccessedAddress, (word_t)ValueToStore)

#define TM_ABORT(TxDescr)                  STMAbortTransaction (TxDesc)




#endif /* _STM_INTERFACE_H_ */
