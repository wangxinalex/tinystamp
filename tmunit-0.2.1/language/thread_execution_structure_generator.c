/*
 * 
 * Author(s):
 *   Derin Harmanci <derin.harmanci@unine.ch>
 *
 * Copyright (c) 2008.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION

#include "thread_execution_structure_generator.h"
#include "schedule_execution_structure_generator.h"

dyn_arr_t  Dyn_TxDefArray;
TxInfo_t*  TxDefArray;
unsigned   TxDefNum; 


dyn_arr_t Dyn_ThreadDefArray;
ThreadInfo_t* ThreadDefArray; 

unsigned   ThreadDefArraySize ,
           ThreadDefNum       ,
           ThreadTypeNum      ;
dyn_arr_t  Dyn_CurrentThreadDefList;

unsigned short CurrentTxContainerNo   ;
unsigned short TxBlockStartContainerNo;

dyn_arr_t  TxBlockStartContainerNoList;
dyn_arr_t  CurrentTxContainerList; 
dyn_arr_t  CurrentTxList;
dyn_arr_t  CurrentTxCandidateList;

unsigned CurrentDelayVal;
bool DelayOpEncountered;





void barrier_init(barrier_t *b, int n)
{
  pthread_cond_init(&b->complete, NULL);
  pthread_mutex_init(&b->mutex, NULL);
  b->count = n;
  b->crossing = 0;
}

void barrier_cross(barrier_t *b)
{
  pthread_mutex_lock(&b->mutex);
  /* One more thread through */
  b->crossing++;
// HARMANCI DEBUGG  printf("b->crossing= %u\n",b->crossing);
  /* If not all here, wait */
  if (b->crossing < b->count) {
    pthread_cond_wait(&b->complete, &b->mutex);
  } else {
    pthread_cond_broadcast(&b->complete);
    /* Reset for next time */
    b->crossing = 0;
  }
  pthread_mutex_unlock(&b->mutex);
}



int InitializeTempThreadStructuresUsedInParsing()
{
    Initialize_DynamicArray(&Dyn_ThreadDefArray);
    Initialize_DynamicArray(&Dyn_TxDefArray);
    
    Initialize_DynamicArray(&CurrentTxContainerList);
    Initialize_DynamicArray(&CurrentTxList);
    Initialize_DynamicArray(&CurrentTxCandidateList);
    Initialize_DynamicArray(&TxBlockStartContainerNoList);

    CurrentDelayVal = 0;
    DelayOpEncountered = FALSE;

    Initialize_DynamicArray(&Dyn_CurrentThreadDefList);
    ThreadTypeNum   = 0;

//    if(ExecuteSchedule)
//      {
	Initialize_DynamicArray(&Dyn_Schedule);
	Initialize_DynamicArray(&Dyn_ScheduleList);

    if(ExecuteSchedule)
    {
	Initialize_DynamicArray(&Dyn_ScheduleThreadDefArray);
	ScheduleThreadNum = 0;
    }

    Initialize_DynamicArray(&Dyn_InvariantArray);
    InvariantNum = 0;
    
    return 0;
}


// From thread.h
/*!  

  \todo  Copy  also  the  TxCandidateList  of the  current  ThreadDef  into
  ThreadTxContainerList (ThreadTxContainerList  is copied using MakeStaticCopy
  but the pointer  TxCandidateList of each element of the list (TxContainer_t) 
  points to the actual  Tx Candidate List of the element. The contens of these
  Tx Candidate Lists should also be copied.

 */
void AddNewThreadDef(char* ThreadName)
{
    Extend_DynamicArray(&Dyn_ThreadDefArray,sizeof(ThreadInfo_t));
    ((ThreadInfo_t *)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].Name = dupstr(ThreadName);

    TxContainer_t* ThreadTxContainerList = (TxContainer_t*)MakeStaticCopy_DynamicArray(&CurrentTxContainerList, sizeof(TxContainer_t));
    assert(ThreadTxContainerList!= NULL);

// NEW ADDED CODE HARMANCI
    unsigned TxContainerNo;
    unsigned TxContainerNum = GetSize_DynamicArray(&CurrentTxContainerList) ;
    for(TxContainerNo=0; TxContainerNo < TxContainerNum ; TxContainerNo++)
    {
	TxCandidate_t* CurrentTxCandidateListPtr = ((TxContainer_t*)(CurrentTxContainerList.ArrayStartAddress))[TxContainerNo].TxCandidateList;
	int            SizeOfListInBytes         = (((TxContainer_t*)(CurrentTxContainerList.ArrayStartAddress))[TxContainerNo].CandidateTxNum) * sizeof(TxCandidate_t);

	ThreadTxContainerList[TxContainerNo].TxCandidateList = (TxCandidate_t*)malloc( SizeOfListInBytes);
	memcpy(ThreadTxContainerList[TxContainerNo].TxCandidateList,CurrentTxCandidateListPtr,SizeOfListInBytes);
    }
// END OF  NEW ADDED CODE HARMANCI


    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].ID = ThreadDefNum;
    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].TxContainerList = ThreadTxContainerList;
    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].TxContainerNum  = CurrentTxContainerList.ArrayElementNum;
    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].CommitNum = 0;
    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].AbortNum  = 0;

    ThreadDefNum++; 
}


void Duplicate_ThreadDef(char* SourceThreadName)
{

    unsigned FoundThreadNo  = FindThreadByName(SourceThreadName, (ThreadInfo_t*)Dyn_ThreadDefArray.ArrayStartAddress, ThreadDefNum);
    bool ThreadNameNotFound = (FoundThreadNo == ThreadDefNum );
    if( ThreadNameNotFound )
    {
	fprintf(stderr,"ERROR: Duplicate_ThreadDef(): The name of the thread definition to duplicate\n"
                       "       could not be found in Dyn_ThreadDefArray\n.");
	assert(0);
    }

    Extend_DynamicArray(&Dyn_ThreadDefArray,sizeof(ThreadInfo_t));
    ThreadInfo_t * SourceThreadDef = &(((ThreadInfo_t *)(Dyn_ThreadDefArray.ArrayStartAddress))[ FoundThreadNo]);

    ((ThreadInfo_t *)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].Name = dupstr(SourceThreadName);

    unsigned TxContainerListSizeInMemory = (SourceThreadDef ->TxContainerNum) * sizeof(TxContainer_t);
    TxContainer_t* ThreadTxContainerList = (TxContainer_t*)malloc(TxContainerListSizeInMemory);
    memcpy(ThreadTxContainerList, SourceThreadDef ->TxContainerList, TxContainerListSizeInMemory);
    assert(ThreadTxContainerList!= NULL);

// NEW ADDED CODE HARMANCI
    unsigned TxContainerNo;
    unsigned TxContainerNum = SourceThreadDef ->TxContainerNum;
    for(TxContainerNo=0; TxContainerNo < TxContainerNum ; TxContainerNo++)
    {
	TxCandidate_t* CurrentTxCandidateListPtr = (SourceThreadDef ->TxContainerList)[TxContainerNo].TxCandidateList;
	int            SizeOfListInBytes         = ( (SourceThreadDef ->TxContainerList)[TxContainerNo].CandidateTxNum ) * sizeof(TxCandidate_t);

	ThreadTxContainerList[TxContainerNo].TxCandidateList = (TxCandidate_t*)malloc( SizeOfListInBytes);
	memcpy(ThreadTxContainerList[TxContainerNo].TxCandidateList,CurrentTxCandidateListPtr,SizeOfListInBytes);
    }
// END OF  NEW ADDED CODE HARMANCI


    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].ID = ThreadDefNum;
    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].TxContainerList = ThreadTxContainerList;
    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].TxContainerNum  = SourceThreadDef ->TxContainerNum;
    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].CommitNum = 0;
    ((ThreadInfo_t*)(Dyn_ThreadDefArray.ArrayStartAddress))[ThreadDefNum].AbortNum  = 0;

    ThreadDefNum++; 
}




// From interface.h
void AddNewTxCanidate(dyn_arr_t* CurrentTxCandidateList, const char* CurrentTransactionName, double Percentage)
{

    unsigned SearchedTxID    = FindTxByName(CurrentTransactionName,TxDefArray,TxDefNum);
    unsigned TxCandidateNum  = CurrentTxCandidateList -> ArrayElementNum;
    Extend_DynamicArray(CurrentTxCandidateList,sizeof(TxCandidate_t));
    TxCandidate_t* AccessedCandidate = &(((TxCandidate_t*)(CurrentTxCandidateList -> ArrayStartAddress))[TxCandidateNum]);
    AccessedCandidate -> TxID       = SearchedTxID;
    AccessedCandidate -> Percentage = Percentage;
}



// From interface.h
void GenerateAndAttachContainersForForwardTxList(dyn_arr_t* CurrentTxList, unsigned RepetitionCount)
{
    if(VerboseParserOutput)
	printf("Calling GenerateAndAttachContainersForForwardTxList for %u repetition\n",RepetitionCount );


    unsigned TxListSize = CurrentTxList -> ArrayElementNum,
	     TxNo;

    
    
    for(TxNo=0; TxNo< TxListSize  ; TxNo++)
    {		  
	TxContainerInfo_t* CurrentTransactionInfo = &( ((TxContainerInfo_t*)(CurrentTxList -> ArrayStartAddress))[TxNo] );
	
	char* CurrentTransactionName = CurrentTransactionInfo -> TxName;
	if(VerboseParserOutput)
	    printf("\t%s", CurrentTransactionName );
	
//	unsigned SearchedTxID = FindTxByName(CurrentTransactionName,TxDefArray,TxDefNum);
	AddNewTxCanidate(&CurrentTxCandidateList, CurrentTransactionName, UNSPECIFIED_PERCENTAGE);



	ConnectionInfo_t ConnectionInfo[2];
	ConnectionInfo[0].Type = NEXT; 
	ConnectionInfo[0].BranchOffset = 1 ;
	if(TxNo == TxListSize-1 && RepetitionCount > 1)
	{

	    ConnectionInfo[1].Type = LOOP_BACK;
	    ConnectionInfo[1].BranchOffset =  - TxListSize + 1;
	    ConnectionInfo[1].IterationNum = RepetitionCount;
	    InsertTxContainerToThread(&CurrentTxContainerList,&CurrentTxCandidateList, ConnectionInfo, 2, CurrentTransactionInfo -> PrecedingDelay);
	}
	else if(TxNo == TxListSize-1 && RepetitionCount == 0)
	{
	    ConnectionInfo[0].BranchOffset = -TxListSize +1 ;
	    InsertTxContainerToThread(&CurrentTxContainerList,&CurrentTxCandidateList, ConnectionInfo, 1, CurrentTransactionInfo -> PrecedingDelay);
	}
	else
	{
	    InsertTxContainerToThread(&CurrentTxContainerList,&CurrentTxCandidateList, ConnectionInfo, 1, CurrentTransactionInfo -> PrecedingDelay);
	}
	
	Clear_DynamicArray(&CurrentTxCandidateList);
	
    }
    if(VerboseParserOutput)
	printf("\n");
    
    
    Clear_DynamicArray(CurrentTxList);
}



unsigned FindTxByName(const char* SearchedTransactionName, const TxInfo_t* TxDefArray, unsigned TxDefNum)
{
    unsigned SearchedTxID = TxDefNum;
    unsigned TxDefNo ;
    for(TxDefNo=0; TxDefNo< TxDefNum; TxDefNo++)
    {
	char* VisitedTxName = TxDefArray[TxDefNo].Name;
	bool SearchedTxFound = (strcmp(SearchedTransactionName,VisitedTxName) == 0);
	if( SearchedTxFound ) 
	{
	    SearchedTxID = TxDefNo;
	    break;
	}
    }
    return SearchedTxID ; 
    
}


unsigned FindThreadByName(const char* SearchedThreadName, const ThreadInfo_t* ThreadDefArray, unsigned ThreadDefNum)
{
    unsigned SearchedThreadID = ThreadDefNum;
    unsigned ThreadDefNo ;
    for(ThreadDefNo=0; ThreadDefNo< ThreadDefNum; ThreadDefNo++)
    {
	char* VisitedThreadName = ThreadDefArray[ThreadDefNo].Name;
	bool SearchedThreadFound = (strcmp(SearchedThreadName,VisitedThreadName) == 0);
	if( SearchedThreadFound ) 
	{
	    SearchedThreadID = ThreadDefNo;
	    break;
	}
    }
    return SearchedThreadID ; 
    
}


void InsertTxContainerToThread(dyn_arr_t* CurrentTxContainerList, const dyn_arr_t* CurrentTxCandidateList, ConnectionInfo_t* ConnectionInfo, unsigned ConnectionNum, unsigned* PrecedingDelayPair)
{
    assert(CurrentTxContainerList != NULL);
    assert(CurrentTxCandidateList != NULL);
    assert(ConnectionInfo != NULL);
    assert(PrecedingDelayPair != NULL);

    unsigned AddedContainerPos = AddNewContainerToThread(CurrentTxContainerList);
    TxContainer_t* CurrentTxContainer = &(((TxContainer_t*)(CurrentTxContainerList -> ArrayStartAddress))[AddedContainerPos]);
    InsertTxCandidateListInContainer(CurrentTxCandidateList, CurrentTxContainer);
    
    unsigned  ConnectionNo;
    for( ConnectionNo=0;  ConnectionNo<  ConnectionNum;  ConnectionNo++)
    {
	ConnectionInfo_t* CurrentInfo = &(ConnectionInfo[ConnectionNo]);
	if(CurrentInfo -> Type == NEXT)
	    InsertBranchAmongTxContainers(CurrentTxContainerList, AddedContainerPos, AddedContainerPos + CurrentInfo -> BranchOffset, NEXT, 0);
	else if(CurrentInfo -> Type == LOOP_BACK)
	    InsertBranchAmongTxContainers(CurrentTxContainerList, AddedContainerPos, AddedContainerPos + CurrentInfo -> BranchOffset , LOOP_BACK, CurrentInfo -> IterationNum);
	else
	{
	    printf("ERROR: UNKNOWN CONNECTION TYPE AMONG CONTAINERS.");
	    assert(0);
	}
	
    }

    CurrentTxContainer-> PrecedingDelay[0] = PrecedingDelayPair[0];

}



void InsertTxCandidateListInContainer(const dyn_arr_t* CurrentTxCandidateList, TxContainer_t* CurrentTxContainer)
{
    
    assert(CurrentTxCandidateList != NULL);
    assert(CurrentTxContainer     != NULL);
    
    unsigned CandidateTxListSize = CurrentTxCandidateList -> ArrayElementNum;
    unsigned CandidateListSizeInMemory = CandidateTxListSize * sizeof(TxCandidate_t) ;
    CurrentTxContainer -> TxCandidateList = (TxCandidate_t*)malloc(CandidateListSizeInMemory);
    CurrentTxContainer -> CandidateTxNum  = CandidateTxListSize;
    
     unsigned  CandidateNo; 


     // Find out whether all candidates were specified. Calculate also the sum
     // of the specified percentages.
     double SpecifiedPercentageSum = 0.0;
     bool AllCandidatesSpecified= TRUE;
     unsigned UnspecifiedCandidateNum = 0;
     for(CandidateNo=0 ;  CandidateNo < CandidateTxListSize  ; CandidateNo++)
     {		
	 double   CandidatePercentage = (((TxCandidate_t*)(CurrentTxCandidateList -> ArrayStartAddress))[CandidateNo]).Percentage;
	 bool     CandidateSpecified  = !( CandidatePercentage ==  UNSPECIFIED_PERCENTAGE);
	 if( CandidateSpecified )
	 {
	     SpecifiedPercentageSum += CandidatePercentage ;
	 }
	 else
	 {
	     UnspecifiedCandidateNum++;
	     AllCandidatesSpecified = FALSE;
	 }
     }
     

     double UnspecifiedCandidatePercentage;
     if( AllCandidatesSpecified )	 
     {
	 // If all candidates are specified check whether the sum of the
	 // percentages sum up to 100%
	 double ErrorMargin=DBL_MIN;
	 bool PercentageSumConsistent = ( 100.0 - ErrorMargin <= SpecifiedPercentageSum  && SpecifiedPercentageSum <= 100.0 + ErrorMargin );
	 if(!PercentageSumConsistent)
	 {
	     REPORT_SEMANTIC_ERROR("Percentage sum of specified transaction candidates does not sum up to 100%%\n");
	 }
     }
     else
     {
	 // If  all  candidates  are  not specified,  divide  the  unspecified
	 // percentage equitably
	 assert(UnspecifiedCandidateNum > 0);
	 
	 double UnspecifiedPercentageSum  = 100.0 - SpecifiedPercentageSum;
	 UnspecifiedCandidatePercentage  = (double)((double)UnspecifiedPercentageSum/(double)UnspecifiedCandidateNum);
     }	 
	 
     // Filling up the TxCandidateList of CurrentTxContainer.
     // The  order  of  Candidate  List  is  the same  with  the  order  of
     // candidates written in the config file. So there is no need assign a
     // different  index for  the Containers.  The index  of  Candidates in
     // CurrentTxCandidateList is the same as the index of containers.
     for(CandidateNo=0 ;  CandidateNo < CandidateTxListSize  ; CandidateNo++)
     {		
	 TxCandidate_t* CurrentCandidateTxListElement = &(((TxCandidate_t*)(CurrentTxCandidateList->ArrayStartAddress))[CandidateNo]);
	 
	 double   CandidatePercentage = CurrentCandidateTxListElement -> Percentage;
	 bool     CandidateSpecified  = !( CandidatePercentage ==  UNSPECIFIED_PERCENTAGE);
	 
	 (CurrentTxContainer -> TxCandidateList)[CandidateNo].TxID       = CurrentCandidateTxListElement -> TxID;  

	 // If percentage  is not  specified assign the  calculated percentage
	 // for unspecified candidates (otherwise assign specified percentage)
	 if( CandidateSpecified) 
	     (CurrentTxContainer -> TxCandidateList)[CandidateNo].Percentage = CurrentCandidateTxListElement -> Percentage; 
	 else
	     (CurrentTxContainer -> TxCandidateList)[CandidateNo].Percentage = UnspecifiedCandidatePercentage; 
     }
     
}




unsigned AddNewContainerToThread(dyn_arr_t* TargetTxContainerList)
{
    unsigned TxContainerNum = TargetTxContainerList -> ArrayElementNum ;
    Extend_DynamicArray(TargetTxContainerList,sizeof(TxContainer_t));
    
    TxContainer_t* CurrentContainer = &(((TxContainer_t*)(TargetTxContainerList -> ArrayStartAddress))[TxContainerNum]);
    
    MakeTxContainerDefault(CurrentContainer);
    return TxContainerNum;
}




void MakeTxContainerDefault(TxContainer_t* TargetContainer)
{
    //HARMANCI: CODE ADDED FOR VARIABLE EXPR WITHIN THREAD DEF
    TargetContainer -> LoopEndNodeWithVarExpr = FALSE;
    TargetContainer -> LoopLimitExprPos       = 0 ;       
    // END OF CODE ADDED FOR VARIABLE EXPR WITHIN THREAD DEF

    TargetContainer -> TxCandidateList          = NULL; 
    TargetContainer -> CandidateTxNum           = 0;
    TargetContainer -> InitialRepetitionCount   = 0;
    TargetContainer -> RepetitionCount          = 0;
    TargetContainer -> NextContainerID[0]       = 0;
    TargetContainer -> NextContainerID[1]       = 0;
    TargetContainer -> CandidateSeed            = 0;
    TargetContainer -> CandidateSelectionFunc   = NULL;
}





void InsertBranchAmongTxContainers(dyn_arr_t* CurrentTxContainerList, unsigned FromContainerPos,unsigned ToContainerPos,Branch_t BranchType, int IterationNum)
{
    TxContainer_t* FromContainer = &(((TxContainer_t*)(CurrentTxContainerList -> ArrayStartAddress))[FromContainerPos]) ;
    FromContainer -> NextContainerID[BranchType] = ToContainerPos;
    FromContainer -> InitialRepetitionCount = IterationNum;
    FromContainer -> RepetitionCount        = IterationNum;
    FromContainer -> LoopStartNode          = FALSE;

    if(VerboseParserOutput)
	printf("NextContainerID[0]= %u\n",FromContainer -> NextContainerID[0]);
}


//HARMANCI: FUNCTION ADDED FOR VARIABLE EXPR WITHIN THREAD DEF
void InsertVarExprBranchAmongTxContainers(dyn_arr_t* CurrentTxContainerList, unsigned FromContainerPos,unsigned ToContainerPos,Branch_t BranchType, int LoopLimitExprPos)
{
    TxContainer_t* FromContainer = &(((TxContainer_t*)(CurrentTxContainerList -> ArrayStartAddress))[FromContainerPos]) ;
    FromContainer -> NextContainerID[BranchType] = ToContainerPos;
    FromContainer -> LoopEndNodeWithVarExpr = TRUE;
    FromContainer -> LoopLimitExprPos       = LoopLimitExprPos;
    FromContainer -> LoopStartNode          = FALSE;

    if(VerboseParserOutput)
	printf("NextContainerID[0]= %u\n",FromContainer -> NextContainerID[0]);
}






void GenerateAndAttachNewContainerForSimpleTxBlock(const char* CurrentTransactionName, bool* DelayOpEncountered,  unsigned CurrentDelayVal)
{
    if(VerboseParserOutput)
	printf("Calling GenerateAndAttachNewContainerForSimpleTxBlock\n");
    
    unsigned PrecedingDelayPair[2];
    
    if( *DelayOpEncountered )
    {
	PrecedingDelayPair[0] = CurrentDelayVal;
	*DelayOpEncountered = FALSE;
    }
    else
    {
	PrecedingDelayPair[0] = 0;
    }
    PrecedingDelayPair[1] = 0;
    

//    unsigned SearchedTxID = FindTxByName(CurrentTransactionName,TxDefArray,TxDefNum);
    AddNewTxCanidate(&CurrentTxCandidateList, CurrentTransactionName, UNSPECIFIED_PERCENTAGE);
    

    ConnectionInfo_t ConnectionInfo;
    ConnectionInfo.Type = NEXT; 
    ConnectionInfo.BranchOffset = 1 ;
    InsertTxContainerToThread(&CurrentTxContainerList,&CurrentTxCandidateList, &ConnectionInfo, 1, PrecedingDelayPair);
    
    Clear_DynamicArray(&CurrentTxCandidateList);
    
}




void GenerateAndAttachNewContainerForTxChoiceList(const dyn_arr_t* CurrentTxCandidateList, unsigned RepetitionCount, bool* DelayOpEncountered,  unsigned CurrentDelayVal)
{
    if(VerboseParserOutput)
	printf("GenerateAndAttachNewContainerForTxChoiceList for %u repetition.\n", RepetitionCount); 

    unsigned PrecedingDelayPair[2];
    
    if( *DelayOpEncountered )
    {
	PrecedingDelayPair[0] = CurrentDelayVal;
	*DelayOpEncountered = FALSE;
    }
    else
    {
	PrecedingDelayPair[0] = 0;
    }
    PrecedingDelayPair[1] = 0;
    

    ConnectionInfo_t ConnectionInfo[2];
    ConnectionInfo[0].Type = NEXT ;
    ConnectionInfo[0].BranchOffset = 1 ;
    if( RepetitionCount > 1)
    {
	ConnectionInfo[1].Type = LOOP_BACK;
	ConnectionInfo[1].BranchOffset = 0 ;
	ConnectionInfo[1].IterationNum = RepetitionCount  ;
	InsertTxContainerToThread(&CurrentTxContainerList,CurrentTxCandidateList, ConnectionInfo, 2, PrecedingDelayPair);
    }
    else if( RepetitionCount == 0)
    {
	ConnectionInfo[0].BranchOffset = 0 ;
	InsertTxContainerToThread(&CurrentTxContainerList,CurrentTxCandidateList, ConnectionInfo, 1, PrecedingDelayPair);
    }
    else
	InsertTxContainerToThread(&CurrentTxContainerList,CurrentTxCandidateList, ConnectionInfo, 1, PrecedingDelayPair);

    
    TxContainer_t* CurrentTxContainer = &(((TxContainer_t*)(CurrentTxContainerList.ArrayStartAddress))[CurrentTxContainerList.ArrayElementNum -1]);
    unsigned CandidateTxListSize = CurrentTxCandidateList -> ArrayElementNum;
    
    bool UniformSelection = TRUE;
    unsigned  CandidateNo;
    for(CandidateNo=0;  CandidateNo <  CurrentTxContainer -> CandidateTxNum ; CandidateNo++)
    {
	TxCandidate_t* CurrentCandidate = &((CurrentTxContainer -> TxCandidateList)[CandidateNo]);
	unsigned       CurrentCandidatePercentage = CurrentCandidate -> Percentage;
	bool PercentageConformsUniformDist =  (CurrentCandidatePercentage == 100/CandidateTxListSize);
	if( !PercentageConformsUniformDist )
	{
	    UniformSelection = FALSE;
	    break;
	}
    }
    
    if(UniformSelection)
    {
	if(VerboseParserOutput)
	    printf("Uniform distributed candidate list. Setting UniformDistNextTx as Random function.\n");

	CurrentTxContainer -> CandidateSelectionFunc = UniformDistNextTx;
    }
    else
    {
	if(VerboseParserOutput)
	    printf("NOT Uniform distributed candidate list. Setting PercentageDistNextTx as Random function.\n");
	CurrentTxContainer -> CandidateSelectionFunc = PercentageDistNextTx;
    }


    
    if(VerboseParserOutput)
    {
	printf("CurrentCandidate list is:\n");
	for(CandidateNo=0;  CandidateNo <  CurrentTxContainer -> CandidateTxNum ; CandidateNo++)
	{
	    TxCandidate_t* CurrentCandidate = &((CurrentTxContainer -> TxCandidateList)[CandidateNo]);
	    printf("\t%u\t%.12f\n",  CurrentCandidate ->TxID,CurrentCandidate-> Percentage);  
	}
    }
    
}






// HARMANCI RANDOM
unsigned UniformDistNextTx(TxContainer_t* CurrentTxContainer)
{
    assert(CurrentTxContainer != NULL) ;
    unsigned  CandidateNum = CurrentTxContainer ->CandidateTxNum ;
    unsigned* Seed        = &(CurrentTxContainer -> CandidateSeed);
    unsigned  ChosenElementNo =  (unsigned)((double)CandidateNum * (double)((double)RAND_R(Seed)/(double)(RAND_MAX_VAL + 1.0))) ;
    return ChosenElementNo;
}

// HARMANCI RANDOM
unsigned  PercentageDistNextTx(TxContainer_t* CurrentTxContainer)
{
    assert(CurrentTxContainer != NULL) ;
    unsigned  CandidateNum = CurrentTxContainer ->CandidateTxNum ;
    unsigned* Seed        = &(CurrentTxContainer -> CandidateSeed);

    double SelectedPosInHundredScale = (double)100 * (double)((double)RAND_R(Seed)/(double)(RAND_MAX_VAL + 1.0));

    unsigned CandidateNo;
    unsigned SelectedCandidate = CandidateNum;
    double   CurrentRegionUpperLimit = 0 ;
    for(CandidateNo=0; CandidateNo< CandidateNum; CandidateNo++)
    {
	double CurrentPercentageValue = (double)(CurrentTxContainer -> TxCandidateList[CandidateNo]).Percentage;
	CurrentRegionUpperLimit += CurrentPercentageValue;
	if( CandidateNo == CandidateNum-1)
	    CurrentRegionUpperLimit = 100.0;
	bool SelectedPosInCurrentRegion = (SelectedPosInHundredScale < CurrentRegionUpperLimit );
	if( SelectedPosInCurrentRegion )
	{
	    SelectedCandidate = CandidateNo;
	    break;
	}
    }
    assert( SelectedCandidate < CandidateNum);
    return SelectedCandidate;
}


#endif
