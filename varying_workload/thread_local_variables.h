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
   void *locals;
} stat_t;

typedef struct ThLocalVarCollectionStruct {
stm_tx_t* TxDesc;
stat_t   Statistics;
unsigned WriteValue;
char*    PrintOffset;
unsigned ThreadID;
char*    ThreadName;
char**   TransactionNames;
signed long _wp;
signed long _t;
signed long _rep;
signed long _cond;
signed long _size;
signed long _RAND;
unsigned seed__RAND;
signed long k;
} ThLocalVarCollection;

#endif
