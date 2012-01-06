#include "simulation_parameters.h"
#include "barrier.h"
#include <sys/time.h>
#include <unistd.h>    // for usleep function
#include "tm_interface.h"
#include "initialization.h"
#include "shared_var_definitions.h"
#include "rng_interface.h"



#include "thread_local_variables.h"  // For stat_t structure definition
extern stat_t** Statistics;

#define PRINT_DELAY_BEFORE_TX(Delay)  if( EnableTrace )     \
                                      {                     \
  			                    printf("%s[%u]D(%u)-,\n", ThLocals.PrintOffset, ID, Delay); \
                                            fflush(NULL);   \
}                     


// Variables rquired for tm interfaces, can be moved to another file
#if defined ( TL2 )

    extern __thread stm_tx_t* TxDesc;
    extern AO_t tx_id_counter;
    extern __thread sigjmp_buf* envPtr; 

#else  // for example fpr tinySTM_new 

    extern __thread stm_tx_t* TxDesc;

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

void* RunThread_32(void *Parameters)
{
  thread_input_t* ThreadParameters= (thread_input_t*)Parameters;
  unsigned ID = ThreadParameters-> thread_ID;
  unsigned int CurrentThreadSeed = ThreadParameters->  ThreadSeed ; 

char* ThreadNames[]={"P_1","P_2","P_3","P_4","P_5","P_6","P_7","P_8","P_9","P_10","P_11","P_12","P_13","P_14","P_15","P_16","P_17","P_18","P_19","P_20","P_21","P_22","P_23","P_24","P_25","P_26","P_27","P_28","P_29","P_30","P_31","P_32","P_33","P_34","P_35","P_36","P_37","P_38","P_39","P_40","P_41","P_42","P_43","P_44","P_45","P_46","P_47","P_48"};
char* TransactionNames[]={"T_transfer","T_balance"};




 ThLocalVarCollection ThLocals;
 ThLocals.ThreadID = ID;
 ThLocals.TxDesc = NULL;
 ThLocals.Statistics.CommitNum=0;
 ThLocals.Statistics.AbortNum=0;
 ThLocals.Statistics.MaxRetries=0;
 ThLocals.ThreadName = ThreadNames[ID];
 ThLocals.TransactionNames = TransactionNames;

// Initializing random variable seeds
ThLocals.seed__SRC = (unsigned) RAND_R(&CurrentThreadSeed);
ThLocals.seed__DST = (unsigned) RAND_R(&CurrentThreadSeed);
if(RandomDebug)
{
printf("Generating Random variable seeds for Thread %u...\n",ID);
printf("Seed of _SRC: %u\n", ThLocals.seed__SRC);
printf("Seed of _DST: %u\n", ThLocals.seed__DST);
}

// Initializing thread local variables (other than random variables).
ThLocals._NB = 8192;
ThLocals._k = 0;


// Definition and initialization of thread local variables.
unsigned RepetitionNo[1];


   ThLocals.WriteValue = (unsigned) RAND_R (&CurrentThreadSeed);
   if(RandomDebug)
   {
       printf("Initial WriteValue is set to  %u for Thread %u...\n",ThLocals.WriteValue, ID); 
       fflush(NULL);
   } 

   ThLocals.PrintOffset = NULL;
   if(EnableTrace)
   {
     unsigned short CurrentOffsetSize = 2*32+1 ; 
     ThLocals.PrintOffset = (char*)malloc(CurrentOffsetSize*sizeof(char)); 

     unsigned short TabCounter= CurrentOffsetSize -1 ; 
     char* CurrentChar = ThLocals.PrintOffset; 
     while(TabCounter >0) 
     { 
     	*CurrentChar = '\t'; 
     	CurrentChar ++; 
     	TabCounter --; 
     } 
     CurrentChar = '\0'; 
   }


   TM_INIT_THREAD(ThLocals.TxDesc);
   printf("Starting thread %u...\n",ID);
   barrier_cross(&barrier);

   gettimeofday(&(ThLocals.Statistics.start_time), NULL); 

for(; ; )
{
ExecuteTransaction(0, ThLocals.TxDesc, &ThLocals);
if(TerminateRequestedBySignal)
   TERMINATE_THREAD;
}

   TERMINATE_THREAD;
   
}

#undef TERMINATE_THREAD    
