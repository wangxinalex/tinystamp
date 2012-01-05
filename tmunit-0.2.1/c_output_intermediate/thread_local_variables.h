#ifndef _____THREAD_LOCAL_VARIABLES_H_________
#define _____THREAD_LOCAL_VARIABLES_H_________

#include "tm_interface.h"
#include <sys/time.h>
typedef struct StatisticsStruct
{
   unsigned long CommitNum;
   unsigned long AbortNum;
   unsigned long CurrentRetryNum;
   unsigned long MaxRetries;
   struct timeval start_time;
   struct timeval end_time;
} stat_t;

typedef struct ThLocalVarCollectionStruct {
stm_tx_t* TxDesc;
stat_t   Statistics;
unsigned WriteValue;
char*    PrintOffset;
unsigned ThreadID;
char*    ThreadName;
char**   TransactionNames;
signed long _NB;
signed long _SRC;
unsigned seed__SRC;
signed long _DST;
unsigned seed__DST;
signed long _k;
} ThLocalVarCollection;

#endif
