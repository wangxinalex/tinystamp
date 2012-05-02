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

#include "generate_files.h"

const char* TRANSACTIONAL_MEM_READ = "TM_READ";
const char* TRANSACTIONAL_MEM_WRITE = "TM_WRITE";
const char* TRANSACTION_START_MACRO_NAME = "TX_START";
const char* TRANSACTION_READ_ONLY_START_MACRO_NAME = "TX_START_RO";
const char* TRANSACTION_COMMIT_MACRO_NAME = "TX_COMMIT";

const char* INTERMEDIATE_GENERATED_C_OUTPUT_PATH = XSTR(ENV_INTERMEDIATE_GENERATED_C_OUTPUT_PATH);
const char* GENERATED_C_OUTPUT_PATH = XSTR(ENV_GENERATED_C_OUTPUT_PATH);
const char* POST_PATMAP_SCRIPT_PATH = XSTR(ENV_POST_PATMAP_SCRIPT_PATH);


void Generate_C_Code()
{
    printf("\n"
	   "----------------------------------------------------\n"
	   "            Generating Intermediate C output        \n"
	   "----------------------------------------------------\n"
	   "\n"
          );

    GenerateCodeInitializingGlobalOptions();

    Generate_Thread_Local_Variables();
    Generate_ThreadLocalVariableInitializations();

    GenerateSharedVariableDefinitions();
    GenerateSharedVariableInitializations();

    Generate_Transaction_C_Code();

    unsigned ThreadNo;
    for(ThreadNo=0; ThreadNo<ThreadDefNum ; ThreadNo++)
    {
	Generate_C_CodeForThread(ThreadNo);
    }


    printf("\n"
	   "\n"
	   "-------------------------------------------------------\n"
	   "   Applying intermediate output to templates files     \n"
	   "(This creates the final C code in 'c_output' directory)\n"
	   "-------------------------------------------------------\n"
           "\n" );

    // Part which runs on script after the files to be written by C code are generated

     char DummyString[100];
     sprintf(DummyString,"%s",POST_PATMAP_SCRIPT_PATH);
     chdir(DummyString);

     sprintf(DummyString,"./post_patmap %u", ThreadDefNum);
     system(DummyString);
     chdir(XSTR(ENV_SRC_DIR_PATH));


}




void GenerateSharedVariableDefinitions()
{

    FILE *SharedVariableDefinitionFile;
    FILE *SharedVariableDeclarationFile;
    char CurrentFileName[100];

    sprintf(CurrentFileName,"%s/shared_var_definitions.h", INTERMEDIATE_GENERATED_C_OUTPUT_PATH);

    SharedVariableDeclarationFile = fopen(CurrentFileName,"w");
    assert (SharedVariableDeclarationFile != NULL);

    sprintf(CurrentFileName,"%s/shared_var_definitions.c", INTERMEDIATE_GENERATED_C_OUTPUT_PATH);
    SharedVariableDefinitionFile = fopen(CurrentFileName,"w");
    assert (SharedVariableDefinitionFile != NULL);



    ThreadInfo_t* FirstThreadDef  = &(ThreadDefArray[0]);
    VarExpr*      VarExprList     = FirstThreadDef->VarExprList;
    unsigned      VarExprListSize = FirstThreadDef->VarExprNum ;


    fprintf(SharedVariableDeclarationFile,"#ifndef _____SHARED_VARIABLES_H_________\n"
       	                                  "#define _____SHARED_VARIABLES_H_________\n"
	                                  "\n"
       	                                  "typedef unsigned long Word;\n"
	                                  "\n");


    fprintf(SharedVariableDefinitionFile,"#include \"shared_var_definitions.h\"\n");


    unsigned VarExprNo;
    for(VarExprNo=0; VarExprNo< VarExprListSize; VarExprNo++)
    {
	VarExpr* CurrentVarExpr = &(VarExprList[VarExprNo]);

	// We do not check managed versions of shared variables because they are actually the same as unmanaged versions
	bool SharedUnmanagedVariable = (CurrentVarExpr -> Type <= VAR_SHARED_CONSTANT_UNMANAGED);
	if(SharedUnmanagedVariable)
	{
	    char* SharedVarName = dupstr(CurrentVarExpr ->Name);
	    fprintf(SharedVariableDeclarationFile, "extern Word* %s;\n",SharedVarName);
	    fprintf(SharedVariableDefinitionFile, "Word* %s;\n",SharedVarName);
	}
	else
	{
	    bool SharedArray =  (CurrentVarExpr -> Type ==  VAR_SHARED_ARRAY) \
		                                        ||                    \
 		                (CurrentVarExpr -> Type == VAR_SHARED_ARRAY_CONSTANT) ;
	    if(SharedArray)
	    {

		char* SharedArrayName = dupstr(CurrentVarExpr ->Name);
		fprintf(SharedVariableDeclarationFile, "extern Word* %s;\n",SharedArrayName);
		fprintf(SharedVariableDeclarationFile, "extern unsigned  %s_array_size;\n",SharedArrayName);

		fprintf(SharedVariableDefinitionFile, "Word* %s;\n",SharedArrayName);
		fprintf(SharedVariableDefinitionFile, "unsigned  %s_array_size;\n",SharedArrayName);
	    }

	}

    }

    fprintf(SharedVariableDeclarationFile,"\n#endif\n");

    fclose(SharedVariableDeclarationFile);
    fclose(SharedVariableDefinitionFile);

    printf("- Generated code declaring shared variables.\n");

}



void GenerateSharedVariableInitializations()
{


    char* MemoryAllocationCode= NULL;
    char* InitializationCode= NULL;
    char* TempCodeLine = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);


    bool SharedDataInitializationRequired = FALSE;
    MemoryAllocationCode = strext(MemoryAllocationCode,"// Allocating memory for shared variables and arrays.\n");
    InitializationCode = strext(InitializationCode, "// Initializing shared variables and arrays.\n");


    char* AddrValuePrintCode=NULL;
    AddrValuePrintCode = strext(AddrValuePrintCode,"\n"
				                   "#ifdef ENABLE_TRACE_CODE\n"
				                   "if ( EnableTrace )\n"
				                   "{\n"
				                   );
/*     AddrValuePrintCode = strext(AddrValuePrintCode,"// *INDENT-OFF*\n" */
/*                                                    "if ( EnableTrace )\n" */
/* 				                   "{\n" */
/* 				                    "printf("); */

//    char* SharedVariableNameList=NULL;

    ThreadInfo_t* FirstThreadDef  = &(ThreadDefArray[0]);
    VarExpr*      VarExprList     = FirstThreadDef->VarExprList;
    unsigned      VarExprListSize = FirstThreadDef->VarExprNum ;

    bool FirstArrayEncountered = TRUE;
    unsigned VarExprNo;
    for(VarExprNo=0; VarExprNo< VarExprListSize; VarExprNo++)
    {
	VarExpr* CurrentVarExpr = &(VarExprList[VarExprNo]);

	// We do not check managed versions of shared variables because they are actually the same as unmanaged versions
	bool SharedUnmanagedVariable = (CurrentVarExpr -> Type <= VAR_SHARED_CONSTANT_UNMANAGED);
	if(SharedUnmanagedVariable)
	{
	    char* SharedVarName = dupstr(CurrentVarExpr ->Name);
	    sprintf(TempCodeLine, "%s = (Word*)malloc(sizeof(Word));\n", SharedVarName);
	    MemoryAllocationCode = strext(MemoryAllocationCode,TempCodeLine);

	    unsigned long VariableInitValue = VAR_EXPR_Evaluate(CurrentVarExpr,VarExprList, VarExprListSize);
	    sprintf(TempCodeLine, "*%s = %lu;\n", SharedVarName, VariableInitValue);
	    InitializationCode = strext(InitializationCode,TempCodeLine);

	    sprintf(TempCodeLine, "printf(\"Address of %s : %%p\\n\",%s );\n", SharedVarName , SharedVarName);
	    AddrValuePrintCode = strext(AddrValuePrintCode,TempCodeLine);

/* 	    sprintf(TempCodeLine, ",%s", SharedVarName); */
/* 	    SharedVariableNameList = strext(SharedVariableNameList, TempCodeLine); */

	    SharedDataInitializationRequired = TRUE;
	}
	else
	{
	    bool SharedArray =  (CurrentVarExpr -> Type ==  VAR_SHARED_ARRAY) \
		                                        ||                    \
 		                (CurrentVarExpr -> Type == VAR_SHARED_ARRAY_CONSTANT) ;
	    if(SharedArray)
	    {

		char* SharedArrayName = dupstr(CurrentVarExpr ->Name);
		unsigned ArrayLowerBound = CurrentVarExpr -> OperandID[0];
		unsigned ArrayUpperBound = CurrentVarExpr -> OperandID[1];

		unsigned ArraySize = ArrayUpperBound- ArrayLowerBound + 1;
		sprintf(TempCodeLine, "\n%s_array_size = %u;\n", SharedArrayName, ArraySize);
		MemoryAllocationCode = strext(MemoryAllocationCode,TempCodeLine);

		sprintf(TempCodeLine, "%s = (Word*)malloc(%s_array_size*sizeof(Word));\n", SharedArrayName, SharedArrayName);
		MemoryAllocationCode = strext(MemoryAllocationCode,TempCodeLine);


		Word* ArrayAddress = (Word *)VAR_EXPR_Evaluate(CurrentVarExpr,VarExprList, VarExprListSize);


		if(FirstArrayEncountered)
		    InitializationCode = strext(InitializationCode,"unsigned ElementNo;\n");

		sprintf(TempCodeLine, "for(ElementNo=0; ElementNo< %s_array_size ; ElementNo++)\n", SharedArrayName);
		InitializationCode = strext(InitializationCode,TempCodeLine);

		sprintf(TempCodeLine, "%s[ElementNo] = 0;\n", SharedArrayName);
		InitializationCode = strext(InitializationCode,TempCodeLine);


		unsigned ElementNo;
		for(ElementNo=0; ElementNo< ArraySize ; ElementNo++)
		{
		    Word ElementValue = ArrayAddress[ElementNo];
		    if( ElementValue != 0)
		    {
			sprintf(TempCodeLine, "%s[%u] = %lu;\n", SharedArrayName, ElementNo, ElementValue);
			InitializationCode = strext(InitializationCode,TempCodeLine);
		    }
		}

		InitializationCode = strext(InitializationCode, "\n");


		sprintf(TempCodeLine, "for(ElementNo=0; ElementNo< %s_array_size ; ElementNo++)\n", SharedArrayName);
		AddrValuePrintCode = strext(AddrValuePrintCode,TempCodeLine);

		sprintf(TempCodeLine, "printf(\"Address of %s[%%u] : %%p\\n\",ElementNo, &(%s[ElementNo]) );\n", SharedArrayName, SharedArrayName);
		AddrValuePrintCode = strext(AddrValuePrintCode,TempCodeLine);


		SharedDataInitializationRequired = TRUE;

	    }

	}

    }



    FILE *SharedVariableInitializationFile;
    FILE *SharedVariableAllocationFile;
    char CurrentFileName[100];

    sprintf(CurrentFileName,"%s/shared_var_init.c",INTERMEDIATE_GENERATED_C_OUTPUT_PATH);

    SharedVariableInitializationFile = fopen(CurrentFileName,"w");
    assert (SharedVariableInitializationFile != NULL);

    sprintf(CurrentFileName,"%s/shared_var_alloc.c",INTERMEDIATE_GENERATED_C_OUTPUT_PATH);

    SharedVariableAllocationFile = fopen(CurrentFileName,"w");
    assert (SharedVariableAllocationFile != NULL);


    // If there is no shared variable to initialize then empty the initialization file
    if( SharedDataInitializationRequired)
    {
	fprintf(SharedVariableAllocationFile,"%s",MemoryAllocationCode);
	fprintf(SharedVariableInitializationFile,"%s",InitializationCode);

//	AddrValuePrintCode = strext(AddrValuePrintCode,SharedVariableNameList);
//	AddrValuePrintCode = strext(AddrValuePrintCode,");\n");
	AddrValuePrintCode = strext(AddrValuePrintCode,"\n}\n#endif\n");
//	AddrValuePrintCode = strext(AddrValuePrintCode,"// *INDENT-ON*\n");

	fprintf(SharedVariableInitializationFile,"%s",AddrValuePrintCode);

    }

    fclose(SharedVariableAllocationFile);
    fclose(SharedVariableInitializationFile);
    free(MemoryAllocationCode);
    free(InitializationCode);
    free(TempCodeLine);

    printf("- Generated code initializing shared variables.\n");

}




void  Generate_Thread_Local_Variables()
{


    FILE *ThreadLocalVariableHeaderFile;
    char CurrentFileName[100];

    sprintf(CurrentFileName,"%s/thread_local_variables.h", INTERMEDIATE_GENERATED_C_OUTPUT_PATH);

    ThreadLocalVariableHeaderFile = fopen(CurrentFileName,"w");
    assert (ThreadLocalVariableHeaderFile != NULL);

    // Generate Header file HEADER
    fprintf(ThreadLocalVariableHeaderFile,"#ifndef _____THREAD_LOCAL_VARIABLES_H_________\n"
       	                                  "#define _____THREAD_LOCAL_VARIABLES_H_________\n\n");


    fprintf(ThreadLocalVariableHeaderFile,"#include \"tm_interface.h\"\n"
	                                  "#include <sys/time.h>\n");
//	                                  "stm_tx_t* TxDesc[%u];\n",TxDefNum);

    fprintf(ThreadLocalVariableHeaderFile,"typedef struct StatisticsStruct\n"
	                                  "{\n"
	                                  "   unsigned long CommitNum;\n"
	                                  "   unsigned long AbortNum;\n"
	                                  "   unsigned long CurrentRetryNum;\n"
	                                  "   unsigned long MaxRetries;\n"
	                                  "   struct timeval start_time;\n"
	                                  "   struct timeval end_time;\n"
									  "   void *locals;\n"
	                                  "} stat_t;\n\n");

//    fprintf(ThreadLocalVariableHeaderFile,"stat_t Statistics[%u];\n",ThreadDefNum);

    fprintf(ThreadLocalVariableHeaderFile,"typedef struct ThLocalVarCollectionStruct {\n");
    fprintf(ThreadLocalVariableHeaderFile, "stm_tx_t* TxDesc;\n"
	                                   "stat_t   Statistics;\n"
	                                   "unsigned WriteValue;\n"
	                                   "char*    PrintOffset;\n"
	                                   "unsigned ThreadID;\n"
	                                   "char*    ThreadName;\n"
                                           "char**   TransactionNames;\n" \
	   );



    ThreadInfo_t* FirstThreadDef  = &(ThreadDefArray[0]);
    VarExpr*      VarExprList     = FirstThreadDef->VarExprList;
    unsigned      VarExprListSize = FirstThreadDef->VarExprNum ;


    unsigned VarExprNo;
    for(VarExprNo=0; VarExprNo< VarExprListSize; VarExprNo++)
    {
	VarExpr* CurrentVarExpr = &(VarExprList[VarExprNo]);

	bool ThreadLocalVariable = (CurrentVarExpr -> Type >= VAR_LOCAL_SIMPLE && CurrentVarExpr -> Type <= VAR_LOCAL_ARRAY_CONSTANT) \
	                                                                       ||                                                     \
                          	    (CurrentVarExpr -> Type == OP_RANDOM_DIST  || CurrentVarExpr -> Type ==OP_RANDOM_DIST_CONSTANT) ;
	bool ConstantValue =  IsConsantValue(CurrentVarExpr);
	if( !ConstantValue && ThreadLocalVariable )
	{
	    fprintf(ThreadLocalVariableHeaderFile,"signed long %s;\n", CurrentVarExpr->Name);
	    bool RandomVariable = (CurrentVarExpr -> Type == OP_RANDOM_DIST  || CurrentVarExpr -> Type ==OP_RANDOM_DIST_CONSTANT);
	    if(RandomVariable)
		fprintf(ThreadLocalVariableHeaderFile,"unsigned seed_%s;\n", CurrentVarExpr->Name);
	}
    }

    fprintf(ThreadLocalVariableHeaderFile,"} ThLocalVarCollection;\n");

    fprintf(ThreadLocalVariableHeaderFile,"\n#endif\n");
    fclose(ThreadLocalVariableHeaderFile);

    printf("- Generated code declaring thread local variables.\n");
}



void  Generate_ThreadLocalVariableInitializations()
{
    Generate_ThreadSeedInitializations();

    FILE * ThreadLocalVarInitializationFile;
    char CurrentFileName[100];

    sprintf(CurrentFileName,"%s/thread_local_var_init.c", INTERMEDIATE_GENERATED_C_OUTPUT_PATH);
    ThreadLocalVarInitializationFile = fopen(CurrentFileName,"a");
    assert (ThreadLocalVarInitializationFile != NULL);
    fprintf(ThreadLocalVarInitializationFile, "\n"
	                                      "// Initializing thread local variables (other than random variables).\n");

    ThreadInfo_t* FirstThreadDef  = &(ThreadDefArray[0]);
    VarExpr*      VarExprList     = FirstThreadDef->VarExprList;
    unsigned      VarExprListSize = FirstThreadDef->VarExprNum ;
    unsigned VarExprNo;
    for(VarExprNo=0; VarExprNo< VarExprListSize; VarExprNo++)
    {
	VarExpr* CurrentVarExpr = &(VarExprList[VarExprNo]);

	bool ConstantValue = IsConsantValue(CurrentVarExpr);
	if( ! ConstantValue)
	{
	    bool LocalVariable = ( CurrentVarExpr -> Type == VAR_LOCAL_SIMPLE || CurrentVarExpr -> Type == VAR_LOCAL_SIMPLE_CONSTANT );
	    if(LocalVariable)
	    {
		fprintf(ThreadLocalVarInitializationFile, "ThLocals.%s = %lu;\n", CurrentVarExpr -> Name, CurrentVarExpr -> Value);
	    }
	    bool LocalArray = (  CurrentVarExpr -> Type == VAR_LOCAL_ARRAY || CurrentVarExpr -> Type == VAR_LOCAL_ARRAY_CONSTANT);
	    if(LocalArray)
	    {

		unsigned ArrayLowerBound = CurrentVarExpr -> OperandID[0];
		unsigned ArrayUpperBound = CurrentVarExpr -> OperandID[1];

		unsigned ArraySize = ArrayUpperBound- ArrayLowerBound + 1;
		Word*    ArrayAddress = (Word*)CurrentVarExpr -> Addr;
		unsigned ElementNo;
		for(ElementNo=0; ElementNo< ArraySize; ElementNo++)
		{
		    fprintf(ThreadLocalVarInitializationFile, "ThLocals.%s[%u] = %lu;\n", CurrentVarExpr -> Name, ElementNo, ArrayAddress[ElementNo]);
		}
	    }
	}
    }

    fclose(ThreadLocalVarInitializationFile);

    printf("- Generated code initializing thread local variables in thread.\n");
}


void Generate_ThreadSeedInitializations()
{


    FILE * ThreadSeedInitializationFile;
    char CurrentFileName[100];

    sprintf(CurrentFileName,"%s/thread_local_var_init.c", INTERMEDIATE_GENERATED_C_OUTPUT_PATH);
    ThreadSeedInitializationFile = fopen(CurrentFileName,"w");
    assert (ThreadSeedInitializationFile != NULL);
    fprintf(ThreadSeedInitializationFile, "// Initializing random variable seeds\n");
    bool ThreadSeedInitializationRequired = FALSE;

    char* SeedValuePrintCode=NULL;
    SeedValuePrintCode = strext(SeedValuePrintCode,"if(RandomDebug)\n"
				                   "{\n"
	                                            "printf(\"Generating Random variable seeds for Thread %u...\\n\",ID);\n"
	                       );
    char* TempCodeLine = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);

    ThreadInfo_t* FirstThreadDef  = &(ThreadDefArray[0]);
    VarExpr*      VarExprList     = FirstThreadDef->VarExprList;
    unsigned      VarExprListSize = FirstThreadDef->VarExprNum ;
    unsigned VarExprNo;
    for(VarExprNo=0; VarExprNo< VarExprListSize; VarExprNo++)
    {
	VarExpr* CurrentVarExpr = &(VarExprList[VarExprNo]);
	bool RandomVariable = (CurrentVarExpr -> Type == OP_RANDOM_DIST  || CurrentVarExpr -> Type ==OP_RANDOM_DIST_CONSTANT);
	if( RandomVariable)
	{
	    fprintf(ThreadSeedInitializationFile,"ThLocals.seed_%s = (unsigned) RAND_R(&CurrentThreadSeed);\n", CurrentVarExpr->Name);
//	    fprintf(ThreadSeedInitializationFile,"printf(\"seed_%s[%%u] = %%u \\n\",ID, ThLocals.seed_%s);\n", CurrentAddrGen->Name, CurrentAddrGen->Name);

	    sprintf(TempCodeLine,"printf(\"Seed of %s: %%u\\n\", ThLocals.seed_%s);\n", CurrentVarExpr->Name, CurrentVarExpr->Name);
	    SeedValuePrintCode = strext(SeedValuePrintCode,TempCodeLine);

	    ThreadSeedInitializationRequired = TRUE;

	}

    }


    // If there is no thread seed to initialize then empty the initialization file
    if(!ThreadSeedInitializationRequired)
    {
 	fclose(ThreadSeedInitializationFile);
 	ThreadSeedInitializationFile = fopen(CurrentFileName,"w");
 	assert (ThreadSeedInitializationFile != NULL);
    }
    else
    {
	SeedValuePrintCode = strext(SeedValuePrintCode,"}\n");
	fprintf(ThreadSeedInitializationFile,"%s", SeedValuePrintCode);
    }
    fclose(ThreadSeedInitializationFile);

    printf("- Generated code initializing seeds of random variables in thread.\n");
}


void GenerateVariableDefsBeforeSwitchStatement()
{
    FILE* VarDefBeforeSwitchStatementFile;
    char CurrentFileName[100];

    sprintf(CurrentFileName,"%s/execute_transaction_variable_defs.c", INTERMEDIATE_GENERATED_C_OUTPUT_PATH);

    VarDefBeforeSwitchStatementFile = fopen(CurrentFileName,"w");
    assert (VarDefBeforeSwitchStatementFile != NULL);

    ThreadInfo_t* FirstThreadDef = &(ThreadDefArray[0]);

    unsigned TxDefNo;
    unsigned TxDefNum = FirstThreadDef -> TxDefNum;

    bool SetReadOnlyHintVariable = FALSE;
    if( TransmitReadOnlyTxHint )
    {
	for( TxDefNo=0; TxDefNo< TxDefNum; TxDefNo++)
	{
	    TxInfo_t* CurrentTxDef = &(FirstThreadDef-> TxDefArray[TxDefNo]);
	    if( CurrentTxDef -> ReadOnly)
	    {
		SetReadOnlyHintVariable = TRUE;
		break;
	    }
	}
    }

    if( SetReadOnlyHintVariable )
    {
	fprintf(VarDefBeforeSwitchStatementFile,"int _ro;\n");
    }

    bool VarToUpdateExists = FALSE;
    VarExpr* VarExprList   = FirstThreadDef->VarExprList;
    unsigned VarExprListSize = FirstThreadDef->VarExprNum ;
    unsigned VarExprNo;
    // Traverse over the VarExprList to find out whether
    // there are any Variables to update


    for( VarExprNo=0; VarExprNo< VarExprListSize; VarExprNo++)
    {
	VarExpr* CurrentVarExpr = &(VarExprList[VarExprNo]);
	bool AssociatedVarExprRequiresUpdate   = ( CurrentVarExpr -> Type == OP_RANDOM_DIST ) ||  ( CurrentVarExpr -> Type == OP_RANDOM_DIST_CONSTANT ) ;
	if( AssociatedVarExprRequiresUpdate )
	{
	    VarToUpdateExists = TRUE;
	    break;
	}
    }
    if(VarToUpdateExists)
    {
	fprintf(VarDefBeforeSwitchStatementFile,"unsigned Range;\n");
    }

/*     VarExpr* VarExprList   = FirstThreadDef->VarExprList; */
/*     // Traverse over all transaction definitions to find out the different */
/*     // loop iterators. */
/*     dyn_arr_t LoopIteratorNameList; */
/*     Initialize_DynamicArray(&LoopIteratorNameList); */
/*     for( TxDefNo=0; TxDefNo< TxDefNum; TxDefNo++) */
/*     { */
/* 	TxInfo_t* CurrentTxDef = &(FirstThreadDef-> TxDefArray[TxDefNo]); */

/* 	int TxOpNo; */
/* 	int TxOpNum = CurrentTxDef -> TxOpNum[0]; */
/* 	for(TxOpNo=0; TxOpNo< TxOpNum; TxOpNo++) */
/* 	{ */
/* 	    TxOpContainer_t* CurrentTxOpContainer = &(CurrentTxDef -> TxOpList[0][TxOpNo]); */
/* 	    bool LoopStartContainer = CurrentTxOpContainer -> LoopIteratorContainer; */
/* 	    if(LoopStartContainer) */
/* 	    { */
/* 		VarExpr* ConditionExpr = &(VarExprList[CurrentTxOpContainer -> ConditionExprPos]); */
/* 		unsigned LoopIteratorVarID  = ConditionExpr->OperandID[0]; */

/* 		// Check whether the loop iterator already exists in the list */
/* 		bool IteratorExistInList = FALSE; */
/* 		unsigned CurrentListSize = GetSize_DynamicArray(&LoopIteratorNameList); */
/* 		unsigned ElementNo; */
/* 		for(ElementNo=0; ElementNo< CurrentListSize ; ElementNo++) */
/* 		{ */
/* 		    unsigned* CurrentElement = GetElement_DynamicArray(&LoopIteratorNameList, ElementNo, sizeof(unsigned)); */
/* 		    if( *CurrentElement == LoopIteratorVarID) */
/* 		    { */
/* 			IteratorExistInList = TRUE; */
/* 			break; */
/* 		    } */
/* 		} */

/* 		// If loop variable is not in the list add it to the list */
/* 		if( !IteratorExistInList ) */
/* 		{ */
/* 		    Extend_DynamicArray(&LoopIteratorNameList, sizeof(unsigned)); */
/* 		    unsigned LastAddedElementPos = GetSize_DynamicArray(&LoopIteratorNameList)-1; */
/* 		    unsigned* LastAddedElement   = GetElement_DynamicArray(&LoopIteratorNameList, LastAddedElementPos, sizeof(unsigned)); */
/* 		    *LastAddedElement = LoopIteratorVarID;  */
/* 		} */
/* 	    } */
/* 	} */

/*     } */

    // Using the list  of Loop iterators generate the  lines that define those
    // loop iterators (they should be defined before the switch statement).

    // Starting to write the definition line
/*     fprintf(VarDefBeforeSwitchStatementFile,"int "); */

    // Adding comma seperated list of loop iterator names in the definition.
/*     unsigned IteratorNum = GetSize_DynamicArray(&LoopIteratorNameList); */
/*     unsigned IteratorNo; */
/*     for(IteratorNo=0; IteratorNo< IteratorNum ; IteratorNo++) */
/*     { */
/* 	unsigned*  IteratorIDPtr = GetElement_DynamicArray(&LoopIteratorNameList, IteratorNo, sizeof(unsigned)); */
/* 	VarExpr* IteratorVarExpr = &(VarExprList[(*IteratorIDPtr)]); */
/* 	bool NotLastIterator = (IteratorNo < IteratorNum-1); */

/* 	if( NotLastIterator ) */
/* 	    fprintf(VarDefBeforeSwitchStatementFile,"%s,",IteratorVarExpr->Name); */
/* 	else // if LastIterator */
/* 	    fprintf(VarDefBeforeSwitchStatementFile,"%s;\n",IteratorVarExpr->Name); */

/*     } */


    fclose(VarDefBeforeSwitchStatementFile);
}


void GenerateManagedAdressAccessString(unsigned AddressVarExprID, const VarExpr* VarExprList, unsigned VarExprListSize, char** AddressVarExprString)
{
    GenerateVarExprString(AddressVarExprID, VarExprList, VarExprListSize, AddressVarExprString);


    const VarExpr* OperandExpr = &(VarExprList[AddressVarExprID]);
    bool SharedArrayAccess = ( OperandExpr->Type == OP_MANAGED_ARRAY_ACCESS ||  OperandExpr->Type == OP_UNMANAGED_ARRAY_ACCESS  );
    if(SharedArrayAccess)
    {
        char* TempString = NULL;
        TempString = strext(TempString,"&(");
        TempString = strext(TempString,*AddressVarExprString);
        TempString = strext(TempString,")");
        free(*AddressVarExprString);
        *AddressVarExprString = TempString;

    }
    else  // The operand should be a simple shared variable
    {
        // Chopping the "(*" from the beginning and the ")" from the end
        char* TempString = dupstr(*AddressVarExprString);
        free(*AddressVarExprString);
        unsigned TempStringLength = strlen(TempString);
        // Chopping the chracted from the end
        TempString[TempStringLength-1] = '\0';

        //Chopping the first two characters
        *AddressVarExprString = dupstr( &(TempString[2]) );
    }

}


void MarkBlockTerminations(const TxInfo_t* CurrentTxDef, dyn_arr_t* BlockTerminations)
{

    unsigned TxOpNum = CurrentTxDef -> TxOpNum[0];
    unsigned TxOpNo;
    for(TxOpNo=0; TxOpNo< TxOpNum; TxOpNo++)
    {
	TxOpContainer_t* CurrentTxOpContainer = &(CurrentTxDef -> TxOpList[0][TxOpNo]) ;
	bool LoopIteratorStartTxOp = (CurrentTxOpContainer -> LoopIteratorContainer) ;
	bool ConditionTxOp         = (CurrentTxOpContainer -> ConditionExprPos != INVALID_CONDITION_EXPR_POS);
	if ( LoopIteratorStartTxOp || ConditionTxOp )
	{
	    unsigned CurrentBlockTerminationPos = CurrentTxOpContainer -> NextContainerID[1] -1 ;

	    // CurrentBlockTerminationPos exists already in BlockTerminations?
	    bool AlreadyInList = FALSE;
	    unsigned ElementNum = GetSize_DynamicArray(BlockTerminations);
	    unsigned ElementNo;
	    for(ElementNo=0; ElementNo< ElementNum; ElementNo++)
	    {
		unsigned* CurrentElement = GetElement_DynamicArray(BlockTerminations, ElementNo, sizeof(unsigned));
		if( *CurrentElement == CurrentBlockTerminationPos)
		{
		    AlreadyInList = TRUE;
		    break;
		}
	    }

	    if( !AlreadyInList)
	    {
		Extend_DynamicArray(BlockTerminations, sizeof(unsigned));
		unsigned  LastAddedElementPos = GetSize_DynamicArray(BlockTerminations) - 1;
		unsigned* AddedElement = GetElement_DynamicArray(BlockTerminations, LastAddedElementPos, sizeof(unsigned));
		*AddedElement = CurrentBlockTerminationPos;
	    }
	}
    }

    unsigned PreviousTerminationNum = 0;
    unsigned CurrentTerminationNum = GetSize_DynamicArray(BlockTerminations);
    while( PreviousTerminationNum != CurrentTerminationNum)
    {
	unsigned TerminationNo;
	for( TerminationNo=0; TerminationNo< CurrentTerminationNum; TerminationNo++)
	{
	    unsigned* CurrentTerminationPos = GetElement_DynamicArray(BlockTerminations, TerminationNo, sizeof(unsigned));
	    TxOpContainer_t* TerminationTxOpContainer = &(CurrentTxDef -> TxOpList[0][*CurrentTerminationPos]) ;
	    unsigned NextTxOpPos = *CurrentTerminationPos +1;
	    bool BranchBypassingNextTxOp = (TerminationTxOpContainer->NextContainerID[0] > NextTxOpPos );
	    if( BranchBypassingNextTxOp )
	    {
		unsigned NewTerminationTxOpPos = TerminationTxOpContainer->NextContainerID[0] -1;

		// NewTerminationTxOpPos  exists already in BlockTerminations?
		bool AlreadyInList = FALSE;
		unsigned ElementNum = GetSize_DynamicArray(BlockTerminations);
		unsigned ElementNo;
		for(ElementNo=0; ElementNo< ElementNum; ElementNo++)
		{
		    unsigned* CurrentElement = GetElement_DynamicArray(BlockTerminations, ElementNo, sizeof(unsigned));
		    if( *CurrentElement == NewTerminationTxOpPos )
		    {
			AlreadyInList = TRUE;
			break;
		    }
		}

		if( !AlreadyInList)
		{
		    Extend_DynamicArray(BlockTerminations, sizeof(unsigned));
		    unsigned  LastAddedElementPos = GetSize_DynamicArray(BlockTerminations) - 1;
		    unsigned* AddedElement = GetElement_DynamicArray(BlockTerminations, LastAddedElementPos, sizeof(unsigned));
		    *AddedElement = NewTerminationTxOpPos;
		}

	    }
	}
	PreviousTerminationNum = CurrentTerminationNum;
        CurrentTerminationNum = GetSize_DynamicArray(BlockTerminations);
    }

}


void PrepareBlockTerminationCode(dyn_arr_t* BlockTerminations, char** CodeAfterTxOp )
{

    unsigned TerminationNum = GetSize_DynamicArray(BlockTerminations);
    unsigned TerminationNo;
    for( TerminationNo=0; TerminationNo< TerminationNum; TerminationNo++)
    {
	unsigned* CurrentTerminationPos = GetElement_DynamicArray(BlockTerminations, TerminationNo, sizeof(unsigned));
	CodeAfterTxOp[*CurrentTerminationPos] = strext(CodeAfterTxOp[*CurrentTerminationPos],"}\n");
    }
}


void PrepareIntermediateBranchCode(TxInfo_t* CurrentTxDef, dyn_arr_t* BlockTerminations, char** CodeBeforeTxOp)
{
    unsigned TerminationNum = GetSize_DynamicArray(BlockTerminations);
    unsigned TerminationNo;
    for( TerminationNo=0; TerminationNo< TerminationNum; TerminationNo++)
    {
	unsigned* CurrentTerminationPos = GetElement_DynamicArray(BlockTerminations, TerminationNo, sizeof(unsigned));
	TxOpContainer_t* BlockTerminatingTxOpContainer = &(CurrentTxDef -> TxOpList[0][*CurrentTerminationPos]) ;
	unsigned NextTxOpPos = *CurrentTerminationPos+1;
	bool BranchBypassingNextTxOp = (BlockTerminatingTxOpContainer->NextContainerID[0] > NextTxOpPos );

	if( BranchBypassingNextTxOp )
	{
	    TxOpContainer_t* NextTxOpContainer = &(CurrentTxDef -> TxOpList[0][NextTxOpPos]) ;
	    bool NextContainerIsConditionTxOp  = (NextTxOpContainer -> ConditionExprPos != INVALID_CONDITION_EXPR_POS && !(NextTxOpContainer -> LoopIteratorContainer) );
	    if( NextContainerIsConditionTxOp) // Next container contains an "else if" statement
	    {
		// Prepare the "else " prefix for the "else if" statement (the if part will be printed while the TxOp is processed)
		CodeBeforeTxOp[NextTxOpPos] = strext(CodeBeforeTxOp[NextTxOpPos],"else ");
	    }
	    else // Next container is the first TxOp of an "else" block
	    {
		// Prepare the code opening an "else" block
		CodeBeforeTxOp[NextTxOpPos] = strext(CodeBeforeTxOp[NextTxOpPos],"else\n{\n");
	    }

	}

    }

}

void PrepareVarAssignCode(TxInfo_t* CurrentTxDef, char** CodeAfterTxOp, const  VarExpr* VarExprList, unsigned VarExprListSize)
{
    unsigned TxOpNum = CurrentTxDef -> TxOpNum[0];
    unsigned TxOpNo;
    for( TxOpNo=0; TxOpNo< TxOpNum; TxOpNo++)
    {
	TxOpContainer_t* CurrentTxOpContainer = &(CurrentTxDef -> TxOpList[0][TxOpNo]) ;
	bool LoopStartContainer = (CurrentTxOpContainer -> LoopIteratorContainer);
	if( ! LoopStartContainer)
	{
	    unsigned VarAssignNo;
	    for(VarAssignNo=0; VarAssignNo< CurrentTxOpContainer -> VarAssignNum; VarAssignNo++)
	    {
		var_assign_t* CurrentVarAssign = &(CurrentTxOpContainer -> VarAssigns[VarAssignNo]);

		char* EvaluatedVarExprString=NULL;
		GenerateVarExprString(CurrentVarAssign->EvaluatedVarExprID, VarExprList, VarExprListSize, &EvaluatedVarExprString);

		char* AssignedVarExprString=NULL;
		GenerateVarExprString(CurrentVarAssign->AssignedVarID, VarExprList, VarExprListSize, &AssignedVarExprString);

		CodeAfterTxOp[TxOpNo]=strext(CodeAfterTxOp[TxOpNo],AssignedVarExprString);
		CodeAfterTxOp[TxOpNo]=strext(CodeAfterTxOp[TxOpNo]," = ");
		CodeAfterTxOp[TxOpNo]=strext(CodeAfterTxOp[TxOpNo],EvaluatedVarExprString);
		CodeAfterTxOp[TxOpNo]=strext(CodeAfterTxOp[TxOpNo],";\n");

	    }
	}
    }
}



 void GenerateRandomVariableUpdateCode(FILE* TransactionsContentFile, const TxInfo_t* CurrentTxDef, const VarExpr* VarExprList, unsigned VarExprListSize)
 {

     unsigned VarToUpdateNum = CurrentTxDef -> VarToUpdateNum;
     char*    RandomVariableUpdateCode = NULL;

     unsigned VarToUpdateNo;
     for(VarToUpdateNo = 0; VarToUpdateNo< VarToUpdateNum; VarToUpdateNo++)
     {
	 unsigned CurrentVarToUpdateID = CurrentTxDef -> VarListToUpdate[VarToUpdateNo];
	 char* VarToUpdateString = NULL;
	 GenerateVarExprString(CurrentVarToUpdateID, VarExprList, VarExprListSize, &VarToUpdateString);

	 const VarExpr* VarToUpdate = &(VarExprList[CurrentVarToUpdateID ]);
	 assert(VarToUpdate != NULL);


	 unsigned LowerLimitVarExprID = VarToUpdate->OperandID[0];
	 unsigned UpperLimitVarExprID = VarToUpdate->OperandID[1];

	 char* LowerLimitVarExprString = NULL;
	 GenerateVarExprString(LowerLimitVarExprID, VarExprList, VarExprListSize, &LowerLimitVarExprString);

	 char* UpperLimitVarExprString = NULL;
	 GenerateVarExprString(UpperLimitVarExprID, VarExprList, VarExprListSize, &UpperLimitVarExprString);


	 char* TempCodeLine = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	 sprintf(TempCodeLine,"Range = %s - %s + 1;\n", UpperLimitVarExprString, LowerLimitVarExprString );
	 RandomVariableUpdateCode = strext(RandomVariableUpdateCode,TempCodeLine);


	 // Removing the "ThLocals->" prefix for use in seed variable name
	 unsigned CharNumToRemove  = strlen("ThLocals->");
	 char* RandomVariableNameBase = dupstr(&(VarToUpdateString[CharNumToRemove]));

	 sprintf(TempCodeLine," %s = %s + ChooseFromUniformDist( Range, &(ThLocals->seed_%s) );\n ", VarToUpdateString, LowerLimitVarExprString,  RandomVariableNameBase );
	 RandomVariableUpdateCode = strext(RandomVariableUpdateCode,TempCodeLine);

/* 	 if( EnableTrace) */
/* 	 { */
/* 	     // Code to print the value of seed if a trace is being printed. */
/* 	     sprintf(TempCodeLine,"if(EnableTrace)\n" */
/* 		     "    printf(\"%%s[%%u]%s=%%u\\n\", ThLocals->PrintOffset, ThLocals->ThreadID, %s);\n",RandomVariableNameBase, VarToUpdateString); */
/* 	     RandomVariableUpdateCode = strext(RandomVariableUpdateCode,TempCodeLine); */

/* 	 } */



	 free(VarToUpdateString);
	 free(LowerLimitVarExprString);
	 free(UpperLimitVarExprString);
	 free(TempCodeLine);
	 free(RandomVariableNameBase);

     }
     if( RandomVariableUpdateCode != NULL)
	 fprintf(TransactionsContentFile,"%s",RandomVariableUpdateCode);

 }




void  Generate_Transaction_C_Code()
{

    GenerateVariableDefsBeforeSwitchStatement();

    ThreadInfo_t* FirstThreadDef = &(ThreadDefArray[0]);

    unsigned TxDefNo;
    unsigned TxDefNum = FirstThreadDef -> TxDefNum;


    // Open the file
    char CurrentFileName[100];
    sprintf(CurrentFileName,"%s/transactions.content", INTERMEDIATE_GENERATED_C_OUTPUT_PATH);

    FILE* TransactionsContentFile = fopen(CurrentFileName,"w");
    assert (TransactionsContentFile != NULL);

    VarExpr* VarExprList     = FirstThreadDef->VarExprList;
    unsigned VarExprListSize = FirstThreadDef->VarExprNum ;

    dyn_arr_t BlockTerminations;
    Initialize_DynamicArray(&BlockTerminations);
    for( TxDefNo=0; TxDefNo< TxDefNum; TxDefNo++)
    {

	TxInfo_t* CurrentTxDef = &(FirstThreadDef-> TxDefArray[TxDefNo]);
	unsigned TxOpNum = CurrentTxDef -> TxOpNum[0];
	char* CodeBeforeTxOp[TxOpNum];
	char* CodeAfterTxOp[TxOpNum];
	unsigned TxOpNo;
	for(TxOpNo=0; TxOpNo< TxOpNum; TxOpNo++)
	{
	    CodeBeforeTxOp[TxOpNo] = NULL;
	    CodeAfterTxOp[TxOpNo]  = NULL;
	}


	Clear_DynamicArray(&BlockTerminations);
	MarkBlockTerminations(CurrentTxDef, &BlockTerminations);
	PrepareIntermediateBranchCode(CurrentTxDef, &BlockTerminations, CodeBeforeTxOp);

	PrepareVarAssignCode(CurrentTxDef, CodeAfterTxOp, VarExprList, VarExprListSize);
	PrepareBlockTerminationCode(&BlockTerminations, CodeAfterTxOp);



	fprintf(TransactionsContentFile,"case %u:\n", TxDefNo);
	// Generating code updating the random variables before the transaction starts.
	GenerateRandomVariableUpdateCode(TransactionsContentFile, CurrentTxDef, VarExprList, VarExprListSize);
	if( CurrentTxDef -> ReadOnly && TransmitReadOnlyTxHint )
	    fprintf(TransactionsContentFile,"%s;\n",TRANSACTION_READ_ONLY_START_MACRO_NAME );
	else
	    fprintf(TransactionsContentFile,"%s;\n",TRANSACTION_START_MACRO_NAME );

	for( TxOpNo=0; TxOpNo< TxOpNum; TxOpNo++)
	{



	    // Writing code to be printed before CurrentTxOp
	    if( CodeBeforeTxOp[TxOpNo] != NULL)
		fprintf(TransactionsContentFile,"%s",CodeBeforeTxOp[TxOpNo]);

	    TxOpContainer_t* CurrentTxOp = &(CurrentTxDef -> TxOpList[0][TxOpNo]) ;
	    if ( CurrentTxOp -> TxOperation == READ)
	    {
		unsigned AddressVarExprID = CurrentTxOp -> AddrOp;
		char* AddressVarExprString= NULL;
		GenerateManagedAdressAccessString(AddressVarExprID, VarExprList, VarExprListSize, &AddressVarExprString);

		char* ReadAccessString = NULL;
		ReadAccessString = strext(ReadAccessString,TRANSACTIONAL_MEM_READ);
		ReadAccessString = strext(ReadAccessString,"(");
		ReadAccessString = strext(ReadAccessString,AddressVarExprString);
		ReadAccessString = strext(ReadAccessString,")");


		fprintf(TransactionsContentFile,"%s;\n", ReadAccessString);


		unsigned VariableToStoreReturnedValue_ID =  CurrentTxOp -> AccessedAddrGenID[0];
		bool VariableToStoreReturnValueSpecified = ( VariableToStoreReturnedValue_ID < (unsigned) -1 );
		if( VariableToStoreReturnValueSpecified )
		{
		    char* AssignedVarString= NULL;
		    GenerateVarExprString(VariableToStoreReturnedValue_ID, VarExprList, VarExprListSize, &AssignedVarString);
		    fprintf(TransactionsContentFile,"%s = ValueRead;\n", AssignedVarString);
		}
	    }
	    else if ( CurrentTxOp -> TxOperation == WRITE)
	    {
		unsigned AddressVarExprID = CurrentTxOp -> AddrOp;
		char* AddressVarExprString= NULL;
		GenerateManagedAdressAccessString(AddressVarExprID, VarExprList, VarExprListSize, &AddressVarExprString);


		char* WriteAccessString = NULL;
		WriteAccessString = strext(WriteAccessString,TRANSACTIONAL_MEM_WRITE);
		WriteAccessString = strext(WriteAccessString,"(");
		WriteAccessString = strext(WriteAccessString,AddressVarExprString);
		WriteAccessString = strext(WriteAccessString,")");


		char* StoreValueSourceVarExprString = NULL;
		unsigned StoreValueSourceVariableExprID = CurrentTxOp -> AccessedAddrGenID[0];
		bool StoreValueSourceVariableSpecified = ( StoreValueSourceVariableExprID < (unsigned) -1 );
		if( StoreValueSourceVariableSpecified)
		{
		    GenerateVarExprString(StoreValueSourceVariableExprID, VarExprList, VarExprListSize, &StoreValueSourceVarExprString);
		}
		else
		{
		    StoreValueSourceVarExprString = dupstr("ThLocals->WriteValue");
		}

		// Replacing the last ")" in the WriteAccessString with a ","
		unsigned WriteAccessStringLength = strlen(WriteAccessString);
		WriteAccessString[WriteAccessStringLength-1] = ',';
		WriteAccessString = strext(WriteAccessString,StoreValueSourceVarExprString);
		WriteAccessString = strext(WriteAccessString,")");

		fprintf(TransactionsContentFile,"%s;\n", WriteAccessString);
		if(!StoreValueSourceVariableSpecified)
		    fprintf(TransactionsContentFile,"ThLocals->WriteValue++;\n");

	    }
	    else if ( CurrentTxOp -> TxOperation == INVALID )
	    {

		bool LoopIteratorStartTxOp = (CurrentTxOp -> LoopIteratorContainer) ;
		bool ConditionTxOp         = (CurrentTxOp -> ConditionExprPos != INVALID_CONDITION_EXPR_POS);
		if ( LoopIteratorStartTxOp )
		{
		    // Generating the for loop statement



		    // Generating the initialization statement
		    VarExpr* LoopConditionExpr =  &(VarExprList[ CurrentTxOp -> ConditionExprPos ]);
		    unsigned LoopInitialValExprID = LoopConditionExpr->OperandID[2];
		    char* LoopInitialValExprString = NULL;
		    GenerateVarExprString(LoopInitialValExprID, VarExprList, VarExprListSize, &LoopInitialValExprString);

		    unsigned LoopIteratorID = LoopConditionExpr->OperandID[0];
		    char* LoopIteratorString = NULL;
		    GenerateVarExprString(LoopIteratorID, VarExprList, VarExprListSize, &LoopIteratorString);


		    char* InitializationStatement = NULL;
		    InitializationStatement = strext(InitializationStatement,LoopIteratorString);
		    InitializationStatement = strext(InitializationStatement," = ");
		    InitializationStatement = strext(InitializationStatement,LoopInitialValExprString);

		    free(LoopInitialValExprString);
		    free(LoopIteratorString);

		    // Generation Condition Expression
		    char* ConditionExprString = NULL;
		    GenerateVarExprString(CurrentTxOp -> ConditionExprPos, VarExprList, VarExprListSize, &ConditionExprString);

		    // Generating Increment statement
		    var_assign_t* CurrentVarAssign = &(CurrentTxOp -> VarAssigns[0]);

		    char* IncrementString=NULL;
		    GenerateVarExprString(CurrentVarAssign -> EvaluatedVarExprID, VarExprList, VarExprListSize, &IncrementString);

		    char* AssignedVarExprString=NULL;
		    GenerateVarExprString(CurrentVarAssign -> AssignedVarID, VarExprList, VarExprListSize, &AssignedVarExprString);


		    char* IncrementStatement = NULL;
		    IncrementStatement = strext(IncrementStatement,AssignedVarExprString);
		    IncrementStatement = strext(IncrementStatement," = ");
		    IncrementStatement = strext(IncrementStatement,IncrementString);

		    free(IncrementString);
		    free(AssignedVarExprString);

		    fprintf(TransactionsContentFile,"for( %s; %s; %s )\n{\n" , InitializationStatement, ConditionExprString, IncrementStatement );

		}
		else if(ConditionTxOp)
		{
		    char* ConditionStatement  = NULL;
		    GenerateVarExprString(CurrentTxOp -> ConditionExprPos, VarExprList, VarExprListSize, &ConditionStatement);

		    char* IfStatement = NULL;
		    IfStatement = strext(IfStatement,"if");
		    IfStatement = strext(IfStatement,ConditionStatement);
		    IfStatement = strext(IfStatement,"\n{\n");

		    fprintf(TransactionsContentFile,"%s", IfStatement);
		}
	    }

	    // Writing code to be printed after CurrentTxOp
	    if( CodeAfterTxOp[TxOpNo] != NULL)
		fprintf(TransactionsContentFile,"%s",CodeAfterTxOp[TxOpNo]);
	}

	fprintf(TransactionsContentFile,"%s;\n",TRANSACTION_COMMIT_MACRO_NAME);
	fprintf(TransactionsContentFile,"break;\n");

    }
    fclose(TransactionsContentFile);

    printf("- Generated code related to transactions.\n");

}




void GenerateCodeInitializingGlobalOptions()
{

    char CurrentFileName[100];
    FILE* SimulationParameterInitializationFile;

    sprintf(CurrentFileName,"%s/simulation_parameter_initialization.c", INTERMEDIATE_GENERATED_C_OUTPUT_PATH);
    SimulationParameterInitializationFile = fopen(CurrentFileName,"w");
    assert (SimulationParameterInitializationFile != NULL);

    fprintf(SimulationParameterInitializationFile,"TransmitReadOnlyTxHint = %u;\n"
	                                          "\n"
	                                          "MainSeed = %u;\n"
	                                          "MainMax = %u;\n"
	                                          "RandomDebug = %u;\n"
	                                          "\n"
	                                          "WaitForTimeOut = %u;\n"
	                                          "TimeOutValueSet = %u;\n"
	                                          "DelayUnit = %u;\n"
	                                          "TimeOut = %u;\n"
	                                          "\n"
	                                          "PrintStats = %u;\n"
	                                          "EnableTrace = %u;\n"
	                                          "JustGenerateTrace = %u;\n"
	                                          "EnableTraceFromCommandLine = %u;\n"
	                                          "\n"
	                                          "SerialThreadExecution = %u;\n", \
	    TransmitReadOnlyTxHint,		\
	    MainSeed,					\
	    MainMax,					\
	    RandomDebug,				\
	    WaitForTimeOut,				\
	    TimeOutValueSet,			\
	    DelayUnit,					\
	    TimeOut,					\
	    PrintStats,					\
	    EnableTrace,				\
	    JustGenerateTrace,			\
	    EnableTraceFromCommandLine,	\
	    SerialThreadExecution);

    fclose(SimulationParameterInitializationFile);

    printf("- Generated code initializing simulation_parameters.\n");

    return;
}


void Generate_C_CodeForThread(unsigned ThreadID) {
	char DummyString[1000];
    char CurrentFileName[100];

    FILE* ThreadContentFile;

    sprintf(CurrentFileName,"%s/thread_%u.content", INTERMEDIATE_GENERATED_C_OUTPUT_PATH, ThreadID);

    ThreadContentFile = fopen(CurrentFileName,"w");
    assert (ThreadContentFile != NULL);


    ThreadInfo_t* CurrentThreadDef = &(ThreadDefArray[ThreadID]);
    int ContainerNo;
    int ContainerNum = (int) CurrentThreadDef -> TxContainerNum ;

    char* CodeBeforeTransaction[ContainerNum];
    char* CodeAfterTransaction[ContainerNum];


    dyn_arr_t LoopStartContainers;
    Initialize_DynamicArray(&LoopStartContainers);
    unsigned LoopNestinglevel = 0;
    unsigned MaxLoopNestingLevel = 0 ;
    unsigned RequiredTxCandidateListContainerNum = 0;



    // Initializing the strings that come before and after a transaction
    for(ContainerNo=0; ContainerNo< ContainerNum; ContainerNo++)
    {
	CodeBeforeTransaction[ContainerNo] = NULL;
	CodeAfterTransaction[ContainerNo]  = NULL;
    }

    // First pass over Containers (reverse pass).
    //    i) Finding out loop beginning and terminations.
    //   ii) Finds out the number of multi candidate TxContainers
    for(ContainerNo=ContainerNum-1; ContainerNo >= 0; ContainerNo--)
    {
//	printf("ContainerNo=%d\n",ContainerNo);
	TxContainer_t* CurrentTxContainer = &(CurrentThreadDef -> TxContainerList[ContainerNo]);

	// Find out whether the current node is a loop end node
	bool FiniteLoopEndContainer   =  ( CurrentTxContainer -> InitialRepetitionCount > 0 || CurrentTxContainer -> LoopEndNodeWithVarExpr);
	bool InfiniteLoopEndContainer =  ( CurrentTxContainer -> NextContainerID[0] < ContainerNo+1 );
	bool LoopEndContainer = ( FiniteLoopEndContainer || InfiniteLoopEndContainer );

	if( LoopEndContainer)
	{

	    // Generate code for terminating the loop
	    sprintf(DummyString,"}\n");
	    CodeAfterTransaction[ContainerNo] = strext(CodeAfterTransaction[ContainerNo],DummyString);


	    // Generate code for beginning of the loop
	    unsigned LoopStartContainerNo;
	    if( InfiniteLoopEndContainer )
	    {
		sprintf(DummyString,"for(; ; )\n{\n");
		LoopStartContainerNo = CurrentTxContainer -> NextContainerID[0];
	    }
	    else if( FiniteLoopEndContainer )
	    {

	        //HARMANCI: CODE ADDED/MODIFIED FOR VARIABLE EXPR WITHIN THREAD DEF		
		char* LoopLimitExprString = NULL;
		if(CurrentTxContainer ->LoopEndNodeWithVarExpr )
		{
		    ThreadInfo_t* FirstThreadDef = &(ThreadDefArray[0]);
		    VarExpr*      VarExprList     = FirstThreadDef->VarExprList;
		    unsigned      VarExprListSize = FirstThreadDef->VarExprNum ;

		    GenerateVarExprString(CurrentTxContainer -> LoopLimitExprPos, VarExprList, VarExprListSize, &LoopLimitExprString);
		}
		else
		{
		    int MaxIntegerValueCharNum = 100;
		    LoopLimitExprString = (char *)malloc(sizeof(char)*MaxIntegerValueCharNum);
		    sprintf (LoopLimitExprString, "%u", CurrentTxContainer -> InitialRepetitionCount);
		}    
		
		sprintf(DummyString,"for(RepetitionNo[%u]=0 ; RepetitionNo[%u]< %s ; RepetitionNo[%u]++ )\n{\n",LoopNestinglevel, LoopNestinglevel, LoopLimitExprString , LoopNestinglevel);
		// END OF CODE ADDED/MODIFIED FOR VARIABLE EXPR WITHIN THREAD DEF		

		LoopStartContainerNo = CurrentTxContainer -> NextContainerID[1];
	    }
	    CodeBeforeTransaction[LoopStartContainerNo] = strext(CodeBeforeTransaction[ContainerNo],DummyString);

	    // Store the start node for the current loop so that when reached to the start node the nesting level can be decreased
	    Extend_DynamicArray(&LoopStartContainers,sizeof(LoopStartContainerNo));
	    unsigned LoopStartContainerPos = GetSize_DynamicArray(&LoopStartContainers) -1 ;
	    unsigned*  CurrentElement =  GetElement_DynamicArray(&LoopStartContainers,LoopStartContainerPos,sizeof(unsigned));
	    *CurrentElement = LoopStartContainerNo;

	    // Increase Loop nesting level
	    LoopNestinglevel++;
	    if (MaxLoopNestingLevel < LoopNestinglevel)
		MaxLoopNestingLevel = LoopNestinglevel;
	}


	// Decrease nesting level, if this container is a loop start that has been recorded beforehand
	if(LoopNestinglevel >0)
	{
	    bool CheckNextStartContainer = TRUE;
	    while( CheckNextStartContainer)
	    {
		unsigned NextLoopStartContainerNum = LoopStartContainers.ArrayElementNum ;
		unsigned NextLoopStartContainerToRemove = ((unsigned*)(LoopStartContainers.ArrayStartAddress))[NextLoopStartContainerNum-1];
		if( NextLoopStartContainerToRemove == ContainerNo )
		{
		    Chop_DynamicArray(&LoopStartContainers);
		    assert( LoopNestinglevel > 0);
		    LoopNestinglevel --;
		    NextLoopStartContainerNum = LoopStartContainers.ArrayElementNum ;
		    if( NextLoopStartContainerNum == 0)
			CheckNextStartContainer = FALSE;
		}
		else
		    CheckNextStartContainer= FALSE;
	    }

	}

	// Finding out the number of multi candidate TxContainers
	bool CurrentContainerHasMultipleCandidates = (CurrentTxContainer -> CandidateTxNum > 1);
	if ( CurrentContainerHasMultipleCandidates  )
	    RequiredTxCandidateListContainerNum++;

    }



    sprintf(CurrentFileName,"%s/thread_%u_variable_declarations.c", INTERMEDIATE_GENERATED_C_OUTPUT_PATH, ThreadID);
    FILE* ThreadVariableDeclarationFile = fopen(CurrentFileName,"w");
    assert (ThreadVariableDeclarationFile != NULL);
    fprintf(ThreadVariableDeclarationFile,"// Definition and initialization of thread local variables.\n");

    bool LoopsExist = (MaxLoopNestingLevel > 0);
    if( LoopsExist )
    {
	sprintf(DummyString,"unsigned RepetitionNo[%u];\n",MaxLoopNestingLevel);
	fprintf(ThreadVariableDeclarationFile,"%s",DummyString);
    }

    // (Conditional) Second pass over Containers (forward pass).
    // This pass is only done if there is need for TxCandidateListContainers.
    // If so, the pass will generating the code to initialize those TxCandidateListContainers.
    unsigned TxCandidateListContainerNo=0;
    if(RequiredTxCandidateListContainerNum >0 )
    {
//	sprintf(DummyString,"TxCandidateListContainer_t CandidateListContainer[%u];\n",RequiredTxCandidateListContainerNum);
/* 	sprintf(DummyString,"unsigned CandidateListContainer[%u];\n",RequiredTxCandidateListContainerNum); */
/* 	ThreadHeaderFile */

	fprintf(ThreadVariableDeclarationFile,"unsigned ChosenTransactionID;\n");
	sprintf(DummyString,"TxCandidateListContainer_t CandidateListContainer[%u];\n",RequiredTxCandidateListContainerNum);
	fprintf(ThreadVariableDeclarationFile,"%s",DummyString);
	for(ContainerNo=0; ContainerNo< ContainerNum; ContainerNo++)
	{
	    TxContainer_t* CurrentTxContainer = &(CurrentThreadDef -> TxContainerList[ContainerNo]);
	    bool CurrentContainerHasMultipleCandidates = (CurrentTxContainer -> CandidateTxNum > 1);
	    if( CurrentContainerHasMultipleCandidates)
	    {
		fprintf(ThreadVariableDeclarationFile,"CandidateListContainer[%u].CandidateNum = %u;\n",TxCandidateListContainerNo,CurrentTxContainer -> CandidateTxNum);
		fprintf(ThreadVariableDeclarationFile,"CandidateListContainer[%u].Seed         = (unsigned) RAND_R(&CurrentThreadSeed);\n",TxCandidateListContainerNo);
		if ( CurrentTxContainer -> CandidateSelectionFunc == UniformDistNextTx)
		    fprintf(ThreadVariableDeclarationFile,"CandidateListContainer[%u].Distribution = UNIFORM;\n",TxCandidateListContainerNo);
		else if ( CurrentTxContainer -> CandidateSelectionFunc == PercentageDistNextTx)
		    fprintf(ThreadVariableDeclarationFile,"CandidateListContainer[%u].Distribution = PERCENTAGE;\n",TxCandidateListContainerNo);
		else
		    fprintf(ThreadVariableDeclarationFile,"CandidateListContainer[%u].Distribution = INVALID_DISTRIBUTION;\n",TxCandidateListContainerNo);

		fprintf(ThreadVariableDeclarationFile,"CandidateListContainer[%u].TxCandidateList = (TxCandidate_t*)malloc(CandidateListContainer[%u].CandidateNum*sizeof( TxCandidate_t ));\n", TxCandidateListContainerNo, TxCandidateListContainerNo);
		unsigned CandidateNo;
		for(CandidateNo=0; CandidateNo< CurrentTxContainer -> CandidateTxNum; CandidateNo++)
		{
		    fprintf(ThreadVariableDeclarationFile,"CandidateListContainer[%u].TxCandidateList[%u].TxID = %u;\n", TxCandidateListContainerNo, CandidateNo, CurrentTxContainer -> TxCandidateList[CandidateNo].TxID);
		    fprintf(ThreadVariableDeclarationFile,"CandidateListContainer[%u].TxCandidateList[%u].Percentage = %.12f;\n", TxCandidateListContainerNo, CandidateNo, CurrentTxContainer -> TxCandidateList[CandidateNo].Percentage);
		}

		if(RandomDebug)
		    fprintf(ThreadVariableDeclarationFile,"printf(\"Thread[%%u]: CandidateListContainer[%u].Seed = %%u \\n\", ID, CandidateListContainer[%u].Seed);\n", TxCandidateListContainerNo, TxCandidateListContainerNo);


		TxCandidateListContainerNo ++;
		if(TxCandidateListContainerNo == RequiredTxCandidateListContainerNum )
		    break;
	    }

	}
    }

    fclose(ThreadVariableDeclarationFile);



    // Third pass over Containers (forward pass). Generating the code for each containers on the output file.
    TxCandidateListContainerNo = 0;
    for(ContainerNo=0; ContainerNo< ContainerNum; ContainerNo++)
    {
	TxContainer_t* CurrentTxContainer = &(CurrentThreadDef -> TxContainerList[ContainerNo]);



	if( CodeBeforeTransaction[ContainerNo] != NULL)
	{
	    fprintf(ThreadContentFile,"%s",CodeBeforeTransaction[ContainerNo]);
	}



/* 	unsigned DelayBeforeTransaction = (unsigned) CurrentTxContainer ->PrecedingDelay[0] ; */
/* 	if( DelayBeforeTransaction > 0) */
/* 	{ */
/* 	    sprintf(DummyString,"usleep(%u);\n",DelayBeforeTransaction*DelayUnit); */
/* 	    fprintf(ThreadContentFile,"%s",DummyString); */
/* 	} */


/* 	if(EnableTrace) */
/* 	    fprintf(ThreadContentFile,"PRINT_DELAY_BEFORE_TX(%u);\n", DelayBeforeTransaction); */


	bool MultipleCandidateContainer = CurrentTxContainer -> CandidateTxNum > 1;
	if( !MultipleCandidateContainer)
	    fprintf(ThreadContentFile,"ExecuteTransaction(%u, ThLocals.TxDesc, &ThLocals);\n", (CurrentTxContainer->TxCandidateList[0]).TxID);
	else {
	    fprintf(ThreadContentFile,"ChosenTransactionID = ChooseTransaction( &(CandidateListContainer[%u]) );\n", TxCandidateListContainerNo);
	    fprintf(ThreadContentFile,"ExecuteTransaction(ChosenTransactionID, ThLocals.TxDesc, &ThLocals);\n");
	    TxCandidateListContainerNo++;
	}

	fprintf(ThreadContentFile,	"if(TerminateRequestedBySignal || i_got_killed(ThLocals.ThreadID))\n"
								"	TERMINATE_THREAD;\n");

	if( CodeAfterTransaction[ContainerNo] != NULL) {
	    fprintf(ThreadContentFile,"%s",CodeAfterTransaction[ContainerNo]);
	}

    }


    fclose(ThreadContentFile);


    // Generating Thread and Transaction Name arrays
    sprintf(CurrentFileName,"%s/thread_and_transaction_names.c", INTERMEDIATE_GENERATED_C_OUTPUT_PATH);
    FILE* ThreadAndTransactionNamesFile = fopen(CurrentFileName,"w");
    assert (ThreadAndTransactionNamesFile != NULL);

    char* ThreadAndTransactionNameDefinitionCode =NULL;
    ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode,"char* ThreadNames[]={");


    unsigned ThreadDefNo=0;
    char* CurrentThreadName;
    for(ThreadDefNo=0; ThreadDefNo < ThreadDefNum ; ThreadDefNo++)
    {
	CurrentThreadName = dupstr(ThreadDefArray[ThreadDefNo].Name);
	ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, "\"");
	ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, CurrentThreadName);
	ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, "\"");
	if( ThreadDefNo < ThreadDefNum-1 )
	    ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, ",");
	else
	    ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, "};\n");
	free(CurrentThreadName);
    }



    ThreadInfo_t* FirstThreadDef = &(ThreadDefArray[0]);
    unsigned TxDefNo;
    unsigned TxDefNum = FirstThreadDef -> TxDefNum;
    ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode,"char* TransactionNames[]={");
    for( TxDefNo=0; TxDefNo< TxDefNum; TxDefNo++)
    {
	TxInfo_t* CurrentTxDef = &(FirstThreadDef-> TxDefArray[TxDefNo]);
	ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, "\"");
	ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, CurrentTxDef -> Name);
	ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, "\"");
	if( TxDefNo < TxDefNum-1 )
	    ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, ",");
	else
	    ThreadAndTransactionNameDefinitionCode = strext(ThreadAndTransactionNameDefinitionCode, "};\n");
    }
    fprintf(ThreadAndTransactionNamesFile,"%s",ThreadAndTransactionNameDefinitionCode);
    fclose(ThreadAndTransactionNamesFile);


    printf("- Generated code related to threads.\n");

}



char* GenerateOperationString(unsigned Operation )
{
    unsigned MaxOperationStringSize = 4;
    char* OperationString = malloc(MaxOperationStringSize*sizeof(char));

    switch(Operation)
    {
	case PLUS:
	    OperationString = dupstr(" + ");
	    break;
	case MINUS:
	    OperationString = dupstr(" - ");
	    break;
	case MULTIPLY:
	    OperationString = dupstr(" * ");
	    break;
	case DIVIDE:
	    OperationString = dupstr(" / ");
	    break;
	case EQUAL:
	    OperationString = dupstr(" == ");
	    break;
	case NOT_EQUAL:
	    OperationString = dupstr(" != ");
	    break;
	case SMALLER_THAN:
	    OperationString = dupstr(" < ");
	    break;
	case GREATER_THAN:
	    OperationString = dupstr(" > ");
	    break;
	case SMALLER_EQUAL:
	    OperationString = dupstr(" <= ");
	    break;
	case GREATER_EQUAL:
	    OperationString = dupstr(" >= ");
	    break;
	case NOT:
	    OperationString = dupstr("!");
	    break;
	case AND:
	    OperationString = dupstr(" && ");
	    break;
	case OR:
	    OperationString = dupstr(" || ");
	    break;
        default:
            free(OperationString);
            OperationString = NULL;
	    break;
    }
    return OperationString;
}




bool IsConsantValue(const VarExpr* Target)
{
    char* VarExprName =  Target -> Name;
    unsigned Value = (unsigned)atoi(VarExprName);
    if(Value == 0)
    {
	bool ZeroString = (strcmp("0",VarExprName) == 0);
	if (ZeroString)
	    return TRUE;
	else
	    return FALSE;
    }
    else
	return TRUE;
}



void GenerateVarExprString(unsigned TargetVarExprID, const  VarExpr* VarExprList, unsigned VarExprListSize, char** ExpressionString)
{
    assert( VarExprList != NULL);
    const VarExpr* TargetVarExpr = &(VarExprList[TargetVarExprID]);
    bool IsLeafVarExpr = ( TargetVarExpr -> Type <= VAR_LOCAL_ARRAY_CONSTANT  \
                                                ||                            \
                           TargetVarExpr -> Type == OP_RANDOM_DIST            \
			                        ||                            \
			   TargetVarExpr -> Type ==OP_RANDOM_DIST_CONSTANT    \
	                 );
    if ( IsLeafVarExpr)
    {
	// Next line is the reason for limitation NO 4: Random variables can be only local (and not shared).
	bool ThreadLocalVariable = (TargetVarExpr -> Type >= VAR_LOCAL_SIMPLE && TargetVarExpr -> Type <= VAR_LOCAL_ARRAY_CONSTANT) \
	                                                                      ||                                                    \
                          	    (TargetVarExpr -> Type == OP_RANDOM_DIST  || TargetVarExpr -> Type ==OP_RANDOM_DIST_CONSTANT) ;
	if(ThreadLocalVariable)
	{
	    bool ConstantValue  = IsConsantValue(TargetVarExpr);
	    if(!ConstantValue)
		*ExpressionString = strext(*ExpressionString, "ThLocals->");
	}
	bool SharedVariable = (TargetVarExpr -> Type <= VAR_SHARED_CONSTANT_MANAGED);
	if( SharedVariable )
	{
	    *ExpressionString = strext(*ExpressionString, "(*");

	    bool ManagedSharedVariable = (TargetVarExpr -> Type == VAR_SHARED_MANAGED);
	    if(ManagedSharedVariable)
	    {
		// We Chop the & character which is at the beginning when we generate the ExpressionString
		*ExpressionString = strext(*ExpressionString, &((TargetVarExpr -> Name)[1]));
	    }
	    else
		*ExpressionString = strext(*ExpressionString, TargetVarExpr -> Name);

	    *ExpressionString = strext(*ExpressionString, ")");
	}
	else
	    *ExpressionString = strext(*ExpressionString, TargetVarExpr -> Name);
    }
    else
    {
	bool SingleOperandExpr = (TargetVarExpr -> Type >=  OP_ARITH_UNARY &&  TargetVarExpr -> Type <=  OP_MEMORY_WRITE);
	if(SingleOperandExpr)
	{
	    char* OperandString=NULL;
	    GenerateVarExprString(TargetVarExpr -> OperandID[0], VarExprList, VarExprListSize, &OperandString );

	    bool TransactionaMemOp = (TargetVarExpr -> Type == OP_MEMORY_READ || TargetVarExpr -> Type == OP_MEMORY_WRITE);
	    if( TransactionaMemOp)
	    {
		if(TargetVarExpr -> Type == OP_MEMORY_READ)
		    *ExpressionString = strext(*ExpressionString,TRANSACTIONAL_MEM_READ);
		else if(TargetVarExpr -> Type == OP_MEMORY_WRITE)
		    *ExpressionString = strext(*ExpressionString,TRANSACTIONAL_MEM_WRITE);

		const VarExpr* OperandExpr = &(VarExprList[TargetVarExpr -> OperandID[0]]);
		bool SharedArrayAccess = ( OperandExpr->Type == OP_MANAGED_ARRAY_ACCESS ||  OperandExpr->Type == OP_UNMANAGED_ARRAY_ACCESS  );
		if(SharedArrayAccess)
		{
		    char* TempString = NULL;
		    TempString = strext(TempString,"&(");
		    TempString = strext(TempString,OperandString);
		    TempString = strext(TempString,")");
		    free(OperandString);
		    OperandString = TempString;

		}
		else  // The operand should be a simple shared variable
		{
		    // Chopping the "(*" from the beginning and the ")" from the end
		    char* TempString = dupstr(OperandString);
		    free(OperandString);
		    unsigned TempStringLength = strlen(TempString);
		    // Chopping the chracted from the end
		    TempString[TempStringLength-1] = '\0';

		    //Chopping the first two characters
		    OperandString = dupstr( &(TempString[2]) );
		}
	    }
	    else
	    {
		char* OperationString = GenerateOperationString( TargetVarExpr ->Operation);
		*ExpressionString = strext(*ExpressionString, OperationString);
	    }
	    *ExpressionString = strext(*ExpressionString,"(");
	    *ExpressionString = strext(*ExpressionString,OperandString);
	    *ExpressionString = strext(*ExpressionString,")");
	}
	else // Two operand Expr
	{

	    char* FirstOperandString = NULL;
	    GenerateVarExprString(TargetVarExpr -> OperandID[0], VarExprList, VarExprListSize, &FirstOperandString );
	    assert(FirstOperandString != NULL);

	    char* SecondOperandString = NULL;
	    GenerateVarExprString(TargetVarExpr -> OperandID[1], VarExprList, VarExprListSize, &SecondOperandString );
	    assert(SecondOperandString != NULL);


	    bool ArrayAccess = ( TargetVarExpr -> Type == OP_UNMANAGED_ARRAY_ACCESS || TargetVarExpr -> Type == OP_MANAGED_ARRAY_ACCESS);
	    if(ArrayAccess)
	    {
		*ExpressionString = strext(*ExpressionString, FirstOperandString);
		*ExpressionString = strext(*ExpressionString, "[");
		*ExpressionString = strext(*ExpressionString, SecondOperandString);
		*ExpressionString = strext(*ExpressionString, "]");
	    }
	    else
	    {
		char* OperationString = GenerateOperationString( TargetVarExpr ->Operation);

		*ExpressionString = strext(*ExpressionString,"(");
		*ExpressionString = strext(*ExpressionString, FirstOperandString);
		*ExpressionString = strext(*ExpressionString, OperationString);
		*ExpressionString = strext(*ExpressionString, SecondOperandString);
		*ExpressionString = strext(*ExpressionString,")");

	    }
	}
    }


}



