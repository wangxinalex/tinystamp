// Definition and initialization of thread local variables.
unsigned RepetitionNo[1];
unsigned ChosenTransactionID;
TxCandidateListContainer_t CandidateListContainer[1];
CandidateListContainer[0].CandidateNum = 2;
CandidateListContainer[0].Seed         = (unsigned) RAND_R(&CurrentThreadSeed);
CandidateListContainer[0].Distribution = PERCENTAGE;
CandidateListContainer[0].TxCandidateList = (TxCandidate_t*)malloc(CandidateListContainer[0].CandidateNum*sizeof( TxCandidate_t ));
CandidateListContainer[0].TxCandidateList[0].TxID = 0;
CandidateListContainer[0].TxCandidateList[0].Percentage = 80.000000000000;
CandidateListContainer[0].TxCandidateList[1].TxID = 1;
CandidateListContainer[0].TxCandidateList[1].Percentage = 20.000000000000;
