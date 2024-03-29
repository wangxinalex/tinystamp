#ifndef _____INITIALIZATION_H______
#define _____INITIALIZATION_H______

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tm_interface.h"
#include "rng_interface.h"	// For random number seed initializations
#include "simulation_parameters.h"	// For the definition MainSeed variable

typedef struct thread_input_struct
{
  unsigned short thread_ID;
  unsigned MaxTxNumToExecute;
  unsigned ThreadSeed;
  unsigned short useBarrier;
}
thread_input_t;


extern unsigned ThreadNum;
extern unsigned *ThreadSeed;

typedef void *(*ThreadRunFunc) (void *Parameters);

void SetThreadNum ();
void InitializeThreadSeeds (unsigned ThreadNum, unsigned maxThreadNum);
void InitializeThreadRunFunctions ();


void *RunThread_0 (void *Parameters);



#endif
