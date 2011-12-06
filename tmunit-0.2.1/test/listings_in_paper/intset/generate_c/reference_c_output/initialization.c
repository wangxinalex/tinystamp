#include "initialization.h"

unsigned ThreadNum;
unsigned *ThreadSeed;

ThreadRunFunc ThreadRun[2] = { NULL };


void SetThreadNum ()
{
  ThreadNum = 2;
}


void InitializeThreadSeeds (unsigned ThreadNum)
{
  assert (ThreadNum != 0);
  ThreadSeed = (unsigned *) malloc (ThreadNum * sizeof (unsigned));
  if (MainSeed == 0)
  {
    printf ("MainSeed is ZERO.\n");
    SRAND ((int) time (0));
  }
  else
    SRAND (MainSeed);


  unsigned ThreadNo;
  for (ThreadNo = 0; ThreadNo < ThreadNum; ThreadNo++)
    ThreadSeed[ThreadNo] = RAND ();

  printf ("MainSeed=%u\n", MainSeed);
  printf ("ListOfThreadSeeds={");
  for (ThreadNo = 0; ThreadNo < ThreadNum; ThreadNo++)
  {
    printf ("%u", ThreadSeed[ThreadNo]);
    if (ThreadNo < ThreadNum - 1)
      printf (",");
    else
      printf ("}\n");
  }


}



void InitializeThreadRunFunctions ()
{
  ThreadRun[0] = RunThread_0;
  ThreadRun[1] = RunThread_1;
}
