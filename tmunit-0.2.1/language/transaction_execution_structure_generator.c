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


#ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION


#include "transaction_execution_structure_generator.h"
dyn_arr_t CurrentTxOpList;
dyn_arr_t ConditionTerminationTxOpList ;
bool EndOfIfElseBlock;
dyn_arr_t Dyn_VarAssignList;
dyn_arr_t Dyn_VarExprToUpdateList;


int InitializeTempTransactionStructuresUsedInParsing()
{
    Initialize_DynamicArray(&CurrentTxOpList);
    Initialize_DynamicArray(&ConditionTerminationTxOpList);
    EndOfIfElseBlock = FALSE;
    Initialize_DynamicArray(&Dyn_VarAssignList);
    Initialize_DynamicArray(&Dyn_VarExprToUpdateList);

    return 0;
}


void ExtendVarExprToUpdate(const char* VarExprString)
{

    VarExpr* CurrentVarExpr;
    unsigned CurrentVarExprID = FindVarExpr(VarExprString,&CurrentVarExpr);
    assert(CurrentVarExpr!=NULL);

    bool AssociatedVarExprRequiresUpdate   = ( CurrentVarExpr -> Type == OP_RANDOM_DIST ) ||  ( CurrentVarExpr -> Type == OP_RANDOM_DIST_CONSTANT ) ;
    if( AssociatedVarExprRequiresUpdate ) 
    {
	// See whether the Addr is already in the CurrentVarExprToUpdateList
	unsigned VarExprNum = GetSize_DynamicArray(&Dyn_VarExprToUpdateList);
	unsigned VarExprNo ;
	bool SearchedIDFound = FALSE;
	for(VarExprNo=0; VarExprNo< VarExprNum; VarExprNo++) 
	{ 
	    unsigned* VarExprIDRequiringUpdate = GetElement_DynamicArray( &Dyn_VarExprToUpdateList, VarExprNo, sizeof(unsigned));
	    SearchedIDFound =  (*VarExprIDRequiringUpdate == CurrentVarExprID); 
	    if(SearchedIDFound) 
		break; 
	} 
	
	// if not in CurrentAddrGenToUpdateList then add it to this list
	if( !SearchedIDFound ) 
	{
	    Extend_DynamicArray(&Dyn_VarExprToUpdateList, sizeof(unsigned)); 
	    unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VarExprToUpdateList) -1 ;
	    unsigned*  CurrentElement = GetElement_DynamicArray( &Dyn_VarExprToUpdateList, LastElementPos, sizeof(unsigned));
	    *CurrentElement = CurrentVarExprID; 
	}
    }
    
    return;
}





void TxOp_SetInfo(TxOpContainer_t* TargetOpContainer, TxOpInfo_t* GivenOpInfo)
{
    assert(TargetOpContainer);
    assert(GivenOpInfo);
    TargetOpContainer -> PrecedingDelay    = GivenOpInfo -> Delay;
    TargetOpContainer -> TxOperation       = GivenOpInfo -> Op;
    TargetOpContainer -> AddrOp            = GivenOpInfo -> AddrOp;
//    TargetOpContainer -> AccessedAddrGenID = GivenOpInfo -> AddrGenIDList[0];
    TargetOpContainer -> AccessedAddrGenID[0] = GivenOpInfo -> AddrGenIDList[0];
    TargetOpContainer -> AccessedAddrGenID[1] = GivenOpInfo -> AddrGenIDList[1];


/*     TargetOpContainer -> AccessedAddrGenIDNum   = GivenOpInfo -> AddrGenIDNum; */
/*     unsigned AddrGenIDListSizeInMemory = (GivenOpInfo -> AddrGenIDNum)*sizeof(unsigned); */
/*     TargetOpContainer -> AccessedAddrGenIDList  = (unsigned*)malloc(AddrGenIDListSizeInMemory) ; */
/*     memcpy(TargetOpContainer -> AccessedAddrGenIDList, GivenOpInfo -> AddrGenIDList, AddrGenIDListSizeInMemory); */
}


void GenerateAndAttachNewContainerForSingleTxOp(dyn_arr_t* CurrentTxOpContainerList,TxOpInfo_t* GivenOpInfo) 
{ 
//    printf("Calling GenerateAndAttachNewContainerForSingleTxOp\n"); 

/*     unsigned SearchedTxID = FindTxByName(CurrentTransactionName,TxDefArray,TxDefNum);  */
/*     AddNewTxCanidate(&CurrentTxCandidateList, SearchedTxID, UNSPECIFIED_PERCENTAGE);  */
 
/*     ConnectionInfo_t ConnectionInfo;  */
/*     ConnectionInfo.Type = NEXT;   */
/*     ConnectionInfo.BranchOffset = 1 ;  */
/*     InsertTxContainerToThread(&CurrentTxContainerList,&CurrentTxCandidateList, &ConnectionInfo, 1);  */
 
/*     ClearArray(&CurrentTxCandidateList);  */
 

    ConnectionInfo_t ConnectionInfo;       
    ConnectionInfo.Type = NEXT;   
    ConnectionInfo.BranchOffset = 1 ;  
    InsertTxOpContainerToTransaction(CurrentTxOpContainerList, GivenOpInfo, &ConnectionInfo, 1);  

} 


void InsertBranchAmongTxOpContainers(dyn_arr_t* CurrentTxOpContainerList, unsigned FromContainerPos,unsigned ToContainerPos,Branch_t BranchType, int IterationNum)
{
    TxOpContainer_t* FromContainer = &(((TxOpContainer_t*)(CurrentTxOpContainerList -> ArrayStartAddress))[FromContainerPos]) ;
    FromContainer -> NextContainerID[BranchType] = ToContainerPos;
    FromContainer -> InitialRepetitionCount = IterationNum;
    FromContainer -> RepetitionCount        = IterationNum;
//    printf("NextContainerID[0]= %u\n",FromContainer -> NextContainerID[0]);
}



 void InsertTxOpContainerToTransaction(dyn_arr_t* CurrentTxOpContainerList, TxOpInfo_t* OperationInfo, ConnectionInfo_t* ConnectionInfo, unsigned ConnectionNum) 
 { 
     assert(CurrentTxOpContainerList != NULL); 
     assert(ConnectionInfo != NULL); 

     unsigned AddedContainerPos = AddNewContainerToTransaction(CurrentTxOpContainerList); 
     TxOpContainer_t* CurrentTxOpContainer = &(((TxOpContainer_t*)(CurrentTxOpContainerList -> ArrayStartAddress))[AddedContainerPos]); 
     TxOp_SetInfo(CurrentTxOpContainer,OperationInfo);
  
     unsigned  ConnectionNo; 
     for( ConnectionNo=0;  ConnectionNo<  ConnectionNum;  ConnectionNo++) 
     { 
 	ConnectionInfo_t* CurrentInfo = &(ConnectionInfo[ConnectionNo]); 
 	if(CurrentInfo -> Type == NEXT) 
 	    InsertBranchAmongTxOpContainers(CurrentTxOpContainerList, AddedContainerPos, AddedContainerPos + CurrentInfo -> BranchOffset, NEXT, 0); 
 	else if(CurrentInfo -> Type == LOOP_BACK) 
 	    InsertBranchAmongTxOpContainers(CurrentTxOpContainerList, AddedContainerPos, AddedContainerPos + CurrentInfo -> BranchOffset , LOOP_BACK, CurrentInfo -> IterationNum); 
 	else 
 	{ 
 	    printf("ERROR: UNKNOWN CONNECTION TYPE AMONG CONTAINERS."); 
 	    assert(0); 
 	} 
	
     } 

    CurrentTxOpContainer-> DelayBeforeCommit = 0 ;
    CurrentTxOpContainer-> LoopIteratorAddrGenID = -1;
 } 


unsigned AddNewContainerToTransaction(dyn_arr_t* TargetTxOpContainerList)
{
    unsigned TxOpContainerNum = TargetTxOpContainerList -> ArrayElementNum ;
    Extend_DynamicArray(TargetTxOpContainerList,sizeof(TxOpContainer_t));
    TxOpContainer_t* CurrentOpContainer = (TxOpContainer_t*)GetElement_DynamicArray(TargetTxOpContainerList, TxOpContainerNum, sizeof(TxOpContainer_t));
    
    MakeTxOpContainerDefault(CurrentOpContainer);
    return TxOpContainerNum;
}


void MakeTxOpContainerDefault(TxOpContainer_t* TargetOpContainer)
{
    TX_OP_CONTAINER_Initialize(TargetOpContainer);
}


#endif
