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

#include "thread.h"

barrier_t barrier,
          termination_barrier;

unsigned long TerminateRequestedBySignal;
unsigned*  ThreadSeed;



// Variables rquired for tm interfaces, can be moved to another file
#if defined ( TL2 )

   __thread stm_tx_t* TxDesc=NULL;
   AO_t tx_id_counter =0 ;
   __thread sigjmp_buf* envPtr; 

#elif defined ( SWISS_TM ) || defined ( WSTM )
   __thread stm_tx_t* TxDesc = NULL;

#elif defined ( ENNALS ) // for example for tinySTM_new 
   __thread stm_tx_t* TxDesc = NULL;
   __thread ptst_t* ptst   = NULL;

#else  // for example for tinySTM_new 
   __thread stm_tx_t* TxDesc=(stm_tx_t*)0x1;

#endif



void* ThreadStart(void *Parameters)
{
  thread_input_t* ThreadParameters= (thread_input_t*)Parameters;
  unsigned ID = ThreadParameters-> thread_ID;
//  unsigned MaxTxNumToExecute = ThreadParameters -> MaxTxNumToExecute;
  unsigned int CurrentThreadSeed = ThreadParameters->  ThreadSeed ; 
  

  if(ExecuteSchedule)
  {
      ThreadDefArray[ID].BarrierSelf      = ThreadParameters -> ThreadBarrier;
      ThreadDefArray[ID].SchedulerBarrier = ThreadParameters -> SchedulerBarrier;
  }
  else
  {
      ThreadDefArray[ID].BarrierSelf      = NULL;
      ThreadDefArray[ID].SchedulerBarrier = NULL;
  }

  if(RandomDebug)
      printf("Generating Random variable seeds for Thread %u...\n",ID); 

    unsigned VarExprNum = ThreadDefArray[ID].VarExprNum; 
    unsigned VarExprNo;
    for (VarExprNo=0; VarExprNo< VarExprNum; VarExprNo++)
    {
	VarExpr* CurrentVarExpr =  &(ThreadDefArray[ID].VarExprList[VarExprNo]);
	bool VarExprIsRandomized = ((CurrentVarExpr -> Type == OP_RANDOM_DIST) ||  (CurrentVarExpr -> Type == OP_RANDOM_DIST_CONSTANT)) ;
	if( VarExprIsRandomized )
	{
	    CurrentVarExpr -> OperandID[2] = (unsigned) RAND_R(&CurrentThreadSeed);
	    if(RandomDebug)
		printf("Seed of %s: %u\n",CurrentVarExpr -> Name, CurrentVarExpr -> OperandID[2]);
	}
	    
    }

/*    unsigned AddrGenNo; */
/*    for(AddrGenNo=0; AddrGenNo< AddrGenNum; AddrGenNo++) */
/*    { */
/*        AddrGen_t*  CurrentAddrGen = &(ThreadDefArray[ID].ExplicitAddrGenList[AddrGenNo]); */
/*        bool AddrGenIsRandomized = (CurrentAddrGen -> NextAddrGeneratorFunc ==  RandomNextInRange); */
/*        if( AddrGenIsRandomized) */
/*        { */
/* 	   CurrentAddrGen -> Increment_or_Seed = (unsigned) RAND_R(&CurrentThreadSeed); */
/* 	   printf("%s:%u\n",CurrentAddrGen -> Name, CurrentAddrGen -> Increment_or_Seed); */
/*        } */
/*    } */

  if(RandomDebug)
      printf("Generating TxCandidate seeds for Thread %u...\n",ID); fflush(NULL);

   unsigned TxContainerNum = ThreadDefArray[ID].TxContainerNum; 
   unsigned TxContainerNo;
   for(TxContainerNo=0; TxContainerNo< TxContainerNum; TxContainerNo++)
   {
       TxContainer_t*  CurrentTxContainer = &(ThreadDefArray[ID].TxContainerList[TxContainerNo]);
       bool TxContainerIsRandomized = ( CurrentTxContainer -> CandidateTxNum > 1) ;
       if( TxContainerIsRandomized)
       {
	   CurrentTxContainer -> CandidateSeed = (unsigned) RAND_R(&CurrentThreadSeed);	
	   if(RandomDebug)
	       printf("%u:%u\n",TxContainerNo, CurrentTxContainer -> CandidateSeed);
       }
   }

   // Preparing the offset if messages are to be  printed on console for this thread 
   unsigned short ThreadOffsetlenght = 2*ID+1 ;
   ThreadDefArray[ID].ConsoleDisplayOffset = (char*)malloc(ThreadOffsetlenght*sizeof(char));
   unsigned short TabCounter= ThreadOffsetlenght -1 ;
   char* CurrentChar = ThreadDefArray[ID].ConsoleDisplayOffset;
   while(TabCounter >0)
   {
       *CurrentChar = '\t';
       CurrentChar ++;
       TabCounter --;
   }
   *CurrentChar = '\0';



   ThreadDefArray[ID].WriteValue = (unsigned) RAND_R(&CurrentThreadSeed); 

  if(RandomDebug)
      printf("Initial WriteValue is set to  %u for Thread %u...\n",ThreadDefArray[ID].WriteValue, ID); fflush(NULL);

   printf("Starting thread %u...\n",ID); fflush(NULL);

  ExecuteThread(ID);
  return NULL;
}



void ExecuteThread(unsigned ThreadNo)
{
    ThreadDefArray[ThreadNo].Active = TRUE;

    unsigned CurrentTxContainerID = 0 ;
    unsigned TxContainerNum = ThreadDefArray[ThreadNo].TxContainerNum;
    TxContainer_t* CurrentTxContainerList = ThreadDefArray[ThreadNo].TxContainerList;

    gettimeofday(&(ThreadDefArray[ThreadNo].start_time), NULL); 

    TM_INIT_THREAD(TxDesc);


    barrier_cross(&barrier);
    if(ExecuteSchedule)
	barrier_cross(ThreadDefArray[ThreadNo].BarrierSelf);

     while( CurrentTxContainerID < TxContainerNum)
     {
	 TxContainer_t* CurrentTxContainer = &(CurrentTxContainerList[CurrentTxContainerID]);
	 unsigned SelectedTxID = ChooseTransaction( CurrentTxContainer,ThreadNo) ;
	 

	 // TM_PARAM passed to ExecuteTransaction
//	 bool TransactionCompleted = ExecuteTransaction(NULL, &(ThreadDefArray[ThreadNo]), SelectedTxID);
         #ifdef STATISTICS_TEST
  	   bool Success = ExecuteTransaction(TxDesc, &(ThreadDefArray[ThreadNo]), SelectedTxID);
	   if( !Success)
 	     ThreadDefArray[ThreadNo].UnfinishedTxNum++;
	 #else  
	   ExecuteTransaction(TxDesc, &(ThreadDefArray[ThreadNo]), SelectedTxID); 
         #endif

	 
	 if( TerminateRequestedBySignal )
	     break;
    
	 bool Branch = FALSE;
	 bool IsBranchingElement = (CurrentTxContainer->InitialRepetitionCount > 0 && !(CurrentTxContainer->LoopStartNode) );
//	 printf("IsBranchingElement= %u\t",IsBranchingElement);
	 if( IsBranchingElement )
	 {
	     Branch = (CurrentTxContainer->RepetitionCount > 1);

//	     printf("Branch= %u\tRepetitionCount= %u\t",IsBranchingElement,CurrentTxContainer -> RepetitionCount);
	     CurrentTxContainer -> RepetitionCount = CurrentTxContainer -> RepetitionCount - 1;
 	     if(!Branch)
 		 CurrentTxContainer -> RepetitionCount = CurrentTxContainer -> InitialRepetitionCount;
	 }
 
	 CurrentTxContainerID = CurrentTxContainer -> NextContainerID[Branch];
     }    

  if(ExecuteSchedule)
      barrier_cross(ThreadDefArray[ThreadNo].SchedulerBarrier);

  gettimeofday(&(ThreadDefArray[ThreadNo].end_time), NULL); 


  TM_EXIT_THREAD(TxDesc);

  ThreadDefArray[ThreadNo].Active = FALSE;

    return;
}


bool ExecuteTransaction(stm_tx_t* TxDesc, ThreadInfo_t* CurrentThreadInfo, unsigned CurrentTxID)
{
     TxInfo_t* CurrentTx = &(CurrentThreadInfo -> TxDefArray[CurrentTxID]); 
//     printf("Transaction %s: ",CurrentTx->Name);
    
     TxOpContainer_t* CurrentTxOpContainerList = CurrentTx -> TxOpList[0];
     unsigned TxOpContainerNum  = CurrentTx -> TxOpNum[0]; 
   

     VarExpr* VarExprList     = ThreadDefArray[CurrentThreadInfo->ID].VarExprList ;
     unsigned VarExprListSize = ThreadDefArray[CurrentThreadInfo->ID].VarExprNum;

     
     // Traverse the VarListToUpdate to mark the (random) variables that requires update
     // The marked variables would update themselves when they are accessed.
     unsigned VarToUpdateNum = CurrentTx -> VarToUpdateNum;
     unsigned VarToUpdateNo;
     for(VarToUpdateNo = 0; VarToUpdateNo< VarToUpdateNum; VarToUpdateNo++)
     {
	 unsigned CurrentVarToUpdateID = CurrentTx -> VarListToUpdate[VarToUpdateNo];
	 VarExpr* VarToUpdate = &(VarExprList[CurrentVarToUpdateID ]);
	 assert(VarToUpdate != NULL);
	 
	 assert( (VarToUpdate -> Type == OP_RANDOM_DIST) || (VarToUpdate -> Type == OP_RANDOM_DIST_CONSTANT) );
	 VarToUpdate -> Operation = 1; // Operation field is set to non-zero to mark the need for update.
     }


      int* ReadOnlyTx = NULL; 
      if( TransmitReadOnlyTxHint ) 
 	 ReadOnlyTx =  &(CurrentTx -> ReadOnly); 

      #if defined(STATISTICS_TEST) && defined(MATCH_STM_ABORT_NUM)
         #warning "Code storing initial abort num effective" 
         unsigned long InitialAbortNumOfThread; 
         STM_GET_PARAMETER(TxDesc, "nb_aborts", &(InitialAbortNumOfThread) ); 
      #endif	 

      CurrentTx -> CurrentRetryNum = (unsigned long) -1;

      START_TX(TxDesc, ReadOnlyTx);
      CurrentTx -> CurrentRetryNum++;
      if( CurrentTx -> CurrentRetryNum > 0)
      {
	  if(ExecuteSchedule)
	  {
	      printf("%s[%s:%s] A \n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name);
	      if( NoAbortInSchedule )
	      {
		  printf("%s[%s:%s] Invariant NO_ABORT fails. \n"
			 "\n"
			 "\n"
			 "-----------------------------------------------------\n"
			 "                    TEST FAILS                       \n"
			 "-----------------------------------------------------\n"
			 "\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name);
		  exit(1);
	      }

	      printf("%s[%s:%s] Terminates\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name);
	      return FALSE;
	  }
	  else if(EnableTrace)
	  {
	      printf("%s[%s:%s] A(%lu)\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name, CurrentTx -> CurrentRetryNum);
	      fflush(NULL);
	  }
      }
      
      if(EnableTrace)
      {
	  printf("\n%s[%s:%s] S\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name);
	  fflush(NULL);
      }

     
     if( TerminateRequestedBySignal )
     {

         #if defined(STATISTICS_TEST) && defined(MATCH_STM_ABORT_NUM)
             #warning "Code storing final abort num (due to unexpected thread termination) effective"
 
	     unsigned long CurrentAbortNumOfThread;
	     STM_GET_PARAMETER(TxDesc, "nb_aborts", &(CurrentAbortNumOfThread) );
	     assert(CurrentAbortNumOfThread - InitialAbortNumOfThread  == CurrentTx -> CurrentRetryNum);
	 #endif
			
		
	 CurrentTx -> AbortNum = CurrentTx -> AbortNum + CurrentTx -> CurrentRetryNum;
	 if(CurrentTx -> MaxRetryNum < CurrentTx -> CurrentRetryNum)
	 {
	     CurrentTx -> MaxRetryNum = CurrentTx -> CurrentRetryNum;
	 }

	 return FALSE; // Function returns without the transaction being completed
     }

     
     
     // Check whether Invariants are satisfied (once at the beginning of the transaction)
     if(ExecuteSchedule)
     {
	 bool UnsatisfiedInvariantsExist = FALSE;
	 // Validate all invariants
	 unsigned InvariantNo;
	 for(InvariantNo=0; InvariantNo< InvariantNum; InvariantNo++)
	 {
	     Invariant* CurrentInvariant = GetElement_DynamicArray(&Dyn_InvariantArray, InvariantNo, sizeof(Invariant)) ;
	     VarExpr* CurrentInvariantExpr = &(VarExprList[ CurrentInvariant -> VarExprID] );
	     bool InvariantSatisfied = VAR_EXPR_Evaluate(CurrentInvariantExpr, VarExprList, VarExprListSize); 
	     if( !InvariantSatisfied )
	     {
		 UnsatisfiedInvariantsExist = TRUE;
		 printf( "Invariant '%s' not satisfied.\n", CurrentInvariant->Name);
		 
	     }
	 }
	 
	 if(UnsatisfiedInvariantsExist)
	 {
	     printf("Interruption in Schedule: One or more invariants not satisfied at the\n"
		    "beginning of transcation '%s' (before any operations of the transaction\n"
		    "were executed).\n"
		    "\n\n"
		    "-----------------------------------------------------\n"
		    "                    TEST FAILS                       \n"
		    "-----------------------------------------------------\n"
		    "\n", CurrentTx->Name);
	     exit(1);
	 }
     }

     unsigned StartTxOpContainerID=0;
     unsigned CurrentTxOpContainerID=StartTxOpContainerID;
     while( CurrentTxOpContainerID < TxOpContainerNum) 
     { 
	        TxOpContainer_t* CurrentTxOpContainer = &(CurrentTxOpContainerList[CurrentTxOpContainerID]);
		
		bool Branch = FALSE;
		if( CurrentTxOpContainer -> ConditionExprPos != INVALID_CONDITION_EXPR_POS)
		{

		    VarExpr* ConditionExpr = &(VarExprList[CurrentTxOpContainer -> ConditionExprPos]);

		    if( CurrentTxOpContainer -> LoopIteratorContainer)  
		    {
			if( !CurrentTxOpContainer -> LoopExecuting )
			{
			    // The loop iterator needs to be initialized
			    VarExpr* LoopIteratorInitialValExpr = &(VarExprList[ ConditionExpr->OperandID[2] ]); 
			    unsigned InitialValue = VAR_EXPR_Evaluate(LoopIteratorInitialValExpr, VarExprList, VarExprListSize);

			    VarExpr* AssignedVar  = &( VarExprList[ConditionExpr->OperandID[0]]);
			    assert(AssignedVar !=NULL);
			    AssignedVar -> Value = InitialValue;

			    CurrentTxOpContainer -> LoopExecuting = TRUE;
			}
			else
			{
			    var_assign_t* CurrentVarAssign = &(CurrentTxOpContainer -> VarAssigns[0]);
			    
			    VarExpr*  ExprToEvaluate  = &(VarExprList[ CurrentVarAssign->EvaluatedVarExprID ]);
			    assert(ExprToEvaluate !=NULL);
			    signed long ValueToAssign = VAR_EXPR_Evaluate(ExprToEvaluate, VarExprList, VarExprListSize);
			    
			    VarExpr* AssignedVar      = &( VarExprList[ CurrentVarAssign->AssignedVarID ]);
			    assert(AssignedVar !=NULL);
			    AssignedVar -> Value = ValueToAssign;

			}

		    }

		    bool ConditionHolds = (bool) VAR_EXPR_Evaluate(ConditionExpr, VarExprList, VarExprListSize);
		    Branch = !ConditionHolds;		    

		    if( Branch && CurrentTxOpContainer -> LoopIteratorContainer)
			CurrentTxOpContainer -> LoopExecuting = FALSE;
		}

		
		if( !Branch)
		{
		    bool OperationTransactional = FALSE;

		    if( CurrentTxOpContainer -> TxOperation == INVALID)
		    {
			// Do nothing just skip the operation phase.
		    }
		    else if( CurrentTxOpContainer -> TxOperation == READ )
		    {
			unsigned AccessedVarExprID = CurrentTxOpContainer -> AddrOp;
			VarExpr* AccessedVarExpr = &(VarExprList[ AccessedVarExprID ]);
			assert(AccessedVarExpr != NULL);
			
			Word* AccessedAddress = (Word*) VAR_EXPR_Evaluate( AccessedVarExpr, VarExprList, VarExprListSize);

			char* AccessedVariableName;
			if(EnableTrace)
			{
			    // For trace display purposes only
			    
			    // Since   we   are    in   a   managed   access   the
			    // AccessedVariableName   starts   from   the   second
			    // characted  of  AccessedVarExpr->Name.  That is  the
			    // reason  for  using  &(AccessedVarExpr->Name[1])  in
			    // copying the name.
			    AccessedVariableName = dupstr(&(AccessedVarExpr->Name[1]));
			    bool ArrayAccess =  (AccessedVarExpr -> Type == OP_MANAGED_ARRAY_ACCESS);
			    if( ArrayAccess  )
			    {
				VarExpr* ArrayOperandExpr = &(VarExprList[ AccessedVarExpr -> OperandID[0] ]); 
				// Since we have done gone through the evaluation of AccessedVarExpr above, 
				// and the Operand is an array access, the variable expression stored 
				// the index of the last accessed array element in its Value field
				sprintf(AccessedVariableName,"%s[%ld]", ArrayOperandExpr->Name, AccessedVarExpr -> Value);
			    }
			    printf("%s[%s:%s] R(%s)\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name, AccessedVariableName);
			    fflush(NULL);
			}


			Word ReturnedValue = TM_LOAD(TxDesc, AccessedAddress );

			
			if(EnableTrace)
			{
			    printf("%s[%s:%s] R(%s,%ld)\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name, AccessedVariableName , ReturnedValue );
			    fflush(NULL);
			    free(AccessedVariableName);
			}


			unsigned VariableToStoreReturnedValue_ID =  CurrentTxOpContainer -> AccessedAddrGenID[0];
			bool VariableToStoreReturnValueSpecified = ( VariableToStoreReturnedValue_ID < (unsigned) -1 );
			if(VariableToStoreReturnValueSpecified)
			{
			    VarExpr*  VariableStoringReturnedValue = &(VarExprList[ VariableToStoreReturnedValue_ID ]);
			    VariableStoringReturnedValue -> Value = ReturnedValue;
			    
			}

			OperationTransactional = TRUE;

		    }
		    else if( CurrentTxOpContainer -> TxOperation == WRITE )
		    {

			unsigned AccessedVarExprID = CurrentTxOpContainer -> AddrOp;
			VarExpr* AccessedVarExpr = &(VarExprList[ AccessedVarExprID ]);
			assert(AccessedVarExpr != NULL);

			Word* AccessedAddress = (Word*) VAR_EXPR_Evaluate( AccessedVarExpr, VarExprList, VarExprListSize);

			unsigned StoreValueSourceVariableExprID = CurrentTxOpContainer -> AccessedAddrGenID[0];
			bool StoreValueSourceVariableSpecified = ( StoreValueSourceVariableExprID < (unsigned) -1 );
			unsigned ValueToStore;
			if( StoreValueSourceVariableSpecified)
			{
			    VarExpr*  StoreValueSourceVarExpr = &(VarExprList[ StoreValueSourceVariableExprID ]);
			    ValueToStore = VAR_EXPR_Evaluate( StoreValueSourceVarExpr, VarExprList, VarExprListSize);
			}
			else
			{
			    ValueToStore = CurrentThreadInfo->WriteValue;
			    CurrentThreadInfo->WriteValue++;
			}

			char* AccessedVariableName;
			if(EnableTrace)
			{
			    // For trace display purposes only
			    
			    // Since   we   are    in   a   managed   access   the
			    // AccessedVariableName   starts   from   the   second
			    // characted  of  AccessedVarExpr->Name.  That is  the
			    // reason  for  using  &(AccessedVarExpr->Name[1])  in
			    // copying the name.
			    AccessedVariableName = dupstr(&(AccessedVarExpr->Name[1]));
			    bool ArrayAccess =  (AccessedVarExpr -> Type == OP_MANAGED_ARRAY_ACCESS);
			    if( ArrayAccess )
			    {
				VarExpr* ArrayOperandExpr = &(VarExprList[ AccessedVarExpr -> OperandID[0] ]); 
				// Since we have done gone through the evaluation of AccessedVarExpr above, 
				// and the Operand is an array access, the variable expression stored 
				// the index of the last accessed array element in its Value field
				sprintf(AccessedVariableName,"%s[%ld]", ArrayOperandExpr->Name, AccessedVarExpr -> Value);
			    }
			    printf("%s[%s:%s] W(%s)\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name, AccessedVariableName );
			    fflush(NULL);
			}

			TM_STORE(TxDesc, AccessedAddress,ValueToStore );


			if(EnableTrace)
			{
			    printf("%s[%s:%s] W(%s,%u)\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name, AccessedVariableName , ValueToStore );
			    fflush(NULL);
			    free(AccessedVariableName);
			}

			OperationTransactional = TRUE;

		    }
		    else if( CurrentTxOpContainer -> TxOperation == LABEL_OP )
		    {
			if( CurrentTxOpContainer -> LabelEnabled )
			{
			    printf("%s[%s:%s]:%s \n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name, CurrentTxOpContainer -> Label);
			    barrier_cross(CurrentThreadInfo -> SchedulerBarrier);
			    barrier_cross(CurrentThreadInfo -> BarrierSelf);
			}
		    }
		    else if (CurrentTxOpContainer -> TxOperation == ABORT )
		    {
			if(EnableTrace)
			{
			    printf("%s[%s:%s] Simulated Abort \n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name);
			    fflush(NULL);
			}
			TM_ABORT(TxDesc);
		    }
		    else {
			assert(0);
		    }


		    // Check whether Invariants are satisfied (only if a transactional operation has been performed
		    if(ExecuteSchedule && OperationTransactional)
		    {
			bool UnsatisfiedInvariantsExist = FALSE;
			// Validate all invariants
			unsigned InvariantNo;
			for(InvariantNo=0; InvariantNo< InvariantNum; InvariantNo++)
			{
			    Invariant* CurrentInvariant = GetElement_DynamicArray(&Dyn_InvariantArray, InvariantNo, sizeof(Invariant)) ;
			    VarExpr* CurrentInvariantExpr = &(VarExprList[ CurrentInvariant -> VarExprID] );
			    bool InvariantSatisfied = VAR_EXPR_Evaluate(CurrentInvariantExpr, VarExprList, VarExprListSize); 
			    if( !InvariantSatisfied )
			    {
				UnsatisfiedInvariantsExist = TRUE;
				printf( "Invariant '%s' not satisfied.\n", CurrentInvariant->Name);

			    }
			}
			
			if(UnsatisfiedInvariantsExist)
			{
			    printf("Interruption in Schedule: One or more invariants not satisfied in transcation '%s'.\n"
				   "\n\n"
				   "-----------------------------------------------------\n"
				   "                    TEST FAILS                       \n"
				   "-----------------------------------------------------\n"
				   "\n", CurrentTx->Name);
			    exit(1);
			}
		    }

		    
		    if( !CurrentTxOpContainer -> LoopIteratorContainer )
		    {
			// Performing VarAssigns.
			unsigned VarAssignNo;
			for(VarAssignNo=0; VarAssignNo< CurrentTxOpContainer -> VarAssignNum; VarAssignNo++)
			{
			    var_assign_t* CurrentVarAssign = &(CurrentTxOpContainer -> VarAssigns[VarAssignNo]);
			    
			    VarExpr*  ExprToEvaluate  = &( VarExprList[CurrentVarAssign->EvaluatedVarExprID] );
			    assert(ExprToEvaluate !=NULL);
			    signed long ValueToAssign = VAR_EXPR_Evaluate( ExprToEvaluate, VarExprList, VarExprListSize);
			    
			    VarExpr* AssignedVar      = &( VarExprList[CurrentVarAssign->AssignedVarID] ); 
			    assert(AssignedVar !=NULL);

			    // Should check what kind of variable /variable expression is in AssignedVar
			    // If SHARED VAR => Should call evaluated to get the address of shared var and write into that address.
			    // If SHARED ARRAY ACCESS => Should again call Evaluate to get address and write into it
			    // If LOCAL VAR  => write into Value fields as done below
			    // If LOCAL_ARRAY ACCESS => Should call Evaluate to get address and write into it
			    // If a CONSTANT => Assignment not valid (bit this should be found out during parsing)
			    bool LocalVariable = (AssignedVar -> Type == VAR_LOCAL_SIMPLE );			    
			    if( LocalVariable)
			    {
				AssignedVar -> Value = ValueToAssign;
			    }
			    else
			    {
				// Should  be elaborated  more because  to get
				// addresses  of  shared  variables or  arrays
				// requires Evaluation on Managed versions of 
				// variables/arrays.

/* 				bool ArrayAccess    = (AssignedVar -> Type == OP_UNMANAGED_ARRAY_ACCESS); */
/* 				bool SharedVariable = (AssignedVar -> Type == VAR_SHARED_UNMANAGED);			     */
/* 				if( ArrayAccess || SharedVariable) */
/* 				{ */
/* 				    Word* AddressToAssign = (Word*)VAR_EXPR_Evaluate( AssignedVar, VarExprList, VarExprListSize); */
/* 				    *AddressToAssign      = (Word)ValueToAssign; */
/* 				} */
/* 				else */
/* 				{ */
/* 				    fprintf(stderr,"ExecuteTransaction: ERROR in '%s': Neither local/shared variable nor array assignment.\nCan not perform assignement.\n", CurrentTx -> Name); */
/* 				    assert(0); */
/* 				} */
			    }
			    
			}
		    }
		}
		
		CurrentTxOpContainerID = CurrentTxOpContainer -> NextContainerID[Branch];

		if( TerminateRequestedBySignal )
		{
                    #if defined(STATISTICS_TEST) && defined(MATCH_STM_ABORT_NUM)
                        #warning "Code storing final abort num (due to unexpected thread termination) effective"
 
 		        unsigned long CurrentAbortNumOfThread;
			STM_GET_PARAMETER(TxDesc, "nb_aborts", &(CurrentAbortNumOfThread) );
			assert(CurrentAbortNumOfThread - InitialAbortNumOfThread  == CurrentTx -> CurrentRetryNum);
		    #endif
			
			
		    CurrentTx -> AbortNum = CurrentTx -> AbortNum + CurrentTx -> CurrentRetryNum;
		    if(CurrentTx -> MaxRetryNum < CurrentTx -> CurrentRetryNum)
		    {
			CurrentTx -> MaxRetryNum = CurrentTx -> CurrentRetryNum;
		    }

		    return FALSE; // Function returns without the transaction being completed
		}
		
     } 

     if(EnableTrace)
     {
	 printf("%s[%s:%s] Try C\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name);
	 fflush(NULL);
     }

     COMMIT_TX(TxDesc);

     if(EnableTrace)
     {
	 printf("%s[%s:%s] C\n\n", CurrentThreadInfo->ConsoleDisplayOffset, CurrentThreadInfo ->Name, CurrentTx->Name);
	 fflush(NULL);
     }



     if(ExecuteSchedule )
     {
	 bool UnsatisfiedInvariantsExist = FALSE;
	 // Validate all invariants
	 unsigned InvariantNo;
	 for(InvariantNo=0; InvariantNo< InvariantNum; InvariantNo++)
	 {
	     Invariant* CurrentInvariant = GetElement_DynamicArray(&Dyn_InvariantArray, InvariantNo, sizeof(Invariant)) ;
	     VarExpr* CurrentInvariantExpr = &(VarExprList[ CurrentInvariant -> VarExprID] );
	     bool InvariantSatisfied = VAR_EXPR_Evaluate(CurrentInvariantExpr, VarExprList, VarExprListSize); 
	     if( !InvariantSatisfied )
	     {
		 UnsatisfiedInvariantsExist = TRUE;
		 printf( "Invariant '%s' not satisfied.\n", CurrentInvariant->Name);
		 
	     }
	 }
	 
	 if(UnsatisfiedInvariantsExist)
	 {
	     printf("Interruption in Schedule: One or more invariants not satisfied in transcation '%s'.\n"
		    "\n\n"
		    "-----------------------------------------------------\n"
		    "                    TEST FAILS                       \n"
		    "-----------------------------------------------------\n"
		    "\n", CurrentTx->Name);
	     exit(1);
	 }
     }


     CurrentTx -> CommitNum++;

     CurrentTx -> AbortNum = CurrentTx -> AbortNum + CurrentTx -> CurrentRetryNum;
     if(CurrentTx -> MaxRetryNum < CurrentTx -> CurrentRetryNum)
     {
	 CurrentTx -> MaxRetryNum = CurrentTx -> CurrentRetryNum;
     }

     #if defined(STATISTICS_TEST) && defined(MATCH_STM_ABORT_NUM)
        #warning "Code storing final abort num  effective" 
 
        unsigned long CurrentAbortNumOfThread; 
	STM_GET_PARAMETER(TxDesc, "nb_aborts", &(CurrentAbortNumOfThread) ); 
	assert(CurrentAbortNumOfThread - InitialAbortNumOfThread  == CurrentTx -> CurrentRetryNum);
     #endif
  
     return TRUE;
}


unsigned ChooseTransaction(TxContainer_t* CurrentTxContainer, unsigned ThreadNo)
{
// printf("\tTxID: %u",CurrentTxContainer -> TxCandidateList[0].TxID);
    unsigned CandidateNum = CurrentTxContainer -> CandidateTxNum;

    
    unsigned SelectedCandidateNo ,
	     SelectedTxID        ;
    assert(CandidateNum != 0);
    if(CandidateNum > 1)
    {
	assert( CurrentTxContainer -> CandidateSelectionFunc != NULL);
	SelectedCandidateNo = CurrentTxContainer -> CandidateSelectionFunc(CurrentTxContainer);
	SelectedTxID        = CurrentTxContainer -> TxCandidateList[SelectedCandidateNo].TxID;

    }
    else 
    {
	SelectedTxID = CurrentTxContainer ->TxCandidateList[0].TxID;
    }
//    printf("\tTxID: %u",SelectedTxID);

       

/*     unsigned CandidateNo ; */
/*     printf("\t\tCandidates={"); */
/*     for(CandidateNo=0; CandidateNo< CandidateNum; CandidateNo++)  */
/*     {  */
/*  	printf("%u",CurrentTxContainer ->TxCandidateList[CandidateNo].TxID);  */
/* 	if(CandidateNo < CandidateNum -1) */
/* 	    printf(","); */
/* 	else */
/* 	    printf("}\n");  */
/*     }  */
    return SelectedTxID;
}



void InitializeThreadSeeds(unsigned ThreadNum)
{
    assert (ThreadNum != 0);
    ThreadSeed = (unsigned *)malloc(ThreadNum*sizeof(unsigned));
    if(MainSeed == 0)
    {
	printf("MainSeed is given zero. Main Seed is taken from the clock.\n");
	srand((int)time(0));
    }
    else
	SRAND(MainSeed);
    
    unsigned ThreadNo;
    for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++)
	ThreadSeed[ThreadNo] = RAND();

    if(RandomDebug)
    {
	printf("MainSeed=%u\n",MainSeed);
	printf("ListOfThreadSeeds={");
	for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++)
	{ 
	    printf("%u",ThreadSeed[ThreadNo]); 
	    if(ThreadNo < ThreadNum -1)
		printf(",");
	    else
		printf("}\n"); 
	} 
    }

}


