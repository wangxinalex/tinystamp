/* =============================================================================
 *
 * thread.c
 *
 * =============================================================================
 *
 * Copyright (C) Stanford University, 2006.  All Rights Reserved.
 * Author: Chi Cao Minh
 *
 * =============================================================================
 *
 * For the license of bayes/sort.h and bayes/sort.c, please see the header
 * of the files.
 *
 * ------------------------------------------------------------------------
 *
 * For the license of kmeans, please see kmeans/LICENSE.kmeans
 *
 * ------------------------------------------------------------------------
 *
 * For the license of ssca2, please see ssca2/COPYRIGHT
 *
 * ------------------------------------------------------------------------
 *
 * For the license of lib/mt19937ar.c and lib/mt19937ar.h, please see the
 * header of the files.
 *
 * ------------------------------------------------------------------------
 *
 * For the license of lib/rbtree.h and lib/rbtree.c, please see
 * lib/LEGALNOTICE.rbtree and lib/LICENSE.rbtree
 *
 * ------------------------------------------------------------------------
 *
 * Unless otherwise noted, the following license applies to STAMP files:
 *
 * Copyright (c) 2007, Stanford University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of Stanford University nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY STANFORD UNIVERSITY ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL STANFORD UNIVERSITY BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * =============================================================================
 */


#include <assert.h>
#include <stdlib.h>
#include "thread.h"
#include "types.h"

#include "tm.h"

#include "../../tinySTM/src/atomic_ops/atomic_ops.h"
#define ATOMIC_OPS_joerg
#include "../../tinySTM/src/atomic.h"

#define CACHE_LINE_SIZE (64)

static THREAD_LOCAL_T    global_threadId;       // some strange pthread stuff
__thread long            global_myThreadID;
static long              global_numThread       = 1;  // only mainThread=1, working threads are additionally added here
static THREAD_BARRIER_T* global_barrierPtr      = NULL;
static long*             global_threadIds       = NULL;
static THREAD_ATTR_T     global_threadAttr;
static THREAD_T*         global_threads         = NULL;
static void            (*global_funcPtr)(void*) = NULL;
static void*             global_argPtr          = NULL;
static volatile bool_t   global_doShutdown      = FALSE;
static volatile long*    global_iFinished;      // array of flagbits where threads can say: IFinished
static volatile long*    global_kill;           // array of flabbits to kill threads
static long              global_maxNumClient;   // amount of clients that where initialized & amount of ram that was allocated = maximal number of threads to start. @ maximum there is therefore global_numThread==global_maxNumClients
static volatile long     global_workLeftToDo=0;  // name says everything
static long* global_amountOfCommitsDone;

static unsigned long ** global_abortsCounters=0;
static unsigned long * global_abortsValues=0;

static void threadWait (void* argPtr) {
    long threadId = *(long*)argPtr;
    THREAD_LOCAL_SET(global_threadId, (long)threadId);
    global_myThreadID=threadId;
    while (1) {
        THREAD_BARRIER(global_barrierPtr, threadId); /* wait for start parallel */
        if (global_doShutdown) {
            break;
        }
        global_funcPtr(global_argPtr);
        THREAD_BARRIER(global_barrierPtr, threadId); /* wait for end parallel */
        if (threadId == 0) {
            break;
        }
    }
}

static void threadWaitNoBarrier (void* argPtr) {
    long threadId = *(long*)argPtr;
    THREAD_LOCAL_SET(global_threadId, (long)threadId);
    TM_THREAD_ENTER();
    global_abortsCounters[threadId]=stm_get_stats_position("nb_aborts");
    global_myThreadID=threadId;
    global_funcPtr(global_argPtr);
    global_abortsCounters[threadId]=(unsigned long)0;
    TM_THREAD_EXIT();
}

static void threadWaitNoBarrierWorkPices(void* argPtr) {
    long threadId = *(long*)argPtr;
    THREAD_LOCAL_SET(global_threadId, (long)threadId);
    TM_THREAD_ENTER();
    global_myThreadID=threadId;
    global_abortsCounters[threadId]=(unsigned long*)stm_get_stats_position("nb_aborts");
    while(((long)ATOMIC_FETCH_DEC_FULL(&global_workLeftToDo))>0) {
        global_funcPtr(global_argPtr);
        if(global_kill[threadId/64]&(((long)1)<<(threadId%64)))
            break;
    }
    global_abortsCounters[threadId]=(unsigned long)0;
    TM_THREAD_EXIT();
    __sync_and_and_fetch(&(global_iFinished[threadId/64]),~(((long)1)<<(threadId%64))); // from http://gcc.gnu.org/onlinedocs/gcc/Atomic-Builtins.html
}

static void threadWaitNoBarrierInsideBench(void* argPtr) {
    long threadId = *(long*)argPtr;
    THREAD_LOCAL_SET(global_threadId, (long)threadId);
    global_myThreadID=threadId;
    global_funcPtr(global_argPtr);
    __sync_and_and_fetch(&(global_iFinished[threadId/64]),~(((long)1)<<(threadId%64)));
}

void binary_print_long_value(long l) {
    printf("\n");
    int i;
    for(i=64; i-->0;)
        printf("%ld",(l>>i)&((long)1));
    fflush(stdout);
}

 // kills thread with the number threadNr
void killThreadNr(long threadNr) {
    assert(threadNr<global_maxNumClient);
    global_kill[threadNr/64]=global_kill[threadNr/64]|(((long)1)<<(threadNr%64));
    while(global_iFinished[threadNr/64]&(((long)1)<<(threadNr%64))) {}//{printf("\ni am looping inside killThreadNr_whileLoop");}
    global_kill[threadNr/64]=global_kill[threadNr/64]^(((long)1)<<(threadNr%64));
//    THREAD_JOIN(global_threads[threadNr]); // it's strange, but with join it won't work
    --global_numThread;
}

// checks all threads if they are still running
int every_thread_finished() {
    long i;
    for(i=(global_numThread)/64; i-->0;) {
        if((long) global_iFinished[i])
            return 0;
    }
    for(i=(global_numThread)%64; i--;) {
        if(((long) global_iFinished[(global_numThread-1)/64]>>i)&((long)1))
            return 0;
    }
    return 1;
}

int i_got_killed() {
    long myThreadId=global_myThreadID;
    if(global_kill[myThreadId/64]&(((long)1)<<(myThreadId%64)))
        return 1;
    return 0;
}

void thread_startup (long numThread) {
    long i;
    global_numThread = numThread;
    global_doShutdown = FALSE;

    /* Set up barrier */
    assert(global_barrierPtr == NULL);
    global_barrierPtr = THREAD_BARRIER_ALLOC(numThread);
    assert(global_barrierPtr);
    THREAD_BARRIER_INIT(global_barrierPtr, numThread);

    /* Set up ids */
    THREAD_LOCAL_INIT(global_threadId);
    assert(global_threadIds == NULL);
    global_threadIds = (long*)malloc(numThread * sizeof(long));
    assert(global_threadIds);
    for (i = 0; i < numThread; i++) {
        global_threadIds[i] = i;
    }

    /* Set up thread list */
    assert(global_threads == NULL);
    global_threads = (THREAD_T*)malloc(numThread * sizeof(THREAD_T));
    assert(global_threads);

    /* Set up pool */
    THREAD_ATTR_INIT(global_threadAttr);
    for (i = 1; i < numThread; i++) {
        THREAD_CREATE(global_threads[i],
                      global_threadAttr,
                      &threadWait,
                      &global_threadIds[i]);
    }
    /*
     * Wait for primary thread to call thread_start
     */
}

void initial_thread_startup_noBarriers (long initialThreads, char useWorkPieces) { // true = yes, use work pieces, false: use other things. false=0, true!=0
    long i;
    global_numThread = initialThreads+1;
        assert(global_kill);

    void (*threadWaitMethodPtr)(void*) = NULL;
    if(useWorkPieces)
        threadWaitMethodPtr=&threadWaitNoBarrierWorkPices;
    else
        threadWaitMethodPtr=&threadWaitNoBarrierInsideBench;

    /* Set up pool */
    THREAD_ATTR_INIT(global_threadAttr);
    for(i=global_numThread; --i;) {
        assert(global_threadIds[i]);
        THREAD_CREATE(global_threads[i],
                      global_threadAttr,
                      threadWaitMethodPtr,
                      &global_threadIds[i]);
    }
}

void thread_startup_noBarriers(long numThread, char useWorkPieces) {
    global_numThread += numThread;
    long tooMuch=global_numThread-global_maxNumClient;
    if(tooMuch>0) {
        global_numThread-=tooMuch;
        numThread-=tooMuch;
    }
    assert(global_numThread<=global_maxNumClient);

    void (*threadWaitMethodPtr)(void*) = NULL;
    if(useWorkPieces)
        threadWaitMethodPtr=&threadWaitNoBarrierWorkPices;
    else
        threadWaitMethodPtr=&threadWaitNoBarrierInsideBench;

    long i;
    for (i = global_numThread-numThread; i < global_numThread; ++i) {
        __sync_or_and_fetch(&(global_iFinished[i/64]),(((long)1)<<(i%64))); // from http://gcc.gnu.org/onlinedocs/gcc/Atomic-Builtins.html
        THREAD_CREATE(global_threads[i],
                      global_threadAttr,
                      threadWaitMethodPtr,
                      &global_threadIds[i]);
    }
}

void thread_start (void (*funcPtr)(void*), void* argPtr) {
    global_funcPtr = funcPtr;
    global_argPtr = argPtr;
    long threadId = 0; /* primary */
    threadWait((void*)&threadId);
}

void thread_start_noBarriers() {
    long threadId = 0; /* primary */
    threadWaitNoBarrier((void*)&threadId);
}

void thread_prepare_start(void (*funcPtr) (void*), void* argPtr, long maxNumClient, long amountOfWorkPieces) {
    global_funcPtr = funcPtr;
    global_argPtr = argPtr;
    global_maxNumClient = maxNumClient;
    global_workLeftToDo=amountOfWorkPieces;

    int memAllocErrorPosix;
    assert(sizeof(long)==8);
    memAllocErrorPosix=posix_memalign((void**)&global_iFinished, 64, 8*(maxNumClient/64+1));  // from http://pubs.opengroup.org/onlinepubs/000095399/functions/posix_memalign.html
    assert(global_iFinished);
    assert(!memAllocErrorPosix);
    memAllocErrorPosix=posix_memalign((void**)&global_kill, 64, 8*(maxNumClient/64+1));  // from http://pubs.opengroup.org/onlinepubs/000095399/functions/posix_memalign.html
    assert(global_kill);
    assert(!memAllocErrorPosix);
    long i;
    for (i=maxNumClient/64+1;--i;) {
        global_iFinished[i]=0xffffffffffffffff;
        global_kill[i]=(long)0;
    }
    global_kill[0]=(long)0;
    global_iFinished[0]=0xfffffffffffffffe;

    int posixMemalignError=posix_memalign((void**)&global_amountOfCommitsDone, 64, CACHE_LINE_SIZE*global_maxNumClient);
    assert(!posixMemalignError);
    assert(global_amountOfCommitsDone);
    for (i=global_maxNumClient; i--;)
        global_amountOfCommitsDone[CACHE_LINE_SIZE/sizeof(long)*i]=0;

    // Set up ids
    THREAD_LOCAL_INIT(global_threadId);
    assert(global_threadIds == NULL);
    global_threadIds = (long*)malloc(global_maxNumClient * sizeof(long));
    assert(global_threadIds);
    for (i = 0; i < global_maxNumClient; i++) {
        global_threadIds[i] = i;
    }

    // Set up thread list
    assert(global_threads == NULL);
    global_threads = (THREAD_T*)malloc(global_maxNumClient * sizeof(THREAD_T));
    assert(global_threads);

    global_abortsCounters = (unsigned long **) malloc( global_maxNumClient * sizeof(unsigned long*));
    global_abortsValues = (unsigned long *) malloc( global_maxNumClient * sizeof(unsigned long));
    for(i=global_maxNumClient; i--;) {
        global_abortsCounters[i]=(unsigned long)0;
        global_abortsValues[i]=(unsigned long)0;
    }
}

void thread_shutdown () {
    /* Make secondary threads exit wait() */
    global_doShutdown = TRUE;
    THREAD_BARRIER(global_barrierPtr, 0);

    long numThread = global_numThread;

    long i;
    for (i = 1; i < numThread; i++) {
        THREAD_JOIN(global_threads[i]);
    }
    THREAD_BARRIER_FREE(global_barrierPtr);
    global_barrierPtr = NULL;
    free(global_threadIds);
    global_threadIds = NULL;
    free(global_threads);
    global_threads = NULL;
    global_numThread = 1;
    free((void*) global_iFinished);
    free((void*) global_kill);
    free((void*) global_amountOfCommitsDone);
    free(global_abortsCounters);
    free(global_abortsValues);
}

void thread_shutdown_noBarriers() {
    long numThread = global_numThread;
    long i;
    for (i = 1; i < numThread; i++)
        THREAD_JOIN(global_threads[i]);

    free(global_threadIds);
    global_threadIds = NULL;
    free(global_threads);
    global_threads = NULL;
    global_numThread = 1;
}

thread_barrier_t* thread_barrier_alloc (long numThread) {
    thread_barrier_t* barrierPtr;
    assert(numThread > 0);
    assert((numThread & (numThread - 1)) == 0); /* must be power of 2 */
    barrierPtr = (thread_barrier_t*)malloc(numThread * sizeof(thread_barrier_t));
    if (barrierPtr != NULL) {
        barrierPtr->numThread = numThread;
    }
    return barrierPtr;
}

void thread_barrier_free (thread_barrier_t* barrierPtr) {
    free(barrierPtr);
}

void thread_barrier_init (thread_barrier_t* barrierPtr){
    long i;
    long numThread = barrierPtr->numThread;

    for (i = 0; i < numThread; i++) {
        barrierPtr[i].count = 0;
        THREAD_MUTEX_INIT(barrierPtr[i].countLock);
        THREAD_COND_INIT(barrierPtr[i].proceedCond);
        THREAD_COND_INIT(barrierPtr[i].proceedAllCond);
    }
}

void thread_barrier (thread_barrier_t* barrierPtr, long threadId){
    long i = 2;
    long base = 0;
    long index;
    long numThread = barrierPtr->numThread;

    if (numThread < 2) {
        return;
    }

    do {
        index = base + threadId / i;
        if ((threadId % i) == 0) {
            THREAD_MUTEX_LOCK(barrierPtr[index].countLock);
            barrierPtr[index].count++;
            while (barrierPtr[index].count < 2) {
                THREAD_COND_WAIT(barrierPtr[index].proceedCond,
                                 barrierPtr[index].countLock);
            }
            THREAD_MUTEX_UNLOCK(barrierPtr[index].countLock);
        } else {
            THREAD_MUTEX_LOCK(barrierPtr[index].countLock);
            barrierPtr[index].count++;
            if (barrierPtr[index].count == 2) {
                THREAD_COND_SIGNAL(barrierPtr[index].proceedCond);
            }
            while (THREAD_COND_WAIT(barrierPtr[index].proceedAllCond,
                                    barrierPtr[index].countLock) != 0)
            {
                /* wait */
            }
            THREAD_MUTEX_UNLOCK(barrierPtr[index].countLock);
            break;
        }
        base = base + numThread / i;
        i *= 2;
    } while (i <= numThread);

    for (i /= 2; i > 1; i /= 2) {
        base = base - numThread / i;
        index = base + threadId / i;
        THREAD_MUTEX_LOCK(barrierPtr[index].countLock);
        barrierPtr[index].count = 0;
        THREAD_COND_SIGNAL(barrierPtr[index].proceedAllCond);
        THREAD_MUTEX_UNLOCK(barrierPtr[index].countLock);
    }
}

long thread_getId() {
    return (long)THREAD_LOCAL_GET(global_threadId);
}

void add_one_commit() { // depreciated, should not be used anymore
    assert(0); // because depreciated
    assert(global_amountOfCommitsDone);
    assert(CACHE_LINE_SIZE);
    ++global_amountOfCommitsDone[CACHE_LINE_SIZE/sizeof(long)*(global_myThreadID)];
}

long* getMyCommitCounter() {
//    return &(global_amountOfCommitsDone[CACHE_LINE_SIZE/sizeof(long)*(global_myThreadID)]);  // does exactly the same
    return global_amountOfCommitsDone+CACHE_LINE_SIZE/sizeof(long)*(global_myThreadID);
}

unsigned long** getGlobal_abortsCounters() {
    return global_abortsCounters;
}

//long getGlobalMaxNumClient() {
//	return global_maxNumClient;
//}

#define USE_ALGO_00 0

void ajust_amount_of_threads( void (*ptr2runMoreThreads)(long)) {
#ifdef USE_ALGO_00
    long sumOfAllCommitsEver;
	unsigned long abortsDiff;
#endif
#ifdef USE_ALGO_01
    long doneCounter=0;
    long sumOfAllCommitsEver;
#endif // USE_ALG0_01
#ifdef USE_ALGO_02
    long doneCounter=0;
#endif // USE_ALGO_02
#ifdef USE_ALGO_03
    long level=16;
    long sumOfAllCommitsEver;
#endif // USE_ALGO_03
#ifdef USE_ALGO_04
    long level=16;
    long sumOfAllCommitsEver;
    long amountOfCommitsChangePrediction=0;
#endif // USE_ALGO_04
#ifdef USE_ALGO_05
    long level=16;
    long sumOfAllCommitsEver;
    srand ( time(NULL) );
    int randomNumber=0;
    long lastNumThread=0;
#endif // USE_ALGO_05
#ifdef USE_ALGO_06
    long level=16;
    long sumOfAllCommitsEver;
    srand ( time(NULL) );
    int randomNumber=0;
    long lastNumThread=0;
    long abortsBeforeSleep;
    long abortsAfterSleep;
    long abortsDiff;
#endif // USE_ALGO_06
#ifdef USE_ALGO_07
    long level=16;
    long sumOfAllCommitsEver;
    srand ( time(NULL) );
    int randomNumber=0;
    long lastNumThread=0;
    unsigned long abortsDiff;
#endif // USE_ALGO_07
    long milisecondsOfSleep=250;
    int lastDone=0;
    int lastAction=0;
    long cdlsOld=0;
    long bestcdlsEver=1;
    long bestcdlsEverReachedAt=2;
    long commitsDuringLastSleep;
    long sumOfAllCommitsEverLastTime=getTotalAmountOfCommits();
#ifdef USE_ALGO_00
	increaseAmountOfThreads(global_maxNumClient, ptr2runMoreThreads);
#endif // USE_ALGO_00
    while (!every_thread_finished()) {
#ifdef USE_ALGO_00 // just for plotting graph purposes
		getAmountOfAborts2init();
        sumOfAllCommitsEverLastTime=getTotalAmountOfCommits();
        mySleep(milisecondsOfSleep);
        abortsDiff=getAmountOfAborts2();
        sumOfAllCommitsEver=getTotalAmountOfCommits();
        commitsDuringLastSleep=sumOfAllCommitsEver-sumOfAllCommitsEverLastTime;
        printf("running with %ld threads and got %ld commits and %ld aborts\n", global_numThread-1, commitsDuringLastSleep, abortsDiff);
#endif // USE_ALGO_00
#ifdef USE_ALGO_01
        sumOfAllCommitsEverLastTime=getTotalAmountOfCommits();
        mySleep(milisecondsOfSleep);
        sumOfAllCommitsEver=getTotalAmountOfCommits();
        commitsDuringLastSleep=sumOfAllCommitsEver-sumOfAllCommitsEverLastTime;
        double percentOfBest=((double)commitsDuringLastSleep)/((double)bestcdlsEver)*((double)100);
        if(commitsDuringLastSleep>cdlsOld && lastDone==1) { // if you increased last time and it got better, increase again
            if(doneCounter>5) {  // if you increased 6 times and it got better 6 times, increase 11 at the time. if not yet 6, just increase again
                int j;
                for(j=11; --j;)
                    increaseAmountOfThreadsByOne(ptr2runMoreThreads);
                doneCounter=2;
            }
            else {
                increaseAmountOfThreadsByOne(ptr2runMoreThreads);
                ++doneCounter;
            }
            lastDone=1;
            lastAction=1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone==1) { // if you increased last time and it got worse, decrease
            decreaseAmountOfThreadsByOne();
            lastDone=-1;
            lastAction=-1;
            doneCounter=0;
        }
        else if((commitsDuringLastSleep>cdlsOld) && lastDone==-1) { // if you decreased and got better, decrease one more time
            if(doneCounter<-5) {  // if you decreased 6 times and it got better 6 times, decrease by 10 threads
                int j;
                for(j=11; --j;)
                    decreaseAmountOfThreadsByOne();
                doneCounter=-2;
            }
            else {
                decreaseAmountOfThreadsByOne();
                --doneCounter;
            }
            lastDone=-1;
            lastAction=-1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone==-1) { // if you decreased and it got worse, increase again
            increaseAmountOfThreadsByOne(ptr2runMoreThreads);
            lastDone=1;
            lastAction=1;
            doneCounter=0;
        }
        else if(lastDone==0) {
            increaseAmountOfThreadsByOne(ptr2runMoreThreads);
            lastDone=1;
            lastAction=1;
            ++doneCounter;
        }
        else {
            lastDone=0;
            doneCounter=0;
        }
        printf("Was running with %ld threads and got %f / 100 commits, compared to best ever.\n",global_numThread-lastDone, percentOfBestEver);
        fflush(stdout);

        if(commitsDuringLastSleep>bestcdlsEver) {
            bestcdlsEver=commitsDuringLastSleep;
            bestcdlsEverReachedAt=global_numThread;
            printf("new bestcdlsEver record of %ld\n",commitsDuringLastSleep);
        }
        cdlsOld=commitsDuringLastSleep;

        if(commitsDuringLastSleep>14000) {
            milisecondsOfSleep/=2;
            bestcdlsEver/=2;
            cdlsOld/=2;
        }
        else if(commitsDuringLastSleep<11) {
            milisecondsOfSleep*=2;
            bestcdlsEver*=2;
            cdlsOld*=2;
        }
#endif // USE_ALGO_01
#ifdef USE_ALGO_02          // tried, what ever happens first, x-amount of commits or time running out, seems not to work well
        const long amountOfSleepPieces=100; // divide sleep time in .. amount of sleep pieces and check each time if condition two allready holds
        int i;
        long sum;
        commitsDuringLastSleep=0;
        sumOfAllCommitsEverLastTime=getTotalAmountOfCommits();
        for (i=amountOfSleepPieces+1; --i;) {
                    mySleep(milisecondsOfSleep/amountOfSleepPieces);
                    sum = getTotalAmountOfCommits();
                    if(sum - sumOfAllCommitsEverLastTime > 10000) {
                        commitsDuringLastSleep = (sum - sumOfAllCommitsEverLastTime)/((amountOfSleepPieces+1-i)*(milisecondsOfSleep/amountOfSleepPieces));
                        break;
                    }
        }
        if(!commitsDuringLastSleep)
            commitsDuringLastSleep=(getTotalAmountOfCommits() - sumOfAllCommitsEverLastTime)/((amountOfSleepPieces)*(milisecondsOfSleep/amountOfSleepPieces));

        double percentOfBestEver=((double)commitsDuringLastSleep)/((double)bestcdlsEver)*((double)100);
        if(commitsDuringLastSleep>cdlsOld && lastDone==1) { // if you increased last time and it got better, increase again
            if(doneCounter>6) {  // if you increased 6 times and it got better 6 times, increase 11 at the time. if not yet 6, just increase again
                int j;
                for(j=11; --j;)
                    increaseAmountOfThreadsByOne(ptr2runMoreThreads);
                doneCounter=0;
            }
            else {
                increaseAmountOfThreadsByOne(ptr2runMoreThreads);
                ++doneCounter;
            }
            lastDone=1;
            lastAction=1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone==1) { // if you increased last time and it got worse, decrease
            decreaseAmountOfThreadsByOne();
            lastDone=-1;
            lastAction=-1;
            doneCounter=0;
        }
        else if((commitsDuringLastSleep>cdlsOld) && lastDone==-1) { // if you decreased and got better, decrease one more time
            if(doneCounter<-6) {  // if you decreased 6 times and it got better 6 times, decrease by 10 threads
                int j;
                for(j=11; --j;)
                    decreaseAmountOfThreadsByOne();
                doneCounter=0;
            }
            else {
                decreaseAmountOfThreadsByOne();
                --doneCounter;
            }
            lastDone=-1;
            lastAction=-1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone==-1) { // if you decreased and it got worse, increase again
            increaseAmountOfThreadsByOne(ptr2runMoreThreads);
            lastDone=1;
            lastAction=1;
            doneCounter=0;
        }
        else if(lastDone==0) {
            increaseAmountOfThreadsByOne(ptr2runMoreThreads);
            lastDone=1;
            lastAction=1;
            ++doneCounter;
        }
        else {
            lastDone=0;
        }
        printf("Was running with %ld threads and got %f / 100 commits, compared to best ever.\n",global_numThread-lastDone, percentOfBestEver);
        fflush(stdout);

        if(commitsDuringLastSleep>bestcdlsEver) {
            bestcdlsEver=commitsDuringLastSleep;
            bestcdlsEverReachedAt=global_numThread;
            printf("new bestcdlsEver record of %ld\n",commitsDuringLastSleep);
        }
        cdlsOld=commitsDuringLastSleep;

        if(commitsDuringLastSleep>14000) {
            milisecondsOfSleep/=2;
            bestcdlsEver/=2;
            cdlsOld/=2;
        }
        else if(commitsDuringLastSleep<7) {
            milisecondsOfSleep*=2;
            bestcdlsEver*=2;
            cdlsOld*=2;
        }
#endif // USE_ALGO_02
#ifdef USE_ALGO_03              // features nice sleep-increase-decrease features and an upper limit of max length of sleep
        sumOfAllCommitsEverLastTime=getTotalAmountOfCommits();
        mySleep(milisecondsOfSleep);
        sumOfAllCommitsEver=getTotalAmountOfCommits();
        commitsDuringLastSleep=sumOfAllCommitsEver-sumOfAllCommitsEverLastTime;
        double percentOfBestEver=((double)commitsDuringLastSleep)/((double)bestcdlsEver)*((double)100);
        if(commitsDuringLastSleep>cdlsOld && lastDone>0) { // if you increased last time and it got better, increase again
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=level;
            lastAction=1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone>0) { // if you increased last time and it got worse, decrease
            decreaseAmountOfThreads(level);
            lastDone=-level;
            lastAction=-1;
            if((level-1))
                level/=2;
        }
        else if((commitsDuringLastSleep>cdlsOld) && lastDone<0) { // if you decreased and got better, decrease one more time
            decreaseAmountOfThreads(level);
            lastDone=-level;
            lastAction=-1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone<0) { // if you decreased and it got worse, increase again
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=level;
            lastAction=1;
            if((level-1))
                level/=2;
        }
        else if(lastDone==0) {
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=level;
            lastAction=1;
        }
        else {
            lastDone=0;
            lastAction=0;
        }
        printf("Was running with %ld threads and got %f / 100 commits, compared to best ever.\n",global_numThread-lastDone, percentOfBestEver);
        fflush(stdout);

        if(commitsDuringLastSleep>bestcdlsEver) {
            bestcdlsEver=commitsDuringLastSleep;
            bestcdlsEverReachedAt=global_numThread;
            printf("new bestcdlsEver record of %ld\n",commitsDuringLastSleep);
        }
        cdlsOld=commitsDuringLastSleep;

        if(commitsDuringLastSleep>220000) {
            milisecondsOfSleep/=2;
            bestcdlsEver/=2;
            cdlsOld/=2;
        }
        else if(commitsDuringLastSleep<22000 && milisecondsOfSleep<2000) {
            milisecondsOfSleep*=2;
            bestcdlsEver*=2;
            cdlsOld*=2;
        }
#endif // USE_ALGO_03
#ifdef USE_ALGO_04              // features amountOfCommitsChangePrediction
        sumOfAllCommitsEverLastTime=getTotalAmountOfCommits();
        mySleep(milisecondsOfSleep);
        sumOfAllCommitsEver=getTotalAmountOfCommits();
        commitsDuringLastSleep=sumOfAllCommitsEver-sumOfAllCommitsEverLastTime;
        if(lastAction==0) // first iteration
            amountOfCommitsChangePrediction=commitsDuringLastSleep;
        double percentOfBestEver=((double)commitsDuringLastSleep)/((double)bestcdlsEver)*((double)100);
        if(commitsDuringLastSleep-amountOfCommitsChangePrediction>cdlsOld && lastDone==1) { // if you increased last time and it got better, increase again
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=1;
            lastAction=1;
        }
        else if((commitsDuringLastSleep-amountOfCommitsChangePrediction<cdlsOld) && lastDone==1) { // if you increased last time and it got worse, decrease
            decreaseAmountOfThreads(level);
            lastDone=-1;
            lastAction=-1;
            if((level-1))
                level/=2;
        }
        else if((commitsDuringLastSleep-amountOfCommitsChangePrediction>cdlsOld) && lastDone==-1) { // if you decreased and got better, decrease one more time
            decreaseAmountOfThreads(level);
            lastDone=-1;
            lastAction=-1;
        }
        else if((commitsDuringLastSleep-amountOfCommitsChangePrediction<cdlsOld) && lastDone==-1) { // if you decreased and it got worse, increase again
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=1;
            lastAction=1;
            if((level-1))
                level/=2;
        }
        else if(lastDone==0) {
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=1;
            lastAction=1;
        }
        else {
            lastDone=0;
        }
        printf("Was running with %ld threads and got %f / 100 commits, compared to best ever.\n",global_numThread-lastDone, percentOfBestEver);
        fflush(stdout);

        if(commitsDuringLastSleep>bestcdlsEver) {
            bestcdlsEver=commitsDuringLastSleep;
            bestcdlsEverReachedAt=global_numThread;
            printf("new bestcdlsEver record of %ld\n",commitsDuringLastSleep);
        }
        amountOfCommitsChangePrediction=(amountOfCommitsChangePrediction*5+(commitsDuringLastSleep-cdlsOld))/6;
        cdlsOld=commitsDuringLastSleep;

        if(commitsDuringLastSleep>220000) {
            milisecondsOfSleep/=2;
            bestcdlsEver/=2;
            cdlsOld/=2;
            amountOfCommitsChangePrediction/=2;
        }
        else if(commitsDuringLastSleep<22000 && milisecondsOfSleep<2000) {
            milisecondsOfSleep*=2;
            bestcdlsEver*=2;
            cdlsOld*=2;
            amountOfCommitsChangePrediction*=2;
        }
#endif // USE_ALGO_04
#ifdef USE_ALGO_05              // yet another copy of algo 3
        sumOfAllCommitsEverLastTime=getTotalAmountOfCommits();
        mySleep(milisecondsOfSleep);
        sumOfAllCommitsEver=getTotalAmountOfCommits();
        commitsDuringLastSleep=sumOfAllCommitsEver-sumOfAllCommitsEverLastTime;
        lastNumThread=global_numThread;
        double percentOfBestEver=((double)commitsDuringLastSleep)/((double)bestcdlsEver)*((double)100);
        if(commitsDuringLastSleep>cdlsOld && lastDone>0) { // if you increased last time and it got better, increase again
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=level;
            lastAction=1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone>0) { // if you increased last time and it got worse, decrease
            decreaseAmountOfThreads(level);
            lastDone=-level;
            lastAction=-1;
            if((level-1))
                level/=2;
        }
        else if((commitsDuringLastSleep>cdlsOld) && lastDone<0) { // if you decreased and got better, decrease one more time
            decreaseAmountOfThreads(level);
            lastDone=-level;
            lastAction=-1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone<0) { // if you decreased and it got worse, increase again
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=level;
            lastAction=1;
            if((level-1))
                level/=2;
        }
        else if(lastDone==0) {
            randomNumber=rand()%2;
            if(randomNumber) {
                increaseAmountOfThreads(level, ptr2runMoreThreads);
                lastDone=level;
                lastAction=1;
            }
            else {
                decreaseAmountOfThreads(level);
                lastDone=-level;
                lastAction=-1;
            }
        }
        else {
            lastDone=0;
            lastAction=0;
        }
        printf("Was running with %ld threads and got %f / 100 commits, compared to best ever. #commits: %ld \n",lastNumThread-1, percentOfBestEver, commitsDuringLastSleep);
        fflush(stdout);

        if(commitsDuringLastSleep>bestcdlsEver) {
            bestcdlsEver=commitsDuringLastSleep;
            bestcdlsEverReachedAt=global_numThread;
            printf("new bestcdlsEver record of %ld\n",commitsDuringLastSleep);
        }
        cdlsOld=commitsDuringLastSleep;

        if(commitsDuringLastSleep>220000) {
            milisecondsOfSleep/=2;
            bestcdlsEver/=2;
            cdlsOld/=2;
        }
        else if(commitsDuringLastSleep<22000 && milisecondsOfSleep<2000) {
            milisecondsOfSleep*=2;
            bestcdlsEver*=2;
            cdlsOld*=2;
        }
#endif // USE_ALGO_05
#ifdef USE_ALGO_06              // yet another copy of algo 5
        sumOfAllCommitsEverLastTime=getTotalAmountOfCommits();
        abortsBeforeSleep=getTotalAmountOfAborts();
        mySleep(milisecondsOfSleep);
        sumOfAllCommitsEver=getTotalAmountOfCommits();
        abortsAfterSleep=getTotalAmountOfAborts();
        abortsDiff=abortsAfterSleep-abortsBeforeSleep;
        commitsDuringLastSleep=sumOfAllCommitsEver-sumOfAllCommitsEverLastTime;
        lastNumThread=global_numThread;
        double percentOfBestEver=((double)commitsDuringLastSleep)/((double)bestcdlsEver)*((double)100);
        if(commitsDuringLastSleep>cdlsOld && lastDone>0) { // if you increased last time and it got better, increase again
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=level;
            lastAction=1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone>0) { // if you increased last time and it got worse, decrease
            decreaseAmountOfThreads(level);
            lastDone=-level;
            lastAction=-1;
            if((level-1))
                level/=2;
        }
        else if((commitsDuringLastSleep>cdlsOld) && lastDone<0) { // if you decreased and got better, decrease one more time
            decreaseAmountOfThreads(level);
            lastDone=-level;
            lastAction=-1;
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone<0) { // if you decreased and it got worse, increase again
            increaseAmountOfThreads(level, ptr2runMoreThreads);
            lastDone=level;
            lastAction=1;
            if((level-1))
                level/=2;
        }
        else if(lastDone==0) {
            randomNumber=rand()%2;
            if(randomNumber) {
                increaseAmountOfThreads(level, ptr2runMoreThreads);
                lastDone=level;
                lastAction=1;
            }
            else {
                decreaseAmountOfThreads(level);
                lastDone=-level;
                lastAction=-1;
            }
        }
        else {
            lastDone=0;
            lastAction=0;
        }
        printf("Was running with %ld threads and got %f / 100 commits, compared to best ever. #commits: %ld #aborts: %ld\n",lastNumThread-1, percentOfBestEver, commitsDuringLastSleep, abortsDiff);
        fflush(stdout);

        if(commitsDuringLastSleep>bestcdlsEver) {
            bestcdlsEver=commitsDuringLastSleep;
            bestcdlsEverReachedAt=global_numThread;
            printf("new bestcdlsEver record of %ld\n",commitsDuringLastSleep);
        }
        cdlsOld=commitsDuringLastSleep;

        if(commitsDuringLastSleep>220000) {
            milisecondsOfSleep/=2;
            bestcdlsEver/=2;
            cdlsOld/=2;
        }
        else if(commitsDuringLastSleep<22000 && milisecondsOfSleep<2000) {
            milisecondsOfSleep*=2;
            bestcdlsEver*=2;
            cdlsOld*=2;
        }
#endif // USE_ALGO_06
#ifdef USE_ALGO_07              // yet another copy of algo 6
        sumOfAllCommitsEverLastTime=getTotalAmountOfCommits();
		getAmountOfAborts2init();
        mySleep(milisecondsOfSleep);
        sumOfAllCommitsEver=getTotalAmountOfCommits();
        abortsDiff=getAmountOfAborts2();
        commitsDuringLastSleep=sumOfAllCommitsEver-sumOfAllCommitsEverLastTime;
        lastNumThread=global_numThread;
        double percentOfBestEver=((double)commitsDuringLastSleep)/((double)bestcdlsEver)*((double)100);
        if(commitsDuringLastSleep>cdlsOld && lastDone>0) { // if you increased last time and it got better, increase again
            lastDone = increaseAmountOfThreads(level, ptr2runMoreThreads);
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone>0) { // if you increased last time and it got worse, decrease
            lastDone=decreaseAmountOfThreads(level);
            if((level-1))
                level/=2;
        }
        else if((commitsDuringLastSleep>cdlsOld) && lastDone<0) { // if you decreased and got better, decrease one more time
            lastDone=decreaseAmountOfThreads(level);
        }
        else if((commitsDuringLastSleep<cdlsOld) && lastDone<0) { // if you decreased and it got worse, increase again
            lastDone=increaseAmountOfThreads(level, ptr2runMoreThreads);
            if((level-1))
                level/=2;
        }
        else if(lastDone==0) {
            randomNumber=rand()%2;
            if(global_numThread==2){ // one working thread running, additional to the main thread
				randomNumber=1;
				if((level-1))
					level/=2;
            }
            if(randomNumber) {
                lastDone=increaseAmountOfThreads(level, ptr2runMoreThreads);
            }
            else {
                lastDone=decreaseAmountOfThreads(level);
            }
        }
        else {
            lastDone=0;
        }
        // commits and aborts are only counted during sleep
        printf("Was running with %ld threads and got %f / 100 commits, compared to best ever. #commits: %ld #aborts:\t %lu \n",lastNumThread-1, percentOfBestEver, commitsDuringLastSleep, abortsDiff);
        fflush(stdout);

        if(commitsDuringLastSleep>bestcdlsEver) {
            bestcdlsEver=commitsDuringLastSleep;
            bestcdlsEverReachedAt=global_numThread;
            printf("new bestcdlsEver record of %ld\n",commitsDuringLastSleep);
        }
        cdlsOld=commitsDuringLastSleep;

        if(commitsDuringLastSleep>220000) {
            milisecondsOfSleep/=2;
            bestcdlsEver/=2;
            cdlsOld/=2;
            printf("sleep time halved\n");
        }
        else if(commitsDuringLastSleep<22000 && milisecondsOfSleep<2000) {
            milisecondsOfSleep*=2;
            bestcdlsEver*=2;
            cdlsOld*=2;
			printf("sleep time doubled\n");
        }
#endif // USE_ALGO_07
    }
}

int increaseAmountOfThreadsByOne(void (*ptr2runMoreThreads)(long)) {
    if(global_numThread < global_maxNumClient) {
        (*ptr2runMoreThreads)(1);
        return 1;
    }
    return 0;
}

int increaseAmountOfThreads(long amountOfNewThreads,void (*ptr2runMoreThreads)(long)) {
    int success=0;
    int j=0;
    for (j=amountOfNewThreads+1; --j;)
        success+=increaseAmountOfThreadsByOne(ptr2runMoreThreads);
	return success;
}

void decreaseAmountOfThreadsByOne() {
    if(global_numThread > 2) {
        killThreadNr(global_numThread-1);
    }
}

int decreaseAmountOfThreads(long amountOfDeletingThreads) {
    assert(global_numThread<global_maxNumClient+1);
    long k;
    long copyOfGlobalNumThread=global_numThread;
    for (k=amountOfDeletingThreads+1; (global_numThread>2) && (--k);) {
        flagThreadToBeKilled(global_numThread-1);
        --global_numThread;
    }
    int returnValue= global_numThread - copyOfGlobalNumThread;
    for (k=amountOfDeletingThreads+1; (copyOfGlobalNumThread>2) && (--k);) {
        waitForThreadAndRestore(copyOfGlobalNumThread-1);
        --copyOfGlobalNumThread;
    }
    return returnValue;
}

void flagThreadToBeKilled(long threadNr) {
        global_kill[threadNr/64]=global_kill[threadNr/64]|(((long)1)<<(threadNr%64));
}

void waitForThreadAndRestore(long threadNr) {
    while(global_iFinished[threadNr/64]&(((long)1)<<(threadNr%64))) {}
    global_kill[threadNr/64]=global_kill[threadNr/64]^(((long)1)<<(threadNr%64));
}

void mySleep(long miliseconds) {
    struct timespec waitingTime={0};
    waitingTime.tv_sec=(int)(miliseconds/1000);
    waitingTime.tv_nsec=(miliseconds%1000)*1000000;
    nanosleep(&waitingTime, NULL);
//    while(nanosleep(&waitingTime, &waitingTime)==-1)
//        continue;
}

long getTotalAmountOfCommits() {
    long total = 0;
    int i;
    for (i=global_maxNumClient; i-->0;)
        total+=global_amountOfCommitsDone[CACHE_LINE_SIZE/sizeof(long)*i];
    return total;
}

unsigned long getTotalAmountOfAborts() {
    unsigned long total=0;
    int i;
    for (i=global_numThread; i-->0;) {
//    for (i=global_maxNumClient; i-->0;) {
        if(global_abortsCounters[i])
            total+=*(global_abortsCounters[i]);
//		else
//			printf("error\n");
//			total+=global_abortsEndValues[i];
    }
    return total;
}

void getAmountOfAborts2init() {
    int i;
    for (i=global_numThread; i-->0;) {
        if(global_abortsCounters[i])
            global_abortsValues[i]=*(global_abortsCounters[i]);
		else
			global_abortsValues[i]=(unsigned long)0;
    }
}

unsigned long getAmountOfAborts2() {
    unsigned long total=(unsigned long)0;
    int i;
    for (i=global_numThread; i-->0;) {
        if(global_abortsCounters[i] && (global_abortsValues[i]!=(unsigned long)0)) {
/*			total+=*(global_abortsCounters[i]);
			total+=(*(global_abortsCounters[i]) - global_abortsValues[i]);
            if(*(global_abortsCounters[i]) > (unsigned long)844674407302783)
				printf("it happend here %lu \t %d \n",*(global_abortsCounters[i]),i);
            if((global_abortsValues[i]) > (unsigned long)844674407302782)
				printf("it happend here2 %lu \t %d \n",global_abortsValues[i],i);
			if(global_abortsValues[i]<0)
				printf("it happend here3 %lu \t %d \n",global_abortsValues[i],i);*/
			total+= *(global_abortsCounters[i]) - (global_abortsValues[i]);
        }
    }
    return total;
}

/* =============================================================================
 * thread_getNumThread
 * -- Call after thread_start() to get number of threads inside parallel region
 * =============================================================================
 */
long thread_getNumThread() {
    return global_numThread;
}

/* =============================================================================
 * thread_barrier_wait
 * -- Call after thread_start() to synchronize threads inside parallel region
 * =============================================================================
 */
void thread_barrier_wait() {
#ifndef SIMULATOR
#ifndef OTHERTHREADBARRIER
    long threadId = thread_getId();
#endif /* !OTHERTHREADBARRIER */
#endif /* !SIMULATOR */
    THREAD_BARRIER(global_barrierPtr, threadId);
}

/* =============================================================================
 * TEST_THREAD
 * =============================================================================
 */
#ifdef TEST_THREAD

#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS    (4)
#define NUM_ITERATIONS (3)

void printId (void* argPtr) {
    long threadId = global_myThreadID;
    long numThread = thread_getNumThread();
    long i;

    for ( i = 0; i < NUM_ITERATIONS; i++ ) {
        thread_barrier_wait();
        if (threadId == 0) {
            sleep(1);
        } else if (threadId == numThread-1) {
            usleep(100);
        }
        printf("i = %li, tid = %li\n", i, threadId);
        if (threadId == 0) {
            puts("");
        }
        fflush(stdout);
    }
}

int main () {
    puts("Starting...");
    /* Run in parallel */
    thread_startup(NUM_THREADS);
    /* Start timing here */
    thread_start(printId, NULL);
    thread_start(printId, NULL);
    thread_start(printId, NULL);
    /* Stop timing here */
    thread_shutdown();
    puts("Done.");
    return 0;
}

#endif /* TEST_THREAD */

/* =============================================================================
 *
 * End of thread.c
 *
 * =============================================================================
 */
