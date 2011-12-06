#include "transactions.h"



void ExecuteTransaction (unsigned TransactionID, stm_tx_t * TxDescr, ThLocalVarCollection * ThLocals)
{

  Word ValueRead;
  sigjmp_buf *_e;

  (ThLocals->Statistics).CurrentRetryNum = (unsigned long) -1;
  switch (TransactionID)
  {

  case 0:
    TX_START;
    for (ThLocals->_i = 0; (ThLocals->_i <= 2); ThLocals->_i = (ThLocals->_i + 1))
    {
      TM_READ (x);
    }
    TX_COMMIT;
    break;

  default:
    printf ("ExecuteTransaction: UNKNOWN TransactionID requested. Terminating...\n");
    assert (0);

  }


}
