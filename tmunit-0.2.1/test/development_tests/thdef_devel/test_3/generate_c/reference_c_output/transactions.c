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
    TX_COMMIT;
    break;
  case 1:
    TX_START;
    TM_WRITE (x, ThLocals->WriteValue);
    ThLocals->WriteValue++;
    TX_COMMIT;
    break;
  case 2:
    TX_START;
    TM_READ (y);
    TX_COMMIT;
    break;

  default:
    printf ("ExecuteTransaction: UNKNOWN TransactionID requested. Terminating...\n");
    assert (0);

  }


}
