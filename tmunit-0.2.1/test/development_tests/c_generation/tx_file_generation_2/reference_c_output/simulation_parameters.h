#ifndef  __________________GLOBAL_H____________
#define  __________________GLOBAL_H____________


// #include <assert.h>
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>




#ifdef __cplusplus
extern "C" {
#endif



#ifndef __cplusplus
typedef enum {FALSE,TRUE} bool;
#else
#define TRUE true    
#define FALSE false    
#endif


extern bool TransmitReadOnlyTxHint; 

extern unsigned MainSeed;
extern bool RandomDebug;

extern bool WaitForTimeOut;
extern bool TimeOutValueSet;
extern unsigned DelayUnit;
extern unsigned TimeOut;


extern bool PrintStats;
extern bool EnableTrace;
extern bool JustGenerateTrace;
extern bool EnableTraceFromCommandLine;

extern bool SerialThreadExecution;

extern unsigned long TerminateRequestedBySignal;



#ifdef __cplusplus
}
#endif


#endif
