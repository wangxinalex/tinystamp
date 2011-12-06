// Definition and initialization of thread local variables.
unsigned ChosenTransactionID;
TxCandidateListContainer_t CandidateListContainer[1];
CandidateListContainer[0].CandidateNum = 2;
CandidateListContainer[0].Seed         = (unsigned) RAND_R(&CurrentThreadSeed);
CandidateListContainer[0].Distribution = UNIFORM;
CandidateListContainer[0].TxCandidateList = (TxCandidate_t*)malloc(CandidateListContainer[0].CandidateNum*sizeof( TxCandidate_t ));
CandidateListContainer[0].TxCandidateList[0].TxID = 2;
CandidateListContainer[0].TxCandidateList[0].Percentage = 50.000000000000;
CandidateListContainer[0].TxCandidateList[1].TxID = 1;
CandidateListContainer[0].TxCandidateList[1].Percentage = 50.000000000000;
printf("Thread[%u]: CandidateListContainer[0].Seed = %u \n", ID, CandidateListContainer[0].Seed);
