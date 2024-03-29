/* =============================================================================
 *
 * intruder.c
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
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "decoder.h"
#include "detector.h"
#include "dictionary.h"
#include "packet.h"
#include "stream.h"
#include "thread.h"
#include "timer.h"
#include "tm.h"

#include <unistd.h> // to use sleep in the main rutine

__thread long* myCommitCounter;

enum param_types {
    PARAM_ATTACK = (unsigned char)'a',
    PARAM_LENGTH = (unsigned char)'l',
    PARAM_NUM    = (unsigned char)'n',
    PARAM_SEED   = (unsigned char)'s',
    PARAM_THREAD = (unsigned char)'t',
    PARAM_INITIAL= (unsigned char)'i',
};

enum param_defaults {
    PARAM_DEFAULT_ATTACK = 10,
    PARAM_DEFAULT_LENGTH = 16,
    PARAM_DEFAULT_NUM    = 1 << 20,
    PARAM_DEFAULT_SEED   = 1,
    PARAM_DEFAULT_THREAD = 100,
    PARAM_DEFAULT_INITIAL= 1,
};

long global_params[256] = { /* 256 = ascii limit */
    [PARAM_ATTACK] = PARAM_DEFAULT_ATTACK,
    [PARAM_LENGTH] = PARAM_DEFAULT_LENGTH,
    [PARAM_NUM]    = PARAM_DEFAULT_NUM,
    [PARAM_SEED]   = PARAM_DEFAULT_SEED,
    [PARAM_THREAD] = PARAM_DEFAULT_THREAD,
    [PARAM_INITIAL]= PARAM_DEFAULT_INITIAL,
};

typedef struct arg {
  /* input: */
    stream_t* streamPtr;
    decoder_t* decoderPtr;
  /* output: */
    vector_t** errorVectors;
} arg_t;


/* =============================================================================
 * displayUsage
 * =============================================================================
 */
static void
displayUsage (const char* appName)
{
    printf("Usage: %s [options]\n", appName);
    puts("\nOptions:                            (defaults)\n");
    printf("   a <UINT>   Percent [a]ttack             (%i)\n", PARAM_DEFAULT_ATTACK);
    printf("   l <UINT>   Max data [l]ength            (%i)\n", PARAM_DEFAULT_LENGTH);
    printf("   n <UINT>   [n]umber of flows            (%i)\n", PARAM_DEFAULT_NUM);
    printf("   s <UINT>   Random [s]eed                (%i)\n", PARAM_DEFAULT_SEED);
    printf("   t <UINT>   Number of [t]hreads          (%i)\n", PARAM_DEFAULT_THREAD);
    printf("   i <UINT>   Number of [i]nitial threads  (%i)\n", PARAM_DEFAULT_INITIAL);
    exit(1);
}

/* =============================================================================
 * parseArgs
 * =============================================================================
 */
static void
parseArgs (long argc, char* const argv[])
{
    long i;
    long opt;

    opterr = 0;

    while ((opt = getopt(argc, argv, "a:l:n:s:t:i:")) != -1) {
        switch (opt) {
            case 'a':
            case 'l':
            case 'n':
            case 's':
            case 't':
            case 'i':
                global_params[(unsigned char)opt] = atol(optarg);
                break;
            case '?':
            default:
                opterr++;
                break;
        }
    }

    for (i = optind; i < argc; i++) {
        fprintf(stderr, "Non-option argument: %s\n", argv[i]);
        opterr++;
    }

    if (opterr) {
        displayUsage(argv[0]);
    }
}


/* =============================================================================
 * processPackets
 * =============================================================================
 */
void processPackets (void* argPtr) {
    TM_THREAD_ENTER();
    long threadId = thread_getId();
    myCommitCounter=getMyCommitCounter();
    unsigned long ** globalAbortsCounter = getGlobal_abortsCounters();
    globalAbortsCounter[threadId]=(unsigned long*) stm_get_stats_position("nb_aborts");

    stream_t*   streamPtr    = ((arg_t*)argPtr)->streamPtr;
    decoder_t*  decoderPtr   = ((arg_t*)argPtr)->decoderPtr;
    vector_t**  errorVectors = ((arg_t*)argPtr)->errorVectors;

    detector_t* detectorPtr = PDETECTOR_ALLOC();
    assert(detectorPtr);
    PDETECTOR_ADDPREPROCESSOR(detectorPtr, &preprocessor_toLower);

    vector_t* errorVectorPtr = errorVectors[threadId];

    while (1) {
        if(i_got_killed())
            break;

        char* bytes;
//        TM_BEGIN();       // ------------------------------------------------------------ TX 11
        TM_JBS_BEGIN(11);
        bytes = TMSTREAM_GETPACKET(streamPtr);
        TM_END();
        INCREASE_COMMIT_COUNTER;
        if (!bytes) {
            break;
        }

        packet_t* packetPtr = (packet_t*)bytes;
        long flowId = packetPtr->flowId;

        error_t error;
//        TM_BEGIN();       // ------------------------------------------------------------ TX 12
        TM_JBS_BEGIN(12);
        error = TMDECODER_PROCESS(decoderPtr,
                                  bytes,
                                  (PACKET_HEADER_LENGTH + packetPtr->length));
        TM_END();
        INCREASE_COMMIT_COUNTER;
        if (error) {
            /*
             * Currently, stream_generate() does not create these errors.
             */
            assert(0);
            bool_t status = PVECTOR_PUSHBACK(errorVectorPtr, (void*)flowId);
            assert(status);
        }

        char* data;
        long decodedFlowId;
//        TM_BEGIN();       // ------------------------------------------------------------ TX 13
        TM_JBS_BEGIN(13);
        data = TMDECODER_GETCOMPLETE(decoderPtr, &decodedFlowId);
        TM_END();
        INCREASE_COMMIT_COUNTER;
        if (data) {
            error_t error = PDETECTOR_PROCESS(detectorPtr, data);
            P_FREE(data);
            if (error) {
                bool_t status = PVECTOR_PUSHBACK(errorVectorPtr,
                                                 (void*)decodedFlowId);
                assert(status);
            }
        }

    }
    globalAbortsCounter[threadId]= 0;
    PDETECTOR_FREE(detectorPtr);
    TM_THREAD_EXIT();
}

/* =============================================================================
 * main original
 * =============================================================================
 */
/*MAIN(argc, argv)
{
    GOTO_REAL();

    // Initialization

    parseArgs(argc, (char** const)argv);
    long numThread = global_params[PARAM_THREAD];
    SIM_GET_NUM_CPU(numThread);
    TM_STARTUP(numThread);
    P_MEMORY_STARTUP(numThread);
    thread_startup(numThread);

    long percentAttack = global_params[PARAM_ATTACK];
    long maxDataLength = global_params[PARAM_LENGTH];
    long numFlow       = global_params[PARAM_NUM];
    long randomSeed    = global_params[PARAM_SEED];
    printf("Percent attack  = %li\n", percentAttack);
    printf("Max data length = %li\n", maxDataLength);
    printf("Num flow        = %li\n", numFlow);
    printf("Random seed     = %li\n", randomSeed);

    dictionary_t* dictionaryPtr = dictionary_alloc();
    assert(dictionaryPtr);
    stream_t* streamPtr = stream_alloc(percentAttack);
    assert(streamPtr);
    long numAttack = stream_generate(streamPtr,
                                     dictionaryPtr,
                                     numFlow,
                                     randomSeed,
                                     maxDataLength);
    printf("Num attack      = %li\n", numAttack);

    decoder_t* decoderPtr = decoder_alloc();
    assert(decoderPtr);

    vector_t** errorVectors = (vector_t**)malloc(numThread * sizeof(vector_t*));
    assert(errorVectors);
    long i;
    for (i = 0; i < numThread; i++) {
        vector_t* errorVectorPtr = vector_alloc(numFlow);
        assert(errorVectorPtr);
        errorVectors[i] = errorVectorPtr;
    }

    arg_t arg;
    arg.streamPtr    = streamPtr;
    arg.decoderPtr   = decoderPtr;
    arg.errorVectors = errorVectors;

    // Run transactions

    TIMER_T startTime;
    TIMER_READ(startTime);
    GOTO_SIM();
#ifdef OTM
#pragma omp parallel
    {
        processPackets((void*)&arg);
    }

#else
    thread_start(processPackets, (void*)&arg);
#endif
    GOTO_REAL();
    TIMER_T stopTime;
    TIMER_READ(stopTime);
    printf("Elapsed time    = %f seconds\n", TIMER_DIFF_SECONDS(startTime, stopTime));

    // Check solution

    long numFound = 0;
    for (i = 0; i < numThread; i++) {
        vector_t* errorVectorPtr = errorVectors[i];
        long e;
        long numError = vector_getSize(errorVectorPtr);
        numFound += numError;
        for (e = 0; e < numError; e++) {
            long flowId = (long)vector_at(errorVectorPtr, e);
            bool_t status = stream_isAttack(streamPtr, flowId);
            assert(status);
        }
    }
    printf("Num found       = %li\n", numFound);
    assert(numFound == numAttack);

    // Clean up

    for (i = 0; i < numThread; i++) {
        vector_free(errorVectors[i]);
    }
    free(errorVectors);
    decoder_free(decoderPtr);
    stream_free(streamPtr);
    dictionary_free(dictionaryPtr);

    TM_SHUTDOWN();
    P_MEMORY_SHUTDOWN();

    GOTO_SIM();

    thread_shutdown();

    MAIN_RETURN(0);
}*/

static void runMoreThreads(long numThreads) {
    thread_startup_noBarriers(numThreads, 0);
}

/* =============================================================================
 * main, adapted by jbs
 * =============================================================================
 */
MAIN(argc, argv) {
    GOTO_REAL();  // does nothing here
    // Initialization
    parseArgs(argc, (char** const)argv);
    long maxAmountOfClients = global_params[PARAM_THREAD]+1;
#ifdef DYNAMC_THREAD_MANAGEMENT
	long initNumThreads = global_params[PARAM_INITIAL];
	if(initNumThreads<1) {
        printf("ERROR: 3942\nI need at least one worker thread.\ngoodbye\n");
        exit(3942);
    }
    else if(initNumThreads>global_params[PARAM_THREAD]) {
        printf("ERROR: 3943\nI need less initial threads than the maximal amount of threads.\ngoodbye\n");
        exit(3943);
    }

//    long initNumThreads = PORTION_OF_THREADS_TO_START_RIGHT_AT_THE_BEGINNING * (maxAmountOfClients-1);
//    if(initNumThreads<1)
//        initNumThreads=1;
#else
	long initNumThreads = global_params[PARAM_INITIAL];
//    long initNumThreads = maxAmountOfClients-1;
    if(initNumThreads<1) {
        printf("ERROR: 3942\nI need at least one worker thread.\ngoodbye\n");
        exit(3942);
    }
    else if(initNumThreads>global_params[PARAM_THREAD]) {
        printf("ERROR: 3943\nI need less initial threads than the maximal amount of threads.\ngoodbye\n");
        exit(3943);
    }
#endif
    SIM_GET_NUM_CPU(maxAmountOfClients);
    long percentAttack = global_params[PARAM_ATTACK];
    long maxDataLength = global_params[PARAM_LENGTH];
    long numFlow       = global_params[PARAM_NUM];
    long randomSeed    = global_params[PARAM_SEED];
    printf("Percent attack  = %li\n", percentAttack);
    printf("Max data length = %li\n", maxDataLength);
    printf("Num flow        = %li\n", numFlow);
    printf("Random seed     = %li\n", randomSeed);

    dictionary_t* dictionaryPtr = dictionary_alloc();
    assert(dictionaryPtr);
    stream_t* streamPtr = stream_alloc(percentAttack);
    assert(streamPtr);
    long numAttack = stream_generate(streamPtr,
                                     dictionaryPtr,
                                     numFlow,
                                     randomSeed,
                                     maxDataLength);
    printf("Num attack      = %li\n", numAttack);
    printf("max # threads = %li\n", global_params[PARAM_THREAD]);
    printf("initial # threads = %li\n", global_params[PARAM_INITIAL]);
    decoder_t* decoderPtr = decoder_alloc();
    assert(decoderPtr);
    vector_t** errorVectors = (vector_t**)malloc(maxAmountOfClients * sizeof(vector_t*));
    assert(errorVectors);

    long i;
    for (i = 0; i < maxAmountOfClients; i++) {
        vector_t* errorVectorPtr = vector_alloc(numFlow);
        assert(errorVectorPtr);
        errorVectors[i] = errorVectorPtr;
    }

    arg_t arg;
    arg.streamPtr    = streamPtr;
    arg.decoderPtr   = decoderPtr;
    arg.errorVectors = errorVectors;

    // Run transactions

    TIMER_T startTime;
    TIMER_READ(startTime);

    thread_prepare_start(processPackets,(void*)&arg, maxAmountOfClients, 0);

    TM_STARTUP(maxAmountOfClients);
    P_MEMORY_STARTUP(maxAmountOfClients);
//    thread_startup(numThread);
    initial_thread_startup_noBarriers(initNumThreads, 0);

    GOTO_SIM(); // does nothing in our experiment
#ifdef OTM
#pragma omp parallel
    {     processPackets((void*)&arg);    }
#else
//    thread_start(processPackets, (void*)&arg);
#endif
    GOTO_REAL();  // does nothing here

#ifdef DYNAMC_THREAD_MANAGEMENT
    ajust_amount_of_threads(&runMoreThreads);
#else
    while (!every_thread_finished()) {mySleep(1);}//{sleep(0.001);}
#endif

    TIMER_T stopTime;
    TIMER_READ(stopTime);
    printf("Elapsed time    = %f seconds\n", TIMER_DIFF_SECONDS(startTime, stopTime));

    // Check solution

    long numFound = 0;
    for (i = 0; i < maxAmountOfClients; i++) {
        vector_t* errorVectorPtr = errorVectors[i];
        long e;
        long numError = vector_getSize(errorVectorPtr);
        numFound += numError;
        for (e = 0; e < numError; e++) {
            long flowId = (long)vector_at(errorVectorPtr, e);
            bool_t status = stream_isAttack(streamPtr, flowId);
            assert(status);
        }
    }
    printf("Num found       = %li\n", numFound);
    assert(numFound == numAttack);

    // Clean up

    for (i = 0; i < maxAmountOfClients; i++) {
        vector_free(errorVectors[i]);
    }
    free(errorVectors);
    decoder_free(decoderPtr);
    stream_free(streamPtr);
    dictionary_free(dictionaryPtr);

    TM_SHUTDOWN();
    P_MEMORY_SHUTDOWN();

    GOTO_SIM();   // usless in our experiment

    thread_shutdown_noBarriers();

    MAIN_RETURN(0);
}

/* =============================================================================
 *
 * End of intruder.c
 *
 * =============================================================================
 */
