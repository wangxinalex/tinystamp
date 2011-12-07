#include "transactions.h"



void ExecuteTransaction (unsigned TransactionID, stm_tx_t * TxDescr, ThLocalVarCollection * ThLocals)
{

  Word ValueRead;
  sigjmp_buf *_e;
  unsigned Range;

  (ThLocals->Statistics).CurrentRetryNum = (unsigned long) -1;
  switch (TransactionID)
  {

  case 0:
    Range = 5 - 1 + 1;
    ThLocals->_R = 1 + ChooseFromUniformDist (Range, &(ThLocals->seed__R));
    TX_START;
    TM_WRITE (x, ThLocals->WriteValue);
    ThLocals->WriteValue++;
    for (ThLocals->_i = 0; (ThLocals->_i <= ThLocals->_R); ThLocals->_i = (ThLocals->_i + 1))
    {
      TM_READ (&(arr[ThLocals->_i]));
    }
    TM_WRITE (x, ThLocals->WriteValue);
    ThLocals->WriteValue++;
    TX_COMMIT;
    break;

  default:
    printf ("ExecuteTransaction: UNKNOWN TransactionID requested. Terminating...\n");
    assert (0);

  }


}