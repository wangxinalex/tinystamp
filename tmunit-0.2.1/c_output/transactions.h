#ifndef __________TRANSACTIONS_H__________
#define __________TRANSACTIONS_H__________

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tm_interface.h"
#include "initialization.h"
#include "shared_var_definitions.h"
#include "thread_local_variables.h"
#include "simulation_parameters.h"

int i_got_killed(unsigned id);
unsigned ChooseFromUniformDist(unsigned CandidateNum, unsigned* Seed);
void ExecuteTransaction(unsigned TransactionID, stm_tx_t* TxDesc, ThLocalVarCollection* ThLocals);
volatile long*    global_kill;           // array of flabbits to kill threads

#if !(defined (RSTM) || defined (SWISS_TM))

//old#define TX_START 	 _e = STM_GET_ENV(TxDesc);   \
//	       		 sigsetjmp(*_e, 0);          \
//			 TM_START(TxDesc, _e, NULL); \
//			 PRINT_TX_START;             \
//                         (ThLocals->Statistics).CurrentRetryNum++
	#define TX_START	do {									\
							stm_tx_attr_t _a = {0, 0};			\
                            sigjmp_buf *_e = stm_start(&_a);	\
                            if (_e != NULL) sigsetjmp(*_e, 0);	\
						} while (0);							\
						PRINT_TX_START;							\
						(ThLocals->Statistics).CurrentRetryNum++
	#define TX_START_RO	do {									\
							stm_tx_attr_t _a = {0, 1};			\
                            sigjmp_buf *_e = stm_start(&_a);	\
                            if (_e != NULL) sigsetjmp(*_e, 0);	\
						} while (0);							\
						PRINT_TX_START;							\
						(ThLocals->Statistics).CurrentRetryNum++

#else
#define TX_START 	 TM_START(TxDesc, _e, NULL); \
			 PRINT_TX_START;             \
                         (ThLocals->Statistics).CurrentRetryNum++

#define TX_START_RO      _ro = 1;                    \
			 TM_START(TxDesc, _e, &_ro); \
                         PRINT_TX_START; 	     \
                         (ThLocals->Statistics).CurrentRetryNum++
#endif



#define TX_COMMIT   	 PRINT_PRE_TX_COMMIT;        \
                         COMMIT_TX(TxDesc);	     \
                         PRINT_POST_TX_COMMIT;	     \
                         (ThLocals -> Statistics).CommitNum++;    \
                         (ThLocals -> Statistics).AbortNum += (ThLocals->Statistics).CurrentRetryNum;      \
			 if( (ThLocals -> Statistics).MaxRetries < (ThLocals->Statistics).CurrentRetryNum ) \
			     (ThLocals -> Statistics).MaxRetries = (ThLocals->Statistics).CurrentRetryNum;

#define TM_READ(AddrParam)     PRINT_PRE_TM_READ(AddrParam);                      \
                               ValueRead = TM_LOAD(TxDesc, AddrParam);   \
			       PRINT_POST_TM_READ(AddrParam, ValueRead)

#define TM_WRITE(AddrParam,ValueToStore)     PRINT_PRE_TM_WRITE(AddrParam);                 \
                                             TM_STORE(TxDesc, AddrParam,ValueToStore );	    \
                                             PRINT_POST_TM_WRITE(AddrParam, ValueToStore)


#ifdef ENABLE_TRACE_CODE

  #define PRINT_TX_START  if( EnableTrace ) \
	printf("\n%s[%s:%s] S\n", ThLocals->PrintOffset, ThLocals->ThreadName, ThLocals->TransactionNames[TransactionID]); fflush(NULL);


  #define PRINT_PRE_TX_COMMIT  if( EnableTrace ) \
   			            printf("%s[%s:%s] Try C\n", ThLocals->PrintOffset, ThLocals->ThreadName, ThLocals->TransactionNames[TransactionID]); fflush(NULL);

  #define PRINT_POST_TX_COMMIT  if( EnableTrace ) \
   			            printf("%s[%s:%s] C\n\n", ThLocals->PrintOffset, ThLocals->ThreadName, ThLocals->TransactionNames[TransactionID]); fflush(NULL);

  #define PRINT_PRE_TM_READ(AddrExpr)  if( EnableTrace ) \
   			                printf("%s[%s:%s] R(%p)\n", ThLocals->PrintOffset, ThLocals->ThreadName, ThLocals->TransactionNames[TransactionID], AddrExpr ); fflush(NULL);

  #define PRINT_POST_TM_READ(AddrExpr, ValueRead)  if( EnableTrace ) \
                                        printf("%s[%s:%s] R(%p,%u)\n", ThLocals->PrintOffset, ThLocals->ThreadName, ThLocals->TransactionNames[TransactionID], AddrExpr, ValueRead ); fflush(NULL);


  #define PRINT_PRE_TM_WRITE(AddrExpr)  if( EnableTrace ) \
   			                printf("%s[%s:%s] W(%p)\n", ThLocals->PrintOffset, ThLocals->ThreadName, ThLocals->TransactionNames[TransactionID], AddrExpr ); fflush(NULL);

  #define PRINT_POST_TM_WRITE(AddrExpr, ValueToStore)  if( EnableTrace ) \
                                        printf("%s[%s:%s] W(%p,%u)\n", ThLocals->PrintOffset, ThLocals->ThreadName, ThLocals->TransactionNames[TransactionID], AddrExpr, ValueToStore ); fflush(NULL);

#else


  #define PRINT_TX_START
  #define PRINT_PRE_TX_COMMIT
  #define PRINT_POST_TX_COMMIT
  #define PRINT_PRE_TM_READ(AddrExpr)
  #define PRINT_POST_TM_READ(AddrExpr, ValueRead)
  #define PRINT_PRE_TM_WRITE(AddrExpr)
  #define PRINT_POST_TM_WRITE(AddrExpr, ValueToStore)

#endif



#endif
