#include "initialization.h"

// If enabled, it will undo the key changes for dynamic thread management.
// Mainly the functionality which assigns work to each thread.
// #define AUTOREPLACE		1

unsigned ThreadNum;
unsigned maxThreadNum;
unsigned* ThreadSeed;

#ifdef	AUTOREPLACE
	ThreadRunFunc ThreadRun[8] = {NULL};
#else
	ThreadRunFunc ThreadRun[1] = {NULL};
	//ThreadRunFunc *ThreadRun=malloc(MainMax*sizeof(ThreadRunFunc));
#endif

void SetThreadNum() {
    ThreadNum = 8;
}

void InitializeThreadSeeds(unsigned ThreadNum, unsigned maxThreadNum) {
    assert (ThreadNum != 0);
    assert (maxThreadNum != 0);
    ThreadSeed = (unsigned *)malloc(maxThreadNum*sizeof(unsigned));
    if (MainSeed == 0) {
		printf("MainSeed is ZERO.\n");
		SRAND((int)time(0));
    }
    else
      SRAND(MainSeed);

    if (MainMax == 0) {
		printf("MainMax is ZERO. I'll add 10 now.\n");
		MainMax=10;
    }

    unsigned ThreadNo;
    for(ThreadNo=0; ThreadNo<maxThreadNum; ThreadNo++)
		ThreadSeed[ThreadNo] = RAND();

    printf("MainSeed=%u\n",MainSeed);
    printf("ListOfThreadSeeds={");
    for(ThreadNo=0; ThreadNo < maxThreadNum; ThreadNo++) {
		printf("%u",ThreadSeed[ThreadNo]);
		if(ThreadNo < maxThreadNum -1)
			printf(",");
		else
			printf("}\n");
    }
}

void InitializeThreadRunFunctions() {
	#ifdef AUTOREPLACE
    ThreadRun[0] = RunThread_0 ;
    ThreadRun[1] = RunThread_1 ;
    ThreadRun[2] = RunThread_2 ;
    ThreadRun[3] = RunThread_3 ;
    ThreadRun[4] = RunThread_4 ;
    ThreadRun[5] = RunThread_5 ;
    ThreadRun[6] = RunThread_6 ;
    ThreadRun[7] = RunThread_7 ;
	#else
		//	int i=0;
		//	for(i=MainMax; i--;)
		//		ThreadRun[i] = RunThread_0;
		ThreadRun[0] = RunThread_0;
	#endif
}
