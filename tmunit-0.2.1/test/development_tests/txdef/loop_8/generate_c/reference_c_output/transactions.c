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
    Range = ThLocals->_CONST - 0 + 1;
    ThLocals->_R = 0 + ChooseFromUniformDist (Range, &(ThLocals->seed__R));
    Range = (ThLocals->_CONST + 2) - ThLocals->_CONST + 1;
    ThLocals->_N = ThLocals->_CONST + ChooseFromUniformDist (Range, &(ThLocals->seed__N));
    TX_START;
    TM_WRITE (x, ThLocals->WriteValue);
    ThLocals->WriteValue++;
    for (ThLocals->_i = ThLocals->_R; (ThLocals->_i <= ThLocals->_N); ThLocals->_i = (ThLocals->_i + 1))
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
