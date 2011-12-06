#include "transactions.h"



void ExecuteTransaction (unsigned TransactionID, stm_tx_t * TxDescr, ThLocalVarCollection * ThLocals)
{

  Word ValueRead;
  sigjmp_buf *_e;
  int _ro;
  unsigned Range;

  (ThLocals->Statistics).CurrentRetryNum = (unsigned long) -1;
  switch (TransactionID)
  {

  case 0:
    Range = ThLocals->_SIZE - 1 + 1;
    ThLocals->_NB = 1 + ChooseFromUniformDist (Range, &(ThLocals->seed__NB));
    TX_START_RO;
    for (ThLocals->_k = 0; (ThLocals->_k <= (ThLocals->_NB - 1)); ThLocals->_k = (ThLocals->_k + 1))
    {
      TM_READ (&(m[(2 * ThLocals->_k)]));
      TM_READ (&(m[((2 * ThLocals->_k) + 1)]));
    }
    TM_READ (&(m[(2 * ThLocals->_NB)]));
    TX_COMMIT;
    break;
  case 1:
    Range = ThLocals->_SIZE - 1 + 1;
    ThLocals->_NB = 1 + ChooseFromUniformDist (Range, &(ThLocals->seed__NB));
    TX_START;
    if (ThLocals->_f == 0)
    {
      for (ThLocals->_k = 0; (ThLocals->_k <= (ThLocals->_NB - 1)); ThLocals->_k = (ThLocals->_k + 1))
      {
	TM_READ (&(m[(2 * ThLocals->_k)]));
	TM_READ (&(m[((2 * ThLocals->_k) + 1)]));
      }
      TM_READ (&(m[(2 * ThLocals->_NB)]));
      TM_WRITE (&(m[((2 * ThLocals->_NB) - 1)]), ThLocals->WriteValue);
      ThLocals->WriteValue++;
      ThLocals->_f = 1;
      ThLocals->_v = ThLocals->_NB;
    }
    else
    {
      for (ThLocals->_k = 0; (ThLocals->_k <= (ThLocals->_v - 1)); ThLocals->_k = (ThLocals->_k + 1))
      {
	TM_READ (&(m[(2 * ThLocals->_k)]));
	TM_READ (&(m[((2 * ThLocals->_k) + 1)]));
      }
      TM_READ (&(m[(2 * ThLocals->_v)]));
      TM_READ (&(m[((2 * ThLocals->_v) + 1)]));
      TM_WRITE (&(m[((2 * ThLocals->_v) - 1)]), ThLocals->WriteValue);
      ThLocals->WriteValue++;
      TM_WRITE (&(m[(2 * ThLocals->_v)]), ThLocals->WriteValue);
      ThLocals->WriteValue++;
      TM_WRITE (&(m[((2 * ThLocals->_v) + 1)]), ThLocals->WriteValue);
      ThLocals->WriteValue++;
      ThLocals->_f = 0;
    }
    TX_COMMIT;
    break;

  default:
    printf ("ExecuteTransaction: UNKNOWN TransactionID requested. Terminating...\n");
    assert (0);

  }


}
