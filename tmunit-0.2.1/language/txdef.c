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

#include "txdef.h"


void TX_INFO_Initialize(TxInfo_t* Target)
{
    Target -> Name = NULL;

    Target -> TxDefOptionNum = 0;
    Target -> TxOpList = NULL ;
    Target -> TxOpNum  = NULL ; 
    Target -> OptionConditionID = NULL;
    Target -> OutputVariableList = NULL ;
    Target -> OutputCalculationList = NULL ;


    Target -> VarListToUpdate = NULL ;
    Target -> VarToUpdateNum = 0;
    Target -> LoopIteratorAddrGenList = NULL; 
    Target -> LoopIteratorNum = 0;         
//    Target -> LoopIterationCountArray = NULL;
    Target -> LoopEndTxOpList = NULL;
    Target -> LoopEndTxOpNum = 0;          

    Target -> ReadOnly = 0;
    Target -> CommitNum = 0;
    Target -> AbortNum = 0;
    Target -> CurrentRetryNum = 0;
    Target -> MaxRetryNum = 0;
    Target -> InherentDelay = INVALID_DELAY;
}

void TX_INFO_Finalize(TxInfo_t* Target)
{

    free(Target -> Name);

    unsigned OptionNo;
    for(OptionNo=0; OptionNo < Target ->TxDefOptionNum; OptionNo++)
    {
	free(Target -> TxOpList[OptionNo]);
    }
    free(Target -> TxOpList);

    free(Target -> TxOpNum) ; 
    free(Target -> OptionConditionID);
    free(Target -> OutputVariableList) ;
    free(Target -> OutputCalculationList) ;


    free(Target -> VarListToUpdate) ;
    free(Target -> LoopIteratorAddrGenList); 
//    free(Target -> LoopIterationCountArray);
    free(Target -> LoopEndTxOpList);
    
}

void TX_INFO_Copy(const TxInfo_t* Source, TxInfo_t*Target)
{
    unsigned CopySizeInMemory = sizeof(TxInfo_t);
    memcpy(Target,Source,CopySizeInMemory);


    Target -> Name = strdup(Source->Name);

    
    CopySizeInMemory = (Source ->TxDefOptionNum)*sizeof(unsigned) ;
    Target -> TxOpNum  =  (unsigned*)malloc(CopySizeInMemory);
    memcpy(Target -> TxOpNum, Source -> TxOpNum,CopySizeInMemory);
    
    Target -> TxOpList =  (TxOpContainer_t**) malloc( (Source ->TxDefOptionNum)*sizeof(TxOpContainer_t*) ) ;
    unsigned OptionNo;
    for(OptionNo=0; OptionNo < Source -> TxDefOptionNum; OptionNo++)
    {
	unsigned TxOpNum = Target -> TxOpNum[OptionNo] ;
	CopySizeInMemory = TxOpNum * sizeof(TxOpContainer_t) ;
	Target -> TxOpList[OptionNo]  =  (TxOpContainer_t*)malloc(CopySizeInMemory);

	unsigned TxOpNo;
	for (TxOpNo=0; TxOpNo< TxOpNum ; TxOpNo++)
	{
	    TxOpContainer_t* SourceContainer = &( Source->TxOpList[OptionNo][TxOpNo] ) ;
	    TxOpContainer_t* TargetContainer = &( Target->TxOpList[OptionNo][TxOpNo] );
	    TX_OP_CONTAINER_Copy( SourceContainer, TargetContainer);	
	}

    }

    CopySizeInMemory = (Source ->TxDefOptionNum)*sizeof(unsigned) ;
    if( Source -> OptionConditionID != NULL)
    {
	Target -> OptionConditionID = (int*)malloc(CopySizeInMemory);
	memcpy(Target -> OptionConditionID, Source -> OptionConditionID,CopySizeInMemory);
    }

    if( Source -> OutputVariableList != NULL)
    {
	Target -> OutputVariableList = (int*)malloc(CopySizeInMemory);
	memcpy(Target -> OutputVariableList, Source -> OutputVariableList,CopySizeInMemory);
    }
    
    if( Source -> OutputCalculationList != NULL)
    {
	Target -> OutputCalculationList = (int*)malloc(CopySizeInMemory);
	memcpy(Target -> OutputCalculationList, Source -> OutputCalculationList,CopySizeInMemory);
    }


    CopySizeInMemory = (Target -> VarToUpdateNum)*sizeof(unsigned) ;
    Target -> VarListToUpdate = (unsigned*)malloc(CopySizeInMemory);
    memcpy(Target -> VarListToUpdate,Source -> VarListToUpdate,CopySizeInMemory);

    CopySizeInMemory = (Target -> LoopIteratorNum)*sizeof(unsigned) ;
    Target -> LoopIteratorAddrGenList = (unsigned*)malloc(CopySizeInMemory);
    memcpy(Target -> LoopIteratorAddrGenList,Source -> LoopIteratorAddrGenList,CopySizeInMemory);

    CopySizeInMemory = (Target -> LoopEndTxOpNum)*sizeof(unsigned) ;
//    Target -> LoopIterationCountArray = (unsigned*)malloc(CopySizeInMemory);
//    memcpy(Target -> LoopIterationCountArray,Source -> LoopIterationCountArray,CopySizeInMemory);

    Target -> LoopEndTxOpList = (unsigned*)malloc(CopySizeInMemory);
    memcpy(Target -> LoopEndTxOpList,Source -> LoopEndTxOpList,CopySizeInMemory);

}



void TX_INFO_Print(const TxInfo_t* Target)
{

    char* TxOpNumList;
    char* OptionConditionIDList;
    char* OutputVariableList;
    char* OutputCalculationList ;
    char* AddrGenToUpdateList;
    char* LoopIteratorAddrGenList;
//    char* LoopIterationCountArray;
    char* LoopEndTxOpList;




    GenereateUnsignedListOutput(Target -> TxOpNum, Target -> TxDefOptionNum,&TxOpNumList);
    GenereateIntegerListOutput(Target -> OptionConditionID,Target -> TxDefOptionNum,&OptionConditionIDList);
    GenereateIntegerListOutput(Target -> OutputVariableList,Target -> TxDefOptionNum,&OutputVariableList);
    GenereateIntegerListOutput(Target -> OutputCalculationList,Target -> TxDefOptionNum,&OutputCalculationList);

    GenereateUnsignedListOutput(Target -> VarListToUpdate,Target -> VarToUpdateNum,&AddrGenToUpdateList);
    GenereateUnsignedListOutput(Target -> LoopIteratorAddrGenList,Target ->  LoopIteratorNum,&LoopIteratorAddrGenList);
//    GenereateUnsignedListOutput(Target -> LoopIterationCountArray,Target ->  LoopIteratorNum,&LoopIterationCountArray);
    GenereateUnsignedListOutput(Target -> LoopEndTxOpList ,Target ->  LoopEndTxOpNum,&LoopEndTxOpList);

    printf("Name(%p): %s\n"
	   "OptionNum : %u\n"
	   "TxOpNumlist(%p)\t\t: %s\n"
  	   "OptionConditionIDList(%p)\t: %s\n"
	  "OutputVariableList(%p)\t: %s\n"
	  "OutputCalculationList(%p)\t: %s\n"
	  "AddrGenToUpdateList(%p)\t: %s\n"
	  "LoopIteratorAddrGenList(%p)\t: %s\n"
//	  "LoopIterationCountArray(%p)\t: %s\n"
	   "LoopEndTxOpList(%p)\t: %s\n"
	   "ReadOnly  : %u\n"
	   "CommitNum : %lu\n"
	   "AbortNum  : %lu\n"
	   "CurrentRetryNum: %lu\n"
	   "MaxRetryNum: %lu\n"
	   "InherentDelay : %lu\n",
	   Target -> Name, Target -> Name, 	 \
	   Target -> TxDefOptionNum,		 \
	   Target ->TxOpNum, TxOpNumList, 	 \
	   Target -> OptionConditionID,     OptionConditionIDList , 	\
	   Target -> OutputVariableList,    OutputVariableList   ,      \
	   Target -> OutputCalculationList, OutputCalculationList ,     \
	   Target -> VarListToUpdate,   AddrGenToUpdateList   ,     \
	   Target -> LoopIteratorAddrGenList, LoopIteratorAddrGenList, 	\
/*	   Target -> LoopIterationCountArray, LoopIterationCountArray, 	\*/
	   Target -> LoopEndTxOpList,         LoopEndTxOpList,          \
	   Target -> ReadOnly,        \
	   Target -> CommitNum,       \
	   Target -> AbortNum,        \
	   Target -> CurrentRetryNum, \
	   Target -> MaxRetryNum,     \
	   Target -> InherentDelay    \
	);

    
    if( Target -> TxDefOptionNum == 0 )
    {
	printf("TxOpList: EMPTY\n");
    }
    else
    {
	unsigned OptionNo;
	for(OptionNo=0; OptionNo < Target -> TxDefOptionNum; OptionNo++)
	{
	    printf("----- TxOpList[%u] -----\n",OptionNo);
	    
	    unsigned TxOpNum = Target -> TxOpNum[OptionNo] ;
	    unsigned TxOpNo;
	    for (TxOpNo=0; TxOpNo< TxOpNum ; TxOpNo++)
	    {
		TxOpContainer_t* CurrentTxOpContainer = &((Target -> TxOpList)[OptionNo][TxOpNo]);
		printf("(@ %p):\n",CurrentTxOpContainer);
		TX_OP_CONTAINER_Print(CurrentTxOpContainer) ;
		printf("\n");
	    }
	    printf("\n\n");
	    
	}
    }
    
}

    


/* int main() */
/* { */

/*     TxInfo_t Tested_TxDef; */
/*     TX_INFO_Initialize(&Tested_TxDef); */
/*     TX_INFO_Print(&Tested_TxDef); */
/*     printf("\n\n"); */

/*     Tested_TxDef.Name = strdup("TestedTxDef"); */
    
/*     unsigned ConditionNum = 3;     */
/*     unsigned Array[ConditionNum]; */
/*     int      IntArray[ConditionNum]; */
/*     unsigned CopySizeInMemory = ConditionNum*sizeof(unsigned); */

/*     Tested_TxDef.TxDefOptionNum = ConditionNum; */

/*     Array[0] = 1;     Array[1] = 2;       Array[2] = 3; 	 */
/*     Tested_TxDef.TxOpNum = (unsigned*)malloc(CopySizeInMemory); */
/*     memcpy(Tested_TxDef.TxOpNum, Array, CopySizeInMemory); */


/*     IntArray[0] = 4;     IntArray[1] = 5;       IntArray[2] = 6; 	 */
/*     Tested_TxDef.OptionConditionID = (int*)malloc(CopySizeInMemory); */
/*     memcpy(Tested_TxDef.OptionConditionID, IntArray, CopySizeInMemory); */


/*     IntArray[0] = 7;     IntArray[1] = 8;       IntArray[2] = 9; 	 */
/*     Tested_TxDef.OutputVariableList = (int*)malloc(CopySizeInMemory); */
/*     memcpy(Tested_TxDef.OutputVariableList, IntArray, CopySizeInMemory); */


/*     IntArray[0] = 10;     IntArray[1] = 11;       IntArray[2] = 12; 	 */
/*     Tested_TxDef.OutputCalculationList = (int*)malloc(CopySizeInMemory); */
/*     memcpy(Tested_TxDef.OutputCalculationList, IntArray, CopySizeInMemory); */
 	
 	

/*     Tested_TxDef.VarToUpdateNum = 1; */
/*     Array[0] = 13;  */
/*     CopySizeInMemory = (Tested_TxDef.VarToUpdateNum)*sizeof(unsigned); */
/*     Tested_TxDef.VarListToUpdate = (unsigned*)malloc(CopySizeInMemory); */
/*     memcpy(Tested_TxDef.VarListToUpdate,Array, CopySizeInMemory); */


/*     Tested_TxDef.LoopIteratorNum = 2; */
/*     Array[0] = 14;     Array[1] = 15;  */
/*     CopySizeInMemory = (Tested_TxDef.LoopIteratorNum)*sizeof(unsigned); */
/*     Tested_TxDef.LoopIteratorAddrGenList = (unsigned*)malloc(CopySizeInMemory); */
/*     memcpy(Tested_TxDef.LoopIteratorAddrGenList,Array, CopySizeInMemory); */


/*     Array[0] = 16;     Array[1] = 17;  */
/*     Tested_TxDef.LoopIterationCountArray = (unsigned*)malloc(CopySizeInMemory); */
/*     memcpy(Tested_TxDef.LoopIterationCountArray,Array, CopySizeInMemory); */

/*     Tested_TxDef.LoopEndTxOpNum = 3; */
/*     Array[0] = 18;     Array[1] = 19;       Array[2] = 20; 	 */
/*     CopySizeInMemory = (Tested_TxDef.LoopEndTxOpNum)*sizeof(unsigned); */
/*     Tested_TxDef.LoopEndTxOpList = (unsigned*)malloc(CopySizeInMemory); */
/*     memcpy(Tested_TxDef.LoopEndTxOpList,Array, CopySizeInMemory); */

/*     Tested_TxDef.ReadOnly = 1; */
/*     Tested_TxDef.CommitNum = 100; */
/*     Tested_TxDef.AbortNum  = 200; */
/*     Tested_TxDef.InherentDelay = 50; */



/*     Tested_TxDef.TxOpList =  (TxOpContainer_t**) malloc( Tested_TxDef.TxDefOptionNum * sizeof(TxOpContainer_t*) ) ; */
/*     unsigned TxOpCounter = 0; */
/*     unsigned OptionNo; */
/*     for(OptionNo=0; OptionNo < Tested_TxDef.TxDefOptionNum; OptionNo++) */
/*     { */
/* 	unsigned TxOpNum = Tested_TxDef.TxOpNum[OptionNo]; */
/* 	CopySizeInMemory = TxOpNum * sizeof(TxOpContainer_t) ; */
/* 	Tested_TxDef.TxOpList[OptionNo]  =  (TxOpContainer_t*)malloc(CopySizeInMemory); */
	
/* 	unsigned TxOpNo; */
/* 	for (TxOpNo=0; TxOpNo< TxOpNum ; TxOpNo++) */
/* 	{ */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].PrecedingDelay = 1 + (TxOpCounter*10); */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].DelayBeforeCommit = 2 + (TxOpCounter*10); */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].AccessedAddrGenID[0] = 3 + (TxOpCounter*10); */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].AccessedAddrGenID[1] = 4 + (TxOpCounter*10); */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].TxOperation = READ + TxOpCounter%(WRITE-READ+1); */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].AddrOp = PLUS + TxOpCounter%(MULTIPLY-PLUS+1) ; */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].NextContainerID[0] = 5 + (TxOpCounter*10); */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].NextContainerID[1] = 6 + (TxOpCounter*10); */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].RepetitionCount = 7 + (TxOpCounter*10); */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].InitialRepetitionCount = 8 + (TxOpCounter*10); */
/* 	    Tested_TxDef.TxOpList[OptionNo][TxOpNo].LoopIteratorAddrGenID  = 9 + (TxOpCounter*10); */
/* 	    TxOpCounter ++; */
/* 	}        */
	
/*     } */



/*     TX_INFO_Print(&Tested_TxDef); */
/*     printf("\n\n"); */


/*     TxInfo_t Copied_TxDef; */
/*     TX_INFO_Initialize( &Copied_TxDef ); */
/*     TX_INFO_Print(&Copied_TxDef); */
/*     printf("\n\n"); */

/*     TX_INFO_Copy( &Tested_TxDef, &Copied_TxDef ); */
/*     TX_INFO_Print(&Copied_TxDef); */
/*     printf("\n\n"); */


/*     TX_INFO_Finalize(&Tested_TxDef); */
/*     TX_INFO_Finalize(&Copied_TxDef); */


/*     return 0; */
/* } */
