#include "threads.h"
#include "assert.h"
#include "simulation_parameters.h" // for definition of bool type

unsigned ChooseTransaction(TxCandidateListContainer_t* CurrentContainer)
{
// printf("\tTxID: %u",CurrentContainer -> TxCandidateList[0].TxID);
    assert(CurrentContainer != NULL) ;
    unsigned CandidateNum = CurrentContainer -> CandidateNum;
    unsigned* Seed        = &(CurrentContainer -> Seed);

    unsigned SelectedCandidateNo;
    assert(CandidateNum > 1);

	if (CurrentContainer -> Distribution == UNIFORM)
	{
	    SelectedCandidateNo =  (unsigned)((double)CandidateNum * (double)((double)RAND_R(Seed)/(double)(RAND_MAX_VAL + 1.0))) ;
	}
        else if ( CurrentContainer -> Distribution == PERCENTAGE )
	{
	    double SelectedPosInHundredScale = (double)100 * (double)((double)RAND_R(Seed)/(double)(RAND_MAX_VAL + 1.0));
	    
	    unsigned CandidateNo;
	    double   CurrentRegionUpperLimit = 0 ;
	    SelectedCandidateNo = CandidateNum;
	    for(CandidateNo=0; CandidateNo< CandidateNum; CandidateNo++)
	    {
		double CurrentPercentageValue = (double)(CurrentContainer -> TxCandidateList[CandidateNo]).Percentage;
		CurrentRegionUpperLimit += CurrentPercentageValue;
		if( CandidateNo == CandidateNum-1)
		    CurrentRegionUpperLimit = 100.0;
		bool SelectedPosInCurrentRegion = (SelectedPosInHundredScale < CurrentRegionUpperLimit );
		if( SelectedPosInCurrentRegion )
		{
		    SelectedCandidateNo = CandidateNo;
		    break;
		}
	    }
	    assert( SelectedCandidateNo < CandidateNum);

	}
        else
	{
	    fprintf(stderr,"ChooseTransaction: UNKNOWN DISTRIBUTION requested. Terminating program...\n");
	    assert(0);
	}

    unsigned SelectedTxID  = CurrentContainer -> TxCandidateList[SelectedCandidateNo].TxID;
    return SelectedTxID;
}



unsigned ChooseFromUniformDist(unsigned CandidateNum, unsigned* Seed)
{
    assert(Seed != NULL) ;
    unsigned  ChosenElementNo =  (unsigned)((double)CandidateNum * (double)((double)RAND_R(Seed)/(double)(RAND_MAX_VAL + 1.0))) ;
    return ChosenElementNo;
}




