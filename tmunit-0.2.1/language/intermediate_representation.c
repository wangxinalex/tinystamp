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

#include "intermediate_representation.h"

/* int InitializeTempDataStructuresUsedInParsing() */
/* { */
/*     InitializeTempThreadStructuresUsedInParsing(); */
/*     InitializeTempTransactionStructuresUsedInParsing(); */
/* } */


bool CheckAndSetSimulationParameter(const char* VariableName, unsigned Value)
{
    bool IsSimulationParameter = FALSE;

    // JustGenerateTrace option
    bool JustGenerateTraceParameter = (strcmp(VariableName,"TraceOnly") == 0);
    if( JustGenerateTraceParameter )
    {
	if( Value == TRUE || Value== FALSE )
	{
	    JustGenerateTrace = (bool)Value;
	    if( VerboseParserOutput )
		printf("JustGenerateTrace is set to %u\n",JustGenerateTrace);
	}
	else
	{
	    printf("CheckAndSetSimulationParameter: ERROR: Unrecognized value range for boolean option 'TraceOnly'. Values can be 0 or 1.\n");
	    exit(1);
	}
	IsSimulationParameter = TRUE;
    }


    bool EnableTraceParameter = (strcmp(VariableName,"EnableTrace") == 0);
    if( EnableTraceParameter )
    {
	if( Value == TRUE || Value== FALSE )
	{
	    EnableTrace = (bool)Value;
	    if( VerboseParserOutput )
		printf("EnableTrace is set to %u\n",EnableTrace);
	    if( EnableTrace )
	    {
		JustGenerateTrace = FALSE;
		if( VerboseParserOutput )
		    printf("JustGenerateTrace is set to %u\n",JustGenerateTrace);
	    }
	}
	else
	{
	    printf("CheckAndSetSimulationParameter: ERROR: Unrecognized value range for boolean option 'EnableTrace'. Values can be 0 or 1.\n");
	    exit(1);
	}
	IsSimulationParameter = TRUE;
    }

    bool SerialThreadExecutionParameter = (strcmp(VariableName,"SerialThreadExecution") == 0);
    if( SerialThreadExecutionParameter )
    {
	if( Value == TRUE || Value== FALSE )
	{
	    SerialThreadExecution = (bool)Value;
	    if( VerboseParserOutput )
		printf("SerialThreadExecution is set to %u\n",SerialThreadExecution);
	}
	else
	{
	    printf("CheckAndSetSimulationParameter: ERROR: Unrecognized value range for boolean option 'SerialThreadExecution'. Values can be 0 or 1.\n");
	    exit(1);
	}
	IsSimulationParameter = TRUE;
    }

    bool ReadConfigOnlyParameter = (strcmp(VariableName,"ReadConfigOnly") == 0);
    if( ReadConfigOnlyParameter )
    {
	if( Value == TRUE || Value== FALSE )
	{
	    ReadConfigOnly = (bool)Value;
	    if( VerboseParserOutput )
		printf("ReadConfigOnly is set to %u\n",ReadConfigOnly);
	}
	else
	{
	    printf("CheckAndSetSimulationParameter: ERROR: Unrecognized value range for boolean option 'ReadConfigOnly'. Values can be 0 or 1.\n");
	    exit(1);
	}
	IsSimulationParameter = TRUE;
    }

    bool ParseOnlyParameter = (strcmp(VariableName,"ParseOnly") == 0);
    if( ParseOnlyParameter )
    {
	if( Value == TRUE || Value== FALSE )
	{
	    ParseOnly = (bool)Value;
	    if( VerboseParserOutput )
		printf("ParseOnly is set to %u\n",ParseOnly);
	    if( ParseOnly)
	    {
		ReadConfigOnly = TRUE;
		if( VerboseParserOutput )
		    printf("ReadConfigOnly is set to %u\n",ReadConfigOnly);
	    }

	}
	else
	{
	    printf("CheckAndSetSimulationParameter: ERROR: Unrecognized value range for boolean option 'ParseOnly'. Values can be 0 or 1.\n");
	    exit(1);
	}
	IsSimulationParameter = TRUE;
    }


    bool PrintStatsParameter = (strcmp(VariableName,"PrintStatistics") == 0);
    if( PrintStatsParameter )
    {
	if( Value == TRUE || Value== FALSE )
	{
	    PrintStats = (bool)Value;
	    if( VerboseParserOutput )
		printf("PrintStatistics is set to %u\n",PrintStats);
	}
	else
	{
	    printf("CheckAndSetSimulationParameter: ERROR: Unrecognized value range for boolean option 'PrintStatistics'. Values can be 0 or 1.\n");
	    exit(1);
	}
	IsSimulationParameter = TRUE;
    }


    bool RandomDebugParameter = (strcmp(VariableName,"RandomDebug") == 0);
    if( RandomDebugParameter )
    {
	if( Value == TRUE || Value== FALSE )
	{
	    RandomDebug = (bool)Value;
	    if( VerboseParserOutput )
		printf("RandomDebugParameter is set to %u\n",RandomDebug);
	}
	else
	{
	    printf("CheckAndSetSimulationParameter: ERROR: Unrecognized value range for boolean option 'RandomDebug'. Values can be 0 or 1.\n");
	    exit(1);
	}
	IsSimulationParameter = TRUE;
    }


    bool DelayUnitParameter = (strcmp(VariableName,"DelayUnit") == 0);
    if( DelayUnitParameter )
    {
	DelayUnit = Value;
	if( VerboseParserOutput )
	    printf("DelayUnit is set to %u microseconds\n",DelayUnit);
	IsSimulationParameter = TRUE;
    }

    bool WaitForTimeOutParameter = (strcmp(VariableName,"WaitForTimeOut") == 0);
    if( WaitForTimeOutParameter )
    {
	if( Value == TRUE || Value== FALSE )
	{
	    WaitForTimeOut = (bool)Value;
	    if( VerboseParserOutput )
		printf("WaitForTimeOut is set to %u\n",WaitForTimeOut);
	}
	else
	{
	    printf("CheckAndSetSimulationParameter: ERROR: Unrecognized value range for boolean option 'WaitForTimeOut'. Values can be 0 or 1.\n");
	    exit(1);
	}
	IsSimulationParameter = TRUE;
    }




    bool TimeOutValueIsSet = (strcmp(VariableName,"Timeout") == 0);
    if( TimeOutValueIsSet )
    {
	TimeOut = Value;
	if( VerboseParserOutput )
	    printf("TimeOut is set to %u microseconds\n",TimeOut*DelayUnit);
	IsSimulationParameter = TRUE;
	TimeOutValueSet = TRUE;
    }



    bool RandomSeedValue= (strcmp(VariableName,"RandomSeed") == 0);
    if(RandomSeedValue ) {
		MainSeed=Value;
		if( VerboseParserOutput )
			printf("MainSeed (the main random seed) is set to %u.\n",MainSeed);
		IsSimulationParameter = TRUE;
    }



    bool TransmitReadOnlyTxHintParameter = (strcmp(VariableName,"ReadOnlyHint") == 0);
    if( TransmitReadOnlyTxHintParameter )
    {
	if( Value == TRUE || Value== FALSE )
	{
	    TransmitReadOnlyTxHint = (bool)Value;
	    if( VerboseParserOutput )
		printf("ReadOnlyHint is set to %u\n",TransmitReadOnlyTxHint);
	}
	else
	{
	    printf("CheckAndSetSimulationParameter: ERROR: Unrecognized value range for boolean option 'ReadOnlyHint'. Values can be 0 or 1.\n");
	    exit(1);
	}
	IsSimulationParameter = TRUE;
    }






    return IsSimulationParameter;
}


/*! /func  FindVarExpr

           Finds the variable expression given with the name SearchedVarExprName
           inside the Dyn_VariableExpressionArray list.

	   Preconditions:
	       Assumes that SearchedVarExprName is not NULL.

	       If FoundVarExpr is NULL then nothing will be returned
	       through this parameter. If not  the address of the new allocated
	       variable expression is written inside the pointer.

	   Return Value:
               The position of the of found variable expression in
	       Dyn_VariableExpressionArray  list. If the variable expression
	       is not found, it returns the size of the Dyn_VariableExpressionArray
               list (which should be larger than any other possible return values).

	       Also as a return value the address of the found variable expr is written
	       inside the FoundVarExpr pointer parameter. If the expression is not found
	       the content of FoundVarExpr is set to NULL.
 */
unsigned FindVarExpr(const char* SearchedVarExprName, VarExpr** FoundVarExpr)
{
    VarExpr* VarExprList = (VarExpr*)(Dyn_VariableExpressionArray.ArrayStartAddress);
    unsigned VarExprListSize = Dyn_VariableExpressionArray.ArrayElementNum;
    unsigned FoundPos = VAR_EXPR_FindPos( SearchedVarExprName, VarExprList, VarExprListSize);
    bool VariableNotDefined = (FoundPos == VarExprListSize) ;

    if( FoundVarExpr != NULL)
    {
	if(VariableNotDefined)
	    *FoundVarExpr = NULL;
	else
	    *FoundVarExpr = (VarExpr*)GetElement_DynamicArray(&Dyn_VariableExpressionArray, FoundPos, sizeof(VarExpr));
    }

    return FoundPos;
}


/*! /func  AllocVarExpr

           Allocates a new Variable Expression (VarExpr struct) to the end of
           Dyn_VariableExpressionArray list.

	   Preconditions:
	       Assumes (and  does not check  it) that the  variable expression
               does not exist in the Dyn_VariableExpressionArray list.

	       Assumes that SearchedVarExprName is not null.

	       If AllocatedTargetVarExpr is NULL then nothing will be returned
	       through this parameter. If not  the address of the new allocated
	       variable expression is written inside the pointer.

	   Return Value:
               The position of the of the allocated variable expression in
	       Dyn_VariableExpressionArray  list.
 */
unsigned AllocVarExpr(const char* SearchedVarExprName, VarExpr** AllocatedTargetVarExpr )
{
    Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
    unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
    VarExpr* AllocatedVarExpr = (VarExpr*)GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

    VAR_EXPR_Initialize(AllocatedVarExpr);
    AllocatedVarExpr -> Name = dupstr(SearchedVarExprName);

    if(AllocatedTargetVarExpr != NULL )
	*AllocatedTargetVarExpr = AllocatedVarExpr;

    return LastElementPos;
}

/*! /func  FindOrAllocVarExpr

           Looks   whether    the   variable   expression    with   the   name
	   SearchedVarExprName  is   in  Dyn_VariableExpressionArray  list  or
	   not. If it is, it returns the  found pos, if not it allocates a new
	   variable  expression and returns  the position  to the  new created
	   one.


	   Preconditions:
	       Assumes that SearchedVarExprName is not null.

	       If FoundVarExpr  is NULL then nothing will  be returned through
	       this parameter.  But this  parameter is passed to the functions
	       that  are called  inside  (which behave  similarly).If not  the
	       address  of  the  found/new  allocated variable  expression  is
	       written inside the pointer.

	   Return Value:
               The position of the of the allocated variable expression in
	       Dyn_VariableExpressionArray  list.
 */
unsigned FindOrAllocVarExpr(const char* SearchedVarExprName, VarExpr** FoundVarExpr)
{
    unsigned VarExprPos = FindVarExpr(SearchedVarExprName, FoundVarExpr);
    bool VarExprNotFound = ( VarExprPos == Dyn_VariableExpressionArray.ArrayElementNum ) ;
    if( VarExprNotFound )
	VarExprPos = AllocVarExpr(SearchedVarExprName, FoundVarExpr);

    return VarExprPos;
}


VarExpr* GetVarExprPtr(unsigned VarExprID)
{
    unsigned VarExprListSize = Dyn_VariableExpressionArray.ArrayElementNum;
    assert(VarExprID < VarExprListSize);

    return &( ((VarExpr*)(Dyn_VariableExpressionArray.ArrayStartAddress))[VarExprID] );
}



// This function assumes TargetVarExpr exists  and it is possible to evaluate it.
signed long EvaluateVarExpr(VarExpr* TargetVarExpr)
{
    unsigned long ReturnVal;
    VarExpr* VarExprList = (VarExpr*)(Dyn_VariableExpressionArray.ArrayStartAddress);
    unsigned VarExprListSize = Dyn_VariableExpressionArray.ArrayElementNum;
    ReturnVal = VAR_EXPR_Evaluate( TargetVarExpr, VarExprList, VarExprListSize);
    return ReturnVal;
}


unsigned ResolveOperationType(const char* OperationString)
{

    bool PlusOperation = (strcmp(OperationString,"+") == 0);
    if(PlusOperation)
	return PLUS;

    bool MinusOperation = (strcmp(OperationString,"-") == 0);
    if( MinusOperation)
	return MINUS;

    bool MultiplyOperation = (strcmp(OperationString,"*") == 0);
    if( MultiplyOperation)
	return MULTIPLY;

    bool DivideOperation = (strcmp(OperationString,"/") == 0);
    if( DivideOperation)
	return DIVIDE;


    bool EqualOperation = (strcmp(OperationString,"==") == 0);
    if(EqualOperation)
	return EQUAL;

    bool NotEqualOperation = (strcmp(OperationString,"!=") == 0);
    if(NotEqualOperation)
	return NOT_EQUAL;

    bool SmallerThanOperation = (strcmp(OperationString,"<") == 0);
    if(SmallerThanOperation)
	return SMALLER_THAN;

    bool GreaterThanOperation = (strcmp(OperationString,">") == 0);
    if(GreaterThanOperation)
	return GREATER_THAN;

    bool SmallerEqualOperation = (strcmp(OperationString,"<=") == 0);
    if(SmallerEqualOperation)
	return SMALLER_EQUAL;

    bool GreaterEqualOperation = (strcmp(OperationString,">=") == 0);
    if(GreaterEqualOperation)
	return GREATER_EQUAL;

    bool NotOperation = (strcmp(OperationString,"!") == 0);
    if(NotOperation)
	return NOT;

    bool AndOperation = (strcmp(OperationString,"&&") == 0);
    if(AndOperation)
	return AND;

    bool OrOperation = (strcmp(OperationString,"||") == 0);
    if(OrOperation)
	return OR;
    else
	return INVALID_OPERATION;

}


void AddSharedVariableToVarExprList(const char* VarExprString, const char* ValueToAssignString)
{

    VarExpr* CurrentVarExpr;
    FindVarExpr(VarExprString,&CurrentVarExpr);
    bool VariableAlreadyExist = (CurrentVarExpr != NULL);
    if( !VariableAlreadyExist)
    {
	void* SharedVarAddr = (void *)malloc(sizeof(Word));

	// Since we are generating a shared array expression we generate two copies, one for managed and one for unmanaged accesses.
	// Creating Unmanaged copy
	Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	VAR_EXPR_Initialize(CurrentVarExpr);
	CurrentVarExpr -> Name = dupstr(VarExprString);
	CurrentVarExpr -> Type = VAR_SHARED_UNMANAGED;
	CurrentVarExpr -> Addr = SharedVarAddr;
	VAR_EXPR_Print(CurrentVarExpr);

	Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));

	LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	// Creating Managed copy
	unsigned ManagedVersionNameLength = strlen("&") + strlen(VarExprString) + 1 ;
	char* ManagedVersionName = malloc(ManagedVersionNameLength*sizeof(char));
	sprintf(ManagedVersionName,"&%s",VarExprString);

	VAR_EXPR_Initialize(CurrentVarExpr);
	CurrentVarExpr -> Name = dupstr(ManagedVersionName);
	CurrentVarExpr -> Type = VAR_SHARED_MANAGED;
	CurrentVarExpr -> Addr = SharedVarAddr;

    }
    *((Word*)(CurrentVarExpr -> Addr)) = (Word)atoi(ValueToAssignString);
    VAR_EXPR_Print(CurrentVarExpr);

    return;
}

void AddLocalVariableToVarExprList(const char* VarExprString, const char* ValueToAssignString)
{
    VarExpr* CurrentVarExpr;
    FindVarExpr(VarExprString,&CurrentVarExpr);
    bool LocalVariableAlreadyExist = (CurrentVarExpr != NULL);
    if( !LocalVariableAlreadyExist)
    {
	Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	VAR_EXPR_Initialize(CurrentVarExpr);
	CurrentVarExpr -> Name = dupstr(VarExprString);

	// Are all characters (after the underscore) capital letters?
	unsigned CharNum = strlen(VarExprString);
	unsigned CharNo;
	bool IsAllCapitals = TRUE;
	for(CharNo=1; CharNo< CharNum; CharNo++)
	{
	    int ReturnVal = isupper((CurrentVarExpr -> Name)[CharNo]);
	    bool CharIsCapitalLetter = (ReturnVal > 0);
	    if( !CharIsCapitalLetter)
	    {
		IsAllCapitals = FALSE;
		break;
	    }
	}
	if(IsAllCapitals)
	    CurrentVarExpr -> Type = VAR_LOCAL_SIMPLE_CONSTANT;
	else
	    CurrentVarExpr -> Type = VAR_LOCAL_SIMPLE;

    }
    CurrentVarExpr -> Value = (unsigned)atoi(ValueToAssignString);
    VAR_EXPR_Print(CurrentVarExpr);

    return;
}



unsigned GetMemAccessOpAddressParameter(const char* AddressParamString)
{

    VarExpr* InputVarExpr;
    unsigned InputVarExprID = FindVarExpr(AddressParamString,&InputVarExpr);
    if( InputVarExpr == NULL )
    {
	  char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ErrorMessage,"CAN NOT DEFINE the SHARED VARIABLE (or expression) '%s' inside a memory access operation.\n"
		  "Only local variables can be defined at the first point where they are first used\n"
		  "(however, local variables can not be defined in memory access operations).\n"
		  "Shared variables should be defined in the 'Definitions' section.\n", AddressParamString);
	  yyerror(ErrorMessage);
	  free(ErrorMessage);
	  exit(1);
    }

    bool NotSupportedVariableExpression = FALSE; ;
    bool NotSimpleSharedAccess = (InputVarExpr -> Type > VAR_SHARED_ARRAY_CONSTANT );
    if( NotSimpleSharedAccess )
    {
	  bool ArrayAccess =  (InputVarExpr -> Type == OP_UNMANAGED_ARRAY_ACCESS);
	  if( ArrayAccess )
	  {
	      VarExpr* ArrayOperand = GetVarExprPtr(InputVarExpr -> OperandID[0]);
	      bool SharedArrayAccess = (ArrayOperand -> Type <= VAR_SHARED_ARRAY_CONSTANT ) ;
	      if( !SharedArrayAccess)
		  NotSupportedVariableExpression = TRUE;
	  }
	  else
	      NotSupportedVariableExpression = TRUE;

    }

    if( NotSupportedVariableExpression )
    {
	  char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ErrorMessage,"Variable Expression '%s' is not an access to a standalone\n"
		  "shared variable/array. The expression is either a local variable/array\n"
		  "access or any kind of complex variable expression (e.g., with arithmetic,\n"
		  "relational or boolean operations). Those kind of variable expressions are\n"
		  "not allowed in managed (transactional) accesses .\n",AddressParamString);
	  yyerror(ErrorMessage);
	  free(ErrorMessage);

	  exit(1);
    }

    unsigned ActualAccessedVarExprNameLength = strlen("&") + strlen(AddressParamString) + 1;
    char*    ActualAccessedVarExprName = malloc(ActualAccessedVarExprNameLength * sizeof(char));
    sprintf(ActualAccessedVarExprName,"&%s",AddressParamString);

    InputVarExprID = FindVarExpr(ActualAccessedVarExprName,&InputVarExpr);
    assert(InputVarExpr != NULL);

    return InputVarExprID;
}



unsigned GetReadAccessTargetParameter(const char* AddressParamString)
{

    VarExpr* InputVarExpr;
    unsigned InputVarExprID = FindVarExpr(AddressParamString,&InputVarExpr);
    if( InputVarExpr == NULL )
    {
	  char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ErrorMessage,"UNDEFINED  '%s'. TMUNIT does not currently support the \n"
		  "use of undefined variables/variable expression as the target value to\n"
		  "store the result of managed Read operation. Please define '%s'\n"
		  "in 'Definitions' section.\n" ,AddressParamString, AddressParamString);
	  yyerror(ErrorMessage);
	  free(ErrorMessage);

	  exit(1);

    }

    bool LocalAccess  = (InputVarExpr -> Type >= VAR_LOCAL_SIMPLE && InputVarExpr -> Type <= VAR_LOCAL_ARRAY_CONSTANT );
    if( !LocalAccess )
    {
	  char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ErrorMessage,"Variable Expression '%s' is not an local variable/array.\n"
		  "Such a variable expression is not allowed as the target value to store\n"
                  "the result of managed Read operation.\n",AddressParamString);
	  yyerror(ErrorMessage);
	  free(ErrorMessage);

	  exit(1);
    }

    return InputVarExprID;
}


unsigned GetWriteAccessTargetParameter(const char* AddressParamString)
{

    VarExpr* InputVarExpr;
    unsigned InputVarExprID = FindVarExpr(AddressParamString,&InputVarExpr);
    if( InputVarExpr == NULL )
    {
	  char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ErrorMessage,"UNDEFINED  '%s'. TMUNIT does not currently support the \n"
		  "use of undefined variables/variable expression as the source of the \n"
		  "value to store by  a managed Write operation. Please define '%s'\n"
		  "in 'Definitions' section.\n" ,AddressParamString, AddressParamString);
	  yyerror(ErrorMessage);
	  free(ErrorMessage);

	  exit(1);

    }

    return InputVarExprID;
}







/***********************************************************************

typedef enum VariableTypeEnum
{
    SHARED_SIMPLE,
    SHARED_ARRAY,
    LOCAL_SIMPLE,
    LOCAL_ARRAY,
    LOCAL_SIMPLE_CONSTANT,
    LOCAL_ARRAY_CONSTANT,
    INVALID_VARIABLE_TYPE
} VariableType;


char* VariableTypeToString(VariableType InputType)
{
    unsigned MaxStringLenght=strlen("LOCAL_SIMPLE_CONSTANT")+1;
    char* VariableTypeString=malloc(sizeof(char)*MaxStringLenght);
    switch(InputType)
    {
	case SHARED_SIMPLE: sprintf(VariableTypeString,"SHARED_SIMPLE");
	case SHARED_ARRAY : sprintf(VariableTypeString,"SHARED_ARRAY");
	case LOCAL_SIMPLE : sprintf(VariableTypeString,"LOCAL_SIMPLE");
	case LOCAL_ARRAY  : sprintf(VariableTypeString,"");
	case LOCAL_SIMPLE_CONSTANT:  sprintf(VariableTypeString,"LOCAL_SIMPLE_CONSTANT");
	case LOCAL_ARRAY_CONSTANT :  sprintf(VariableTypeString,"LOCAL_ARRAY_CONSTANT");
	case INVALID_VARIABLE_TYPE:  sprintf(VariableTypeString,"INVALID");
	default :                   sprintf(VariableTypeString,"UNKNOWN");
    }
    return VariableTypeString;
}


dyn_arr_t  Dyn_SharedVariableList;
dyn_arr_t  Dyn_LocalVariableList;

typedef struct VariableStruct
{
    char* Name;
    char* Value;
    VariableType Type;
} Variable;

Variable  TempVariableContainer;


void Print_Variable(const Variable* TargetVariable)
{
    printf("Variable:\"%s\"\n"
	   "\tType = %s;\n"
	   "\tValue= %s;\n"
	   ,TargetVariable->Name, TargetVariable->
}

void Construct_Variable(const char* VariableName, VariableType Type, const char* ValueString)
{
    Variable* NewVariablePtr = NULL;
    if( Type == SHARED_SIMPLE || Type == SHARED_ARRAY )
    {
	Extend_DynamicArray(Dyn_SharedVariableList);
	unsigned LastElementPos = GetSize_DynamicArray(Dyn_SharedVariableList) - 1 ;
	NewVariablePtr = GetElement_DynamicArray( Dyn_SharedVariableList, LastElementPos, sizeof(Variable));
    }
    else if ( Type == LOCAL_SIMPLE || Type == LOCAL_ARRAY || Type == LOCAL_SIMPLE_CONSTANT || Type == LOCAL_ARRAY_CONSTANT )
    {
	Extend_DynamicArray(Dyn_LocalVariableList);
	unsigned LastElementPos = GetSize_DynamicArray(Dyn_LocalVariableList) - 1 ;
	NewVariablePtr = GetElement_DynamicArray( Dyn_LocalVariableList, LastElementPos, sizeof(Variable));
    }
    else
    {
	perror("ERROR: In Construct_Variable(): UNKNOWN Variable Type Encountered. Terminating...\n");
	assert(0);
    }

    Variable* NewVariable= (Variable*)malloc(sizeof(Variable));
    NewVariablePtr -> Name  = dupstr(VariableName);
    NewVariablePtr -> Value = dupstr(ValueString);
    NewVariablePtr -> Type  = Type;
}



unsigned FindSharedVariableByName(const char* VariableName)
{

}

unsigned FindLocalVariableByName(const char* VariableName)
{

}

void Construct_VariableExpression()
{

}

**********************************************************************/
