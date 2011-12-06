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
    TM_READ (x);
    TM_READ (y);
    TM_WRITE (x, ThLocals->WriteValue);
    ThLocals->WriteValue++;
    TM_WRITE (y, ThLocals->WriteValue);
    ThLocals->WriteValue++;
    TX_COMMIT;
    break;
  case 1:
    TX_START;
    TM_READ (x);
    ThLocals->_a = ValueRead;
    TM_READ (y);
    ThLocals->_b = ValueRead;
    TM_WRITE (x, (ThLocals->_a - 10));
    TM_WRITE (y, (ThLocals->_b - 10));
    TX_COMMIT;
    break;

  default:
    printf ("ExecuteTransaction: UNKNOWN TransactionID requested. Terminating...\n");
    assert (0);

  }


}
