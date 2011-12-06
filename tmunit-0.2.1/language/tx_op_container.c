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

#include "tx_op_container.h"


void TX_OP_CONTAINER_Initialize(TxOpContainer_t* Target)
{
    Target -> ConditionExprPos = INVALID_CONDITION_EXPR_POS;
    Target -> VarAssigns       = NULL;
    Target -> VarAssignNum     = 0;
    Target -> PrecedingDelay = INVALID_DELAY;
    Target -> DelayBeforeCommit =INVALID_DELAY ;
    Target -> LabelEnabled    = FALSE;
    Target -> Label           = NULL;
    Target -> LoopIteratorContainer = FALSE; 
    Target -> LoopExecuting   = FALSE; 
     
    Target -> TxOperation = INVALID;
    Target -> AccessedAddrGenID[0] = INVALID_ADDR_GEN_ID;
    Target -> AccessedAddrGenID[1] = INVALID_ADDR_GEN_ID;
    Target -> AddrOp = INVALID_ADDR_OP;
    Target -> NextContainerID[0] = INVALID_CONTAINER_ID;
    Target -> NextContainerID[1] = INVALID_CONTAINER_ID; 
    Target -> RepetitionCount = 0 ;
    Target -> InitialRepetitionCount = 0;
    Target -> LoopIteratorAddrGenID = INVALID_CONTAINER_ID;
}



void TX_OP_CONTAINER_Finalize(TxOpContainer_t* Target)
{
    if(Target -> VarAssigns != NULL)
	free(Target -> VarAssigns);
}


void TX_OP_CONTAINER_Copy(const TxOpContainer_t* Source, TxOpContainer_t*Target)
{

    unsigned CopySizeInMemory = sizeof(TxOpContainer_t);
    memcpy(Target,Source,CopySizeInMemory);
    if( Source -> Label != NULL)
	Target -> Label = dupstr( Source -> Label );

    if(Source -> VarAssigns != NULL)
    {
	unsigned SizeOfVarAssignsInMemory = Source -> VarAssignNum * sizeof(var_assign_t); 	
	Target -> VarAssigns = (var_assign_t*) malloc(SizeOfVarAssignsInMemory);
	memcpy(Target->VarAssigns, Source->VarAssigns, SizeOfVarAssignsInMemory );
    }

 
/*     Target -> PrecedingDelay    = Source -> PrecedingDelay; */
/*     Target -> DelayBeforeCommit = Source -> DelayBeforeCommit  ; */
     
/*     Target -> TxOperation = Source -> TxOperation; */
/*     Target -> AccessedAddrGenID[0] = INVALID_ADDR_GEN_ID; */
/*     Target -> AccessedAddrGenID[1] = INVALID_ADDR_GEN_ID; */
/*     Target -> AddrOp = Source -> AddrOp ; */
/*     Target -> NextContainerID[0] = Source -> NextContainerID[0]; */
/*     Target -> NextContainerID[1] = Source -> NextContainerID[1];  */
/*     Target -> RepetitionCount = Source -> RepetitionCount   */
/*     Target -> InitialRepetitionCount = Source -> InitialRepetitionCount; */
/*     Target -> LoopIteratorAddrGenID  = Source -> LoopIteratorAddrGenID; */
}



/*!
       \todo  Should be adapted to the new structure, i.e. to the added/removed
              fields, modified data types etc. etc.
               
 */
void TX_OP_CONTAINER_Print(const TxOpContainer_t* Target)
{
    char* ConditionExprPosString;
    unsigned StringSize = strlen("INVALID_CONDITION_EXPR_POS") + 1 ;
    ConditionExprPosString = (char*)malloc( StringSize * sizeof(char) );
    if( Target -> ConditionExprPos == INVALID_CONDITION_EXPR_POS)
	sprintf(ConditionExprPosString,"INVALID_CONDITION_EXPR_POS");
    else
	sprintf(ConditionExprPosString,"%d", Target -> ConditionExprPos);
	
    
    char* TxOperation;
    if(	Target -> TxOperation == READ )
    {
	TxOperation = (char*)malloc(5*sizeof(char));
	sprintf(TxOperation,"Read");
    }
    else if(  Target -> TxOperation == WRITE )
    {
	TxOperation = (char*)malloc(6*sizeof(char));
	sprintf(TxOperation,"Write");
    }
    else if(  Target -> TxOperation == START )
    {
	TxOperation = (char*)malloc(6*sizeof(char));
	sprintf(TxOperation,"Start");
    }
    else if(  Target -> TxOperation == COMMIT )
    {
	TxOperation = (char*)malloc(7*sizeof(char));
	sprintf(TxOperation,"Commit");
    }
    else if(  Target -> TxOperation == LABEL_OP )
    {
	unsigned StringLength = strlen("Label() Enabled:") + strlen( Target ->Label) + strlen("FALSE") +1;
	TxOperation = (char*)malloc(StringLength*sizeof(char));

	char Enabled[]="FALSE";
	if( Target -> LabelEnabled ) 
	    strcpy(Enabled,"TRUE");
	sprintf(TxOperation,"Label(%s)  Enabled:%s", Target ->Label, Enabled);
    }
    else if(  Target -> TxOperation == INVALID )
    {
	TxOperation = (char*)malloc(8*sizeof(char));
	sprintf(TxOperation,"Invalid");
    }
    else
    {
	TxOperation = (char*)malloc(30*sizeof(char));
	sprintf(TxOperation,"Operation Value Out of Range");
    }
    

    char* AddrParamOperation;
    if(	Target -> AddrOp == PLUS )
    {
	AddrParamOperation = (char*)malloc(2*sizeof(char));
	sprintf(AddrParamOperation,"+");
    }
    else if(  Target -> AddrOp == MINUS )
    {
	AddrParamOperation = (char*)malloc(2*sizeof(char));
	sprintf(AddrParamOperation,"-");
    }
    else if(  Target -> AddrOp == MULTIPLY )
    {
	AddrParamOperation = (char*)malloc(2*sizeof(char));
	sprintf(AddrParamOperation,"*");
    }
    else if(  Target -> AddrOp == EQUAL )
    {
	AddrParamOperation = (char*)malloc(3*sizeof(char));
	sprintf(AddrParamOperation,"==");
    }
    else if(  Target -> AddrOp == INVALID_ADDR_OP )
    {
	AddrParamOperation = (char*)malloc(8*sizeof(char));
	sprintf(AddrParamOperation,"Invalid");
    }
    else
    {
	AddrParamOperation = (char*)malloc(30*sizeof(char));
	sprintf(AddrParamOperation,"Operation Value Out of Range");
    }

    

    printf("TxOperation       = %s\n"
           "AddrOp            = %s\n"
	   "AccessedAddrGenID = {%u,%u}\n"
	   "PrecedingDelay    = %u\n"
	   "DelayBeforeCommit = %u\n"
	   "ConditionExprPos  = %s\n"
	   "VarAssignNum      = %u\n"
	   "NextContainerID   = {%u,%u}\n"
           "RepetitionCount   = %u\n"
	   "InitialRepetitionCount = %u\n"
	   "LoopIteratorAddrGenID  = %u\n",  \
	   TxOperation,                      \
	   AddrParamOperation,               \
	   Target -> AccessedAddrGenID[0],   \
	   Target -> AccessedAddrGenID[1],   \
	   Target -> PrecedingDelay,         \
	   Target -> DelayBeforeCommit,      \
	   ConditionExprPosString,           \
	   Target -> VarAssignNum,           \
	   Target -> NextContainerID[0],     \
	   Target -> NextContainerID[1],     \
	   Target -> RepetitionCount,        \
	   Target -> InitialRepetitionCount, \
	   Target -> LoopIteratorAddrGenID   \
         ); 

    free(TxOperation);
    free(AddrParamOperation);


}



/*     int ArraySizeInMemory = ((int)(Target -> AccessedAddrGenIDNum))*sizeof(unsigned);  */
/*     Target -> AccessedAddrGenIDList = (unsigned *)malloc(ArraySizeInMemory); */
/*     memcpy(Target -> AccessedAddrGenIDList, Source -> AccessedAddrGenIDList, ArraySizeInMemory); */
/*
int main()
{
    TxOpContainer_t TestedContainer;
    TX_OP_CONTAINER_Print(&TestedContainer);
    printf("\n\n");

    TX_OP_CONTAINER_Initialize(&TestedContainer);
    TX_OP_CONTAINER_Print(&TestedContainer);
    printf("\n\n");

    TestedContainer.PrecedingDelay = 1;
    TestedContainer.DelayBeforeCommit = 2 ;
    TestedContainer.AccessedAddrGenID[0] = 3;
    TestedContainer.AccessedAddrGenID[1] = 4 ;
    TestedContainer.TxOperation = READ;
    TestedContainer.AddrOp = PLUS ;
    TestedContainer.NextContainerID[0] = 5 ;
    TestedContainer.NextContainerID[1] = 6 ;
    TestedContainer.RepetitionCount = 7 ,
    TestedContainer.InitialRepetitionCount = 8 ;
    TestedContainer.LoopIteratorAddrGenID  = 9 ;


    TX_OP_CONTAINER_Print(&TestedContainer);
    printf("\n\n");

    TxOpContainer_t CopyContainer;
    TX_OP_CONTAINER_Print(&CopyContainer);
    printf("\n\n");

    TX_OP_CONTAINER_Copy(&TestedContainer,&CopyContainer);
    TX_OP_CONTAINER_Print(&CopyContainer);
    printf("\n\n");


    
    return 0;
}
*/
