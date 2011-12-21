#include "initialization.h"

unsigned ThreadNum;
unsigned *ThreadSeed;

ThreadRunFunc ThreadRun[1] = { NULL };


void SetThreadNum ()
{
  ThreadNum = 1;
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

  if (MainMax == 0)
  {
    printf ("MainMax is ZERO. I'll add 10 now.\n");
    MainMax = 10;
  }

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
}
