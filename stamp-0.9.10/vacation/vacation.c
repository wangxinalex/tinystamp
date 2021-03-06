/* =============================================================================
 *
 * vacation.c
 *
 * =============================================================================
 *
 * Copyright (C) Stanford University, 2006.  All Rights Reserved.
 * Author: Chi Cao Minh
 * edited by joerg
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
#include <stdio.h>
#include <getopt.h>
#include "client.h"
#include "customer.h"
#include "list.h"
#include "manager.h"
#include "map.h"
#include "memory.h"
#include "operation.h"
#include "random.h"
#include "reservation.h"
#include "thread.h"
#include "timer.h"
#include "tm.h"
#include "types.h"
#include "utility.h"

#include <unistd.h> // to use sleep in the main rutine

static client_t** clients;
static manager_t* managerPtr;

//long* global_amountOfCommitsDone;

enum param_types {
    PARAM_CLIENTS      = (unsigned char)'c',
    PARAM_NUMBER       = (unsigned char)'n',
    PARAM_QUERIES      = (unsigned char)'q',
    PARAM_RELATIONS    = (unsigned char)'r',
    PARAM_TRANSACTIONS = (unsigned char)'t',
    PARAM_USER         = (unsigned char)'u',
    AMOUNT_OF_WORKPIECES = (unsigned char)'w',
};

#define PARAM_DEFAULT_CLIENTS      (1)
#define PARAM_DEFAULT_NUMBER       (10)
#define PARAM_DEFAULT_QUERIES      (90)
#define PARAM_DEFAULT_RELATIONS    (1 << 16)
#define PARAM_DEFAULT_TRANSACTIONS (1 << 26)
#define PARAM_DEFAULT_USER         (80)
#define PARAM_DEFAULT_WORKPIECES   (1000)

double global_params[256]; /* 256 = ascii limit */

//static const long amountOfWorkPieces=1000;

/* =============================================================================
 * displayUsage
 * =============================================================================
 */
static void displayUsage (const char* appName) {
    printf("Usage: %s [options]\n", appName);
    puts("\nOptions:                                             (defaults)\n");
    printf("    c <UINT>   Number of [c]lients                   (%i)\n",
           PARAM_DEFAULT_CLIENTS);
    printf("    n <UINT>   [n]umber of user queries/transaction  (%i)\n",
           PARAM_DEFAULT_NUMBER);
    printf("    q <UINT>   Percentage of relations [q]ueried     (%i)\n",
           PARAM_DEFAULT_QUERIES);
    printf("    r <UINT>   Number of possible [r]elations        (%i)\n",
           PARAM_DEFAULT_RELATIONS);
    printf("    t <UINT>   Number of [t]ransactions              (%i)\n",
           PARAM_DEFAULT_TRANSACTIONS);
    printf("    u <UINT>   Percentage of [u]ser transactions     (%i)\n",
           PARAM_DEFAULT_USER);
    printf("    w <UINT>   Amount of [w]ork pieces               (%i)\n",
           PARAM_DEFAULT_WORKPIECES);
    exit(1);
}


/* =============================================================================
 * setDefaultParams
 * =============================================================================
 */
static void setDefaultParams () {
    global_params[PARAM_CLIENTS]      = PARAM_DEFAULT_CLIENTS;
    global_params[PARAM_NUMBER]       = PARAM_DEFAULT_NUMBER;
    global_params[PARAM_QUERIES]      = PARAM_DEFAULT_QUERIES;
    global_params[PARAM_RELATIONS]    = PARAM_DEFAULT_RELATIONS;
    global_params[PARAM_TRANSACTIONS] = PARAM_DEFAULT_TRANSACTIONS;
    global_params[PARAM_USER]         = PARAM_DEFAULT_USER;
    global_params[AMOUNT_OF_WORKPIECES] = PARAM_DEFAULT_WORKPIECES;
}


/* =============================================================================
 * parseArgs
 * =============================================================================
 */
static void parseArgs (long argc, char* const argv[]) {
    long i;
    long opt;

    opterr = 0;

    setDefaultParams();

    while ((opt = getopt(argc, argv, "c:n:q:r:t:u:w:")) != -1) {
        switch (opt) {
            case 'c':
            case 'n':
            case 'q':
            case 'r':
            case 't':
            case 'u':
            case 'w':
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
 * addCustomer
 * -- Wrapper function
 * =============================================================================
 */
static bool_t addCustomer (manager_t* managerPtr, long id, long num, long price) {
    return manager_addCustomer_seq(managerPtr, id);
}


/* =============================================================================
 * initializeManager
 * =============================================================================
 */
static manager_t* initializeManager() {
    manager_t* managerPtr;
    long i;
    long numRelation;
    random_t* randomPtr;
    long* ids;
    bool_t (*manager_add[])(manager_t*, long, long, long) = {
        &manager_addCar_seq,
        &manager_addFlight_seq,
        &manager_addRoom_seq,
        &addCustomer
    };
    long t;
    long numTable = sizeof(manager_add) / sizeof(manager_add[0]);

    printf("Initializing manager... ");
    fflush(stdout);

    randomPtr = random_alloc();
    assert(randomPtr != NULL);

    managerPtr = manager_alloc();
    assert(managerPtr != NULL);

    numRelation = (long)global_params[PARAM_RELATIONS];
    ids = (long*)malloc(numRelation * sizeof(long));
    for (i = 0; i < numRelation; i++) {
        ids[i] = i + 1;
    }

    for (t = 0; t < numTable; t++) {

        /* Shuffle ids */
        for (i = 0; i < numRelation; i++) {
            long x = random_generate(randomPtr) % numRelation;
            long y = random_generate(randomPtr) % numRelation;
            long tmp = ids[x];
            ids[x] = ids[y];
            ids[y] = tmp;
        }

        /* Populate table */
        for (i = 0; i < numRelation; i++) {
            bool_t status;
            long id = ids[i];
            long num = ((random_generate(randomPtr) % 5) + 1) * 100;
            long price = ((random_generate(randomPtr) % 5) * 10) + 50;
            status = manager_add[t](managerPtr, id, num, price);
            assert(status);
        }

    } /* for t */

    puts("done.");
    fflush(stdout);

    random_free(randomPtr);
    free(ids);

    return managerPtr;
}


/* =============================================================================
 * initializeClients
 * =============================================================================
 *
static client_t**
initializeClients (manager_t* managerPtr)
{
    random_t* randomPtr;
    client_t** clients;
    long i;
    long numClient = (long)global_params[PARAM_CLIENTS];
    long numTransaction = (long)global_params[PARAM_TRANSACTIONS];
    long numTransactionPerClient;
    long numQueryPerTransaction = (long)global_params[PARAM_NUMBER];
    long numRelation = (long)global_params[PARAM_RELATIONS];
    long percentQuery = (long)global_params[PARAM_QUERIES];
    long queryRange;
    long percentUser = (long)global_params[PARAM_USER];

    printf("Initializing clients... ");
    fflush(stdout);

    randomPtr = random_alloc();
    assert(randomPtr != NULL);

    clients = (client_t**)malloc(numClient * sizeof(client_t*));
    assert(clients != NULL);
    numTransactionPerClient = (long)((double)numTransaction / (double)numClient + 0.5);
    queryRange = (long)((double)percentQuery / 100.0 * (double)numRelation + 0.5);

    for (i = 0; i < numClient; i++) {
        clients[i] = client_alloc(i,
                                  managerPtr,
                                  numTransactionPerClient,
                                  numQueryPerTransaction,
                                  queryRange,
                                  percentUser);
        assert(clients[i]  != NULL);
    }

    puts("done.");
    printf("    Transactions        = %li\n", numTransaction);
    printf("    Clients             = %li\n", numClient);
    printf("    Transactions/client = %li\n", numTransactionPerClient);
    printf("    Queries/transaction = %li\n", numQueryPerTransaction);
    printf("    Relations           = %li\n", numRelation);
    printf("    Query percent       = %li\n", percentQuery);
    printf("    Query range         = %li\n", queryRange);
    printf("    Percent user        = %li\n", percentUser);
    fflush(stdout);

    random_free(randomPtr);

    return clients;
}
*/

/* =============================================================================
 * initializeClients - by joerg
 * =============================================================================
 */
static client_t* initializeOneClient (manager_t* managerPtr, long clientID) {
    random_t* randomPtr;
    client_t* client;

    long numTransaction = (long)global_params[PARAM_TRANSACTIONS];
    long numTransactionPerClient;
    long numQueryPerTransaction = (long)global_params[PARAM_NUMBER];
    long numRelation = (long)global_params[PARAM_RELATIONS];
    long percentQuery = (long)global_params[PARAM_QUERIES];
    long queryRange;
    long percentUser = (long)global_params[PARAM_USER];
//    long maxNumClient = (long)global_params[PARAM_CLIENTS];

    printf("Initializing clients... ");
    fflush(stdout);

    randomPtr = random_alloc();
    assert(randomPtr != NULL);

    numTransactionPerClient=numTransaction/ ((long) global_params[AMOUNT_OF_WORKPIECES]); // improved version
    if(clientID==0)
        numTransactionPerClient=numTransaction % ((long)global_params[AMOUNT_OF_WORKPIECES]);
    queryRange = (long)((double)percentQuery / 100.0 * (double)numRelation + 0.5);

    client = client_alloc(  clientID,
                            managerPtr,
                            numTransactionPerClient,
                            numQueryPerTransaction,
                            queryRange,
                            percentUser);
    assert(client != NULL);
    puts("done.");
    printf("    Transactions        = %li\n", numTransaction);
    printf("    Transactions/client = %li\n", numTransactionPerClient);
    printf("    Queries/transaction = %li\n", numQueryPerTransaction);
    printf("    Relations           = %li\n", numRelation);
    printf("    Query percent       = %li\n", percentQuery);
    printf("    Query range         = %li\n", queryRange);
    printf("    Percent user        = %li\n", percentUser);
    printf("    client ID           = %li\n", clientID);
    fflush(stdout);
    random_free(randomPtr);
    return client;
}



/* =============================================================================
 * checkTables
 * -- some simple checks (not comprehensive)
 * -- dependent on tasks generated for clients in initializeClients()
 * =============================================================================
 */
void
checkTables (manager_t* managerPtr)
{
    long i;
    long numRelation = (long)global_params[PARAM_RELATIONS];
    MAP_T* customerTablePtr = managerPtr->customerTablePtr;
    MAP_T* tables[] = {
        managerPtr->carTablePtr,
        managerPtr->flightTablePtr,
        managerPtr->roomTablePtr,
    };
    long numTable = sizeof(tables) / sizeof(tables[0]);
    bool_t (*manager_add[])(manager_t*, long, long, long) = {
        &manager_addCar_seq,
        &manager_addFlight_seq,
        &manager_addRoom_seq
    };
    long t;

    printf("Checking tables... ");
    fflush(stdout);

    /* Check for unique customer IDs */
    long percentQuery = (long)global_params[PARAM_QUERIES];
    long queryRange = (long)((double)percentQuery / 100.0 * (double)numRelation + 0.5);
    long maxCustomerId = queryRange + 1;
    for (i = 1; i <= maxCustomerId; i++) {
        if (MAP_FIND(customerTablePtr, i)) {
            if (MAP_REMOVE(customerTablePtr, i)) {
                assert(!MAP_FIND(customerTablePtr, i));
            }
        }
    }

    /* Check reservation tables for consistency and unique ids */
    for (t = 0; t < numTable; t++) {
        MAP_T* tablePtr = tables[t];
        for (i = 1; i <= numRelation; i++) {
            if (MAP_FIND(tablePtr, i)) {
                assert(manager_add[t](managerPtr, i, 0, 0)); /* validate entry */
                if (MAP_REMOVE(tablePtr, i)) {
                    assert(!MAP_REMOVE(tablePtr, i));
                }
            }
        }
    }

    puts("done.");
    fflush(stdout);
}


/* =============================================================================
 * freeClients
 * =============================================================================
 */
static void
freeClients (client_t** clients)
{
    long i;
//    long numClient = (long)global_params[PARAM_CLIENTS];

    for (i = 0; i < thread_getNumThread(); i++) {
        client_t* clientPtr = clients[i];
        client_free(clientPtr);
    }
}

static void runMoreThreads(long numThreads) {
    long i;
    for (i=thread_getNumThread()+numThreads; i--!=thread_getNumThread();) {
        if(!clients[i])
            clients[i] = initializeOneClient(managerPtr, i);
    }
    thread_startup_noBarriers(numThreads, 1);
}

/* =============================================================================
 * main (original)
 * =============================================================================
 */
 /*
MAIN(argc, argv)
{
    manager_t* managerPtr;
    client_t** clients;
    TIMER_T start;
    TIMER_T stop;

    GOTO_REAL();

    // Initialization
    parseArgs(argc, (char** const)argv);
    SIM_GET_NUM_CPU(global_params[PARAM_CLIENTS]);
    managerPtr = initializeManager();
    assert(managerPtr != NULL);
    clients = initializeClients(managerPtr);
    assert(clients != NULL);
    long numThread = global_params[PARAM_CLIENTS];
    TM_STARTUP(numThread);
    P_MEMORY_STARTUP(numThread);
    thread_startup(numThread);

    // Run transactions
    printf("Running clients... ");
    fflush(stdout);
    TIMER_READ(start);
    GOTO_SIM();
#ifdef OTM
#pragma omp parallel
    {
        client_run(clients);
    }
#else
    thread_start(client_run, (void*)clients);
#endif
    GOTO_REAL();
    TIMER_READ(stop);
    puts("done.");
    printf("Time = %0.6lf\n",
           TIMER_DIFF_SECONDS(start, stop));
    fflush(stdout);
    checkTables(managerPtr);

    // Clean up
    printf("Deallocating memory... ");
    fflush(stdout);
    freeClients(clients);

    // TODO: The contents of the manager's table need to be deallocated.
    manager_free(managerPtr);
    puts("done.");
    fflush(stdout);

    TM_SHUTDOWN();
    P_MEMORY_SHUTDOWN();

    GOTO_SIM();

    thread_shutdown();

    MAIN_RETURN(0);
}
*/

/* =============================================================================
 * main (version destroyed by joerg)
 * =============================================================================
 */
MAIN(argc, argv)
{
//    manager_t* managerPtr;
//    client_t** clients;
    TIMER_T start;
    TIMER_T stop;

    GOTO_REAL();

    /* Initialization */
    parseArgs(argc, (char** const)argv);
    SIM_GET_NUM_CPU(global_params[PARAM_CLIENTS]);
    managerPtr = initializeManager();
    assert(managerPtr != NULL);

    long maxNumClient = ((long)global_params[PARAM_CLIENTS])+1;
#ifdef DYNAMC_THREAD_MANAGEMENT
    long initNumThreads = PORTION_OF_THREADS_TO_START_RIGHT_AT_THE_BEGINNING * (maxNumClient-1);
    if(initNumThreads<1)
        initNumThreads=1;
#else
    long initNumThreads = maxNumClient-1;
    if(initNumThreads<1) {
        printf("ERROR: 3942\nI need at least one worker thread.");
        exit(3942);
    }
#endif
    clients = (client_t**)malloc(maxNumClient * sizeof(client_t*));
    assert(clients != NULL);
    long i;
    for (i=maxNumClient; i--;)
        clients[i] = initializeOneClient(managerPtr, i);
    for (i=maxNumClient; --i>initNumThreads;)
        clients[i]=0;

    /* Run transactions */
    printf("Running clients... ");
    fflush(stdout);
    TIMER_READ(start);

    TM_STARTUP_NO_ARGS();
    P_MEMORY_STARTUP(maxNumClient);  // = nothing ifndef SIMULATOR
    thread_prepare_start(client_run, (void*)clients, maxNumClient, global_params[AMOUNT_OF_WORKPIECES]);
    initial_thread_startup_noBarriers(initNumThreads, 1);

    GOTO_SIM();  // = nothing ifndef SIMULATOR
#ifdef OTM
#pragma omp parallel
    { client_run(clients); }  // is not executed here
#else
// code here would be executed
    thread_start_noBarriers();
#endif
    GOTO_REAL();    // = nothing ifndef SIMULATOR
//    long u=3; // delete me
//    long u2=ATOMIC_FETCH_DEC_FULL(&u); // just testing wheter it works

#ifdef DYNAMC_THREAD_MANAGEMENT
    ajust_amount_of_threads(&runMoreThreads);
#else
    while (!every_thread_finished()) {mySleep(1);}//{sleep(0.001);}
#endif

    TIMER_READ(stop);

    puts("done.");
    printf("Time = %0.6lf\n",
           TIMER_DIFF_SECONDS(start, stop));
    fflush(stdout);
    checkTables(managerPtr);

    /* Clean up */
    printf("Deallocating memory... ");
    fflush(stdout);
    freeClients(clients);
    /*
     * TODO: The contents of the manager's table need to be deallocated.
     */
    manager_free(managerPtr);
    puts("done.");
    fflush(stdout);

    TM_SHUTDOWN();
    P_MEMORY_SHUTDOWN();

    GOTO_SIM(); // = nothing ifndef SIMULATOR

    thread_shutdown_noBarriers();

    MAIN_RETURN(0);
}

/* =============================================================================
 *
 * End of vacation.c
 *
 * =============================================================================
 */
