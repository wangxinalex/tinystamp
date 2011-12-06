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

#include "variable_expression.h"
dyn_arr_t Dyn_VariableExpressionArray;

#include "tm_interface.h"


const VarExprType INVALID_VAR_EXPR_TYPE= VAR_EXPR_TYPE_NUM;

void VAR_EXPR_Initialize(VarExpr* Target)
{
    Target->Name       = NULL;
    Target->Type       = INVALID_VAR_EXPR_TYPE;
    Target->Operation    = INVALID_OPERATION;
    Target->OperandID[0] = (unsigned)-1;
    Target->OperandID[1] = (unsigned)-1;
    Target->OperandID[2] = (unsigned)-1;
    Target->OperandID[3] = (unsigned)-1;
    Target->OperandID[4] = (unsigned)-1;
    Target->Addr       = NULL;
    Target->Value      = 0;	
}


void VAR_EXPR_Finalize(VarExpr* Target)
{
    if( Target->Name != NULL)
	free(Target->Name);
}


void VAR_EXPR_Copy(const VarExpr* Source, VarExpr* Target)
{
    unsigned SizeInMemory = sizeof(VarExpr);
    memcpy(Target,Source,SizeInMemory);
    if( Target->Name != NULL)
	Target->Name = dupstr(Source->Name);
}


void VAR_EXPR_Print(const VarExpr* Target)
{
    char* NameString;
    if(Target->Name != NULL)
	NameString = dupstr(Target -> Name);
    else
	NameString = dupstr("UNSPECIFIED");

    char*    TypeString; 
    switch (Target->Type)
    {

	case VAR_SHARED_UNMANAGED:
	    TypeString = dupstr("VAR_SHARED_UNMANAGED");
	    break;
	case VAR_SHARED_CONSTANT_UNMANAGED:
	    TypeString = dupstr("VAR_SHARED_CONSTANT_UNMANAGED");
	    break;
	case VAR_SHARED_MANAGED:
	    TypeString = dupstr("VAR_SHARED_MANAGED");
	    break;
	case VAR_SHARED_CONSTANT_MANAGED:
	    TypeString = dupstr("VAR_SHARED_CONSTANT_MANAGED");
	    break;
	case VAR_SHARED_ARRAY:
	    TypeString = dupstr("VAR_SHARED_ARRAY");
	    break;
	    TypeString = dupstr("VAR_SHARED_SIMPLE_CONSTANT");
	    break;
	case VAR_SHARED_ARRAY_CONSTANT:
	    TypeString = dupstr("VAR_SHARED_ARRAY_CONSTANT");
	    break;
	case VAR_LOCAL_SIMPLE:
	    TypeString = dupstr("VAR_LOCAL_SIMPLE");
	    break;
	case VAR_LOCAL_ARRAY:
	    TypeString = dupstr("VAR_LOCAL_ARRAY");
	    break;
	case VAR_LOCAL_SIMPLE_CONSTANT:
	    TypeString = dupstr("VAR_LOCAL_SIMPLE_CONSTANT");
	    break;
	case VAR_LOCAL_ARRAY_CONSTANT:
	    TypeString = dupstr("VAR_LOCAL_ARRAY_CONSTANT");
	    break;


	case OP_ARITH_UNARY:
	    TypeString = dupstr("OP_ARITH_UNARY");
	    break;
	case OP_RELATIONAL_UNARY:
	    TypeString = dupstr("OP_RELATIONAL_UNARY");
	    break;
	case OP_BOOLEAN_UNARY:
	    TypeString = dupstr("OP_BOOLEAN_UNARY");
	    break;
	case OP_MEMORY_READ:
	    TypeString = dupstr("OP_MEMORY_READ");
	    break;
	case OP_MEMORY_WRITE:
	    TypeString = dupstr("OP_MEMORY_WRITE");
	    break;


	case OP_ARITH:
	    TypeString = dupstr("OP_ARITH");
	    break;
	case OP_RELATIONAL:
	    TypeString = dupstr("OP_RELATIONAL");
	    break;
	case OP_BOOLEAN:
	    TypeString = dupstr("OP_BOOLEAN");
	    break;
	case OP_MANAGED_ARRAY_ACCESS:
	    TypeString = dupstr("OP_MANAGED_ARRAY_ACCESS");
	    break;
	case OP_UNMANAGED_ARRAY_ACCESS:
	    TypeString = dupstr("OP_UNMANAGED_ARRAY_ACCESS");
	    break;


	case OP_RANDOM_DIST:
	    TypeString = dupstr("OP_RANDOM_DIST");
	    break;
	case OP_RANDOM_DIST_CONSTANT:
	    TypeString = dupstr("OP_RANDOM_DIST_CONSTANT");
	    break;
	case VAR_EXPR_TYPE_NUM:
	    TypeString = dupstr("INVALID_VARIABLE_EXPRESSION");
	    break;
	default:
	    fprintf(stderr,"ERROR: VAR_EXPR_Print: Unknown Variable Expression Type encountered. Terminating...\n");
	    assert(0);
	    break;
    }

    char* OperationString;
    switch (Target->Operation)
    {
	case INVALID_OPERATION:
	    OperationString=dupstr("INVALID_OPERATION");
	    break;
	case PLUS:
	    OperationString=dupstr("PLUS");
	    break;
	case MINUS:
	    OperationString=dupstr("MINUS");
	    break;
	case MULTIPLY:
	    OperationString=dupstr("MULTIPLY");
	    break;
	case DIVIDE:
	    OperationString=dupstr("DIVIDE");
	    break;
	default:
	    OperationString=dupstr("UNKNOWN OPERATION");
	    break;
    }

    char* AddrString;
    if( Target -> Addr == NULL)
	AddrString =dupstr("NULL");
    else
	AddrString =dupstr("NON_NULL");


    char* OperandListString;
    GenereateUnsignedListOutput(Target->OperandID,4, &OperandListString);
    
    printf("Name       : %s\n"
	   "Type       : %s\n"
	   "Operation  : %s\n"
	   "Value      : %lu\n"
	   "Addr       : %s\n"
	   "OperandList: %s\n", NameString,TypeString, OperationString, Target->Value, AddrString, OperandListString);

    free(NameString);
    free(TypeString);
    free(AddrString);
    free(OperandListString); 

}


unsigned VAR_EXPR_FindPos(const char* SearchedVarExprName, const VarExpr* VarExprList, unsigned VarExprListSize)
{
    unsigned SearchedVarExprID = VarExprListSize;
    unsigned VarExprNo ;
    for(VarExprNo=0; VarExprNo< VarExprListSize; VarExprNo++)
    {
	char* VisitedVarExprName = VarExprList[VarExprNo].Name;
	unsigned ParanthesizedExpressionSize = strlen("(") +strlen(VisitedVarExprName) + strlen(")") + 1;
	char* ParanthesizedVisitedVarExprName = (char*)malloc(ParanthesizedExpressionSize*sizeof(char));
	sprintf(ParanthesizedVisitedVarExprName,"(%s)",VisitedVarExprName);
	bool SearchedVarExprFound = (strcmp(SearchedVarExprName,VisitedVarExprName) == 0) || (strcmp(SearchedVarExprName,ParanthesizedVisitedVarExprName) == 0) ;
	free(ParanthesizedVisitedVarExprName);
	if( SearchedVarExprFound ) 
	{
	    SearchedVarExprID = VarExprNo;
	    break;
	}
    }
    return SearchedVarExprID ; 

}



signed long VAR_EXPR_ComputeArithmetic(unsigned Operation, signed long LeftValue, signed long RightValue)
{
    signed long ComputedValue;
    switch (Operation)
    {
	case PLUS: 
	    ComputedValue = LeftValue + RightValue;
	    break;

	case MINUS: 
	    ComputedValue = LeftValue - RightValue;
	    break;

	case MULTIPLY: 
	    ComputedValue = LeftValue * RightValue;
	    break;

	case DIVIDE: 
	    assert(RightValue != 0);
	    ComputedValue = LeftValue / RightValue;
	    break;
    }
	return ComputedValue;
}



unsigned long VAR_EXPR_ComputeRelational(unsigned Operation, unsigned long LeftValue, unsigned long RightValue)
{
    bool StatementValue;
    switch (Operation)
    {
	case EQUAL: 
	    StatementValue = (LeftValue == RightValue);
	    break;
	case NOT_EQUAL: 
	    StatementValue = (LeftValue != RightValue);
	    break;
	case SMALLER_THAN: 
	    StatementValue = (LeftValue < RightValue);
	    break;
	case GREATER_THAN: 
	    StatementValue = (LeftValue > RightValue);
	    break;
	case SMALLER_EQUAL:
	    StatementValue = (LeftValue <= RightValue);
	    break;
	case GREATER_EQUAL:
	    StatementValue = (LeftValue >= RightValue);
	    break;
    }
    return (unsigned long)StatementValue;

    return 0;
}

unsigned long VAR_EXPR_ComputeBoolean(unsigned Operation, unsigned long LeftValue, unsigned long RightValue)
{
    bool StatementValue;
    switch (Operation)
    {
	case NOT: 
	    StatementValue = !LeftValue ;
	    break;
	case AND: 
	    StatementValue = (LeftValue && RightValue);
	    break;
	case OR: 
	    StatementValue = (LeftValue || RightValue);
	    break;
    }
    return (unsigned long)StatementValue;
}



unsigned ChooseFromUniformDist(unsigned CandidateNum, unsigned* Seed)
{
    assert(Seed != NULL) ;
    unsigned  ChosenElementNo =  (unsigned)((double)CandidateNum * (double)((double)RAND_R(Seed)/(double)(RAND_MAX_VAL + 1.0))) ;
    return ChosenElementNo;
}


 

signed long VAR_EXPR_Evaluate(VarExpr* Target, VarExpr* VarExprList, unsigned VarExprListSize)
{
    assert(Target != NULL);

    unsigned long EvaluatedValue;    

    if( Target->Type <= VAR_LOCAL_ARRAY_CONSTANT)
    {  // Evaluation requiring no operands (thus requiring no recursion)
	switch (Target->Type)
	{
	    case VAR_SHARED_UNMANAGED:
	    case VAR_SHARED_CONSTANT_UNMANAGED:
		EvaluatedValue = *((unsigned long*)(Target->Addr));
		break;
	    case VAR_LOCAL_SIMPLE:
	    case VAR_LOCAL_SIMPLE_CONSTANT:
		EvaluatedValue = (unsigned long)(Target->Value);
		break;
	    case VAR_SHARED_MANAGED:
	    case VAR_SHARED_CONSTANT_MANAGED:
	    case VAR_SHARED_ARRAY:
	    case VAR_SHARED_ARRAY_CONSTANT:
	    case VAR_LOCAL_ARRAY:
	    case VAR_LOCAL_ARRAY_CONSTANT:
		EvaluatedValue =  (unsigned long)(Target->Addr);
		break;
	    default:
		fprintf(stderr,"ERROR: VAR_EXPR_Print: Unknown NON-OPERAND Variable Expression Type encountered. Terminating...\n");
		assert(0);
	}
    }
    else if(  Target->Type <= OP_MEMORY_WRITE )
    { // Evaluation requiring single operand

	signed long OperandValue;
	VarExpr* Operand  ;
	unsigned Operation    ;

	Operand       = &(VarExprList[Target->OperandID[0]]);  
	OperandValue  = VAR_EXPR_Evaluate(Operand, VarExprList, VarExprListSize) ;
	Operation     = Target->Operation;


	switch (Target->Type)
	{
	    case OP_ARITH_UNARY:
		EvaluatedValue = VAR_EXPR_ComputeArithmetic(Operation,OperandValue,0);
		break;
	    case OP_RELATIONAL_UNARY:
		EvaluatedValue = VAR_EXPR_ComputeRelational(Operation,OperandValue,0);
		break;
	    case OP_BOOLEAN_UNARY:
		EvaluatedValue = VAR_EXPR_ComputeBoolean(Operation,OperandValue,0);
		break;
	    case OP_MEMORY_READ:
		// Not implemented yet. Should read the from transactional memory using STM_LOA
		EvaluatedValue = TM_LOAD(TxDesc, (Word*)OperandValue );
	
		if( VerboseParserOutput )
		{
		    // Since   we   are    in   a   managed   access   the
		    // AccessedVariableName   starts   from   the   second
		    // characted  of  AccessedVarExpr->Name.  That is  the
		    // reason  for  using  &(AccessedVarExpr->Name[1])  in
		    // copying the name.
		    char* AccessedVariableName = dupstr(&(Operand->Name[1]));
		    bool ArrayAccess =  (Operand -> Type == OP_MANAGED_ARRAY_ACCESS);
		    if( ArrayAccess  )
		    {
			VarExpr* ArrayOperandExpr = &(VarExprList[ Operand -> OperandID[0] ]); 
			// Since we have done gone through the evaluation of Operand above, 
			// and the Operand is an array access, the variable expression stored 
			// the index of the last accessed array element in its Value field
			sprintf(AccessedVariableName,"%s[%ld]", ArrayOperandExpr->Name,  Operand->Value);
		    }
		    printf("Managed Read from '%s' returns %ld\n",AccessedVariableName, EvaluatedValue);
		}
		break;
	    case OP_MEMORY_WRITE:
		// I'm not sure this can exist
		// Not implemented yet should write to transactional memory using STM_STORE
		break;
	    default:
		break;
	}
    }
    else if(  Target->Type <= OP_UNMANAGED_ARRAY_ACCESS )
    { // Evaluation requiring TWO operands


	unsigned long LeftValue,
	              RightValue;
	unsigned long LowerLimit,  // used only if array access 
	              UpperLimit,  // used only if array access 
	              Index     ;  // used only if array access   
	VarExpr* LeftOperand  ;
	VarExpr* RightOperand ;  
	unsigned Operation    ;

//	unsigned ArraySize;

	LeftOperand  = &(VarExprList[Target->OperandID[0]]);  
	LeftValue    = VAR_EXPR_Evaluate(LeftOperand, VarExprList, VarExprListSize) ;
	
	RightOperand = &(VarExprList[Target->OperandID[1]]);  
	RightValue   = VAR_EXPR_Evaluate(RightOperand, VarExprList, VarExprListSize) ;
	Operation    = Target->Operation;

	switch (Target->Type)
	{
	    case OP_ARITH:
		EvaluatedValue = VAR_EXPR_ComputeArithmetic(Operation,LeftValue,RightValue);
		break;
	    case OP_RELATIONAL:
		EvaluatedValue = VAR_EXPR_ComputeRelational(Operation,LeftValue,RightValue);
		break;
	    case OP_BOOLEAN:
		EvaluatedValue = VAR_EXPR_ComputeBoolean(Operation,LeftValue,RightValue);
		break;
	    case OP_MANAGED_ARRAY_ACCESS:
		// OperandID[0] --> LowerLimitIndex of the array
		// OperandID[1] --> UpperLimitIndex of the array
		LowerLimit  =  LeftOperand -> OperandID[0];
		UpperLimit  =  LeftOperand -> OperandID[1];
		if( RightValue > UpperLimit )
		{
		    fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
		    assert(0);
		}
		else if( RightValue < LowerLimit)
		{
		    fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
		    assert(0);
		}
		else
		{
		    Index = RightValue - LowerLimit;
		    EvaluatedValue= LeftValue + (Index * sizeof(Word));
		}
		Target-> Value = RightValue;
		break;
	    case OP_UNMANAGED_ARRAY_ACCESS:
		// OperandID[0] --> LowerLimitIndex of the array
		// OperandID[1] --> UpperLimitIndex of the array
		LowerLimit  =  LeftOperand -> OperandID[0];
		UpperLimit  =  LeftOperand -> OperandID[1];
		if( RightValue > UpperLimit )
		{
		    fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
		    assert(0);
		}
		else if( RightValue < LowerLimit)
		{
		    fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
		    assert(0);
		}
		else
		{
		    Index = RightValue - LowerLimit;
		    EvaluatedValue= ((Word*)(LeftValue))[Index];
		}
		Target-> Value = RightValue;
		break;
	    default:
		break;
	}
    }
    else if(  Target->Type <= OP_RANDOM_DIST_CONSTANT )
    { // Evaluation requiring FOUR operands


	VarExpr* AddressRangeLowerLimitExpr ;
	VarExpr* AddressRangeUpperLimitExpr ;

	signed long AddrRangeLowerLimit , 
	            AddrRangeUpperLimit ; 
	
	unsigned  AddrRangeSize ;
	unsigned* CurrentAddrGenSeedPtr ;
	unsigned  ChosenPos;

	switch (Target->Type)
	{
	    case OP_RANDOM_DIST:
	    case OP_RANDOM_DIST_CONSTANT:

		if ( Target-> Operation == 0)
		    EvaluatedValue = Target -> Value;
		else
		{		    
		    AddressRangeLowerLimitExpr = &(VarExprList[Target->OperandID[0]]);   
		    assert(AddressRangeLowerLimitExpr != NULL);
		    AddrRangeLowerLimit = VAR_EXPR_Evaluate(AddressRangeLowerLimitExpr, VarExprList, VarExprListSize) ; 
		    
		    AddressRangeUpperLimitExpr = &(VarExprList[Target->OperandID[1]]);
		    assert(AddressRangeUpperLimitExpr != NULL);
		    AddrRangeUpperLimit = VAR_EXPR_Evaluate(AddressRangeUpperLimitExpr, VarExprList, VarExprListSize) ; 
		    
		    AddrRangeSize =  AddrRangeUpperLimit - (AddrRangeLowerLimit - 1) ;
		    CurrentAddrGenSeedPtr = &(Target -> OperandID[2]);
		    ChosenPos = ChooseFromUniformDist(AddrRangeSize, CurrentAddrGenSeedPtr);
		    EvaluatedValue = AddrRangeLowerLimit + ChosenPos;
		    Target -> Value    = EvaluatedValue;
		    Target-> Operation = 0; 
		}
		break;

	    default:
		break;
	}
    }
    else
    {
	fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Unknown Variable Expression Type encountered. Terminating...\n");
	assert(0);
    }

    return EvaluatedValue;
}




