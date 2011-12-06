#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <signal.h>
#include "barrier.h"
#include "initialization.h"
#include "cli.h"

// STM specific
#include <atomic_ops.h>
#include "tm_interface.h"

// Variables rquired for tm interfaces, can be moved to another file
#if defined ( TL2 )

__thread stm_tx_t *TxDesc = NULL;
AO_t tx_id_counter = 0;
__thread sigjmp_buf *envPtr;

#else // for example fpr tinySTM_new

__thread stm_tx_t *TxDesc = (stm_tx_t *) 0x1;

#endif


// Probably only needed by benchrun parameters. Can be moved to initialization.h
#include "simulation_parameters.h"




extern unsigned *ThreadSeed;
extern unsigned ThreadNum;
extern ThreadRunFunc ThreadRun[];

#include "shared_var_definitions.h"
#include "thread_local_variables.h"

#include "thread_local_variables.h"	// For stat_t structure definition
stat_t **Statistics;

// *INDENT-OFF*
void PrintStatistics()
{
    printf("\n\n ------------------ Statistics ------------------\n\n");
    
    long unsigned AggregateCommitNum =00,
	          AggregateAbortNum  = 0;
    double TxCommitRate ,
	   TxAbortRate  ;
    double execution_duration_s = 0;
    unsigned long GlobalMaxRetries = 0;

    unsigned ThreadNo;
    for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++)
    {
	
	struct timeval start_time = Statistics[ThreadNo] -> start_time ;
	struct timeval   end_time = Statistics[ThreadNo] -> end_time   ;
	
	
	long long duration = (end_time.tv_sec * 1000000 + end_time.tv_usec) - (start_time.tv_sec * 1000000 + start_time.tv_usec) ;
//	    long long duration = 987654 + 1000000*ThreadNo;
	long time_rest;
	long duration_s    = (long)(duration/1000000) ;  time_rest = (long)(duration%1000000);
	long duration_ms   = time_rest/1000 ;            time_rest = time_rest%1000;
	long duration_us   = time_rest ;
	long total_duration_ms = duration_s*1000 + duration_ms;
	double total_duration_s = duration_s + (double)((double)(duration_ms)/(double)(1000));




	
	printf("Th[%u]: Cmmt= %ld, Abrt= %ld Duration=%ld.%ld.%ldns, %ldms, %.3fs\n", ThreadNo, Statistics[ThreadNo]->CommitNum, Statistics[ThreadNo]->AbortNum,duration_s,duration_ms,duration_us,total_duration_ms,total_duration_s);
	double CommitRate = (double)(Statistics[ThreadNo]->CommitNum) / total_duration_s;
	double AbortRate  = (double)(Statistics[ThreadNo]->AbortNum) / total_duration_s;
	unsigned long ThreadMaxRetries = Statistics[ThreadNo]->MaxRetries;
	printf("Th[%u]: Cmmt/s= %.3lf, Abrt/s= %.3lf, MaxRetries= %u\n", ThreadNo, CommitRate, AbortRate, ThreadMaxRetries);
        if (execution_duration_s < total_duration_s)
	    execution_duration_s = total_duration_s;
	    
	if( GlobalMaxRetries< ThreadMaxRetries )
	 GlobalMaxRetries = ThreadMaxRetries;

	AggregateCommitNum = AggregateCommitNum + Statistics[ThreadNo]->CommitNum ;
	AggregateAbortNum  = AggregateAbortNum  + Statistics[ThreadNo]->AbortNum  ;
	
    }


    printf("Aggregate Statistics:\n\n");

    TxCommitRate = (double)((double)(AggregateCommitNum)/execution_duration_s)	;
    TxAbortRate  = (double)((double)(AggregateAbortNum)/execution_duration_s)	;


    printf("\tTotal Commit Num  = %lu\n"
	   "\tTotal Abort  Num  = %lu\n"
	   "\tExection Duration = %lf\n"
	   "\tGlobal Commit/s   = %lf\n"
	   "\tGlobal Abort/s    = %lf\n"
	   "\tGlobal MaxRetries = %u\n\n\n",AggregateCommitNum,AggregateAbortNum,execution_duration_s,TxCommitRate,TxAbortRate,GlobalMaxRetries);

}


void PrintDevelopperTestWarning()
{
    printf("\n*************************************************************\n"
	   "*************************************************************\n"
	   "*                        WARNING:                           *\n"
	   "*                                                           *\n"
	   "*                                                           *\n"
	   "*  THIS PROGRAM IS COMPILED TO RUN IN DEVELOPER TEST MODE.  *\n"
	   "*                                                           *\n"
	   "*  This mode has some missing/modified features. If you     *\n"
	   "*  did not mean to execute developping tests to verify/test *\n"
	   "*  TMunit, please type                                      *\n"
	   "*                                                           *\n"
	   "*      make clean                                           *\n"
	   "*      make STM=<name of desired STM>                       *\n"
	   "*                                                           *\n"
	   "* on the command line in order to compile for simulations   *\n" 
	   "* (and user defined unit tests).                            *\n"
	   "*                                                           *\n"
	   "*************************************************************\n"
	   "*************************************************************\n"	       
	);
}
// *INDENT-ON*

int InitializeSimulationParameters ()
{
  TransmitReadOnlyTxHint = 1;

  MainSeed = 1;
  RandomDebug = 0;

  WaitForTimeOut = 1;
  TimeOutValueSet = 1;
  DelayUnit = 1000000;
  TimeOut = 1000000;

  PrintStats = 1;
  EnableTrace = 0;
  JustGenerateTrace = 0;
  EnableTraceFromCommandLine = 0;

  SerialThreadExecution = 0;

  return 0;
}

// *INDENT-OFF*  
void PrintEffectiveSimulationParameters()
{
    // Printing the current values of the simulation parameters
    printf("\n-------------------------------------------------\n"
	   "     Simulation Parameters:\n"
	   "-------------------------------------------------\n"
	   "\n"
	   "JustGenerateTrace      : %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "SerialThreadExecution  : %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "WaitForTimeOut         : %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "TransmitReadOnlyTxHint : %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "EnableTrace            : %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "PrintStats             : %d  (0: FALSE, 1: TRUE; DEFAULT:1)\n"
	   "MainSeed               : %u  (0: seed from clock; DEFAULT: 1)\n"
	   "TimeOut                : %u  (in microseconds, valid only if WaitForTimeOut is 1)\n"
	   "\n"
	   "\n",						\
	   JustGenerateTrace,					\
	   SerialThreadExecution,				\
	   WaitForTimeOut,					\
	   TransmitReadOnlyTxHint,				\
	   EnableTrace,						\
	   PrintStats,						\
	   MainSeed,						\
	   TimeOut						\
	);

#ifndef ENABLE_TRACE_CODE
        if( EnableTrace == 1)
        {
          printf("\n*****************************************************\n"
		 "                    WARNING:\n"
	   	 "*****************************************************\n"
           	 "\n"
           	 " TRACING IS BY DEFAULT DISABLED IN GENERATED C CODE.\n"
		 " (THAT IS BECAUSE THE PERFORMANCE IS SERIOUSLY DEGRADED\n"
		 " IF TRACING IS ENABLED EVEN IF TRACE IS NOT PRINTED OUT).\n"
          	 "\n"
          	 "\n"
		 " If you would like to enable tracing capability please\n"
		 " recompile the generated code by adding the parameter\n"
		 " TRACE=ENABLE to the line where you execute 'make'\n"
		 " ('make' should be executed in the 'c_output' directory).\n"
		 " For example, do the following for recompilation: \n"
		 "\n"
	   	 "    make clean    \n"
	   	 "    make STM=<name of desired STM>  TRACE=ENABLE\n"
	   	 "\n"
	   	 "*****************************************************\n"
	   	 "\n"
	   	 "\n");
        }
#endif
	
}
// *INDENT-ON*  



void InitializeSharedVariables ()
{
// Allocating memory for shared variables and arrays.

  m_array_size = 8194;
  m = (Word *) malloc (m_array_size * sizeof (Word));

// Initializing shared variables and arrays.
  unsigned ElementNo;
  for (ElementNo = 0; ElementNo < m_array_size; ElementNo++)
    m[ElementNo] = 0;


#ifdef ENABLE_TRACE_CODE
  if (EnableTrace)
  {
    for (ElementNo = 0; ElementNo < m_array_size; ElementNo++)
      printf ("Address of m[%u] : %p\n", ElementNo, &(m[ElementNo]));

  }
#endif

  return;
}


void signal_catcher (int sig)
{
  printf (" CAUGHT SIGNAL %d\n", sig);
  AO_store_full (&TerminateRequestedBySignal, TRUE);
}



int main (int argc, char *argv[])
{
  // Initializations
  InitializeSimulationParameters ();
  ProcessCommandLineArguments (argc, argv);
  TerminateRequestedBySignal = FALSE;

  SetThreadNum ();
  InitializeSharedVariables ();

  InitializeThreadSeeds (ThreadNum);
  PrintEffectiveSimulationParameters ();


  // Prepare thread functions and parameters to pass them
  unsigned short ThreadNo;
  pthread_t Thrd[ThreadNum];
  thread_input_t th_input[ThreadNum];
  for (ThreadNo = 0; ThreadNo < ThreadNum; ThreadNo++)
  {
    th_input[ThreadNo].thread_ID = ThreadNo;
    th_input[ThreadNo].ThreadSeed = ThreadSeed[ThreadNo];
  }
  InitializeThreadRunFunctions ();



// *INDENT-OFF*  
    if (signal(SIGHUP, signal_catcher) == SIG_ERR ||
	signal(SIGINT, signal_catcher) == SIG_ERR ||
	signal(SIGTERM, signal_catcher) == SIG_ERR ) {
	perror("Signal setup problem occured.\n");
	exit(1);
    }
// *INDENT-ON*  


  if (SerialThreadExecution)
  {
#ifndef  NO_STM
    printf ("Initializing STM...\n");
#endif
    TM_INIT (0);

    unsigned ThreadNo;
    for (ThreadNo = 0; ThreadNo < ThreadNum; ThreadNo++)
    {
      ThreadRun[ThreadNo] ((void *) &(th_input[ThreadNo]));
    }

#ifndef  NO_STM
    printf ("Shutting STM engine down...\n");
#endif
    TM_EXIT (0);

#ifdef COMPILE_FOR_TEST
    PrintDevelopperTestWarning ();
#endif

  }
  else
  {


    if (PrintStats)
    {
      Statistics = (stat_t **) malloc (ThreadNum * sizeof (stat_t *));
    }
    else
      Statistics = NULL;


    printf ("Initializing STM...\n");
    TM_INIT (0);

    // Start threads (threads will execute their main functionality after all
    // threads are generated, this is provided by the barrier)
    barrier_init (&barrier, ThreadNum + 1);

    for (ThreadNo = 0; ThreadNo < ThreadNum; ThreadNo++)
    {
      pthread_create (&(Thrd[ThreadNo]), NULL, ThreadRun[ThreadNo], (void *) &(th_input[ThreadNo]));
    }

    barrier_cross (&barrier);


    if (WaitForTimeOut)
    {
      struct timespec time_out;
      struct timespec left_time_out;
      time_out.tv_sec = TimeOut / 1000000;
      time_out.tv_nsec = (long) ((TimeOut % 1000000) * 1000);

      printf ("TimeOut=%u, time_out= (%ld,%ld)\n", TimeOut, time_out.tv_sec, time_out.tv_nsec);



      while (nanosleep (&time_out, &left_time_out) == -1)
      {
	if (TerminateRequestedBySignal)
	  break;
	printf ("left_time_out= (%ld,%ld)\n", left_time_out.tv_sec, left_time_out.tv_nsec);

	time_out.tv_sec = left_time_out.tv_sec;
	time_out.tv_nsec = left_time_out.tv_nsec;
      }


// *INDENT-OFF*  
   AO_store_full(&TerminateRequestedBySignal, TRUE);
	printf("\n"
	       "--------------------------\n"
	       "EXECUTION TIMEOUT REACHED.\n"
	       "--------------------------\n");
// *INDENT-ON*  

    }



    for (ThreadNo = 0; ThreadNo < ThreadNum; ThreadNo++)
      pthread_join (Thrd[ThreadNo], NULL);

    printf ("Shutting STM engine down...\n");
    TM_EXIT (0);


    if (PrintStats)
    {
      PrintStatistics ();
      for (ThreadNo = 0; ThreadNo < ThreadNum; ThreadNo++)
	free (Statistics[ThreadNo]);
      free (Statistics);

    }

#ifdef COMPILE_FOR_TEST
    PrintDevelopperTestWarning ();
#endif


  }

  return 0;
}
