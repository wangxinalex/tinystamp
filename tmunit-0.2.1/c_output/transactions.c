#include "transactions.h"

int i_got_killed(unsigned id) {
 	long myThreadId=id;
 //   if(global_kill[myThreadId/64]&(((long)1)<<(myThreadId%64)))
 //       return 1;
 //   return 0;
	return 0;
}

void ExecuteTransaction(unsigned TransactionID, stm_tx_t* TxDescr, ThLocalVarCollection* ThLocals) {
    Word ValueRead;
    sigjmp_buf *_e;
//	stm_tx_attr_t _a;

int _ro;
unsigned Range;

    (ThLocals->Statistics).CurrentRetryNum = (unsigned long) -1;
    switch ( TransactionID ) {

case 0:
Range = ThLocals->_NB - 1 + 1;
 ThLocals->_SRC = 1 + ChooseFromUniformDist( Range, &(ThLocals->seed__SRC) );
 Range = ThLocals->_NB - 1 + 1;
 ThLocals->_DST = 1 + ChooseFromUniformDist( Range, &(ThLocals->seed__DST) );
 TX_START;
TM_READ(&(a[ThLocals->_SRC]));
TM_READ(&(a[ThLocals->_DST]));
TM_WRITE(&(a[ThLocals->_SRC]),ThLocals->WriteValue);
ThLocals->WriteValue++;
TM_WRITE(&(a[ThLocals->_DST]),ThLocals->WriteValue);
ThLocals->WriteValue++;
TX_COMMIT;
break;
case 1:
TX_START_RO;
for( ThLocals->_k = 1; (ThLocals->_k <= ThLocals->_NB); ThLocals->_k = (ThLocals->_k + 1) )
{
TM_READ(&(a[ThLocals->_k]));
}
TX_COMMIT;
break;

		default :
	          printf("ExecuteTransaction: UNKNOWN TransactionID requested. Terminating...\n");
	          assert(0);

    }
}
