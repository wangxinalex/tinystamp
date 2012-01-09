#include "transactions.h"

extern unsigned maxThreadNum;
extern unsigned ThreadNum;

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
    assert(global_iFinished);
    assert(!memAllocErrorPosix);
    memAllocErrorPosix=posix_memalign((void**)&global_kill, 64, 8*(maxThreadNum/64+1));  // from http://pubs.opengroup.org/onlinepubs/000095399/functions/posix_memalign.html
    assert(!memAllocErrorPosix);
    long i;
    for (i=maxThreadNum/64+1;--i;) {
        global_iFinished[i]=0xffffffffffffffff;
        global_kill[i]=(long)0;
    }
    global_kill[0]=(long)0;
    global_iFinished[0]=0xfffffffffffffffe;
}

void freeThreadControlVariables() {
    free((void*) global_iFinished);
    free((void*) global_kill);
}

void waitForThreadAndRestore(long threadNr) {
    while(global_iFinished[threadNr/64]&(((long)1)<<(threadNr%64))) {}
    global_kill[threadNr/64]=global_kill[threadNr/64]^(((long)1)<<(threadNr%64));
}

 // kills thread with the number threadNr
void killThreadNr(long threadNr) {
    assert(threadNr<global_maxNumClient);
    global_kill[threadNr/64]=global_kill[threadNr/64]|(((long)1)<<(threadNr%64));
    while(global_iFinished[threadNr/64]&(((long)1)<<(threadNr%64))) {}//{printf("\ni am looping inside killThreadNr_whileLoop");}
    global_kill[threadNr/64]=global_kill[threadNr/64]^(((long)1)<<(threadNr%64));
//    THREAD_JOIN(global_threads[threadNr]); // it's strange, but with join it won't work
	--ThreadNum;
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

void ExecuteTransaction(unsigned TransactionID, stm_tx_t* TxDescr, ThLocalVarCollection* ThLocals) {
    Word ValueRead;
    sigjmp_buf *_e;
//	stm_tx_attr_t _a;

int _ro;
unsigned Range;

    (ThLocals->Statistics).CurrentRetryNum = (unsigned long) -1;
    switch ( TransactionID ) {

case 0:
Range = ThLocals->_NB - 1 + 1;
 ThLocals->_SRC = 1 + ChooseFromUniformDist( Range, &(ThLocals->seed__SRC) );
 Range = ThLocals->_NB - 1 + 1;
 ThLocals->_DST = 1 + ChooseFromUniformDist( Range, &(ThLocals->seed__DST) );
 TX_START;
TM_READ(&(a[ThLocals->_SRC]));
TM_READ(&(a[ThLocals->_DST]));
TM_WRITE(&(a[ThLocals->_SRC]),ThLocals->WriteValue);
ThLocals->WriteValue++;
TM_WRITE(&(a[ThLocals->_DST]),ThLocals->WriteValue);
ThLocals->WriteValue++;
TX_COMMIT;
break;
case 1:
TX_START_RO;
for( ThLocals->_k = 1; (ThLocals->_k <= ThLocals->_NB); ThLocals->_k = (ThLocals->_k + 1) )
{
TM_READ(&(a[ThLocals->_k]));
}
TX_COMMIT;
break;

		default :
	          printf("ExecuteTransaction: UNKNOWN TransactionID requested. Terminating...\n");
	          assert(0);

    }
}
