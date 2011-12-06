#include "transactions.h"
#include "thread_local_variables.h"

typedef enum  {UNIFORM,
	       PERCENTAGE,
	       INVALID_DISTRIBUTION} DistributionType;


typedef struct  TransactionCandidateStruct
{
    unsigned  TxID       ;
    float     Percentage ;  
} TxCandidate_t;


typedef struct TxCandidateListContainerStruct
{
    TxCandidate_t* TxCandidateList; 
    unsigned  CandidateNum ;
    unsigned  Seed;
    DistributionType Distribution;
} TxCandidateListContainer_t;


unsigned ChooseTransaction(TxCandidateListContainer_t* CurrentContainer);

