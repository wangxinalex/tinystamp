#include "simulation_parameters.h"
#include "barrier.h"
#include <sys/time.h>
#include <unistd.h>		// for usleep function
#include "tm_interface.h"
#include "initialization.h"
#include "shared_var_definitions.h"
#include "rng_interface.h"



#include "thread_local_variables.h"	// For stat_t structure definition
extern stat_t **Statistics;

#define PRINT_DELAY_BEFORE_TX(Delay)  if( EnableTrace )     \
                                      {                     \
  			                    printf("%s[%u]D(%u)-,\n", ThLocals.PrintOffset, ID, Delay); \
                                            fflush(NULL);   \
}


// Variables rquired for tm interfaces, can be moved to another file
#if defined ( TL2 )

extern __thread stm_tx_t *TxDesc;
extern AO_t tx_id_counter;
extern __thread sigjmp_buf *envPtr;

#else // for example fpr tinySTM_new

extern __thread stm_tx_t *TxDesc;

#endif



#define TERMINATE_THREAD    {           \
	                    gettimeofday(&(ThLocals.Statistics.end_time), NULL); \
	                    TM_EXIT_THREAD(ThLocals.TxDesc);                     \
			    if (PrintStats && !SerialThreadExecution)            \
		            {                                                    \
                                Statistics[ID] = malloc(sizeof(stat_t));         \
                                Statistics[ID]-> CommitNum  = ThLocals.Statistics.CommitNum ;   \
                                Statistics[ID]-> AbortNum   = ThLocals.Statistics.AbortNum  ;   \
                                Statistics[ID]-> MaxRetries = ThLocals.Statistics.MaxRetries ;  \
                                Statistics[ID]-> start_time = ThLocals.Statistics.start_time ;  \
                                Statistics[ID]-> end_time   = ThLocals.Statistics.end_time ;    \
                            }                                                    \
			    return NULL; \
                            }

void *RunThread_1 (void *Parameters)
{
  thread_input_t *ThreadParameters = (thread_input_t *) Parameters;
  unsigned ID = ThreadParameters->thread_ID;
  unsigned int CurrentThreadSeed = ThreadParameters->ThreadSeed;

  char *ThreadNames[] = { "Th1", "Th2" };
  char *TransactionNames[] = { "T1", "T2", "T3" };




  ThLocalVarCollection ThLocals;
  ThLocals.ThreadID = ID;
  ThLocals.TxDesc = NULL;
  ThLocals.Statistics.CommitNum = 0;
  ThLocals.Statistics.AbortNum = 0;
  ThLocals.Statistics.MaxRetries = 0;
  ThLocals.ThreadName = ThreadNames[ID];
  ThLocals.TransactionNames = TransactionNames;


// Initializing thread local variables (other than random variables).


// Definition and initialization of thread local variables.
  unsigned ChosenTransactionID;
  TxCandidateListContainer_t CandidateListContainer[1];
  CandidateListContainer[0].CandidateNum = 2;
  CandidateListContainer[0].Seed = (unsigned) RAND_R (&CurrentThreadSeed);
  CandidateListContainer[0].Distribution = UNIFORM;
  CandidateListContainer[0].TxCandidateList = (TxCandidate_t *) malloc (CandidateListContainer[0].CandidateNum * sizeof (TxCandidate_t));
  CandidateListContainer[0].TxCandidateList[0].TxID = 2;
  CandidateListContainer[0].TxCandidateList[0].Percentage = 50.000000000000;
  CandidateListContainer[0].TxCandidateList[1].TxID = 1;
  CandidateListContainer[0].TxCandidateList[1].Percentage = 50.000000000000;
  printf ("Thread[%u]: CandidateListContainer[0].Seed = %u \n", ID, CandidateListContainer[0].Seed);


  ThLocals.WriteValue = (unsigned) RAND_R (&CurrentThreadSeed);
  if (RandomDebug)
  {
    printf ("Initial WriteValue is set to  %u for Thread %u...\n", ThLocals.WriteValue, ID);
    fflush (NULL);
  }

  ThLocals.PrintOffset = NULL;
  if (EnableTrace)
  {
    unsigned short CurrentOffsetSize = 2 * 1 + 1;
    ThLocals.PrintOffset = (char *) malloc (CurrentOffsetSize * sizeof (char));

    unsigned short TabCounter = CurrentOffsetSize - 1;
    char *CurrentChar = ThLocals.PrintOffset;
    while (TabCounter > 0)
    {
      *CurrentChar = '\t';
      CurrentChar++;
      TabCounter--;
    }
    CurrentChar = '\0';
  }


  TM_INIT_THREAD (ThLocals.TxDesc);
  printf ("Starting thread %u...\n", ID);
  barrier_cross (&barrier);

  gettimeofday (&(ThLocals.Statistics.start_time), NULL);

  ChosenTransactionID = ChooseTransaction (&(CandidateListContainer[0]));
  ExecuteTransaction (ChosenTransactionID, ThLocals.TxDesc, &ThLocals);
  if (TerminateRequestedBySignal)
    TERMINATE_THREAD;

  TERMINATE_THREAD;

}

#undef TERMINATE_THREAD
