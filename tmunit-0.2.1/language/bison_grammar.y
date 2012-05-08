%{

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


#ifndef  __GRAMMAR_H__
#define  __GRAMMAR_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "syntax_error.h"
#include "syntax_debug.h"
#include "general.h"
#include "simulation_parameters.h"
#include "intermediate_representation.h"
#include "thread_execution_structure_generator.h"
#include "transaction_execution_structure_generator.h"
#include "schedule_execution_structure_generator.h"
#include "invariant_execution_structure_generator.h"  // For Invariant data structure
#include "variable_expression.h"
#include <ctype.h>  // for isupper function
#include "tm_interface.h" // for using TM functions in VarExprTestDefinitions


extern int yylex();
extern char* yytext;



unsigned TxDefElementNo;
unsigned TxOpNo;
unsigned TxBlockNo;
unsigned ScheduleNo;
unsigned InvariantNo;

struct TxBlockListReturnStruct
{
    bool BoundedRepetition;
    char* string;
};


struct ExpressionReturnStruct
{
    char* string;
    short int  Token;
    unsigned ExpressionType;
} ;

struct EvaluatedVariableExpressionStruct
{
    char* string;
    signed long  Value;
} ;

struct RangeInfoStruct
{
    char* string;
    unsigned long  MinValExpressionID;
    unsigned long  MaxValExpressionID;
    unsigned Increment;
} ;

struct ConditionReturnStruct
{
    char* string;
    unsigned ConditionTxOpContainerPos;
};

enum VariableTypeEnum
{
    SHARED,
    LOCAL,
    SHARED_CONSTANT,
    LOCAL_CONSTANT,
    SHARED_ARRAY,
    LOCAL_ARRAY,
    LOCAL_CONSTANT_ARRAY,
    SCOPED_LOCAL,
    SCOPED_LOCAL_CONSTANT,
    SCOPED_LOCAL_ARRAY,
    SCOPED_LOCAL_CONSTANT_ARRAY,
    VARIABLE_TYPE_NUM
};

struct VariableReturnStruct
{
    char* string;
    enum VariableTypeEnum VariableType;
};

#endif

%}


%union{
   char*     string;
   struct TxBlockListReturnStruct* TxBlockListReturn;
   struct EvaluatedVariableExpressionStruct* EvaluatedVarExpr;
   struct RangeInfoStruct*   RangeInfo;
   struct VariableExpressionStruct*   VarExprPtr;
   struct ConditionReturnStruct*  ConditionReturn;
   struct VariableReturnStruct*   VariableReturn;
} ;



%token <string> SEMICOLON EOF_TOKEN
%token <string> PROPERTIES_HEADER  DEFINITIONS_HEADER  TRANSACTIONS_HEADER THREADS_HEADER SCHEDULES_HEADER INVARIANTS_HEADER
%token <string> VALUE_ASSIGN  DEFINITION_ASSIGN
%token <string> READ_ACCESS_OP WRITE_ACCESS_OP  DELAY_OP ABORT_OP MEM_ALLOC_OP MEM_FREE_OP MEM_BARRIER_OP JUMP_OP

%token <string> OPEN_BRACKETS CLOSE_BRACKETS  OPEN_PARANTHESES CLOSE_PARANTHESES COMMA  BAR
%token <string> OPEN_CURLY_BRACKETS CLOSE_CURLY_BRACKETS LOOP_START  CONDITION_START RANGE_SEPERATOR
%token <string> LABEL NAME ARRAY_NAME NAME_ALL_CAPITALS LOCAL_VARIABLE_NAME LOCAL_ARRAY_NAME NUMBER FLOAT_NUMBER  COLON PERCENTAGE
 // ARRAY_NAME is a NAME followed by a "["
%token <string> NO_ABORT_INVARIANT_TOKEN

%token <string> EQUAL NOT_EQUAL GREATER_EQUAL SMALLER_EQUAL GREATER_THAN  SMALLER_THAN


%token <string> VAR_EXPR_TEST_SECT_HEADER  VAR_EXPR_EVAL


%left PLUS
%left MINUS
%left MULTIPLY DIVIDE

%left AND OR
%left NOT

%type <string> Config Section
%type <string> PropertiesSection  DefinitionsSection  TransactionsSection ThreadsSection SchedulesSection InvariantsSection
%type <string> PropertyDefList PropertyDef
%type <string> VariableDefList VariableDef ArrayInit  Delay
%type <string> TxDefList TxDef TxSpec
%type <string> TxSpecElement TxOp  TxLoopDef  TxConditionalDef ConditionalTxSpec ConditionalTxSpecElement DefaulfConditionTxSpecElement VarAssigns    Jump
%type <string> MemAccessOp  AbortOp  MemAllocOp  MemBarrierOp
%type <string> ConditionalExpression SimpleConditionalExpression  ComplexConditionalExpression ComplexConditionalExpressionElement ComplexConditionalUnit

%type <string> AdditiveArithmeticOp MultiplicativeArithmeticOp  RelationalOp  UnaryBooleanOp BooleanOp
%type <string> VarAssignList VarAssignment
%type <string> Constant FixedValue  RandomizedRange Value   DescriptionName Scope
%type <string> ThreadDefList ThreadDef ThreadType
%type <string> BoundedRepetitionTxBlockListElement UnboundedRepetitionTxBlockListElement
%type <string> TxChoiceList TxChoiceListElement
%type <string> ScheduleDefList ScheduleDef ScheduleSpec TxPortion
%type <string> InvariantDefList InvariantDef

%type <string> VarExprTestSection VarExprTestDefList VarExprTestDef
%type <string> VariableExpression VariableExpressionElement MultiplicativeVariableExpressionElementAccess MultiplicativeFactor ManagedMemAccess
%type <RangeInfo> Range LoopRange

%type <string> __defaultCondTxSpecElement_act_1

%type <TxBlockListReturn>  TxBlockList TxBlockListElement
%type <VarExprPtr> ArrayDef
%type <ConditionReturn> Condition   LoopCondition
%type <VariableReturn>  ArrayAccess Variable

%%

Config :
    Section
    | Section Config
    ;

Section:
    PropertiesSection  |   DefinitionsSection  |  TransactionsSection
    | ThreadsSection | SchedulesSection | InvariantsSection | VarExprTestSection
    ;


VarExprTestSection:
VAR_EXPR_TEST_SECT_HEADER _varExprTestSectstart_act  VarExprTestDefList
   {
       TM_EXIT_THREAD(TxDesc);
       TM_EXIT(TxDesc);
   }
   ;

     _varExprTestSectstart_act:
       {
	   VarExprTestEnabled = TRUE;
//	   Initialize_DynamicArray(&Dyn_VariableExpressionArray);
	   TM_INIT(TxDesc);
	   TM_INIT_THREAD(TxDesc);
      }

VarExprTestDefList:
   VarExprTestDef SEMICOLON
   | VarExprTestDefList VarExprTestDef SEMICOLON
   ;

VarExprTestDef:
   NAME VALUE_ASSIGN FixedValue
    {
	AddSharedVariableToVarExprList($1,$3);

	FREE_RULE_STRINGS(3);
    }
   | LOCAL_VARIABLE_NAME VALUE_ASSIGN FixedValue
    {
	AddLocalVariableToVarExprList($1,$3);

	FREE_RULE_STRINGS(3);
    }
   | ArrayDef VALUE_ASSIGN Value   // Corresponds to  -->  "ArrayInit SEMICOLON  " option of VariableDefList

      {
	  VarExpr* ArrayVarExpr = $1;
	  int ArrayElementNum = (int) (ArrayVarExpr -> OperandID[1] - ArrayVarExpr -> OperandID[0] +1) ;
	  assert(ArrayElementNum > 0);

	  int  ElementNo;
	  for( ElementNo=0; ElementNo < ArrayElementNum; ElementNo ++)
	  {
	      ((Word*)(ArrayVarExpr -> Addr))[ElementNo] = atoi($3);
	  }

	  REPORT_READ_INPUT("'%s' is assigned to all elements of array '%s'\n",$3, ArrayVarExpr->Name);
      }
   | ARRAY_NAME VariableExpression CLOSE_BRACKETS VALUE_ASSIGN Value
    {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr($1);
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';

	  // Checking array's existence
	  VarExpr* ArrayVarExpr;
	  FindVarExpr(ActualArrayName,&ArrayVarExpr);
	  bool ArrayExists = (ArrayVarExpr != NULL);
	  if( !ArrayExists)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Can NOT SET element of UNKNOWN ARRAY  '%s'. Terminating...\n", ActualArrayName);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  VarExpr* ElementVarExpr;
	  FindVarExpr($2,&ElementVarExpr);
	  if(ElementVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", $2);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  signed long ElementNoToAccess = EvaluateVarExpr(ElementVarExpr);
	  unsigned ArrayLowerLimit = ArrayVarExpr -> OperandID[0];
	  unsigned ArrayUpperLimit = ArrayVarExpr -> OperandID[1];
	  if( ElementNoToAccess >  ArrayUpperLimit )
	  {
	      fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
	      assert(0);
	  }
	  else if(  ElementNoToAccess < ArrayLowerLimit)
	  {
	      fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
	      assert(0);
	  }
	  signed long ElementIndexToAccess = ElementNoToAccess - ArrayLowerLimit;

	  // The following can be done with an Evaluation on the managed version of ArrayVarExpr
	  ((Word*)(ArrayVarExpr -> Addr))[ElementIndexToAccess] = atoi($5);


    }
   | LOCAL_ARRAY_NAME VariableExpression CLOSE_BRACKETS VALUE_ASSIGN Value
    {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr($1);
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';

	  // Checking array's existence
	  VarExpr* ArrayVarExpr;
	  FindVarExpr(ActualArrayName,&ArrayVarExpr);
	  bool ArrayExists = (ArrayVarExpr != NULL);
	  if( !ArrayExists)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Can NOT SET element of UNKNOWN ARRAY  '%s'. Terminating...\n", ActualArrayName);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  VarExpr* ElementVarExpr;
	  FindVarExpr($2,&ElementVarExpr);
	  if(ElementVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", $2);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  signed long ElementNoToAccess = EvaluateVarExpr(ElementVarExpr);
	  unsigned ArrayLowerLimit = ArrayVarExpr -> OperandID[0];
	  unsigned ArrayUpperLimit = ArrayVarExpr -> OperandID[1];
	  if( ElementNoToAccess >  ArrayUpperLimit )
	  {
	      fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
	      assert(0);
	  }
	  else if(  ElementNoToAccess < ArrayLowerLimit)
	  {
	      fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
	      assert(0);
	  }
	  signed long ElementIndexToAccess = ElementNoToAccess - ArrayLowerLimit;

	  ((Word*)(ArrayVarExpr -> Addr))[ElementIndexToAccess] = atoi($5);


    }
   | Constant VALUE_ASSIGN FixedValue
    {
	void* SharedVarAddr = (void *)malloc(sizeof(Word));


	VarExpr* CurrentVarExpr;
	FindVarExpr($1,&CurrentVarExpr);
	bool LocalVariableAlreadyExist = (CurrentVarExpr != NULL);
	if( !LocalVariableAlreadyExist)
	{
	    Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	    unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	    CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	    VAR_EXPR_Initialize(CurrentVarExpr);
	    CurrentVarExpr -> Name = dupstr($1);
	    CurrentVarExpr -> Type = VAR_SHARED_CONSTANT_UNMANAGED;
	    CurrentVarExpr -> Addr = SharedVarAddr;

	    Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	    LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	    CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	    unsigned ManagedVersionNameLength = strlen("&") + strlen($1) + 1 ;
	    char* ManagedVersionName = malloc(ManagedVersionNameLength*sizeof(char));
	    sprintf(ManagedVersionName,"&%s",$1);

	    VAR_EXPR_Initialize(CurrentVarExpr);
	    CurrentVarExpr -> Name = dupstr(ManagedVersionName);
	    CurrentVarExpr -> Type = VAR_SHARED_CONSTANT_MANAGED;
	    CurrentVarExpr -> Addr = SharedVarAddr;
	}
	*((Word*)(CurrentVarExpr -> Addr)) = (Word)atoi($3);
	if(VerboseParserOutput)
	    VAR_EXPR_Print(CurrentVarExpr);

	FREE_RULE_STRINGS(3);
    }
   | VAR_EXPR_EVAL OPEN_PARANTHESES VariableExpression CLOSE_PARANTHESES
   {
       VarExpr* EvaluatedVarExpr;
       FindVarExpr($3, &EvaluatedVarExpr);
       assert(EvaluatedVarExpr != NULL);
       signed long AccessedVarExprValue = EvaluateVarExpr(EvaluatedVarExpr);
       printf("Value evaluated for '%s'= %ld\n", $3 , AccessedVarExprValue);
   }
   | VAR_EXPR_EVAL OPEN_PARANTHESES ConditionalExpression CLOSE_PARANTHESES
   {
       VarExpr* EvaluatedVarExpr;
       FindVarExpr($3, &EvaluatedVarExpr);
       assert(EvaluatedVarExpr != NULL);

       START_TX(TxDesc,0);
       signed long AccessedVarExprValue = EvaluateVarExpr(EvaluatedVarExpr);
       printf("Value evaluated for '%s'= %ld\n", $3 , AccessedVarExprValue);
       COMMIT_TX(TxDesc);
   }


   ;


PropertiesSection:
   PROPERTIES_HEADER  __prop_sec_act_1  PropertyDefList
   {
   };


       __prop_sec_act_1:  /* empty */
       {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     PROPERTIES Section\n"
			     "-----------------------------------------------------------------------------\n" );
       };


PropertyDefList:
    PropertyDef SEMICOLON
    | PropertyDefList PropertyDef SEMICOLON
    ;

PropertyDef:
     NAME VALUE_ASSIGN FixedValue
     {
	 REPORT_READ_INPUT("'%s' is assigned to '%s'\n",$3,$1);
	 const char* ParameterName  = $1;
	 unsigned    ParameterValue = (unsigned)atoi($3);
	 CheckAndSetSimulationParameter(ParameterName,ParameterValue);
     }
     ;


DefinitionsSection:
    DEFINITIONS_HEADER  __def_sec_act_1  VariableDefList
    {
    };


       __def_sec_act_1:  /* empty */
       {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     DEFINITIONS Section\n"
			     "-----------------------------------------------------------------------------\n" );
       };



VariableDefList  :
     VariableDef SEMICOLON
     | ArrayInit SEMICOLON
     | VariableDefList VariableDef SEMICOLON
     | VariableDefList ArrayInit SEMICOLON
     ;


ArrayInit:
     ArrayDef VALUE_ASSIGN Value
      {
	  VarExpr* ArrayVarExpr = $1;
	  int ArrayElementNum = (int) (ArrayVarExpr -> OperandID[1] - ArrayVarExpr -> OperandID[0] +1) ;
	  assert(ArrayElementNum > 0);

	  int  ElementNo;
	  for( ElementNo=0; ElementNo < ArrayElementNum; ElementNo ++)
	  {
	      ((Word*)(ArrayVarExpr -> Addr))[ElementNo] = atoi($3);
	  }

	  REPORT_READ_INPUT("'%s' is assigned to all elements of array '%s'\n",$3, ArrayVarExpr->Name);
      }
    ;



ArrayDef:
     ARRAY_NAME Range CLOSE_BRACKETS
      {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr($1);
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';

//	  ALLOC_AND_RETURN_STRING("%s",ActualArrayName);

	  REPORT_READ_INPUT("\tSHARED Array '%s' with elements in range: '%s'\n",ActualArrayName, $2->string);
	  FREE_RULE_STRINGS(3);

	  VarExpr* ArrayVarExpr;
	  FindVarExpr(ActualArrayName, &ArrayVarExpr);
	  if( ArrayVarExpr == NULL)
	  {
	      AllocVarExpr(ActualArrayName, &ArrayVarExpr );
	  }

	  // Are all characters capital letters?
	  unsigned CharNum = strlen(ActualArrayName);
	  unsigned CharNo;
	  bool IsAllCapitals = TRUE;
	  for(CharNo=0; CharNo< CharNum; CharNo++)
	  {
	      int ReturnVal = isupper((ArrayVarExpr -> Name)[CharNo]);
	      bool CharIsCapitalLetter = (ReturnVal > 0);
	      if( !CharIsCapitalLetter)
	      {
		  IsAllCapitals = FALSE;
		  break;
	      }
	  }
	  if(IsAllCapitals)
	      ArrayVarExpr -> Type = VAR_SHARED_ARRAY_CONSTANT;
	  else
	      ArrayVarExpr -> Type = VAR_SHARED_ARRAY;

	  VarExpr* ArrayLowerBoundVarExpr  = GetVarExprPtr($2 -> MinValExpressionID);
	  assert( ArrayLowerBoundVarExpr != NULL);
	  VarExpr* ArrayUpperBoundVarExpr  = GetVarExprPtr($2 -> MaxValExpressionID);
	  assert( ArrayUpperBoundVarExpr != NULL);



	  ArrayVarExpr -> OperandID[0] = EvaluateVarExpr(ArrayLowerBoundVarExpr);
	  ArrayVarExpr -> OperandID[1] = EvaluateVarExpr(ArrayUpperBoundVarExpr);

	  int ArrayElementNum = ArrayVarExpr -> OperandID[1] - ArrayVarExpr -> OperandID[0] +1 ;
	  assert(ArrayElementNum >0);  // Checks whether Min and Max limits were not reversed (if they are reversed or smth else goes wrong assertion stops the program)

	  unsigned long ArraySizeInMemory = ArrayElementNum * sizeof(Word);
	  ArrayVarExpr -> Addr = (void*) malloc(ArraySizeInMemory);
	  // Initialize the array with zeros
	  memset(ArrayVarExpr -> Addr, ArraySizeInMemory,0);

	  $$ = ArrayVarExpr;

	  free(ActualArrayName);
      }
     | LOCAL_ARRAY_NAME Range CLOSE_BRACKETS
      {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr($1);
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';

//	  ALLOC_AND_RETURN_STRING("%s",ActualArrayName);

	  REPORT_READ_INPUT("\tLOCAL Array '%s' with elements in range: '%s'\n",$1, $2->string);
	  FREE_RULE_STRINGS(3);

	  VarExpr* ArrayVarExpr;
	  FindVarExpr(ActualArrayName, &ArrayVarExpr);
	  if( ArrayVarExpr == NULL)
	  {
	      AllocVarExpr(ActualArrayName, &ArrayVarExpr );
	  }

	  // Are all characters capital letters?
	  unsigned CharNum = strlen(ActualArrayName);
	  unsigned CharNo;
	  bool IsAllCapitals = TRUE;
	  for(CharNo=0; CharNo< CharNum; CharNo++)
	  {
	      int ReturnVal = isupper((ArrayVarExpr -> Name)[CharNo]);
	      bool CharIsCapitalLetter = (ReturnVal > 0);
	      if( !CharIsCapitalLetter)
	      {
		  IsAllCapitals = FALSE;
		  break;
	      }
	  }
	  if(IsAllCapitals)
	      ArrayVarExpr -> Type = VAR_LOCAL_ARRAY_CONSTANT;
	  else
	      ArrayVarExpr -> Type = VAR_LOCAL_ARRAY;

	  VarExpr* ArrayLowerBoundVarExpr  = GetVarExprPtr($2 -> MinValExpressionID);
	  assert( ArrayLowerBoundVarExpr != NULL);
	  VarExpr* ArrayUpperBoundVarExpr  = GetVarExprPtr($2 -> MaxValExpressionID);
	  assert( ArrayUpperBoundVarExpr != NULL);



	  ArrayVarExpr -> OperandID[0] = EvaluateVarExpr(ArrayLowerBoundVarExpr);
	  ArrayVarExpr -> OperandID[1] = EvaluateVarExpr(ArrayUpperBoundVarExpr);

	  int ArrayElementNum = ArrayVarExpr -> OperandID[1] - ArrayVarExpr -> OperandID[0] +1 ;
	  assert(ArrayElementNum >0);  // Checks whether Min and Max limits were not reversed (if they are reversed or smth else goes wrong assertion stops the program)

	  unsigned long ArraySizeInMemory = ArrayElementNum * sizeof(Word);
	  ArrayVarExpr -> Addr = (void*) malloc(ArraySizeInMemory);
	  // Initialize the array with zeros
	  memset(ArrayVarExpr -> Addr, ArraySizeInMemory,0);

	  $$ = ArrayVarExpr;

	  free(ActualArrayName);
      }
     ;


VariableDef:
   LOCAL_VARIABLE_NAME VALUE_ASSIGN FixedValue
    {
	VarExpr* CurrentVarExpr;
	FindVarExpr($1,&CurrentVarExpr);
	bool LocalVariableAlreadyExist = (CurrentVarExpr != NULL);
	if( !LocalVariableAlreadyExist)
	{
	    Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	    unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	    CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	    VAR_EXPR_Initialize(CurrentVarExpr);
	    CurrentVarExpr -> Name = dupstr($1);

	    // Are all characters (after the underscore) capital letters?
	    unsigned CharNum = strlen($1);
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
	CurrentVarExpr -> Value = (unsigned)atoi($3);
	if(VerboseParserOutput)
	    VAR_EXPR_Print(CurrentVarExpr);

	FREE_RULE_STRINGS(3);

    }
    | NAME VALUE_ASSIGN Value
       {

	   VarExpr* CurrentVarExpr;
	   FindVarExpr($1,&CurrentVarExpr);
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
	       CurrentVarExpr -> Name = dupstr($1);
	       CurrentVarExpr -> Type = VAR_SHARED_UNMANAGED;
	       CurrentVarExpr -> Addr = SharedVarAddr;
	       if(VerboseParserOutput)
		   VAR_EXPR_Print(CurrentVarExpr);

	       Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));

	       LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	       CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	       // Creating Managed copy
	       unsigned ManagedVersionNameLength = strlen("&") + strlen($1) + 1 ;
	       char* ManagedVersionName = malloc(ManagedVersionNameLength*sizeof(char));
	       sprintf(ManagedVersionName,"&%s",$1);

	       VAR_EXPR_Initialize(CurrentVarExpr);
	       CurrentVarExpr -> Name = dupstr(ManagedVersionName);
	       CurrentVarExpr -> Type = VAR_SHARED_MANAGED;
	       CurrentVarExpr -> Addr = SharedVarAddr;

	   }
	   *((Word*)(CurrentVarExpr -> Addr)) = (Word)atoi($3);
	   if(VerboseParserOutput)
	       VAR_EXPR_Print(CurrentVarExpr);

	   REPORT_READ_INPUT("'%s' is assigned to '%s'\n", $3, $1);
	   FREE_RULE_STRINGS(3);
       };
     | Constant VALUE_ASSIGN Value
       {
	   void* SharedVarAddr = (void *)malloc(sizeof(Word));


	   VarExpr* CurrentVarExpr;
	   FindVarExpr($1,&CurrentVarExpr);
	   bool LocalVariableAlreadyExist = (CurrentVarExpr != NULL);
	   if( !LocalVariableAlreadyExist)
	   {
	       Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	       unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	       CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	       VAR_EXPR_Initialize(CurrentVarExpr);
	       CurrentVarExpr -> Name = dupstr($1);
	       CurrentVarExpr -> Type = VAR_SHARED_CONSTANT_UNMANAGED;
	       CurrentVarExpr -> Addr = SharedVarAddr;

	       Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	       LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	       CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	       unsigned ManagedVersionNameLength = strlen("&") + strlen($1) + 1 ;
	       char* ManagedVersionName = malloc(ManagedVersionNameLength*sizeof(char));
	       sprintf(ManagedVersionName,"&%s",$1);

	       VAR_EXPR_Initialize(CurrentVarExpr);
	       CurrentVarExpr -> Name = dupstr(ManagedVersionName);
	       CurrentVarExpr -> Type = VAR_SHARED_CONSTANT_MANAGED;
	       CurrentVarExpr -> Addr = SharedVarAddr;
	   }
	   *((Word*)(CurrentVarExpr -> Addr)) = (Word)atoi($3);
	   if(VerboseParserOutput)
	       VAR_EXPR_Print(CurrentVarExpr);

	   REPORT_READ_INPUT("'%s' is assigned to '%s'\n", $3, $1);
	   FREE_RULE_STRINGS(3);
       };
     | Scope  LOCAL_VARIABLE_NAME VALUE_ASSIGN Value
       {
	   REPORT_READ_INPUT("'%s' is assigned to '%s:%s'\n", $4, $1,$2);
	   FREE_RULE_STRINGS(4);
       };
     | ARRAY_NAME VariableExpression CLOSE_BRACKETS VALUE_ASSIGN Value
       {
	   // Chopping last character (character '[') of array name
	   char*    ActualArrayName = dupstr($1);
	   unsigned LastCharPos     = strlen(ActualArrayName)-1;
	   ActualArrayName[LastCharPos]='\0';

	   // Checking array's existence
	   VarExpr* ArrayVarExpr;
	   FindVarExpr(ActualArrayName,&ArrayVarExpr);
	   bool ArrayExists = (ArrayVarExpr != NULL);
	   if( !ArrayExists)
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT SET element of UNKNOWN ARRAY  '%s'. Terminating...\n", ActualArrayName);
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }

	   VarExpr* ElementVarExpr;
	   FindVarExpr($2,&ElementVarExpr);
	   if(ElementVarExpr == NULL)
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", $2);
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }

	   signed long ElementNoToAccess = EvaluateVarExpr(ElementVarExpr);
	   unsigned ArrayLowerLimit = ArrayVarExpr -> OperandID[0];
	   unsigned ArrayUpperLimit = ArrayVarExpr -> OperandID[1];
	   if( ElementNoToAccess >  ArrayUpperLimit )
	   {
	       fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
	       assert(0);
	   }
	   else if(  ElementNoToAccess < ArrayLowerLimit)
	   {
	       fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
	       assert(0);
	   }
	   signed long ElementIndexToAccess = ElementNoToAccess - ArrayLowerLimit;

	   // The following can be done with an Evaluation on the managed version of ArrayVarExpr
	   ((Word*)(ArrayVarExpr -> Addr))[ElementIndexToAccess] = atoi($5);


       };
    | LOCAL_ARRAY_NAME VariableExpression CLOSE_BRACKETS VALUE_ASSIGN Value
       {
	   // Chopping last character (character '[') of array name
	   char*    ActualArrayName = dupstr($1);
	   unsigned LastCharPos     = strlen(ActualArrayName)-1;
	   ActualArrayName[LastCharPos]='\0';

	   // Checking array's existence
	   VarExpr* ArrayVarExpr;
	   FindVarExpr(ActualArrayName,&ArrayVarExpr);
	   bool ArrayExists = (ArrayVarExpr != NULL);
	   if( !ArrayExists)
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT SET element of UNKNOWN ARRAY  '%s'. Terminating...\n", ActualArrayName);
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }

	   VarExpr* ElementVarExpr;
	   FindVarExpr($2,&ElementVarExpr);
	   if(ElementVarExpr == NULL)
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", $2);
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }

	   signed long ElementNoToAccess = EvaluateVarExpr(ElementVarExpr);
	   unsigned ArrayLowerLimit = ArrayVarExpr -> OperandID[0];
	   unsigned ArrayUpperLimit = ArrayVarExpr -> OperandID[1];
	   if( ElementNoToAccess >  ArrayUpperLimit )
	   {
	       fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
	       assert(0);
	   }
	   else if(  ElementNoToAccess < ArrayLowerLimit)
	   {
	       fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
	       assert(0);
	   }
	   signed long ElementIndexToAccess = ElementNoToAccess - ArrayLowerLimit;

	   ((Word*)(ArrayVarExpr -> Addr))[ElementIndexToAccess] = atoi($5);


       };
     | Scope ArrayAccess VALUE_ASSIGN Value
       {
	   REPORT_READ_INPUT("'%s' is assigned to '%s:%s'\n", $4, $1, $2->string);
	   FREE_RULE_STRINGS(4);
       };
     | LOCAL_VARIABLE_NAME VALUE_ASSIGN SMALLER_THAN   Range  GREATER_THAN
       {
	   VarExpr* CurrentVarExpr;
	   unsigned CurrentVarExprID = FindVarExpr($1,&CurrentVarExpr);
	   bool LocalVariableAlreadyExist = (CurrentVarExpr != NULL);
	   if( !LocalVariableAlreadyExist)
	   {
	       Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	       CurrentVarExprID = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	       CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, CurrentVarExprID, sizeof(VarExpr));

	       VAR_EXPR_Initialize(CurrentVarExpr);
	       CurrentVarExpr -> Name = dupstr($1);

	       // Are all characters (after the underscore) capital letters?
	       unsigned CharNum = strlen($1);
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
		   CurrentVarExpr -> Type = OP_RANDOM_DIST_CONSTANT;
	       else
		   CurrentVarExpr -> Type = OP_RANDOM_DIST;

	   }
	   else if( CurrentVarExpr -> Type == OP_RANDOM_DIST_CONSTANT )
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT assign new value to CONSTANT LOCAL VARIABLE '%s'. Terminating...\n", $1);
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }


	   // Operand Map for random variables:
	   //   OperandID[0]: MinValExpressionID
	   //   OperandID[1]: MaxValExpressionID
	   //   OperandID[2]: Seed
	   //   OperandID[3]: Increment between values in the range
	   //   OperandID[4]: Random distribution function pointer
           // OperandID[3] and OperandID[4] are not yet used.

	   struct RangeInfoStruct* ParsedRangeInfo = $4;
	   CurrentVarExpr -> Operation    = 1; // Operation is set to non-zero for the variable to initially have a random value.
	   CurrentVarExpr -> OperandID[0] = ParsedRangeInfo -> MinValExpressionID ;
	   CurrentVarExpr -> OperandID[1] = ParsedRangeInfo -> MaxValExpressionID ;
	   CurrentVarExpr -> OperandID[2] = 0;
	   CurrentVarExpr -> OperandID[3] = 1;
	   CurrentVarExpr -> OperandID[4] = (unsigned long)NULL;

	   if(VerboseParserOutput)
	       VAR_EXPR_Print(CurrentVarExpr);


	   FREE_RULE_STRINGS(5);

       }

     ;





TransactionsSection:
     TRANSACTIONS_HEADER __tx_sec_act_1 TxDefList
     {

	 TxDefNum = GetSize_DynamicArray(&Dyn_TxDefArray);
	 TxDefArray = (TxInfo_t*) malloc(sizeof(TxInfo_t)*TxDefNum);

	 unsigned TxDefNo;
	 for(TxDefNo=0; TxDefNo < TxDefNum; TxDefNo++)
	 {
	     TX_INFO_Initialize( &(TxDefArray[TxDefNo]) );

	     TxInfo_t* CurrentTxDef    = GetElement_DynamicArray(&Dyn_TxDefArray,TxDefNo,sizeof(TxInfo_t));
	     unsigned CurrentTxDefOptionNum = 1;
	     TxDefArray[TxDefNo].Name = dupstr(CurrentTxDef ->  Name);

	     TxDefArray[TxDefNo].TxDefOptionNum = CurrentTxDefOptionNum;
	     TxDefArray[TxDefNo].TxOpNum  =  (unsigned*)malloc( CurrentTxDefOptionNum*sizeof(unsigned) );
	     TxDefArray[TxDefNo].TxOpList    =  (TxOpContainer_t**) malloc( CurrentTxDefOptionNum*sizeof(TxOpContainer_t*) ) ;
	     TxDefArray[TxDefNo].VarToUpdateNum  = CurrentTxDef -> VarToUpdateNum;
	     unsigned SizeOfVarToUpdateListInMemory = CurrentTxDef -> VarToUpdateNum * sizeof(unsigned);
	     TxDefArray[TxDefNo].VarListToUpdate = (unsigned*) malloc(SizeOfVarToUpdateListInMemory);
	     memcpy(TxDefArray[TxDefNo].VarListToUpdate, CurrentTxDef ->VarListToUpdate, SizeOfVarToUpdateListInMemory);


	     // We do not need the OptionConditionID list. It is just filled
	     // in for the copying of the data structure works correctly.
	     unsigned CopySizeInMemory = CurrentTxDefOptionNum*sizeof(int);
	     TxDefArray[TxDefNo].OptionConditionID     = (int*) malloc(CopySizeInMemory);
	     TxDefArray[TxDefNo].OutputVariableList    = (int*) malloc(CopySizeInMemory);
	     TxDefArray[TxDefNo].OutputCalculationList = (int*) malloc(CopySizeInMemory);
	     TxDefArray[TxDefNo].OptionConditionID[0]     = 0;
	     TxDefArray[TxDefNo].OutputVariableList[0]    = 0;
	     TxDefArray[TxDefNo].OutputCalculationList[0] = 0;


	     // We do not need any OptionNo. It is put here as a constant for backwards compatibility.
	     unsigned OptionNo=0;
	     unsigned TxOpListSizeInMemory = (CurrentTxDef -> TxOpNum[OptionNo])*sizeof(TxOpContainer_t);
	     TxDefArray[TxDefNo].TxOpList[OptionNo] = (TxOpContainer_t*)malloc(TxOpListSizeInMemory);
	     memcpy(TxDefArray[TxDefNo].TxOpList[OptionNo], CurrentTxDef ->TxOpList[OptionNo], TxOpListSizeInMemory);

	     memcpy(TxDefArray[TxDefNo].TxOpNum, CurrentTxDef -> TxOpNum,  CurrentTxDefOptionNum*sizeof(unsigned));

	     TxDefArray[TxDefNo].ReadOnly = CurrentTxDef ->  ReadOnly;

	     free(CurrentTxDef ->  Name);
	 }
	 Free_DynamicArray(&Dyn_TxDefArray);


     }
     ;


       __tx_sec_act_1:  /* empty */
       {

#ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	   InitializeTempThreadStructuresUsedInParsing();
#endif

#ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	   InitializeTempTransactionStructuresUsedInParsing();
#endif

	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     TRANSACTIONS Section\n"
			     "-----------------------------------------------------------------------------\n" );
       };


TxDefList:
     TxDef SEMICOLON
     | TxDefList TxDef SEMICOLON
     ;

TxDef:
     DescriptionName  __tx_sec_act_2    DEFINITION_ASSIGN TxSpec
       {

#ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	   Extend_DynamicArray(&Dyn_TxDefArray,sizeof(TxInfo_t));
	   unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_TxDefArray) - 1;
	   TxInfo_t* AddedElement = (TxInfo_t*)GetElement_DynamicArray(&Dyn_TxDefArray,LastAddedElementPos,sizeof(TxInfo_t));

	   TX_INFO_Initialize(AddedElement);
	   AddedElement -> Name = dupstr($1);
	   AddedElement -> TxDefOptionNum = 1;
	   AddedElement -> TxOpList   = (TxOpContainer_t**)malloc(sizeof(TxOpContainer_t*));
	   AddedElement -> TxOpNum    = (unsigned*)malloc(sizeof(unsigned));
	   AddedElement -> TxOpNum[0] = GetSize_DynamicArray(&CurrentTxOpList);
	   AddedElement -> VarToUpdateNum  =  (unsigned)GetSize_DynamicArray(&Dyn_VarExprToUpdateList);
	   AddedElement -> VarListToUpdate =  MakeStaticCopy_DynamicArray(&Dyn_VarExprToUpdateList, sizeof(unsigned));

	   unsigned SizeOfTxOpListInMemory =  (AddedElement -> TxOpNum[0])*sizeof(TxOpContainer_t);
	   AddedElement -> TxOpList[0] = (TxOpContainer_t*)malloc(SizeOfTxOpListInMemory);
	   unsigned TxOpNo;
	   for(TxOpNo=0; TxOpNo< AddedElement -> TxOpNum[0] ; TxOpNo++)
	   {
	       TxOpContainer_t* SourceTxOpContainer = (TxOpContainer_t*)GetElement_DynamicArray(&CurrentTxOpList,TxOpNo,sizeof(TxOpContainer_t));
	       TxOpContainer_t* TargetTxOpContainer = &(AddedElement -> TxOpList[0][TxOpNo]);
	       TX_OP_CONTAINER_Copy(SourceTxOpContainer, TargetTxOpContainer);
	   }


	   bool TransactionReadOnly = TRUE;
	   AddedElement -> InherentDelay = 0;
	   unsigned TxOpNum = AddedElement -> TxOpNum[0];
	   for(TxOpNo=0; TxOpNo< TxOpNum; TxOpNo++)
	   {
	       TxOpContainer_t* CurrentTxOpContainer = &(AddedElement -> TxOpList[0][TxOpNo]);

	       if(TransactionReadOnly )
	       {
		   bool CurrentTxOpIsAWrite = (CurrentTxOpContainer -> TxOperation == WRITE);
		   if(CurrentTxOpIsAWrite )
		   {
		       TransactionReadOnly = FALSE;
		       // if the inherent delay is also calculated in the same as this then remove this break
		       break;
		   }
	       }

/* 	       CurrentTxInfo -> InherentDelay +=  CurrentTxOpContainer -> PrecedingDelay; */
/* 	       bool LastTxOp = (TxOpNo == TxOpNum -1); */
/* 	       if( LastTxOp ) */
/* 		   CurrentTxInfo -> InherentDelay +=  CurrentTxOpContainer -> DelayBeforeCommit; */

	   }
	   AddedElement -> ReadOnly = TransactionReadOnly;
	   Clear_DynamicArray(&CurrentTxOpList);

	   if(ExecuteSchedule)
	   {
	       // Generate a Thread only containing the current transaction for schedule execution

	       Extend_DynamicArray(&Dyn_ScheduleThreadDefArray, sizeof(ThreadInfo_t));
	       unsigned AddedScheduleThreadInfoPos = GetSize_DynamicArray(&Dyn_ScheduleThreadDefArray)-1;
	       ThreadInfo_t* AddedScheduleThreadInfo = GetElement_DynamicArray(&Dyn_ScheduleThreadDefArray, AddedScheduleThreadInfoPos, sizeof(ThreadInfo_t));
	       AddedScheduleThreadInfo -> ID = AddedScheduleThreadInfoPos;

	       unsigned MaxDigitNumForScheduleThreadNum = 10;
	       unsigned SchedThreadNameLenght = strlen("Th")+ MaxDigitNumForScheduleThreadNum + 1;
	       char* SchedThreadName = malloc(SchedThreadNameLenght*sizeof(char));
	       sprintf(SchedThreadName,"Th%u",AddedScheduleThreadInfoPos+1);
	       AddedScheduleThreadInfo -> Name = SchedThreadName;

	       // There is only one transaction per thread
	       AddedScheduleThreadInfo -> TxContainerNum = 1;
	       AddedScheduleThreadInfo -> TxContainerList = (TxContainer_t*)malloc(sizeof(TxContainer_t));
	       (AddedScheduleThreadInfo -> TxContainerList)-> CandidateTxNum = 1;
	       (AddedScheduleThreadInfo -> TxContainerList)-> TxCandidateList = (TxCandidate_t*)malloc(sizeof(TxCandidate_t));
	       (AddedScheduleThreadInfo -> TxContainerList)-> TxCandidateList -> TxID = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> TxCandidateList -> Percentage = UNSPECIFIED_PERCENTAGE;
	       (AddedScheduleThreadInfo -> TxContainerList)-> NextContainerID[0] = 1;
	       (AddedScheduleThreadInfo -> TxContainerList)-> NextContainerID[1] = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> RepetitionCount = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> InitialRepetitionCount = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> CandidateSeed = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> CandidateSelectionFunc = NULL;
	       (AddedScheduleThreadInfo -> TxContainerList)-> PrecedingDelay[0] = 0   ;
	       (AddedScheduleThreadInfo -> TxContainerList)-> PrecedingDelay[1] = 0   ;
	       (AddedScheduleThreadInfo -> TxContainerList)-> LoopStartNode = FALSE   ;

	       AddedScheduleThreadInfo -> TxDefNum = 1;
	       AddedScheduleThreadInfo -> TxDefArray = (TxInfo_t*) malloc(sizeof(TxInfo_t));
	       TX_INFO_Copy(AddedElement, AddedScheduleThreadInfo -> TxDefArray);

	       ScheduleThreadNum++;
	   }

#endif


	   REPORT_READ_INPUT("\n");
       }
       ;


       __tx_sec_act_2:
       {
	 REPORT_READ_INPUT("%s is comprised of the following operations:\n",yytext);
	 Clear_DynamicArray(&Dyn_VarExprToUpdateList);
	 TxDefElementNo=0;
	 TxOpNo=0;
       }


// Had to use right recursion
TxSpec:
     TxSpecElement
      {
	  if ($1 != NULL)
	  {
	      REPORT_READ_INPUT("Ele[%u]: %s\n",TxDefElementNo,$1);
	      TxDefElementNo++;
	  }
      }

     | TxSpec COMMA TxSpecElement
       {
	   if ($3 != NULL)
	   {
	       REPORT_READ_INPUT("Ele[%u]: %s\n",TxDefElementNo,$3);
	       TxDefElementNo++;
	   }
       };

TxSpecElement:
     TxOp
       {
	   ALLOC_AND_RETURN_STRING("OpNo[%u]:%s",TxOpNo,$1);
	   FREE_RULE_STRINGS(1);
	   TxOpNo++;
       };
     | TxLoopDef
       {
	   ALLOC_AND_RETURN_STRING("%s",$1);
//	   $$=NULL;
	   FREE_RULE_STRINGS(1);
       };
     | TxConditionalDef
       {
	   ALLOC_AND_RETURN_STRING("%s",$1);
	   FREE_RULE_STRINGS(1);
       };
     | VarAssigns
       {

	   unsigned TxOpListSize  = GetSize_DynamicArray(&CurrentTxOpList);
	   bool     TxOpListEmpty = (TxOpListSize == 0);
	   TxOpContainer_t* TxOpContainerToAttach = NULL;

	   if( TxOpListEmpty  )
	   {
	       // Generate New TxOp and set TxOpContainerToAttach with its pointer
	       TxOpInfo_t  CurrentOpInfo;
	       CurrentOpInfo.Delay = 0 ;
	       CurrentOpInfo.Op    = INVALID ;

	       GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

	       // We set the pointer of the first element of CurrentTxOpList to TxOpContainerToAttach
	       TxOpContainerToAttach = (TxOpContainer_t*) GetElement_DynamicArray(&CurrentTxOpList, 0, sizeof(TxOpContainer_t));
	   }
	   else
	   {
	       unsigned LastTxOpPos = TxOpListSize  - 1 ;
	       TxOpContainerToAttach = GetElement_DynamicArray(&CurrentTxOpList, LastTxOpPos, sizeof(TxOpContainer_t) );
	   }

	   TxOpContainerToAttach -> VarAssignNum = GetSize_DynamicArray(&Dyn_VarAssignList);
	   TxOpContainerToAttach -> VarAssigns   = MakeStaticCopy_DynamicArray(&Dyn_VarAssignList, sizeof(var_assign_t));

	   Clear_DynamicArray(&Dyn_VarAssignList);

	   ALLOC_AND_RETURN_STRING("%s",$1);
	   FREE_RULE_STRINGS(1);
       };
     | LABEL
       {

          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = LABEL_OP ;

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

		  // Adding  the label name to the last added TxOpContainer
		  unsigned LastTxOpNo = GetSize_DynamicArray(&CurrentTxOpList) - 1;
		  TxOpContainer_t* LabelOpContainer = (TxOpContainer_t*) GetElement_DynamicArray(&CurrentTxOpList,LastTxOpNo, sizeof(TxOpContainer_t));
		     // We would like to stript the @ sign at the beginning of
		     // LABEL string so we start copying from the element 1 of
		     // $1 instead of its 0th element
		  LabelOpContainer -> Label = dupstr(&($1[1]));


//		  CurrentDelayVal = 0 ;

	      }

	  #endif

	   ALLOC_AND_RETURN_STRING("Label %s",$1);
	   FREE_RULE_STRINGS(1);
       }
     | Jump
       {
	   ALLOC_AND_RETURN_STRING("%s",$1);
	   FREE_RULE_STRINGS(1);
       };
     | Delay
       {
	   ALLOC_AND_RETURN_STRING("%s",$1);
	   FREE_RULE_STRINGS(1);
       };
     ;

Delay:
     DELAY_OP VariableExpression CLOSE_PARANTHESES
      {
	  ALLOC_AND_RETURN_STRING("DELAY determined by the following variable expression:'%s'", $2);
	  FREE_RULE_STRINGS(3);
	  $$= $2;
      };

TxOp:
     MemAccessOp | AbortOp | MemAllocOp | MemBarrierOp
     ;

MemAccessOp:
     READ_ACCESS_OP  VariableExpression CLOSE_PARANTHESES
       {
          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = READ ;

//		  CurrentOpInfo.AddrGenIDList[0] = CurrentAssociatedAddrGenIDArray[0];
//		  CurrentOpInfo.AddrGenIDList[1] = CurrentAssociatedAddrGenIDArray[1];

		  CurrentOpInfo.AddrOp = GetMemAccessOpAddressParameter($2);
		  CurrentOpInfo.AddrGenIDList[0] = (unsigned) -1;

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

//		  CurrentDelayVal = 0 ;

//		  CurrentAssociatedAddrGenIDArray[0] = INVALID_ADDR_GEN_ID;
//		  CurrentAssociatedAddrGenIDArray[1] = INVALID_ADDR_GEN_ID;
//		  CurrentAddrOp = INVALID_ADDR_OP;
	      }

	  #endif

	  ALLOC_AND_RETURN_STRING("READ from address of '%s'", $2);
 	  FREE_RULE_STRINGS(3);

       }
     | READ_ACCESS_OP VariableExpression COMMA VariableExpression  CLOSE_PARANTHESES
       {

          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = READ ;

//		  CurrentOpInfo.AddrGenIDList[0] = CurrentAssociatedAddrGenIDArray[0];
//		  CurrentOpInfo.AddrGenIDList[1] = CurrentAssociatedAddrGenIDArray[1];

		  CurrentOpInfo.AddrOp = GetMemAccessOpAddressParameter($2);
		  CurrentOpInfo.AddrGenIDList[0] = GetReadAccessTargetParameter($4);

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

//		  CurrentDelayVal = 0 ;

//		  CurrentAssociatedAddrGenIDArray[0] = INVALID_ADDR_GEN_ID;
//		  CurrentAssociatedAddrGenIDArray[1] = INVALID_ADDR_GEN_ID;
//		  CurrentAddrOp = INVALID_ADDR_OP;
	      }

	  #endif

	  ALLOC_AND_RETURN_STRING("READ from address of '%s' into '%s'.",$2, $4);
 	  FREE_RULE_STRINGS(5);
       }
     | WRITE_ACCESS_OP  VariableExpression CLOSE_PARANTHESES
       {

          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = WRITE ;

//		  CurrentOpInfo.AddrGenIDList[0] = CurrentAssociatedAddrGenIDArray[0];
//		  CurrentOpInfo.AddrGenIDList[1] = CurrentAssociatedAddrGenIDArray[1];
		  CurrentOpInfo.AddrOp = GetMemAccessOpAddressParameter($2);
		  CurrentOpInfo.AddrGenIDList[0] = (unsigned) -1;

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

//		  CurrentDelayVal = 0 ;

//		  CurrentAssociatedAddrGenIDArray[0] = INVALID_ADDR_GEN_ID;
//		  CurrentAssociatedAddrGenIDArray[1] = INVALID_ADDR_GEN_ID;
//		  CurrentAddrOp = INVALID_ADDR_OP;
	      }
	 #endif

	  ALLOC_AND_RETURN_STRING("WRITE to address of '%s'.",$2);
 	  FREE_RULE_STRINGS(3);

       }
     | WRITE_ACCESS_OP VariableExpression COMMA VariableExpression  CLOSE_PARANTHESES
       {


          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = WRITE ;

//		  CurrentOpInfo.AddrGenIDList[0] = CurrentAssociatedAddrGenIDArray[0];
//		  CurrentOpInfo.AddrGenIDList[1] = CurrentAssociatedAddrGenIDArray[1];
		  CurrentOpInfo.AddrOp = GetMemAccessOpAddressParameter($2);
		  CurrentOpInfo.AddrGenIDList[0] = GetWriteAccessTargetParameter($4);

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

//		  CurrentDelayVal = 0 ;

//		  CurrentAssociatedAddrGenIDArray[0] = INVALID_ADDR_GEN_ID;
//		  CurrentAssociatedAddrGenIDArray[1] = INVALID_ADDR_GEN_ID;
//		  CurrentAddrOp = INVALID_ADDR_OP;
	      }
	 #endif

	  ALLOC_AND_RETURN_STRING("WRITE  '%s' to address of '%s'.",$4, $2);
 	  FREE_RULE_STRINGS(5);
       }
     ;


AbortOp:
     ABORT_OP FixedValue CLOSE_PARANTHESES
      {

          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = ABORT ;

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

	      }
	 #endif


	  ALLOC_AND_RETURN_STRING("ABORT with probability '%s'",$2);
 	  FREE_RULE_STRINGS(3);
      };

MemAllocOp:
     MEM_ALLOC_OP VariableExpression COMMA VariableExpression CLOSE_PARANTHESES
      {
	  ALLOC_AND_RETURN_STRING("ALLOCATE MEMORY of size '%s' (start address '%s')",$4, $2);
 	  FREE_RULE_STRINGS(5);
      };

     | MEM_FREE_OP VariableExpression CLOSE_PARANTHESES
      {
	  ALLOC_AND_RETURN_STRING("FREE MEMORY at address '%s'",$2);
 	  FREE_RULE_STRINGS(3);
      };

MemBarrierOp:
     MEM_BARRIER_OP NAME COMMA NAME  CLOSE_PARANTHESES
      {

	  ALLOC_AND_RETURN_STRING("MEMORY BARRIER (Name: '%s', Type: '%s')",$2,$4);
 	  FREE_RULE_STRINGS(5);
      };

TxLoopDef:
     LOOP_START LoopCondition __txLoopDef_act_1 COLON TxSpec  CLOSE_CURLY_BRACKETS
      {
	  unsigned LoopConditionTxOpPos = $2 -> ConditionTxOpContainerPos  ;
	  unsigned LoopEndTxOpPos = GetSize_DynamicArray(&CurrentTxOpList) - 1 ;
	  char* String = dupstr($2->string);

	  // Make the forward link to the next operation after the loop (Link to jump over the loop)
	  // LOOP_BACK in following function is named like that due to reuse of previous version of tmunit.
	  // Actually it corresponds to a BRANCH or a JUMP in the new design.
	  InsertBranchAmongTxOpContainers(&CurrentTxOpList, LoopConditionTxOpPos, LoopEndTxOpPos+1, LOOP_BACK, 0);

	  // Make the backwards link from last element of the loop to the conditional tx_op_container.
	  // Again NEXT is the reuse of the previous version of tmunit.
	  InsertBranchAmongTxOpContainers(&CurrentTxOpList, LoopEndTxOpPos, LoopConditionTxOpPos,  NEXT, 0);


	  ALLOC_AND_RETURN_STRING("LOOP END (for the loop with condition: '%s')",String);
	  free(String);
 	  FREE_RULE_STRINGS(6);
      };

      __txLoopDef_act_1:
        {
	    // yyvsp[0].string  is the string corresponding to the
	    // 'LoopCondition' in the above 'TxLoopDef' rule
	    REPORT_READ_INPUT("Ele[%u]: LOOP (Looping Condition: '%s')\n",TxDefElementNo, yyvsp[0].ConditionReturn -> string);
	    TxDefElementNo++;
	}

LoopCondition:
     Condition
       {
	   $$ = $1;
//	   FREE_RULE_STRINGS(1);
       }

     | Variable VALUE_ASSIGN LoopRange
       {
	   VarExpr* LoopIteratorVarExpr;
	   unsigned LoopIteratorID = FindVarExpr($1->string, &LoopIteratorVarExpr);
	   if(LoopIteratorVarExpr== NULL)
	   {
	       LoopIteratorID = AllocVarExpr($1->string, &LoopIteratorVarExpr);
	       assert(LoopIteratorVarExpr != NULL);
	       LoopIteratorVarExpr -> Type = VAR_LOCAL_SIMPLE;
	       LoopIteratorVarExpr -> Value = 0;
	   }

//	   VarExpr* LowerLimitVarExpr = GetVarExprPtr($3 -> MinValExpressionID);
//	   LoopIteratorVarExpr -> Value = EvaluateVarExpr(LowerLimitVarExpr);

	   VarExpr* UpperLimitVarExpr = GetVarExprPtr($3 -> MaxValExpressionID);

	   unsigned LoopIteratorConditionStringLength = strlen($1->string) + strlen("<=") + strlen(UpperLimitVarExpr->Name) + 1;
	   char* LoopIteratorConditionString = malloc(LoopIteratorConditionStringLength*sizeof(char));
	   sprintf(LoopIteratorConditionString,"%s<=%s",$1->string,UpperLimitVarExpr->Name);

	   VarExpr* LoopConditionVarExpr;
	   unsigned LoopConditionVarExprID = AllocVarExpr(LoopIteratorConditionString, &LoopConditionVarExpr);
	   LoopConditionVarExpr -> Type = OP_RELATIONAL;
	   LoopConditionVarExpr -> Operation = SMALLER_EQUAL;
	   LoopConditionVarExpr -> OperandID[0] = LoopIteratorID;
	   LoopConditionVarExpr -> OperandID[1] = $3 -> MaxValExpressionID;
	   LoopConditionVarExpr -> OperandID[2] = $3 -> MinValExpressionID;

	   unsigned IteratorIncementStringLenght = strlen($1->string) + strlen("+") + strlen("9999")+ 1;
	   char* IteratorIncementString = (char *)malloc(IteratorIncementStringLenght * sizeof(char));
	   sprintf(IteratorIncementString,"%s+%u",$1->string, $3->Increment);

	   unsigned IncrementValueExprStringLenght = strlen("9999")+ 1;
	   char* IncrementValueExprString = (char*) malloc(IncrementValueExprStringLenght*sizeof(char));
	   sprintf(IncrementValueExprString,"%u", $3->Increment);


	   VarExpr* IncrementValueExpr;
	   unsigned IncrementValueExprID = FindVarExpr(IncrementValueExprString, &IncrementValueExpr);
	   if( IncrementValueExpr == NULL)
	   {
	       IncrementValueExprID = AllocVarExpr(IncrementValueExprString, &IncrementValueExpr);
	       IncrementValueExpr -> Type = VAR_LOCAL_SIMPLE_CONSTANT;
	       IncrementValueExpr -> Value = $3->Increment;
	   }


	   VarExpr* LoopIteratorIncementExpr;
	   unsigned LoopIteratorIncementExprID = FindVarExpr(IteratorIncementString, &LoopIteratorIncementExpr);
	   if(LoopIteratorIncementExpr == NULL)
	   {
	       LoopIteratorIncementExprID = AllocVarExpr(IteratorIncementString, &LoopIteratorIncementExpr);
	       LoopIteratorIncementExpr -> Type = OP_ARITH;
	       LoopIteratorIncementExpr -> Operation = PLUS;
	       LoopIteratorIncementExpr -> OperandID[0] = LoopIteratorID;
	       LoopIteratorIncementExpr -> OperandID[1] = IncrementValueExprID;
	   }


	   // Generating a tx_op_container for the above condition.
	   TxOpInfo_t  CurrentOpInfo;
	   CurrentOpInfo.Delay = 0 ;
	   CurrentOpInfo.Op    = INVALID ;
	   CurrentOpInfo.AddrOp = 0;

	   GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;
	   unsigned LoopConditionTxOpPos = GetSize_DynamicArray(&CurrentTxOpList) - 1 ;
	   TxOpContainer_t* LoopConditionTxOpContainer = GetElement_DynamicArray(&CurrentTxOpList, LoopConditionTxOpPos, sizeof(TxOpContainer_t) );
	   LoopConditionTxOpContainer -> ConditionExprPos =  LoopConditionVarExprID;

	   LoopConditionTxOpContainer -> LoopIteratorContainer = TRUE;
	   LoopConditionTxOpContainer -> LoopExecuting = FALSE;
	   LoopConditionTxOpContainer -> VarAssignNum = 1;
	   LoopConditionTxOpContainer -> VarAssigns = (var_assign_t*)malloc(sizeof(var_assign_t));
	   (LoopConditionTxOpContainer -> VarAssigns[0]).AssignedVarID = LoopIteratorID;
	   (LoopConditionTxOpContainer -> VarAssigns[0]).EvaluatedVarExprID = LoopIteratorIncementExprID;


           struct ConditionReturnStruct* ReturnVal = (struct ConditionReturnStruct*)malloc(sizeof(struct ConditionReturnStruct));

	   unsigned ReturnStringSize = strlen($1->string) + strlen($2) + strlen($3->string) +1 ;
	   char* ReturnString = (char*) malloc(ReturnStringSize * sizeof(char));
	   sprintf(ReturnString,"'%s%s%s'",$1->string, $2, $3->string);

	   ReturnVal-> string= ReturnString;
	   ReturnVal-> ConditionTxOpContainerPos = LoopConditionTxOpPos;
	   $$ = ReturnVal;

//	   ALLOC_AND_RETURN_STRING("'%s%s%s'",$1->string, $2, $3->string);
	   FREE_RULE_STRINGS(3);
       }


     ;

LoopRange:
     OPEN_BRACKETS Range CLOSE_BRACKETS
      {
	  REPORT_READ_INPUT("\tEncountered Range '%s' in LOOP definition.\n", $2 -> string);
//	  ALLOC_AND_RETURN_STRING("%s", $2 -> string);
	  $$ = $2;
	  FREE_RULE_STRINGS(3);
      };

TxConditionalDef:
     CONDITION_START  ConditionalTxSpec CLOSE_CURLY_BRACKETS
      {
	  unsigned  IfElseBlockSuccessorTxOpContainerPos = GetSize_DynamicArray( &CurrentTxOpList );

	  unsigned* ConditionTerminatingTxOpArray = (unsigned*)(ConditionTerminationTxOpList.ArrayStartAddress);
	  unsigned TxOpNum = GetSize_DynamicArray( &ConditionTerminationTxOpList );
	  unsigned TxOpNo = 0;
	  for(TxOpNo =0; TxOpNo< TxOpNum; TxOpNo++)
	  {
	      unsigned ConditionTerminatingTxOpPos     = ConditionTerminatingTxOpArray[TxOpNo];
	      assert(ConditionTerminatingTxOpPos < IfElseBlockSuccessorTxOpContainerPos );
	      InsertBranchAmongTxOpContainers(&CurrentTxOpList, ConditionTerminatingTxOpPos, IfElseBlockSuccessorTxOpContainerPos, NEXT, 0);
	  }

	  Clear_DynamicArray( &ConditionTerminationTxOpList );
	  EndOfIfElseBlock = FALSE;

	  ALLOC_AND_RETURN_STRING("Encountered CONDITIONAL EXECUTION BLOCK with following conditions:\n%s",$2);
	  FREE_RULE_STRINGS(3);
      };
     ;


ConditionalTxSpec:
     ConditionalTxSpecElement
      {
	  ALLOC_AND_RETURN_STRING("\t - %s",$1);
	  FREE_RULE_STRINGS(1);
      };
     | ConditionalTxSpec BAR ConditionalTxSpecElement
      {
	  ALLOC_AND_RETURN_STRING("%s\n\t - %s",$1,$3);
	  FREE_RULE_STRINGS(3);
      };
     | ConditionalTxSpec BAR DefaulfConditionTxSpecElement
      {
	  EndOfIfElseBlock = TRUE;
	  ALLOC_AND_RETURN_STRING("%s\n\t - ELSE",$1);
	  FREE_RULE_STRINGS(3);
      };
     ;

ConditionalTxSpecElement:
     Condition __conditionalTxSpecElement_act_1 COLON TxSpec
      {
	  struct ConditionReturnStruct* ConditionInfo = $1;


	  unsigned ConditionalBlockStartTxOpPos = ConditionInfo-> ConditionTxOpContainerPos;
	  unsigned ConditionalBlockSuccessorTxOpPos =  GetSize_DynamicArray(&CurrentTxOpList) ;
	  // The successor block should be at least 1 tx_op_container further
	  // than the initial conditional tx_op_container ( a distance of 1
          // is  when no tx_op defined in the conditional block)
	  assert( ConditionalBlockSuccessorTxOpPos - ConditionalBlockStartTxOpPos >= 1);

	  // Make the forward link to the next operation after the condition (either another condition or some TxOp)
	  // LOOP_BACK in following function is named like that due to reuse of previous version of tmunit.
	  // Actualy it corresponds to a BRANCH or a JUMP in the new design.
	  InsertBranchAmongTxOpContainers(&CurrentTxOpList, ConditionalBlockStartTxOpPos, ConditionalBlockSuccessorTxOpPos, LOOP_BACK, 0);


	  Extend_DynamicArray( &ConditionTerminationTxOpList,sizeof(unsigned));
	  unsigned LastAddedElementPos = GetSize_DynamicArray(&ConditionTerminationTxOpList) - 1;
	  unsigned * CurrentElement = (unsigned*) GetElement_DynamicArray(&ConditionTerminationTxOpList, LastAddedElementPos , sizeof(unsigned));
	  *CurrentElement = ConditionalBlockSuccessorTxOpPos -1;

	  ALLOC_AND_RETURN_STRING("%s",ConditionInfo-> string);
	  FREE_RULE_STRINGS(4);
      };

        __conditionalTxSpecElement_act_1:
         {
	     // yyvsp[1].string  indicates the  string returned for the "Condition"  in ConditionalTxSpecElement rule.
	     REPORT_READ_INPUT("Parsing behaviour for  CONDITION: '%s'\n",yyvsp[1].string);

	     if( EndOfIfElseBlock)
	     {
		 char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		 sprintf(ErrorMessage,"Encountered UNEXPECTED CONDITION BLOCK (with condition '%s') after an ELSE block.", yyvsp[1].string );
		 yyerror(ErrorMessage);
		 free(ErrorMessage);
		 exit(1);

	     }

         }
DefaulfConditionTxSpecElement:
     __defaultCondTxSpecElement_act_1 TxSpec
     ;

        __defaultCondTxSpecElement_act_1:
         {
	     REPORT_READ_INPUT("Parsing behaviour for  CONDITION: 'ELSE'\n");
	 }

Condition:
     OPEN_BRACKETS ConditionalExpression CLOSE_BRACKETS
      {

	  char* ConditionString = $2;

	  VarExpr* ConditionVarExpr;
	  unsigned ConditionVarExprID = FindVarExpr(ConditionString, &ConditionVarExpr);
	  if( ConditionVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN Conditional Expression '%s' is encountered while constructing conditional transaction block.\n", ConditionString);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }

	  TxOpInfo_t  CurrentOpInfo;
	  CurrentOpInfo.Delay = 0 ;
	  CurrentOpInfo.Op    = INVALID ;
	  CurrentOpInfo.AddrOp = 0;

	  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;
	  unsigned ConditionTxOpPos = GetSize_DynamicArray(&CurrentTxOpList) - 1 ;
	  TxOpContainer_t* ConditionTxOpContainer = GetElement_DynamicArray(&CurrentTxOpList, ConditionTxOpPos, sizeof(TxOpContainer_t) );

	  ConditionTxOpContainer -> ConditionExprPos =  ConditionVarExprID;

	  struct ConditionReturnStruct* ReturnVal = (struct ConditionReturnStruct*)malloc(sizeof(struct ConditionReturnStruct));
	  ReturnVal-> string= dupstr(ConditionString);
	  ReturnVal-> ConditionTxOpContainerPos = ConditionTxOpPos;

	  $$ = ReturnVal;




//	  ALLOC_AND_RETURN_STRING("%s",$2);
	  FREE_RULE_STRINGS(3);
      };


ConditionalExpression:
     SimpleConditionalExpression
      {
	  ALLOC_AND_RETURN_STRING("%s",$1);
	  FREE_RULE_STRINGS(1);
      };
     | ComplexConditionalExpression
      {
	  ALLOC_AND_RETURN_STRING("%s",$1);
	  FREE_RULE_STRINGS(1);
      };

SimpleConditionalExpression:
     VariableExpression  RelationalOp  VariableExpression
     {
	 // Check the existence of both Variable Expressions (if they exist, record their IDs)
	 VarExpr* FirstExpr;
	 unsigned FirstExprID = FindVarExpr($1, &FirstExpr);
	 if( FirstExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Variable Expression '%s' is encountered in Conditinal Expression. Terminating...\n", $1);
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }
	 VarExpr* SecondExpr;
	 unsigned SecondExprID = FindVarExpr($3, &SecondExpr);
	 if( SecondExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Variable Expression '%s' is encountered in Conditinal Expression. Terminating...\n", $3);
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }



	 unsigned ConditionalExpressionStringLength = strlen($1) + strlen($2) + strlen($3) +1;
	 char* ConditionalExpressionString = (char*)malloc(ConditionalExpressionStringLength*sizeof(char));
	 sprintf(ConditionalExpressionString,"%s%s%s",$1, $2, $3);

	 VarExpr* ConditionalVarExpr;
	 FindOrAllocVarExpr(ConditionalExpressionString, &ConditionalVarExpr);
	 assert(ConditionalVarExpr != NULL);
	 ConditionalVarExpr -> Type = OP_RELATIONAL;
	 ConditionalVarExpr -> Operation = ResolveOperationType($2);
	 ConditionalVarExpr -> OperandID[0] = FirstExprID;
	 ConditionalVarExpr -> OperandID[1] = SecondExprID;

	 $$ = ConditionalExpressionString;

	 FREE_RULE_STRINGS(3);
	 REPORT_READ_INPUT("\tEncountered SIMPLE CONDITIONAL EXPRESSION '%s'\n",$$);
     }
     ;

ComplexConditionalExpressionElement:
     OPEN_PARANTHESES SimpleConditionalExpression CLOSE_PARANTHESES
     {
	 ALLOC_AND_RETURN_STRING("%s%s%s",$1,$2,$3);
	 FREE_RULE_STRINGS(3);
	 REPORT_READ_INPUT("\tEncountered COMPLEX CONDITIONAL EXPRESSION (without any boolean op) : '%s'\n",$$);
     }
     | UnaryBooleanOp OPEN_PARANTHESES SimpleConditionalExpression CLOSE_PARANTHESES
     {
	 // Check the existence of the SimpleConditionalExpression (if they exist, record their IDs)
	 VarExpr* SimpleCondExpr;
	 unsigned SimpleCondExprID = FindVarExpr($3, &SimpleCondExpr);
	 if( SimpleCondExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Simple Conditional Expression '%s' is encountered in Complex Conditional Expression. Terminating...\n", $3);
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }

	 unsigned ConditionalExpressionStringLength = strlen($1) + strlen($2) + strlen($3) + strlen($4) + 1;
	 char* ConditionalExpressionString = (char*)malloc(ConditionalExpressionStringLength*sizeof(char));
	 sprintf(ConditionalExpressionString,"%s%s%s%s",$1, $2, $3, $4);

	 VarExpr* ConditionalVarExpr;
	 FindOrAllocVarExpr(ConditionalExpressionString, &ConditionalVarExpr);
	 assert(ConditionalVarExpr != NULL);
	 ConditionalVarExpr -> Type = OP_BOOLEAN_UNARY;
	 ConditionalVarExpr -> Operation = ResolveOperationType($1);
	 ConditionalVarExpr -> OperandID[0] = SimpleCondExprID;

	 $$ = ConditionalExpressionString;

	 FREE_RULE_STRINGS(4);
	 REPORT_READ_INPUT("\tEncountered COMPLEX CONDITIONAL EXPRESSION (with a UNARY boolean op) : '%s'\n",$$);
     };



ComplexConditionalUnit:
   ComplexConditionalExpressionElement
    {
	 ALLOC_AND_RETURN_STRING("%s",$1);
	 FREE_RULE_STRINGS(1);
    }
   | OPEN_PARANTHESES ComplexConditionalExpression CLOSE_PARANTHESES
     {
	    char* AccessedConditionalString = $2;
	    unsigned NewStringSize = strlen("(") + strlen(AccessedConditionalString) + strlen(")") +1;
	    char* ReturnString = malloc(NewStringSize*sizeof(char));
	    sprintf(ReturnString,"(%s)",AccessedConditionalString);
	    $$ = ReturnString;
	    FREE_RULE_STRINGS(1);
     }
   | UnaryBooleanOp OPEN_PARANTHESES ComplexConditionalExpression CLOSE_PARANTHESES
     {
	 // Check the existence of the SimpleConditionalExpression (if they exist, record their IDs)
	 VarExpr* SimpleCondExpr;
	 unsigned SimpleCondExprID = FindVarExpr($3, &SimpleCondExpr);
	 if( SimpleCondExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Complex Conditional Expression '%s' is encountered in Complex Conditional Expression. Terminating...\n", $3);
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }

	 unsigned ConditionalExpressionStringLength = strlen($1) + strlen($2) + strlen($3) + strlen($4) + 1;
	 char* ConditionalExpressionString = (char*)malloc(ConditionalExpressionStringLength*sizeof(char));
	 sprintf(ConditionalExpressionString,"%s%s%s%s",$1, $2, $3, $4);

	 VarExpr* ConditionalVarExpr;
	 FindOrAllocVarExpr(ConditionalExpressionString, &ConditionalVarExpr);
	 assert(ConditionalVarExpr != NULL);
	 ConditionalVarExpr -> Type = OP_BOOLEAN_UNARY;
	 ConditionalVarExpr -> Operation = ResolveOperationType($1);
	 ConditionalVarExpr -> OperandID[0] = SimpleCondExprID;

	 $$ = ConditionalExpressionString;

	 FREE_RULE_STRINGS(4);
	 REPORT_READ_INPUT("\tEncountered COMPLEX CONDITIONAL EXPRESSION (with a UNARY boolean op) : '%s'\n",$$);
     };



ComplexConditionalExpression:
   ComplexConditionalUnit
     {
	 ALLOC_AND_RETURN_STRING("%s",$1);
	 FREE_RULE_STRINGS(1);
     }
   | ComplexConditionalUnit BooleanOp ComplexConditionalUnit
     {
	 char* FirstExprStr  = $1;
	 char* SecondExprStr = $3;
	 char* BooleanOpStr  = $2;

	 // Check the existence of both Variable Expressions (if they exist, record their IDs)
	 VarExpr* FirstExpr;
	 unsigned FirstExprID = FindVarExpr(FirstExprStr, &FirstExpr);
	 if( FirstExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Complex Conditional Expression '%s' is encountered in a Boolean Expression. Terminating...\n", FirstExprStr);
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }
	 VarExpr* SecondExpr;
	 unsigned SecondExprID = FindVarExpr(SecondExprStr, &SecondExpr);
	 if( SecondExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Complex Conditional Expression '%s' is encountered in a Boolean Expression. Terminating...\n", SecondExprStr);
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }



	 unsigned ConditionalExpressionStringLength = strlen(FirstExprStr) + strlen(BooleanOpStr) + strlen(SecondExprStr) +1;
	 char* ConditionalExpressionString = (char*)malloc(ConditionalExpressionStringLength*sizeof(char));
	 sprintf(ConditionalExpressionString,"%s%s%s", FirstExprStr, BooleanOpStr, SecondExprStr);

	 VarExpr* ConditionalVarExpr;
	 FindOrAllocVarExpr(ConditionalExpressionString, &ConditionalVarExpr);
	 assert(ConditionalVarExpr != NULL);
	 ConditionalVarExpr -> Type = OP_BOOLEAN;
	 ConditionalVarExpr -> Operation = ResolveOperationType(BooleanOpStr);
	 ConditionalVarExpr -> OperandID[0] = FirstExprID;
	 ConditionalVarExpr -> OperandID[1] = SecondExprID;

	 $$ = ConditionalExpressionString;

	 FREE_RULE_STRINGS(5);
	 REPORT_READ_INPUT("\tEncountered COMPLEX CONDITIONAL EXPRESSION (with a BINARY boolean op) : '%s'\n",$$);
     }
     ;



VarAssigns:
     OPEN_CURLY_BRACKETS  __varAssigns_act_1 VarAssignList  CLOSE_CURLY_BRACKETS
      {
	 ALLOC_AND_RETURN_STRING("ASSIGNMENTS:\n%s",$3);
	 FREE_RULE_STRINGS(4);
      };

       __varAssigns_act_1:
      {
	  REPORT_READ_INPUT("\tEncountered VARIABLE ASSIGNMENT block in Transaction definition\n");
	  ALLOC_AND_RETURN_STRING("Temp");
      }

VarAssignList:
     VarAssignment
      {
	  ALLOC_AND_RETURN_STRING("%s\n",$1);
	  FREE_RULE_STRINGS(1);
      }

    | VarAssignList COMMA VarAssignment
      {
	  ALLOC_AND_RETURN_STRING("%s%s\n",$1,$3);
	  FREE_RULE_STRINGS(3);
      }

     ;


VarAssignment:
     Variable VALUE_ASSIGN VariableExpression
      {
	  VarExpr* AssignedVar;
	  unsigned AssignedVarExprID = FindVarExpr($1 -> string, &AssignedVar);
	  if( AssignedVar == NULL)
	  {
	      bool NewLocalVariable = ( ($1->string)[0] == '_' );
	      if( !NewLocalVariable )
	      {
		  // Look whether the AssignedVar Name includes scope
		  // IF YES just skip
		  // IF NO  do the following
		  char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		  sprintf(ErrorMessage,"UNKNOWN SHARED VARIABLE '%s'.\n"
			               "Can not define shared variables inside a transaction definition/variable assignment.\n"
			               "Only local variables can be defined at the point where they are first used.\n"
			               "Shared variables should be defined in the 'Definitions' section (before they are used).\n", $1 -> string);
		  yyerror(ErrorMessage);
		  free(ErrorMessage);
		  exit(1);
	      }

	      // Undefined arrays are caught before this point.
/* 	      unsigned VariableNameLastCharPos = strlen($1->string) - 1 ; */
/* 	      bool NewLocalArrayDefinition =  ($1->string)[VariableNameLastCharPos] == ']'; */
/* 	      if( NewLocalArrayDefinition) */
/* 	      { */
/* 		  char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);  */
/* 		  sprintf(ErrorMessage,"CAN NOT DEFINE LOCAL ARRAY '%s' inside a transaction definition\n" */
/* 			               "(can not known size of array in advance).\n" */
/* 			               "Terminating...\n", $1 -> string); */
/* 		  yyerror(ErrorMessage); */
/* 		  free(ErrorMessage); */
/* 		  exit(1); */

/* 	      } */

	      AssignedVarExprID = AllocVarExpr($1->string, &AssignedVar);
	      AssignedVar -> Type = VAR_LOCAL_SIMPLE;
	  }


	  // If variable is random and if it has not been encountered
	  // before, it will be added to Dyn_VarExprToUpdateList
	  ExtendVarExprToUpdate($1->string);


	  bool AssignedVariableConstant = ( AssignedVar -> Type == VAR_SHARED_CONSTANT_UNMANAGED   \
					                        ||                                 \
					    AssignedVar -> Type == VAR_SHARED_CONSTANT_MANAGED     \
					                        ||                                 \
					    AssignedVar -> Type == VAR_SHARED_ARRAY_CONSTANT       \
					                        ||                                 \
					    AssignedVar -> Type == VAR_LOCAL_SIMPLE_CONSTANT       \
					                        ||                                 \
					    AssignedVar -> Type == VAR_LOCAL_ARRAY_CONSTANT        \
					                        ||                                 \
					    AssignedVar -> Type == OP_RANDOM_DIST_CONSTANT         \
	                                  );
	  if( AssignedVariableConstant )
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"CAN NOT ASSIGN VALUE to CONSTANT VARIABLE '%s'.Terminating...\n", $1 -> string);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }


	  VarExpr* EvaluatedVarExpr;
	  unsigned EvaluatedVarExprID = FindVarExpr($3, &EvaluatedVarExpr);
	  assert( EvaluatedVarExpr != NULL);

	  Extend_DynamicArray(&Dyn_VarAssignList,sizeof(var_assign_t));
	  unsigned LastAssignPos = GetSize_DynamicArray(&Dyn_VarAssignList) -1 ;
	  var_assign_t* CurrentAssign = (var_assign_t*)GetElement_DynamicArray(&Dyn_VarAssignList, LastAssignPos, sizeof(var_assign_t));
	  CurrentAssign -> AssignedVarID = AssignedVarExprID;
	  CurrentAssign -> EvaluatedVarExprID =  EvaluatedVarExprID;

	  REPORT_READ_INPUT("\tEncountered VARIABLE ASSIGNMENT '%s%s%s'\n", $1->string , $2, $3);
	  ALLOC_AND_RETURN_STRING("\t- %s%s%s", $1 ->string, $2, $3 );
	  FREE_RULE_STRINGS(3);
      }
     ;


Jump:
     JUMP_OP LABEL CLOSE_PARANTHESES
      {
	  ALLOC_AND_RETURN_STRING("JUMP to '%s'",$2);
	  FREE_RULE_STRINGS(3);
      };

RelationalOp:
     EQUAL
      {
	  REPORT_READ_INPUT("\tEncountered '==' operation\n");
	  ALLOC_AND_RETURN_STRING("==");
	  FREE_RULE_STRINGS(1);
      };
     | NOT_EQUAL
      {
	  REPORT_READ_INPUT("\tEncountered '!=' operation\n");
	  ALLOC_AND_RETURN_STRING("!=");
	  FREE_RULE_STRINGS(1);
      };

     | SMALLER_THAN
      {
	  REPORT_READ_INPUT("\tEncountered '<' operation\n");
	  ALLOC_AND_RETURN_STRING("<");
	  FREE_RULE_STRINGS(1);
      };

     | GREATER_THAN
      {
	  REPORT_READ_INPUT("\tEncountered '>' operation\n");
	  ALLOC_AND_RETURN_STRING(">");
	  FREE_RULE_STRINGS(1);
      };

     | SMALLER_EQUAL
      {
	  REPORT_READ_INPUT("\tEncountered '<=' operation\n");
	  ALLOC_AND_RETURN_STRING("<=");
	  FREE_RULE_STRINGS(1);
      };
     | GREATER_EQUAL
      {
	  REPORT_READ_INPUT("\tEncountered '>=' operation\n");
	  ALLOC_AND_RETURN_STRING(">=");
	  FREE_RULE_STRINGS(1);
      };
     | NOT
      {
	  REPORT_READ_INPUT("\tEncountered '!' operation\n");
	  ALLOC_AND_RETURN_STRING("!");
	  FREE_RULE_STRINGS(1);
      };


BooleanOp:
     AND
      {
	  REPORT_READ_INPUT("\tEncountered LOGICAL AND operation\n");
	  ALLOC_AND_RETURN_STRING("&&");
	  FREE_RULE_STRINGS(1);
      };

    | OR
      {
	  REPORT_READ_INPUT("\tEncountered LOGICAL OR operation\n");
	  ALLOC_AND_RETURN_STRING("||");
	  FREE_RULE_STRINGS(1);
      };



UnaryBooleanOp:
     NOT
      {
	  REPORT_READ_INPUT("\tEncountered LOGICAL NOT operation\n");
	  ALLOC_AND_RETURN_STRING("!");
	  FREE_RULE_STRINGS(1);
      };



Value:
     FixedValue
       {
	  REPORT_READ_INPUT("\tEncountered FIXED VALUE '%s'\n",$1);
	  ALLOC_AND_RETURN_STRING("%s",$1);
	  FREE_RULE_STRINGS(1);
       }
     | RandomizedRange
       {
	  REPORT_READ_INPUT("\tEncountered '%s'\n",$1);
	  ALLOC_AND_RETURN_STRING("%s",$1);
	  FREE_RULE_STRINGS(1);
       }

     ;

FixedValue:
     NUMBER
      {
	  VarExpr* FixedNumVarExpr;
	  FindOrAllocVarExpr($1, &FixedNumVarExpr);
	  FixedNumVarExpr -> Type = VAR_LOCAL_SIMPLE_CONSTANT;
	  FixedNumVarExpr -> Value = (Word)atoi($1);

	  ALLOC_AND_RETURN_STRING("%s",$1);
	  FREE_RULE_STRINGS(1);
      };

Constant:
     NAME_ALL_CAPITALS
      {
	  REPORT_READ_INPUT("\tEncountered CONSTANT '%s'\n",$1);
	  ALLOC_AND_RETURN_STRING("%s",$1);
	  FREE_RULE_STRINGS(1);
      };

DescriptionName:
     NAME | NAME_ALL_CAPITALS
     ;

RandomizedRange:
     SMALLER_THAN   Range  GREATER_THAN
      {

	  ALLOC_AND_RETURN_STRING("RANDOMIZED RANGE %s", $2 -> string);
	  FREE_RULE_STRINGS(3);
      };

Range:
     VariableExpression RANGE_SEPERATOR VariableExpression
       {

	   struct RangeInfoStruct* ReturnedRangeInfo = (struct RangeInfoStruct*)malloc(sizeof(struct RangeInfoStruct));
	   VarExpr* DummyVarExpr;
	   unsigned RangeLimitVarExprID = FindOrAllocVarExpr($1,&DummyVarExpr);
	   ReturnedRangeInfo -> MinValExpressionID = RangeLimitVarExprID;

	   RangeLimitVarExprID = FindOrAllocVarExpr($3,&DummyVarExpr);
	   ReturnedRangeInfo -> MaxValExpressionID = RangeLimitVarExprID;
	   ReturnedRangeInfo -> Increment = 1 ;

	   char* TempString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	   sprintf(TempString,"'%s' to '%s' (increment 1)",$1, $3);
	   ReturnedRangeInfo ->string = TempString;

	   $$ = ReturnedRangeInfo;

	   FREE_RULE_STRINGS(3);
	   REPORT_READ_INPUT("\tEncountered RANGE '%s'\n",$$ -> string);
       }
     | VariableExpression RANGE_SEPERATOR VariableExpression SEMICOLON VariableExpression
       {
           ALLOC_AND_RETURN_STRING("'%s' to '%s' (increment '%s')", $1, $3 , $5 );
	   FREE_RULE_STRINGS(5);
	   REPORT_READ_INPUT("\tEncountered RANGE '%s'\n",$$ -> string);
       }
     ;


Variable:
     NAME
       {
	   VarExpr* VarExprPtr;
	   FindVarExpr($1, &VarExprPtr);
	   bool VariableExists = (VarExprPtr != NULL);
	   if( VariableExists )
	       ExtendVarExprToUpdate($1);

	   REPORT_READ_INPUT("\tEncountered SHARED variable '%s'\n",$1);
	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   ReturnVal -> string = dupstr($1);
	   ReturnVal -> VariableType = SHARED;

	   $$ = ReturnVal;
	   FREE_RULE_STRINGS(1);
       };
     | LOCAL_VARIABLE_NAME
       {

	   VarExpr* VarExprPtr;
	   FindVarExpr($1, &VarExprPtr);
	   bool VariableExists = (VarExprPtr != NULL);
	   if( VariableExists )
	       ExtendVarExprToUpdate($1);

	   REPORT_READ_INPUT("\tEncountered LOCAL variable '%s'\n",$1);
	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   ReturnVal -> string = dupstr($1);


	   // Are all characters (after the underscore) capital letters?
	   unsigned CharNum = strlen($1);
	   unsigned CharNo;
	   bool IsAllCapitals = TRUE;
	   for(CharNo=1; CharNo< CharNum; CharNo++)
	   {
	       int ReturnVal = isupper(($1)[CharNo]);
	       bool CharIsCapitalLetter = (ReturnVal > 0);
	       if( !CharIsCapitalLetter)
	       {
		   IsAllCapitals = FALSE;
		   break;
	       }
	   }
	   if(IsAllCapitals)
	       ReturnVal -> VariableType = LOCAL_CONSTANT;
	   else
	       ReturnVal -> VariableType = LOCAL;


	   $$ = ReturnVal;
	   FREE_RULE_STRINGS(1);
       };
     | Constant
       {
	   VarExpr* VarExprPtr;
	   FindVarExpr($1, &VarExprPtr);
	   bool VariableExists = (VarExprPtr != NULL);
	   if( VariableExists )
	       ExtendVarExprToUpdate($1);

	   REPORT_READ_INPUT("\tEncountered CONSTANT variable '%s'\n",$1);
	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   ReturnVal -> string = dupstr($1);
	   ReturnVal -> VariableType = SHARED_CONSTANT;

	   $$ = ReturnVal;
	   FREE_RULE_STRINGS(1);
       };
     | Scope  LOCAL_VARIABLE_NAME
       {
	   REPORT_READ_INPUT("\tEncountered LOCAL variable '%s' in the scope '%s'\n",$2,$1);

	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   unsigned ScopedVariableNameLength = strlen($1) + strlen(":")  + strlen($2) + 1 ;
	   ReturnVal -> string = malloc( ScopedVariableNameLength * sizeof(char));
	   sprintf(ReturnVal -> string,"%s:%s", $1,$2);



	   // Are all characters (after the underscore) capital letters?
	   unsigned CharNum = strlen($2);
	   unsigned CharNo;
	   bool IsAllCapitals = TRUE;
	   for(CharNo=1; CharNo< CharNum; CharNo++)
	   {
	       int ReturnVal = isupper(($2)[CharNo]);
	       bool CharIsCapitalLetter = (ReturnVal > 0);
	       if( !CharIsCapitalLetter)
	       {
		   IsAllCapitals = FALSE;
		   break;
	       }
	   }
	   if(IsAllCapitals)
	       ReturnVal -> VariableType = SCOPED_LOCAL_CONSTANT;
	   else
	       ReturnVal -> VariableType = SCOPED_LOCAL;

	   $$ = ReturnVal;
	   FREE_RULE_STRINGS(3);
       };
     | ArrayAccess
       {
	   REPORT_READ_INPUT("\tEncountered ARRAY variable '%s'\n",$1 -> string);
	   $$ = $1;
	   FREE_RULE_STRINGS(1);
       };
     | Scope ArrayAccess
       {
	   REPORT_READ_INPUT("\tEncountered LOCAL ARRAY variable '%s' in the scope '%s'\n",$2->string,$1);

	   if( $2->VariableType == SHARED_ARRAY);
	   {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Scope '%s' encountered before Shared array '%s'.\n"
		                   "Scopes are only allowed for local variables/arrays.\n", $1 , $2 -> string);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);

	   }

	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   unsigned ScopedVariableNameLength = strlen($1) + strlen(":")  + strlen($2->string) + 1 ;
	   ReturnVal -> string = malloc( ScopedVariableNameLength * sizeof(char));
	   sprintf(ReturnVal -> string,"%s:%s", $1,$2->string);

	   if ($2 -> VariableType == LOCAL_CONSTANT_ARRAY)
	       ReturnVal -> VariableType = SCOPED_LOCAL_CONSTANT_ARRAY;
	   else if($2 -> VariableType == LOCAL_ARRAY)
	       ReturnVal -> VariableType = SCOPED_LOCAL_ARRAY;

	   $$ = ReturnVal;

	   FREE_RULE_STRINGS(3);
       };
     ;


ArrayAccess:
      ARRAY_NAME VariableExpression CLOSE_BRACKETS
      {

	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr($1);
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';


	  VarExpr* ArrayVarExpr;
	  unsigned ArrayVarExprID = FindVarExpr(ActualArrayName, &ArrayVarExpr);
	  if( ArrayVarExpr == NULL)
	  {

	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN ARRAY '%s' is encountered  in Array Element access.\n"
		                   "Can not define arrays inside transaction definitions\n"
 		                   "(can not known size of array in advance).\n"
                                   "Arrays should be defined in the 'Definitions' section\n",ActualArrayName);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  VarExpr* IndexVarExpr;
	  unsigned IndexVarExprID = FindVarExpr($2, &IndexVarExpr);
	  if( IndexVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN INDEX expression '%s' is encountered in Array Element access. Terminating...\n", $2);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }

	  // Since we are generating a shared array expression we generate two copies, one for managed and one for unmanaged accesses.
	  // Creating Unmanaged copy (if non-existant)
	  VarExpr* ArrayAccessVarExpr;
	  char *ArrayAccessString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ArrayAccessString, "%s%s%s", $1, $2, $3);
	  FindOrAllocVarExpr(ArrayAccessString, &ArrayAccessVarExpr);
	  assert(ArrayAccessVarExpr != NULL);
	  ArrayAccessVarExpr -> Type = OP_UNMANAGED_ARRAY_ACCESS;
	  ArrayAccessVarExpr -> OperandID[0] = ArrayVarExprID;
	  ArrayAccessVarExpr -> OperandID[1] = IndexVarExprID;

	  // Creating Managed copy (if non-existant)
	  VarExpr* ManagedArrayAccessVarExpr;
	  char *ManagedArrayAccessString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ManagedArrayAccessString, "&%s%s%s", $1, $2, $3);
	  FindOrAllocVarExpr(ManagedArrayAccessString, &ManagedArrayAccessVarExpr);
	  assert(ManagedArrayAccessVarExpr != NULL);
	  ManagedArrayAccessVarExpr -> Type = OP_MANAGED_ARRAY_ACCESS;
	  ManagedArrayAccessVarExpr -> OperandID[0] = ArrayVarExprID;
	  ManagedArrayAccessVarExpr -> OperandID[1] = IndexVarExprID;
	  free(ManagedArrayAccessString);

	  struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	  ReturnVal -> string = ArrayAccessString;
	  ReturnVal -> VariableType = SHARED_ARRAY;

	  $$ = ReturnVal;

	  FREE_RULE_STRINGS(3);
      };
      | LOCAL_ARRAY_NAME VariableExpression CLOSE_BRACKETS
        {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr($1);
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';


	  VarExpr* ArrayVarExpr;
	  unsigned ArrayVarExprID = FindVarExpr(ActualArrayName, &ArrayVarExpr);
	  if( ArrayVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN ARRAY '%s' is encountered  in Array Element access.\n"
		                   "Can not define arrays inside transaction definitions\n"
 		                   "(can not known size of array in advance).\n"
                                   "Arrays should be defined in the 'Definitions' section\n",ActualArrayName);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  VarExpr* IndexVarExpr;
	  unsigned IndexVarExprID = FindVarExpr($2, &IndexVarExpr);
	  if( IndexVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN INDEX expression '%s' is encountered in Array Element access. Terminating...\n", $2);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }


	  VarExpr* ArrayAccessVarExpr;
	  char *ArrayAccessString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ArrayAccessString, "%s%s%s", $1, $2, $3);
	  FindOrAllocVarExpr(ArrayAccessString, &ArrayAccessVarExpr);
	  assert(ArrayAccessVarExpr != NULL);
	  ArrayAccessVarExpr -> Type = OP_UNMANAGED_ARRAY_ACCESS;
	  ArrayAccessVarExpr -> OperandID[0] = ArrayVarExprID;
	  ArrayAccessVarExpr -> OperandID[1] = IndexVarExprID;


	  struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	  ReturnVal -> string = ArrayAccessString;


	   // Are all characters (after the underscore) capital letters?
	   unsigned CharNum = strlen(ActualArrayName);
	   unsigned CharNo;
	   bool IsAllCapitals = TRUE;
	   for(CharNo=1; CharNo< CharNum; CharNo++)
	   {
	       int ReturnVal = isupper((ActualArrayName)[CharNo]);
	       bool CharIsCapitalLetter = (ReturnVal > 0);
	       if( !CharIsCapitalLetter)
	       {
		   IsAllCapitals = FALSE;
		   break;
	       }
	   }
	   if(IsAllCapitals)
	       ReturnVal -> VariableType = LOCAL_CONSTANT_ARRAY;
	   else
	       ReturnVal -> VariableType = LOCAL_ARRAY;

	  $$ = ReturnVal;

	  FREE_RULE_STRINGS(3);
        }
     ;


ManagedMemAccess:
     READ_ACCESS_OP  VariableExpression CLOSE_PARANTHESES
      {

	  VarExpr* InputVarExpr;
	  FindVarExpr($2, &InputVarExpr);
	  if( InputVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN VARIABLE EXPRESSION '%s' is encountered in STM_LOAD access. Terminating...\n",$2);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }

	  bool NotSupportedVariableExpression  = (InputVarExpr -> Type > VAR_SHARED_ARRAY_CONSTANT ) && (InputVarExpr -> Type != OP_UNMANAGED_ARRAY_ACCESS);
	  if( NotSupportedVariableExpression )
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Variable Expression '%s' is not an access to a standalone shared variable/array.\n"
		                   "Other kind of variable expression are not allowed in managed accesses.\n",$2);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);

	      exit(1);
	  }


	  // Chopping last character (character '[') of array name
	  unsigned ActualAccessedVarExprNameLength = strlen("&") + strlen($1) + 1;
	  char*    ActualAccessedVarExprName = malloc(ActualAccessedVarExprNameLength * sizeof(char));
	  sprintf(ActualAccessedVarExprName,"&%s",$2);

	  VarExpr* AccessedVarExpr;
	  unsigned ActualVarExprID = FindVarExpr(ActualAccessedVarExprName, &AccessedVarExpr);
	  if( AccessedVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage, "MANAGED COPY of Variable Expression '%s' can NOT be FOUND. Terminating...\n",$2);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }


	  VarExpr* ManagedAccessVarExpr;
	  char *ManagedAccessString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ManagedAccessString, "%s%s%s", $1, $2, $3);
	  FindOrAllocVarExpr(ManagedAccessString, &ManagedAccessVarExpr);
	  assert(ManagedAccessVarExpr != NULL);
	  ManagedAccessVarExpr -> Type = OP_MEMORY_READ;
	  ManagedAccessVarExpr -> OperandID[0] = ActualVarExprID;

	  $$ = ManagedAccessString;
	  FREE_RULE_STRINGS(3);

      }
     | WRITE_ACCESS_OP  VariableExpression CLOSE_PARANTHESES
      {
	   yyerror("STM_STORE is not allowed in variable/relational/boolean expression evaluation.\n");
	   exit(1);

      }
     | READ_ACCESS_OP VariableExpression COMMA VariableExpression  CLOSE_PARANTHESES
       {
	   yyerror("The STM_LOAD with explicit value return is not permitted in variable/relational/boolean expression evaluation.\n");
	   exit(1);
       }
     | WRITE_ACCESS_OP VariableExpression COMMA VariableExpression  CLOSE_PARANTHESES
       {
	   yyerror("STM_STORE is not allowed in variable/relational/boolean expression evaluation.\n");
	   exit(1);
       }



VariableExpressionElement:
     Value
       {
	    ALLOC_AND_RETURN_STRING("%s",$1);
	    FREE_RULE_STRINGS(1);
       }
     | Variable
       {
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $1; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */


	    ALLOC_AND_RETURN_STRING("%s",$1 -> string);
	    FREE_RULE_STRINGS(1);
       }
     | ManagedMemAccess
      {
	    ALLOC_AND_RETURN_STRING("%s",$1);
	    FREE_RULE_STRINGS(1);

      }

     ;




MultiplicativeVariableExpressionElementAccess:
       MultiplicativeFactor
        {
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $1; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */
	    ALLOC_AND_RETURN_STRING("%s",$1);
	    FREE_RULE_STRINGS(1);

        }
       | MINUS MultiplicativeFactor
         {
//	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $2;

	     char* AccessedVarExprString = $2;
	    unsigned NewStringLength = strlen("-") + strlen(AccessedVarExprString) + 1;
	    char *NewExpressionString = (char*)malloc(NewStringLength*sizeof(char));
	    sprintf(NewExpressionString,"-%s",AccessedVarExprString);


	    VarExpr* CurrentVarExpr;
	    FindVarExpr(NewExpressionString, &CurrentVarExpr);

	    bool Found= (CurrentVarExpr != NULL);
	    if( !Found )
	    {  // If variable expr found, we allocate it.
		unsigned CurrentVarExprID = AllocVarExpr(NewExpressionString, &CurrentVarExpr);

		// We need to construct the VarExpr structure
		CurrentVarExpr -> Type = OP_ARITH;


		// Since we came until this  point the Both of the operands of
                // the Variable expression should be already in the
                // Dyn_VariableExpressionArray
		VarExpr* FirstOperand;
		unsigned FirstOperandID = FindVarExpr("-1", &FirstOperand);
		bool FirstOperandDoesNotExist = (FirstOperand ==NULL);  // Since first operand is a minus sign it may not exist in the Dyn_VariableExpression list (yet)
		if(FirstOperandDoesNotExist)
		{
		    FirstOperandID = AllocVarExpr("-1", &FirstOperand);

		    FirstOperand -> Type = VAR_LOCAL_SIMPLE;
		    FirstOperand -> Value = -1;

		    // Since   a   new  variable   expression   is  added   to
                    // Dyn_VariableExpressionList it is possible that the list
		    // is reallocated  (possibily changing the  pointer to the
                    // current  var expr  that is  constructed). So  we update
                    // CurrentVarExpr.

		    CurrentVarExpr = GetVarExprPtr(CurrentVarExprID);
		}
		VarExpr* SecondOperand;
		unsigned SecondOperandID = FindVarExpr(AccessedVarExprString, &SecondOperand);
		assert(SecondOperand !=NULL);

		CurrentVarExpr -> OperandID[0] = FirstOperandID;
		CurrentVarExpr -> OperandID[1] = SecondOperandID;
		CurrentVarExpr -> Operation    = MULTIPLY;


	    }

/* 	    unsigned long  EvaluatedValue = EvaluateVarExpr(CurrentVarExpr); */
/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string =  NewExpressionString; */
/* 	    ReturnVal->Value  =  EvaluatedValue;  */
/* 	    $$ = ReturnVal ;	   */
	    $$ = NewExpressionString;
	    FREE_RULE_STRINGS(1);

         }
       | MultiplicativeVariableExpressionElementAccess MultiplicativeArithmeticOp MultiplicativeFactor
         {
	    char* FirstAccessedVarExprString = $1;
	    char* SecondAccessedVarExprString = $3;

	    char *NewExpressionString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	    sprintf(NewExpressionString,"%s%s%s",FirstAccessedVarExprString,$2,SecondAccessedVarExprString);

	    VarExpr* CurrentVarExpr;
	    FindVarExpr(NewExpressionString, &CurrentVarExpr);

	    bool Found= (CurrentVarExpr != NULL);
	    if( !Found )
	    {  // If variable expr found, we allocate it.
		AllocVarExpr(NewExpressionString, &CurrentVarExpr);

		// We need to construct the VarExpr structure
		CurrentVarExpr -> Type = OP_ARITH;


		// Since we came until this  point the Both of the operands of
                // the Variable expression should be already in the
                // Dyn_VariableExpressionArray
		VarExpr* FirstOperand;
		unsigned FirstOperandID = FindVarExpr(FirstAccessedVarExprString, &FirstOperand);
		assert(FirstOperand !=NULL);
		VarExpr* SecondOperand;
		unsigned SecondOperandID = FindVarExpr(SecondAccessedVarExprString, &SecondOperand);
		assert(SecondOperand !=NULL);

		CurrentVarExpr -> OperandID[0] = FirstOperandID;
		CurrentVarExpr -> OperandID[1] = SecondOperandID;
		CurrentVarExpr -> Operation    = ResolveOperationType($2);


	    }


/* 	    unsigned long  EvaluatedValue = EvaluateVarExpr(CurrentVarExpr); */
/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = NewExpressionString; */
/* 	    ReturnVal->Value  = EvaluatedValue; */
/* 	    $$ = ReturnVal ;	     */
	    $$ = NewExpressionString;
	    FREE_RULE_STRINGS(3);

         }
       ;

MultiplicativeFactor:
       VariableExpressionElement
        {
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $1; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */
	    ALLOC_AND_RETURN_STRING("%s",$1);
	    FREE_RULE_STRINGS(1);

        }
       | OPEN_PARANTHESES VariableExpression CLOSE_PARANTHESES
         {
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $2; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
	    char* AccessedVarExprString = $2;
	    unsigned NewStringSize = strlen("(") + strlen(AccessedVarExprString) + strlen(")") +1;
	    char* ReturnString = malloc(NewStringSize*sizeof(char));
	    sprintf(ReturnString,"(%s)",AccessedVarExprString);
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */
	    $$ = ReturnString;
	    FREE_RULE_STRINGS(1);
	 }
       ;

VariableExpression:
     MultiplicativeVariableExpressionElementAccess
        {
/* VariableExpression:  */
/*      VariableExpressionElement */
/*         {  */
/*  	   REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",$1);  */
/*  	   ALLOC_AND_RETURN_STRING("%s",$1);  */
/*  	   FREE_RULE_STRINGS(1);  */
/*         };  */
/*      | VariableExpression  ArithmeticOp VariableExpressionElement  */
/*         {  */
/*  	   ALLOC_AND_RETURN_STRING("%s%s%s",$1,$2,$3);  */
/*  	   FREE_RULE_STRINGS(3);  */
/*  	   REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",$$);  */
/*         };  */
/*      | OPEN_PARANTHESES VariableExpression  ArithmeticOp VariableExpressionElement CLOSE_PARANTHESES */
/*        { */
/*  	   ALLOC_AND_RETURN_STRING("%s%s%s%s%s",$1,$2,$3,$4,$5);  */
/*  	   FREE_RULE_STRINGS(5);  */
/*  	   REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",$$);  */
/*        } */
/*      ; */



/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $1; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */
	    REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",$1);
	    ALLOC_AND_RETURN_STRING("%s",$1);
	    FREE_RULE_STRINGS(1);

        };
     | VariableExpression  AdditiveArithmeticOp MultiplicativeVariableExpressionElementAccess
        {
	    char* FirstAccessedVarExprString = $1;
	    char*  SecondAccessedVarExprString = $3;

	    char *NewExpressionString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	    sprintf(NewExpressionString,"%s%s%s",FirstAccessedVarExprString,$2,SecondAccessedVarExprString);

	    VarExpr* CurrentVarExpr;
	    FindVarExpr(NewExpressionString, &CurrentVarExpr);

	    bool Found= (CurrentVarExpr != NULL);
	    if( !Found )
	    {  // If variable expr found, we allocate it.
		AllocVarExpr(NewExpressionString, &CurrentVarExpr);

		// We need to construct the VarExpr structure
		CurrentVarExpr -> Type = OP_ARITH;


		// Since we came until this  point the Both of the operands of
                // the Variable expression should be already in the
                // Dyn_VariableExpressionArray
		VarExpr* FirstOperand;
		unsigned FirstOperandID = FindVarExpr(FirstAccessedVarExprString, &FirstOperand);
		assert(FirstOperand !=NULL);
		VarExpr* SecondOperand;
		unsigned SecondOperandID = FindVarExpr(SecondAccessedVarExprString, &SecondOperand);
		assert(SecondOperand !=NULL);

		CurrentVarExpr -> OperandID[0] = FirstOperandID;
		CurrentVarExpr -> OperandID[1] = SecondOperandID;
		CurrentVarExpr -> Operation    = ResolveOperationType($2);


	    }
/* 	    unsigned long  EvaluatedValue = EvaluateVarExpr(CurrentVarExpr); */
/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = NewExpressionString; */
/* 	    ReturnVal->Value  = EvaluatedValue; */
/* 	    $$ = ReturnVal ;	     */
	    $$ = NewExpressionString;
	    REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",NewExpressionString);
	    FREE_RULE_STRINGS(3);
/*      | OPEN_PARANTHESES VariableExpression  ArithmeticOp VariableExpressionElementAccess CLOSE_PARANTHESES */
/*        { */
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $2; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr -> Value; */
/* 	    $$ = ReturnVal ;	     */
/* 	    FREE_RULE_STRINGS(5);  */
/*        } */

/* VariableExpressionElementAccess: */
/*      LOCAL_VARIABLE_NAME  */
/*        { */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr($1); */

/* 	    VarExpr* CurrentVarExpr;  */
/* 	    FindVarExpr($1, &CurrentVarExpr); */
/* 	    bool VariableExists =  (CurrentVarExpr != NULL); */
/* 	    if(VariableExists ) */
/* 	    { */
/* 		unsigned long EvaluatedValue = EvaluateVarExpr(CurrentVarExpr); */
/* 		ReturnVal->Value  = EvaluatedValue; */
/* 	    }	    */
/* 	    else */
/* 	    { */
/* 		REPORT_SEMANTIC_ERROR("Access to an UNDEFINED LOCAL VARIABLE during evaluation of a variable expression.\n"); */
/* 	    } */

/* 	    $$ = ReturnVal ;	     */
/* 	    FREE_RULE_STRINGS(1); */
/*        }; */


        };
     ;




AdditiveArithmeticOp:
     PLUS
      {
	  REPORT_READ_INPUT("\tEncountered PLUS operation\n");
	  ALLOC_AND_RETURN_STRING("+");
	  FREE_RULE_STRINGS(1);
      };
     | MINUS
      {
	  REPORT_READ_INPUT("\tEncountered MINUS operation\n");
	  ALLOC_AND_RETURN_STRING("-");
	  FREE_RULE_STRINGS(1);
      };


MultiplicativeArithmeticOp:
     MULTIPLY
      {
	  REPORT_READ_INPUT("\tEncountered MULTIPLY operation (or * sign)\n");
	  ALLOC_AND_RETURN_STRING("*");
	  FREE_RULE_STRINGS(1);
      };

     | DIVIDE
      {
	  REPORT_READ_INPUT("\tEncountered DIVIDE operation\n");
	  ALLOC_AND_RETURN_STRING("/");
	  FREE_RULE_STRINGS(1);
      };
     ;



ThreadsSection:
     THREADS_HEADER __th_sec_act_1 ThreadDefList
     {

     };


       __th_sec_act_1:  /* empty */
       {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     THREADS Section\n"
			     "-----------------------------------------------------------------------------\n" );
       };


ThreadDefList:
     ThreadDef SEMICOLON
     | ThreadDefList ThreadDef SEMICOLON
     ;

ThreadDef:
     ThreadType __threadDef_act_1 DEFINITION_ASSIGN  TxBlockList
       {
	   FREE_RULE_STRINGS(4);

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
/* 		 GenerateAndAttachContainersForForwardTxList(&CurrentTxList,1); */
/* 		 Clear_DynamicArray(&CurrentTxList); */
		 GenerateAndAttachContainersForForwardTxList(&Dyn_TxDefArray,1);
		 Clear_DynamicArray(&Dyn_TxDefArray);


                 // char* ThreadName = $1;
		 unsigned ThreadTypeNo;
		 for(ThreadTypeNo=0; ThreadTypeNo < ThreadTypeNum ; ThreadTypeNo++)
		 {
		     char **ThreadNamePtr = (char**)GetElement_DynamicArray(&Dyn_CurrentThreadDefList, ThreadTypeNo, sizeof(char*));
		     AddNewThreadDef(*ThreadNamePtr);
		 }
		 Clear_DynamicArray(&Dyn_CurrentThreadDefList);
		 Clear_DynamicArray(&CurrentTxContainerList);

		 ThreadTypeNum = 0;

	     }
           #endif

       }
     ;
       __threadDef_act_1:
        {
	    REPORT_READ_INPUT("'%s' is/are comprised of the following transactional pattern:\n",yyvsp[0].string);
	    TxBlockNo=0;

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
 	       CurrentTxContainerNo = 0;
	   #endif
	}

ThreadType:
     DescriptionName
       {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      Extend_DynamicArray(&Dyn_CurrentThreadDefList,sizeof(char*));
	      unsigned LastElementNo = GetSize_DynamicArray(&Dyn_CurrentThreadDefList) - 1 ;
	      char** CurrentThreadDefListElement = (char**)GetElement_DynamicArray(&Dyn_CurrentThreadDefList, LastElementNo, sizeof(char*));
	      *CurrentThreadDefListElement = dupstr($1);
	      ThreadTypeNum++;
	  #endif

	  ALLOC_AND_RETURN_STRING("%s",$1);
	  FREE_RULE_STRINGS(1);
       }
     | ThreadType COMMA DescriptionName
       {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      Extend_DynamicArray(&Dyn_CurrentThreadDefList,sizeof(char*));
	      unsigned LastElementNo = GetSize_DynamicArray(&Dyn_CurrentThreadDefList) - 1 ;
	      char** CurrentThreadDefListElement = (char**)GetElement_DynamicArray(&Dyn_CurrentThreadDefList, LastElementNo, sizeof(char*));
	      *CurrentThreadDefListElement = dupstr($3);
	      ThreadTypeNum++;
	  #endif

	  ALLOC_AND_RETURN_STRING("%s,%s",$1,$3);
	  FREE_RULE_STRINGS(3);
       }
     ;


TxBlockList:
     TxBlockListElement
       {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     // The following assignment is for the purpose of passing the
             // BoundedRepetition field to the return value
	     $$ = $1;
	  #endif

	     // The following line is only for debugging
	     // REPORT_READ_INPUT("TxBlockListElement: Bounded:%d, Block:%s",$1 -> BoundedRepetition,$1->string);
	   REPORT_READ_INPUT("TxBlock[%u]: %s",TxBlockNo,$1->string);
	   FREE_RULE_STRINGS(1);
	   TxBlockNo++;
       }
     | TxBlockList COMMA TxBlockListElement
       {
	   // The following two lines are only for debugging
	   // REPORT_READ_INPUT("TxBlockList: Bounded:%d, Block:%s",$1 -> BoundedRepetition,$1->string);
	   // REPORT_READ_INPUT("TxBlockListElement: Bounded:%d, Block:%s",$3 -> BoundedRepetition,$3->string);

          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	   if( $1 -> BoundedRepetition == FALSE)
	   {
	       REPORT_SEMANTIC_ERROR("UNEXPECTED EXECUTABLE ELEMENT (a transaction/ a TxCandidate list / paranthesized block). An infinitely repeating executable element should be the LAST possible executable element in a thread definition!\n");
	   }
	   else
	   {
	     // The following assignment is for the purpose of passing the
             // BoundedRepetition field to the return value
	     $$ = $3;
	   }
	  #endif


	   REPORT_READ_INPUT("TxBlock[%u]: %s",TxBlockNo,$3->string);
	   FREE_RULE_STRINGS(1);
	   TxBlockNo++;
       }
     ;


TxBlockListElement:
    BoundedRepetitionTxBlockListElement
      {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
             //  ALLOC_AND_RETURN_STRING("%s",$1);
	     char *TempString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(TempString,"%s",$1);

	     struct TxBlockListReturnStruct* NewRetVal =  (struct TxBlockListReturnStruct*) malloc(sizeof(struct TxBlockListReturnStruct));
	     NewRetVal -> string = TempString;
	     NewRetVal -> BoundedRepetition = TRUE;
	     $$ = NewRetVal;
	  #endif
	  FREE_RULE_STRINGS(1);
      }
    | UnboundedRepetitionTxBlockListElement
      {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
             //  ALLOC_AND_RETURN_STRING("%s",$1);
	     char *TempString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(TempString,"%s",$1);

	     struct TxBlockListReturnStruct* NewRetVal =  (struct TxBlockListReturnStruct*) malloc(sizeof(struct TxBlockListReturnStruct));
	     NewRetVal -> string = TempString;
	     NewRetVal -> BoundedRepetition = FALSE;
	     $$ = NewRetVal;
	  #endif

	  FREE_RULE_STRINGS(1);
      }
    ;

BoundedRepetitionTxBlockListElement:
     DescriptionName
      {

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 GenerateAndAttachNewContainerForSimpleTxBlock($1, &DelayOpEncountered, CurrentDelayVal);
		 CurrentTxContainerNo++;
	     }
	   #endif


  	  ALLOC_AND_RETURN_STRING("%s\n",$1);
	  FREE_RULE_STRINGS(1);
      }
     | Delay
      {
	  if( DelayOpEncountered )
	  {
	      yyerror("Consecutive delay operations encountered. Terminating...");
	      exit(1);
	  }
	  else
	  {
	      CurrentDelayVal = atoi($1);
	      DelayOpEncountered = TRUE;
	  }


  	  ALLOC_AND_RETURN_STRING("%s\n",$1);
	  FREE_RULE_STRINGS(1);
      }
     | SMALLER_THAN  TxChoiceList  GREATER_THAN
      {

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
 	        if ( !ParseOnly )
 		{
 		    GenerateAndAttachNewContainerForTxChoiceList(&CurrentTxCandidateList, 1,  &DelayOpEncountered, CurrentDelayVal);
 		    Clear_DynamicArray(&CurrentTxCandidateList);
 		    CurrentTxContainerNo++;
 		}
            #endif

  	  ALLOC_AND_RETURN_STRING("Choice List:\n%s",$2);
	  FREE_RULE_STRINGS(3);
      }
     | SMALLER_THAN  TxChoiceList  GREATER_THAN  FixedValue
      {

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION

 	        if ( !ParseOnly )
 		{
 		    GenerateAndAttachNewContainerForTxChoiceList(&CurrentTxCandidateList, 1,  &DelayOpEncountered, CurrentDelayVal);
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo, LOOP_BACK, atoi($4) );
 		    Clear_DynamicArray(&CurrentTxCandidateList);
		    CurrentTxContainerNo++;
 		}
            #endif

		ALLOC_AND_RETURN_STRING("%s times repeated Choice List:\n%s",$4,$2);
	  FREE_RULE_STRINGS(3);
      }
     | SMALLER_THAN  TxChoiceList  GREATER_THAN Variable
      {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
          #endif

  	  ALLOC_AND_RETURN_STRING("%s times repeated Choice List:\n%s", $4->string, $2);
	  FREE_RULE_STRINGS(4);
      }
     | OPEN_PARANTHESES __txBlockStart_act TxBlockList CLOSE_PARANTHESES
       {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 if( VerboseParserOutput)
		     printf("Container no at the end of TxBlock= %u \n",CurrentTxContainerNo-1);
		 if( $3 -> BoundedRepetition == FALSE)
		 {
		     REPORT_SEMANTIC_ERROR("UNEXPECTED TX BLOCK including an infinitely repeating executable element.\n"
                                           "An infinitely repeating executable element should be the LAST possible executable element in a thread definition!\n");
		 }
	     }
          #endif

  	  REPORT_READ_INPUT("End of SIMPLE TxBlockList\n");
	  FREE_RULE_STRINGS(3);
       }
     | OPEN_PARANTHESES __txBlockStart_act TxBlockList CLOSE_PARANTHESES FixedValue
      {

          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 if( VerboseParserOutput )
		     printf("Container no at the end of TxBlock= %u \n",CurrentTxContainerNo-1);

		 if( $3 -> BoundedRepetition == FALSE)
		 {
		     REPORT_SEMANTIC_ERROR("UNEXPECTED REPEATED TX BLOCK including an infinitely repeating executable element.\n"
                                           "An infinitely repeating executable element should be the LAST possible executable element in a thread definition!\n");
		 }


		 unsigned IterationNum = atoi($5);
		 InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo-1, TxBlockStartContainerNo, LOOP_BACK, IterationNum);
	     }
          #endif


  	  REPORT_READ_INPUT("End of  %s times repeated TxBlockList\n",$5);
	  FREE_RULE_STRINGS(5);
      }
     | OPEN_PARANTHESES __txBlockStart_act TxBlockList CLOSE_PARANTHESES __txBlockEnd_act VariableExpression
      {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 if( VerboseParserOutput )
		 {
		     printf("Container no at the end of TxBlock= %u \n",CurrentTxContainerNo-1);
		     printf("Current TxBlockStartContainerNo is: %u \n", TxBlockStartContainerNo);
		 }
		 if( $3 -> BoundedRepetition == FALSE)
		 {
		     REPORT_SEMANTIC_ERROR("UNEXPECTED REPEATED TX BLOCK including an infinitely repeating executable element.\n"
                                           "An infinitely repeating executable element should be the LAST possible executable element in a thread definition!\n");
		 }


		 VarExpr* ElementVarExpr;
		 unsigned LoopLimitExprID = FindVarExpr($6,&ElementVarExpr);
		 if(ElementVarExpr == NULL)
		 {
		     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		     sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", $6);
		     yyerror(ErrorMessage);
		     free(ErrorMessage);
		     exit(1);
		 }

		 InsertVarExprBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo-1, TxBlockStartContainerNo, LOOP_BACK, LoopLimitExprID);


	     }



          #endif


  	  REPORT_READ_INPUT("End of  %s times repeated TxBlockList\n", $3 ->string);
	  FREE_RULE_STRINGS(5);
      }
     ;


UnboundedRepetitionTxBlockListElement:
     DescriptionName MULTIPLY
      {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 GenerateAndAttachNewContainerForSimpleTxBlock($1, &DelayOpEncountered, CurrentDelayVal);
		 #ifdef COMPILE_FOR_TEST
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo, LOOP_BACK, ITERATION_NUM_OF_INFINITE_LOOPS_FOR_TESTS );
		 #else
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo , NEXT, 0);
		 #endif
		 CurrentTxContainerNo++;
	     }
          #endif

  	  ALLOC_AND_RETURN_STRING("INFINITELY REPEATED %s\n",$1);
	  FREE_RULE_STRINGS(2);
      }
     | SMALLER_THAN  TxChoiceList  GREATER_THAN MULTIPLY
      {

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  GenerateAndAttachNewContainerForTxChoiceList(&CurrentTxCandidateList, 1,  &DelayOpEncountered, CurrentDelayVal);
                  #ifdef COMPILE_FOR_TEST
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo, LOOP_BACK, ITERATION_NUM_OF_INFINITE_LOOPS_FOR_TESTS );
		  #else
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo , NEXT, 0);
		  #endif
 		  Clear_DynamicArray(&CurrentTxCandidateList);
		  CurrentTxContainerNo++;
 		}
            #endif


  	  ALLOC_AND_RETURN_STRING("INFINITELY REPEATED Choice List:\n%s",$2);
	  FREE_RULE_STRINGS(3);
      }
     | OPEN_PARANTHESES __txBlockStart_act TxBlockList CLOSE_PARANTHESES MULTIPLY
       {

          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 if( VerboseParserOutput)
		     printf("Container no at the end of TxBlock= %u \n",CurrentTxContainerNo-1);

                 #ifdef COMPILE_FOR_TEST
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo-1, TxBlockStartContainerNo, LOOP_BACK, ITERATION_NUM_OF_INFINITE_LOOPS_FOR_TESTS);
		 #else
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo-1, TxBlockStartContainerNo, NEXT, 0);
		 #endif

	     }
          #endif


  	  REPORT_READ_INPUT("End of  INFINITELY REPEATED TxBlockList\n");
	  FREE_RULE_STRINGS(4);
       }
       ;

         __txBlockStart_act:
         {
           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	    TxBlockStartContainerNo = CurrentTxContainerNo;
	    unsigned ListSize= GetSize_DynamicArray(&TxBlockStartContainerNoList);
	    Extend_DynamicArray(&TxBlockStartContainerNoList, sizeof(unsigned short));
	    unsigned short* nestedTxBlockStartContainerNoPtr = (unsigned short*)GetElement_DynamicArray(&TxBlockStartContainerNoList,ListSize,sizeof(unsigned short));
	    *nestedTxBlockStartContainerNoPtr =  TxBlockStartContainerNo;

	    if ( !ParseOnly && VerboseParserOutput )
		printf("TxBlock Start encountered at Container No %u .\n",TxBlockStartContainerNo);
	   #endif


         }

         __txBlockEnd_act:
         {
           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     //TxBlockStartContainerNo = CurrentTxContainerNo;
	    unsigned LastListElementPos = GetSize_DynamicArray(&TxBlockStartContainerNoList)-1;
	    unsigned short* nestedTxBlockStartContainerNoPtr = (unsigned short*) GetElement_DynamicArray(&TxBlockStartContainerNoList,LastListElementPos,sizeof(unsigned short));

	    TxBlockStartContainerNo = *nestedTxBlockStartContainerNoPtr; 
	    Chop_DynamicArray(&TxBlockStartContainerNoList);

	    if ( !ParseOnly && VerboseParserOutput )
		printf("Current TxBlock Start is now Container No %u .\n",TxBlockStartContainerNo);
	   #endif


         }


TxChoiceList :
    TxChoiceListElement
      {
  	  ALLOC_AND_RETURN_STRING("%s\n",$1);
	  FREE_RULE_STRINGS(1);
      }
    | TxChoiceList BAR TxChoiceListElement
      {
  	  ALLOC_AND_RETURN_STRING("%s%s\n",$1,$3);
	  FREE_RULE_STRINGS(3);
      }
    ;

Scope:
    DescriptionName COLON
    {
	ALLOC_AND_RETURN_STRING("%s",$1);
	FREE_RULE_STRINGS(1);
    }
    ;

TxChoiceListElement:
     DescriptionName
      {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      AddNewTxCanidate(&CurrentTxCandidateList, $1, (double)UNSPECIFIED_PERCENTAGE );
	  #endif

  	  ALLOC_AND_RETURN_STRING("\t- EQUAL PROBA : %s",$1);
	  FREE_RULE_STRINGS(1);
      }
     | Scope FixedValue PERCENTAGE
      {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      AddNewTxCanidate(&CurrentTxCandidateList, $1, (double)atoi($2) );
	  #endif

  	  ALLOC_AND_RETURN_STRING("\t- %f PROBA : %s",atoi($2)/(float)100,$1);
	  FREE_RULE_STRINGS(1);
      }
     | Scope  FLOAT_NUMBER  PERCENTAGE
       {

          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      AddNewTxCanidate(&CurrentTxCandidateList, $1, atof($2) );
	  #endif

	   ALLOC_AND_RETURN_STRING("\t- %.12f PROBA : %s",atof($2)/(double)100,$1);
	   FREE_RULE_STRINGS(1);


       }
       ;



SchedulesSection:
     SCHEDULES_HEADER __sch_sec_act_1  ScheduleDefList
     {
     };

       __sch_sec_act_1:  /* empty */
       {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     SCHEDULES Section\n"
			     "-----------------------------------------------------------------------------\n" );
	   ScheduleNo=0;
       };


ScheduleDefList:
     ScheduleDef SEMICOLON
     | ScheduleDefList ScheduleDef SEMICOLON
     ;

ScheduleDef:
     DescriptionName DEFINITION_ASSIGN ScheduleSpec
      {

	  Extend_DynamicArray(&Dyn_ScheduleList,sizeof(Schedule));
	  unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_ScheduleList) - 1;
	  Schedule* CurrentSchedule = (Schedule*) GetElement_DynamicArray(&Dyn_ScheduleList, LastAddedElementPos, sizeof(Schedule));

	  CurrentSchedule -> Name     = dupstr($1);
	  CurrentSchedule -> Schedule = (ScheduleElement*)MakeStaticCopy_DynamicArray(&Dyn_Schedule, sizeof(ScheduleElement));
	  CurrentSchedule -> ScheduleLength = GetSize_DynamicArray(&Dyn_Schedule);
	  ScheduleNum++;
	  Clear_DynamicArray(&Dyn_Schedule);


	  REPORT_READ_INPUT("Sched[%u]: (%s)\n\t%s\n",ScheduleNo,$1,$3);
	  ScheduleNo++;
      }
     ;


ScheduleSpec:
     TxPortion
      {
  	  ALLOC_AND_RETURN_STRING("%s",$1);
	  FREE_RULE_STRINGS(1);
      }
     | ScheduleSpec COMMA TxPortion
      {
  	  ALLOC_AND_RETURN_STRING("%s,%s",$1,$3);
	  FREE_RULE_STRINGS(3);
      }
     ;


TxPortion:
DescriptionName
       {

	   Extend_DynamicArray(&Dyn_Schedule,sizeof(ScheduleElement));
	   unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_Schedule) - 1;
	   ScheduleElement* SchedElement = (ScheduleElement*) GetElement_DynamicArray(&Dyn_Schedule, LastAddedElementPos, sizeof(ScheduleElement));

	   unsigned FoundTxNo = FindTxByName($1, TxDefArray, TxDefNum);
	   if(FoundTxNo == TxDefNum )
	   {
       	       REPORT_SEMANTIC_ERROR("UNKNOWN Transaction Name %s in schedule\n",$1);
	   }
	   else
	   {
	       SchedElement->ThreadID = FoundTxNo;
	       SchedElement->TxID     = 0;
	       SchedElement-> LabelTxOpContainerNo = TxDefArray[FoundTxNo].TxOpNum[0];

	       SchedElement-> Assertion = FALSE;
	       SchedElement-> AssertionExprID = 0;
	       SchedElement -> VarAssignList = NULL;
	       SchedElement -> VarAssignNum  = 0;

	   }

	   ALLOC_AND_RETURN_STRING("%s",$1);
	   FREE_RULE_STRINGS(1);
       }
     | DescriptionName LABEL
       {

	   Extend_DynamicArray(&Dyn_Schedule,sizeof(ScheduleElement));
	   unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_Schedule) - 1;
	   ScheduleElement* SchedElement = (ScheduleElement*) GetElement_DynamicArray(&Dyn_Schedule, LastAddedElementPos, sizeof(ScheduleElement));

	   unsigned FoundTxNo = FindTxByName($1, TxDefArray, TxDefNum);
	   if(FoundTxNo == TxDefNum )
	   {
       	       REPORT_SEMANTIC_ERROR("UNKNOWN Transaction Name %s in schedule\n",$1);
	   }
	   else
	   {
	       SchedElement->ThreadID = FoundTxNo;
	       SchedElement->TxID     = 0;


	       char* LabelStringToMatch = &($2[1]);
	       unsigned TxOpNo;
	       unsigned FoundTxOpNo= TxDefArray[FoundTxNo].TxOpNum[0];
	       for(TxOpNo=0; TxOpNo< TxDefArray[FoundTxNo].TxOpNum[0]; TxOpNo++)
	       {
		   TxOpContainer_t* CurrentTxOpContainer = &(TxDefArray[FoundTxNo].TxOpList[0][TxOpNo]);
		   if(  CurrentTxOpContainer -> TxOperation == LABEL_OP )
		   {
		       bool LabelFound = (strcmp(LabelStringToMatch, CurrentTxOpContainer -> Label ) == 0);
		       if(LabelFound)
		       {
			   FoundTxOpNo = TxOpNo;
			   break;
		       }
		   }
	       }
	       if( FoundTxOpNo == TxDefArray[FoundTxNo].TxOpNum[0] )
	       {
		   REPORT_SEMANTIC_ERROR("Label %s could not be found in Transaction %s (for generating schedule)\n",LabelStringToMatch,$1);
	       }

	       SchedElement-> LabelTxOpContainerNo = FoundTxOpNo;

	       SchedElement-> Assertion = FALSE;
	       SchedElement-> AssertionExprID = 0;
	       SchedElement -> VarAssignList = NULL;
	       SchedElement -> VarAssignNum  = 0;

	   }

	   ALLOC_AND_RETURN_STRING("%s%s",$1,$2);
	   FREE_RULE_STRINGS(1);
       }
     | OPEN_BRACKETS ConditionalExpression CLOSE_BRACKETS
      {
	  char* AssertionExpressionString = $2;

	    VarExpr* CurrentAssertionExpr;
	    unsigned AssertionExprID = FindVarExpr(AssertionExpressionString, &CurrentAssertionExpr);

	    bool Found= (CurrentAssertionExpr != NULL);
	    if( !Found )
	    {
		char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		sprintf(ErrorMessage,"UNKNOWN CONDITIONAL EXPRESSION '%s' is encountered in Schedule definition. Terminating...\n",AssertionExpressionString);
		yyerror(ErrorMessage);
		free(ErrorMessage);
		assert(0);
	    }


	   Extend_DynamicArray(&Dyn_Schedule,sizeof(ScheduleElement));
	   unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_Schedule) - 1;
	   ScheduleElement* SchedElement = (ScheduleElement*) GetElement_DynamicArray(&Dyn_Schedule, LastAddedElementPos, sizeof(ScheduleElement));


	   SchedElement-> Assertion = TRUE;
	   SchedElement-> AssertionExprID = AssertionExprID ;
	   SchedElement -> VarAssignList = NULL;
	   SchedElement -> VarAssignNum  = 0;

	   SchedElement->ThreadID = 0;
	   SchedElement->TxID     = 0;
	   SchedElement-> LabelTxOpContainerNo = 0;

	  ALLOC_AND_RETURN_STRING("%s%s%s",$1,$2,$3);
	  FREE_RULE_STRINGS(3);
      };
     | VarAssigns
      {

	  Extend_DynamicArray(&Dyn_Schedule,sizeof(ScheduleElement));
	  unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_Schedule) - 1;
	  ScheduleElement* SchedElement = (ScheduleElement*) GetElement_DynamicArray(&Dyn_Schedule, LastAddedElementPos, sizeof(ScheduleElement));

	  SchedElement -> VarAssignNum  = GetSize_DynamicArray(&Dyn_VarAssignList);
	  SchedElement -> VarAssignList = MakeStaticCopy_DynamicArray(&Dyn_VarAssignList, sizeof(var_assign_t));

	  SchedElement-> Assertion = FALSE;
	  SchedElement-> AssertionExprID = 0 ;
	  SchedElement->ThreadID = 0;
	  SchedElement->TxID     = 0;
	  SchedElement-> LabelTxOpContainerNo = 0;

	  Clear_DynamicArray(&Dyn_VarAssignList);
      }
     ;




InvariantsSection:
     INVARIANTS_HEADER __inv_sec_act_1  InvariantDefList
     {
     };


       __inv_sec_act_1:  /* empty */
       {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     INVARIANTS Section\n"
			     "-----------------------------------------------------------------------------\n" );
       };



InvariantDefList:
     InvariantDef SEMICOLON
     {
	 REPORT_READ_INPUT("Invariant[%u]: %s\n",InvariantNo,$1);
	 InvariantNo++;
     }
     | InvariantDefList InvariantDef SEMICOLON
     {
	 REPORT_READ_INPUT("Invariant[%u]: %s\n",InvariantNo,$2);
	 InvariantNo++;
     }
     ;

InvariantDef:
     OPEN_BRACKETS NO_ABORT_INVARIANT_TOKEN CLOSE_BRACKETS
      {
	  NoAbortInSchedule = TRUE;
      }
     | OPEN_BRACKETS ConditionalExpression CLOSE_BRACKETS
      {
	  char* InvariantExpressionString = $2;

	    VarExpr* CurrentInvariantExpr;
	    unsigned InvariantExprID = FindVarExpr(InvariantExpressionString, &CurrentInvariantExpr);

	    bool Found= (CurrentInvariantExpr != NULL);
	    if( !Found )
	    {
		char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		sprintf(ErrorMessage,"UNKNOWN CONDITIONAL EXPRESSION '%s' is encountered in STM_LOAD access. Terminating...\n",InvariantExpressionString);
		yyerror(ErrorMessage);
		free(ErrorMessage);
		assert(0);
	    }

	    Extend_DynamicArray(&Dyn_InvariantArray,sizeof(Invariant));
	    unsigned LastAddedInvariantPos = GetSize_DynamicArray(&Dyn_InvariantArray) - 1;
	    Invariant* CurrentInvariant = GetElement_DynamicArray(&Dyn_InvariantArray, LastAddedInvariantPos, sizeof(Invariant));

	    unsigned CondExprStringLength = strlen($1) +  strlen(InvariantExpressionString) + strlen($3) +1 ;
	    CurrentInvariant -> Name = (char*)malloc(CondExprStringLength*sizeof(char));
	    sprintf(CurrentInvariant -> Name,"%s%s%s",$1, InvariantExpressionString, $3);
	    CurrentInvariant -> VarExprID = InvariantExprID;

	    InvariantNum++;


	    $$ = dupstr(CurrentInvariant -> Name);

//	  ALLOC_AND_RETURN_STRING("%s%s%s",$1,$2,$3);
	  FREE_RULE_STRINGS(3);
      };

%%








