#include "transactions.h"
#include <math.h>

extern unsigned maxThreadNum;
extern unsigned ThreadNum;
extern volatile pthread_t* Thrd;
extern volatile ThreadRunFunc ThreadRun[];
extern volatile thread_input_t* th_input;

__thread long ww;

int i_got_killed(unsigned id) {
 	long myThreadId=id;
    if(global_kill[myThreadId/64]&(((long)1)<<(myThreadId%64)))
        return 1;
	return 0;
}

void initThreadControlVariables() {
    int memAllocErrorPosix;
    assert(sizeof(long)==8);
    memAllocErrorPosix=posix_memalign((void**)&global_iFinished, 64, 8*(maxThreadNum/64+1));  // from http://pubs.opengroup.org/onlinepubs/000095399/functions/posix_memalign.html
	memAllocErrorPosix=posix_memalign((void**)&ready2, 64, 8*(maxThreadNum/64+1));  // from http://pubs.opengroup.org/onlinepubs/000095399/functions/posix_memalign.html
    assert(global_iFinished);
	assert(ready2);
    assert(!memAllocErrorPosix);
    memAllocErrorPosix=posix_memalign((void**)&global_kill, 64, 8*(maxThreadNum/64+1));  // from http://pubs.opengroup.org/onlinepubs/000095399/functions/posix_memalign.html
    assert(!memAllocErrorPosix);
    long i;
    for (i=maxThreadNum/64+1;--i;) {
        global_iFinished[i]=0xffffffffffffffff;
		ready2[i]=0xffffffffffffffff;
        global_kill[i]=(long)0;
    }
    global_kill[0]=(long)0;
    global_iFinished[0]=0xfffffffffffffffe;
	ready2[0]=0xffffffffffffffff;
}

void freeThreadControlVariables() {
    free((void*) global_iFinished);
    free((void*) global_kill);
	free((void*) ready2);
}

void flagThreadToBeKilled(long threadNr) {
	global_kill[threadNr/64]=global_kill[threadNr/64]|(((long)1)<<(threadNr%64));
}

void waitForThreadAndRestore(long threadNr) {
    while(global_iFinished[threadNr/64]&(((long)1)<<(threadNr%64))) {}
    global_kill[threadNr/64]=global_kill[threadNr/64]^(((long)1)<<(threadNr%64));
}

 // kills thread with the number threadNr
void killThreadNr(long threadNr) {
    assert(threadNr<global_maxNumClient);
    global_kill[threadNr/64]=global_kill[threadNr/64]|(((long)1)<<(threadNr%64));
    while(global_iFinished[threadNr/64]&(((long)1)<<(threadNr%64))) {}; //printf("\ni am looping inside killThreadNr_whileLoop %X, waiting for nr. %ld",global_iFinished[0], threadNr);  }
    global_kill[threadNr/64]=global_kill[threadNr/64]^(((long)1)<<(threadNr%64));
//    THREAD_JOIN(global_threads[threadNr]); // it's strange, but with join it won't work
	--ThreadNum;
}

int killSomeThreadsInTransactions(int level) {
	int i;
	int sum=0;
	for(i=0; i<level; ++i) {
		if(ThreadNum > 1) {
			global_kill[(ThreadNum-1)/64]=global_kill[(ThreadNum-1)/64]|(((long)1)<<(long)((long)((long)ThreadNum-(long)1)%(long)64));
			--sum;
//			printf("ThreadNum-1=%d\t",ThreadNum-1);
			--ThreadNum;
		}
	}
//	printf("\n");
	for (i=0; i>sum; --i) {
		//printf("(((ThreadNum-1)-sum)+i)=%d\t",(((ThreadNum-1)-sum)+i)); fflush(stdout);
		while(global_iFinished[(((ThreadNum-1)-sum)+i)/64]&(((long)1)<<(long)((long)(((ThreadNum-1)-sum)+i)%(long)64))) {};
		global_kill[(((ThreadNum-1)-sum)+i)/64]=global_kill[(((ThreadNum-1)-sum)+i)/64]^(((long)1)<<(long)((long)(((ThreadNum-1)-sum)+i)%(long)64));
	}
//	printf("\n");
	return sum;
}

// checks all threads if they are still running
int every_thread_finished() {
    long i;
    for(i=(ThreadNum)/64; i-->0;) {
        if((long) global_iFinished[i])
            return 0;
    }
    for(i=(ThreadNum)%64; i--;) {
        if(((long) global_iFinished[(ThreadNum-1)/64]>>i)&((long)1))
            return 0;
    }
    return 1;
}

void flagThreadAsRunning(unsigned threadID) {
	__sync_or_and_fetch(&(global_iFinished[threadID/64]),(((long)1)<<(threadID%64))); // from http://gcc.gnu.org/onlinedocs/gcc/Atomic-Builtins.html
}

int startSomeThreadsInTransactionsTemplate(int level) {
    int i;
    int sum=0;
    for(i=0; i<level; ++i) {
        if(ThreadNum<maxThreadNum) {
			flagThreadAsRunning(ThreadNum);
            pthread_create(&(Thrd[ThreadNum]),NULL,ThreadRun[0],(void *)&(th_input[ThreadNum]));
            ++ThreadNum;
            ++sum;
        }
    }
	for(i=0; i<sum; ++i) {
		while(ready2[(((ThreadNum)-sum)+i)/64]&(((long)1)<<(long)((long)(((ThreadNum)-sum)+i)%(long)64))) {};
	    __sync_or_and_fetch(&(ready2[(((ThreadNum)-sum)+i)/64]),(((long)1)<<((((ThreadNum)-sum)+i)%64)));
	}
	return sum;
}

int startSomeThreads3inTransactions(int level) {
    int i;
    int sum=0;
    for(i=0; i<level; ++i) {
        if(ThreadNum<maxThreadNum) {
			sstih();
            ++sum;
		}
	}
	for(i=0; i<sum; ++i) {
		while(ready2[(((ThreadNum)-sum)+i)/64]&(((long)1)<<(long)((long)(((ThreadNum)-sum)+i)%(long)64))) {};
		__sync_or_and_fetch(&(ready2[(((ThreadNum)-sum)+i)/64]),(((long)1)<<((((ThreadNum)-sum)+i)%64)));
	}
	return sum;
}


void ExecuteTransaction(unsigned TransactionID, stm_tx_t* TxDescr, ThLocalVarCollection* ThLocals) {
    Word ValueRead;
    sigjmp_buf *_e;
//	stm_tx_attr_t _a;

unsigned Range;

    (ThLocals->Statistics).CurrentRetryNum = (unsigned long) -1;
    switch ( TransactionID ) {

case 0:
TX_START;
TM_READ(W);
ThLocals->_t = ValueRead;
ww=ThLocals->_t;
if(ThLocals->_t > ThLocals->_wp)
{
ThLocals->_rep = ThLocals->_wp;
ThLocals->_t = (ThLocals->_t - ThLocals->_wp);
ThLocals->_cond = 1;
TM_WRITE(W,ThLocals->_t);
}
else
{
ThLocals->_rep = ThLocals->_t;
ThLocals->_t = 0;
ThLocals->_cond = 0;
TM_WRITE(W,ThLocals->_t);
}
TX_COMMIT;
break;
case 1:
//TX_START;
//TM_READ(W);
//int u=ValueRead;
//TX_COMMIT;

//Range = ThLocals->_size;
// Range = 800;
// Range = (double) ww * (double) ww / ((double)100000.0 * (double) 100000.0);
//  Range = (double) 1.0 / (double) ((80000000.0-(double)ww)/10.0+20) * (double) 100000000.0;
//Range = 8;
Range = (double)(80000002-ww)/(double)8000;
 ThLocals->_RAND = 1 + ChooseFromUniformDist( Range, &(ThLocals->seed__RAND) );
 long rand2 = 1+ChooseFromUniformDist( Range, &(ThLocals->seed__RAND) );
// if(ThLocals->_RAND==ranad2)
// 	printf("bae");
 TX_START;
//ThLocals->_size = 1;
for( ThLocals->k = 1; (ThLocals->k <= (double)1000000000.0/(double)((ww+2))); ThLocals->k += 1) {
	TM_READ(&(a[ThLocals->_RAND+ThLocals->k]));
	ThLocals->_t = ValueRead;
}
TM_WRITE(&(a[rand2]),1);
for (ThLocals->k = 1; (ThLocals->k <= (double)10000000.0/(double)((ww+2))); ThLocals->k +=1 ){
	TM_WRITE(&(a[1+ChooseFromUniformDist( Range, &(ThLocals->seed__RAND) )]),1);
}
//ThLocals->_size = (ThLocals->_size + 1);



//TM_WRITE(&(a[ThLocals->_RAND]),ThLocals->WriteValue);
//ThLocals->WriteValue++;
TX_COMMIT;

/* original code
Range = ThLocals->_size - 1 + 1;
 ThLocals->_RAND = 1 + ChooseFromUniformDist( Range, &(ThLocals->seed__RAND) );
  TX_START;
  ThLocals->_size = 1;
  for( ThLocals->k = 1; (ThLocals->k <= ThLocals->_size); ThLocals->k = (ThLocals->k + 1) )
  {
  TM_READ(&(a[ThLocals->k]));
  ThLocals->_t = ValueRead;
  if(ThLocals->_t == 0)
  {
  TM_WRITE(&(a[ThLocals->k]),1);
  }
  else{
  ThLocals->_size = (ThLocals->_size + 1);
  }
  }

  TM_WRITE(&(a[ThLocals->_RAND]),ThLocals->WriteValue);
  ThLocals->WriteValue++;
  TX_COMMIT;
 */
break;

		default :
	          printf("ExecuteTransaction: UNKNOWN TransactionID requested. Terminating...\n");
	          assert(0);

    }
}
