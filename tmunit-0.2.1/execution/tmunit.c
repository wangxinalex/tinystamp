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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simulation_parameters.h"

#include "thread_execution_structure_generator.h"
extern ThreadInfo_t* ThreadDefArray;

#include "thread.h"
extern unsigned long TerminateRequestedBySignal;

#include "schedule_execution_structure_generator.h"
extern dyn_arr_t Dyn_ScheduleList;
extern char*	SelectedScheduleName;
extern unsigned SelectedScheduleNo;

#include <atomic_ops.h> // For operations to be done on shared TerminateRequestedBySignal  variable
#include <signal.h>	 // For signal name declarations and signal operations

#include "user_interface_console.h"
extern dyn_arr_t Dyn_ThreadDefConfigList;

#include "variable_expression.h"
extern dyn_arr_t Dyn_VariableExpressionArray;

extern FILE* yyin;
extern int   yyparse(void);

char* PreprocessedFileName = NULL;

#include "tm_interface.h"
#include "generate_files.h" // For GenerateVarExprString function

void PrintStatistics();
void PrintEffectiveSimulationParameters();
void PrintDevelopperTestWarning();


#if defined (ENNALS)
   stm* MEMORY;
#endif


int InitializeSimulationParameters() {
	MainSeed = 1 ;
	ReadConfigOnly = FALSE;
	ParseOnly = FALSE;
	PrintStats = TRUE;
	EnableTrace = FALSE;
	TransmitReadOnlyTxHint = FALSE;
	WaitForTimeOut = FALSE;
	TimeOutValueSet = FALSE;
	DelayUnit = 1000000;

	SerialThreadExecution = FALSE;
	ExecuteSchedule = FALSE;
	NoAbortInSchedule = FALSE;
	VarExprTestEnabled = FALSE;

	VerboseParserOutput = FALSE;
	EnableTraceFromCommandLine = FALSE;
	DurationSetInCommandLine   = FALSE;
	SeedSetInCommandLine	   = FALSE;

	RandomDebug = FALSE;
	Generate_C_output = FALSE;

	return 0;
}


int TransformToExecutableRepresentation() {
	ThreadDefArray = (ThreadInfo_t*)MakeStaticCopy_DynamicArray(&Dyn_ThreadDefArray,sizeof(ThreadInfo_t));

	// Generate local copies of Variable Expressions and Transaction Definitions in thread infos.
	unsigned TxDefArraySizeInMemory = TxDefNum*sizeof(TxInfo_t);
/*	 unsigned ExplicitAddrGenListSizeInMemory = ExplicitAddrGenNum*sizeof(AddrGen_t); */
	unsigned ThreadDefNo;
	for(ThreadDefNo=0; ThreadDefNo< ThreadDefNum; ThreadDefNo++ ) {
		ThreadInfo_t* CurrentThread = GetElement_DynamicArray(&Dyn_ThreadDefArray, ThreadDefNo, sizeof(ThreadInfo_t));
		ThreadDefArray[ThreadDefNo].Name = dupstr(CurrentThread->Name);

		ThreadDefArray[ThreadDefNo].TxDefNum = TxDefNum;
		ThreadDefArray[ThreadDefNo].TxDefArray = (TxInfo_t*)malloc(TxDefArraySizeInMemory);
		unsigned TxNo;
		for(TxNo=0; TxNo< TxDefNum; TxNo++) {
			ThreadDefArray[ThreadDefNo].TxDefArray[TxNo].Name = dupstr(TxDefArray[TxNo].Name);
			TX_INFO_Copy( &(TxDefArray[TxNo]), &(ThreadDefArray[ThreadDefNo].TxDefArray[TxNo]) );
//			TX_INFO_Print(&(TxDefArray[TxNo]));
//			TX_INFO_Print(&(ThreadDefArray[ThreadDefNo].TxDefArray[TxNo]));
		}

		ThreadDefArray[ThreadDefNo].VarExprNum = GetSize_DynamicArray(&Dyn_VariableExpressionArray);
		unsigned VarExprListSizeInMemory = ThreadDefArray[ThreadDefNo].VarExprNum * sizeof(VarExpr);
		ThreadDefArray[ThreadDefNo].VarExprList = (VarExpr*) malloc(VarExprListSizeInMemory);

		unsigned VarExprNo;
		for(VarExprNo=0; VarExprNo< ThreadDefArray[ThreadDefNo].VarExprNum  ; VarExprNo++) {
			VarExpr* CurrentVarExpr = (VarExpr*)GetElement_DynamicArray(&Dyn_VariableExpressionArray, VarExprNo, sizeof(VarExpr));
			VAR_EXPR_Copy(CurrentVarExpr, &(ThreadDefArray[ThreadDefNo].VarExprList[VarExprNo]));
		}
		ThreadDefArray[ThreadDefNo].Active = FALSE;
		#ifdef STATISTICS_TEST
			ThreadDefArray[ThreadDefNo].UnfinishedTxNum = 0;
		#endif
	}
	return 0;
}

int TransformToExecutableRepresentationForSchedule() {
	ThreadDefArray = (ThreadInfo_t*)MakeStaticCopy_DynamicArray(&Dyn_ScheduleThreadDefArray,sizeof(ThreadInfo_t));
	unsigned TxDefArraySizeInMemory = sizeof(TxInfo_t);
	unsigned ThreadDefNo;
	for(ThreadDefNo=0; ThreadDefNo< ScheduleThreadNum; ThreadDefNo++ ) {
		ThreadInfo_t*SourceThreadInfo = GetElement_DynamicArray(&Dyn_ScheduleThreadDefArray,ThreadDefNo, sizeof(ThreadInfo_t));

		ThreadDefArray[ThreadDefNo].TxDefNum = 1;
		ThreadDefArray[ThreadDefNo].TxDefArray = (TxInfo_t*)malloc(TxDefArraySizeInMemory);

		ThreadDefArray[ThreadDefNo].TxDefArray[0].Name = dupstr(SourceThreadInfo->TxDefArray[0].Name);
		TX_INFO_Copy( &(SourceThreadInfo->TxDefArray[0]), &(ThreadDefArray[ThreadDefNo].TxDefArray[0]) );

		ThreadDefArray[ThreadDefNo].VarExprNum = GetSize_DynamicArray(&Dyn_VariableExpressionArray);
		unsigned VarExprListSizeInMemory = ThreadDefArray[ThreadDefNo].VarExprNum * sizeof(VarExpr);
		ThreadDefArray[ThreadDefNo].VarExprList = (VarExpr*) malloc(VarExprListSizeInMemory);

		unsigned VarExprNo;
		for(VarExprNo=0; VarExprNo< ThreadDefArray[ThreadDefNo].VarExprNum  ; VarExprNo++) {
			VarExpr* CurrentVarExpr = (VarExpr*)GetElement_DynamicArray(&Dyn_VariableExpressionArray, VarExprNo, sizeof(VarExpr));
			VAR_EXPR_Copy(CurrentVarExpr, &(ThreadDefArray[ThreadDefNo].VarExprList[VarExprNo]));
		}
		ThreadDefArray[ThreadDefNo].Active = FALSE;
	}

	return 0;
}


void signal_catcher(int sig) {
  printf(" CAUGHT SIGNAL %d\n", sig);
  AO_store_full(&TerminateRequestedBySignal, TRUE);
}

void abort_behaviour(int sig) {
	printf("PROGRAM TERMINATES WITH ABORT.\n");
	exit(1);
}

/*!  \fn  int main(int argc, char*  argv[])
	 \brief   Function that first removes comments form input then parses it.
*/
int main(int argc, char*  argv[]) {
    #ifdef SUPPRESS_ASSERT_BEHAVIOUR
        signal(SIGABRT, abort_behaviour);
    #endif

	InitializeSimulationParameters();
	int ConfigFileArgumentPos = ProcessCommandLineArguments(argc,argv);

	char* ConfigFileName = dupstr(argv[ConfigFileArgumentPos]);
	FILE* ConfigFile= fopen(ConfigFileName,"r");
	if( ConfigFile == NULL) {
		char* ErrorMessage= malloc(sizeof(char)*MAX_CONSOLE_MESSAGE_LENGHT);
		sprintf(ErrorMessage,"%s",ConfigFileName);
		perror(ErrorMessage);
		free(ErrorMessage);
		exit(1);
	}
	fclose(ConfigFile);

	printf("\nInput Configuration File: %s\n",ConfigFileName);

	char* CommandString= malloc(sizeof(char)*MAX_CONSOLE_MESSAGE_LENGHT);
	char PreprocessedFileNameLength = strlen(ConfigFileName)+strlen("_preprocessed")+1;
	PreprocessedFileName = malloc(sizeof(char)*PreprocessedFileNameLength);
	sprintf(PreprocessedFileName,"%s_preprocessed",ConfigFileName);
	sprintf(CommandString,"%s/preprocess %s > %s", XSTR(ENV_PREPROCESSOR_SCRIPT_PATH), ConfigFileName,PreprocessedFileName);
	system(CommandString);

	if (argc > 1)
		yyin = fopen(PreprocessedFileName, "r");

	Initialize_DynamicArray(&Dyn_VariableExpressionArray);


	if( VerboseParserOutput )
	printf("\n-------------------------------------------------\n"
		   "	 *******  Parsing starts  ********\n"
		   "-------------------------------------------------\n\n"
		  );

	int ParsingReturnVal = yyparse();
	bool ParseSuccessful = (ParsingReturnVal == 0);

	if( VerboseParserOutput )
	printf("\n-------------------------------------------------\n"
		   "	 *******  Parsing completed  ********\n"
		   "-------------------------------------------------\n\n"
		  );

	if(VarExprTestEnabled) {
		if( Generate_C_output ) {
			unsigned VarExprListSize = GetSize_DynamicArray(&Dyn_VariableExpressionArray) ;
			VarExpr* VarExprList	 = Dyn_VariableExpressionArray.ArrayStartAddress ;
			unsigned VarExprNo;
			for(VarExprNo=0; VarExprNo< VarExprListSize; VarExprNo++) {
				char* CurrentExprString=NULL;
				GenerateVarExprString(VarExprNo, VarExprList, VarExprListSize, &CurrentExprString);
				printf("VarExpr[%u]: %s\n", VarExprNo, CurrentExprString);
			}
		}

	// If we are doing a  VarExprTest then we do not want to run any simulation.
	// Thus we set ParseSuccessful to FALSE to terminate program.
		ParseSuccessful = FALSE;
	}

	if( ParseSuccessful ) {
		#ifdef COMPILE_FOR_TEST
			PrintDevelopperTestWarning();
		#endif
		// Overriding config file parameters which have been given from command line.
		if(EnableTraceFromCommandLine)
			EnableTrace = TRUE;
		if( DurationSetInCommandLine)
			TimeOut = CommandLineDuration;
		if(SeedSetInCommandLine)
			MainSeed = CommandLineSeed;

		// If a  ThreadDefinition Config List has been  entered, check whether
			// the Thread names given in the list are one of the defined threads
		// (if not print and error and quit the program).
		unsigned ReplicatedThreadDefNum = GetSize_DynamicArray(&Dyn_ThreadDefConfigList);
		unsigned ReplicatedThreadDefNo;
		unsigned ReplicateThreadNum = 0;
		for(ReplicatedThreadDefNo=0; ReplicatedThreadDefNo< ReplicatedThreadDefNum; ReplicatedThreadDefNo++) {
			thread_def_config_t* CurrentElement = GetElement_DynamicArray(&Dyn_ThreadDefConfigList, ReplicatedThreadDefNo, sizeof(thread_def_config_t));
			printf("RepThDef[%u]: Name:%s ,Rep: %d\n", ReplicatedThreadDefNo,  CurrentElement ->  ThreadDefName, CurrentElement ->  ReplicationNum);
			unsigned FoundThreadNo  = FindThreadByName(CurrentElement ->ThreadDefName, (ThreadInfo_t*)Dyn_ThreadDefArray.ArrayStartAddress, ThreadDefNum);
			bool ThreadNameNotFound = (FoundThreadNo == ThreadDefNum );
			if( ThreadNameNotFound ) {
				printf("\nERROR: main():\n"
						"The thread name '%s' given in the thread configuration list of '-t' parameter\n"
						"does not exist in the configuration file '%s'\n\n",   CurrentElement ->  ThreadDefName, ConfigFileName);
				exit(1);
			}

			unsigned ReplicateNo=0;
			unsigned ReplicateNumForCurrentThreadDef = CurrentElement ->ReplicationNum - 1;
			for(ReplicateNo=0; ReplicateNo < ReplicateNumForCurrentThreadDef ; ReplicateNo++) {
				Duplicate_ThreadDef( CurrentElement -> ThreadDefName);

				unsigned MaxNumberOfDigitsAllowedForDuplicateNo = 16;
				unsigned DuplicateThreadNameLenght = strlen(CurrentElement -> ThreadDefName)+ strlen("(")+ MaxNumberOfDigitsAllowedForDuplicateNo + strlen(")") +1;
				char* DuplicateThreadName = (char*)malloc(DuplicateThreadNameLenght*sizeof(char));
				sprintf(DuplicateThreadName,"%s(%d)",CurrentElement -> ThreadDefName, ReplicateNo);

				unsigned DuplicateThreadDefNo = GetSize_DynamicArray(&Dyn_ThreadDefArray)-1;
				char** DuplicateTxNamePtr = &(((ThreadInfo_t *)(Dyn_ThreadDefArray.ArrayStartAddress))[DuplicateThreadDefNo].Name);
				free(*DuplicateTxNamePtr);
				*DuplicateTxNamePtr = DuplicateThreadName;
			}

			ReplicateThreadNum += ReplicateNumForCurrentThreadDef;
		}

		if(Generate_C_output) {  // C code generation
			TransformToExecutableRepresentation();
			Generate_C_Code();

			#ifdef COMPILE_FOR_TEST
				PrintDevelopperTestWarning();
				printf("\n\n"
						"-------------------------------------------------------\n"
						"The warning above is repeated to increase visibility.\n"
						"-------------------------------------------------------\n"
						"\n"
						"\n");
			#endif
		}
		else { // Interpreted Execution
			/* 	TerminateRequestedBySignal = FALSE; */
			/* 	EnableTrace = !NoTrace; */
			if(ExecuteSchedule) {
				EnableTrace = TRUE;

				// Check whether the requested schedule name exists among the stored schedules
				unsigned ScheduleNo = INVALID_SCHEDULE_NO;
				unsigned SelectedScheduleNo =  ScheduleNum;
				for(ScheduleNo=0; ScheduleNo< ScheduleNum ; ScheduleNo++) {
					Schedule* CurrentSchedStruct = (Schedule*)GetElement_DynamicArray(&Dyn_ScheduleList, ScheduleNo , sizeof(Schedule));
					bool ScheduleFound = (strcmp(CurrentSchedStruct->Name, SelectedScheduleName) == 0);
					if( ScheduleFound )	{
						SelectedScheduleNo = ScheduleNo;
						break;
					}
				}
				bool ScheduleFound = (SelectedScheduleNo < ScheduleNum);
				if( !ScheduleFound) {
					printf("\nERROR: main():\n"
							"The schedule name '%s' given with the '-S' parameter does not exist\n"
							"in the configuration file '%s'\n\n",   SelectedScheduleName, ConfigFileName);
					exit(1);
				}

				TransformToExecutableRepresentationForSchedule();

				unsigned ThreadNum = ScheduleThreadNum ;
				InitializeThreadSeeds(ThreadNum);
				pthread_t	   Thrd[ThreadNum];
				thread_input_t  th_input[ThreadNum];
				// Creating a barrier per thread.
				// And extra barrier is also provided for the scheduler thread.
				barrier_t* ThreadBarriers[ThreadNum];

				barrier_t* SchedulerBarrier = malloc(sizeof(barrier_t));
				barrier_init(SchedulerBarrier,2);
				barrier_init(&barrier, ThreadNum+1);


				unsigned ThreadNo=0;
				for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++) {
					th_input[ThreadNo].thread_ID  = ThreadNo;
					//		th_input[ThreadNo].MaxTxNumToExecute = TxToExecute;
					th_input[ThreadNo].ThreadSeed = ThreadSeed[ThreadNo];

					ThreadBarriers[ThreadNo] = malloc(sizeof(barrier_t));
					barrier_init(ThreadBarriers[ThreadNo], 2);
					th_input[ThreadNo].ThreadBarrier	= ThreadBarriers[ThreadNo];
					th_input[ThreadNo].SchedulerBarrier = SchedulerBarrier;
				}

				// Probably not needed, but since there is no default constructor type of
				// function  generating  all  Label  type  TxOps  with  Labels
				// disabled. We go through  all the transaction definitions of
				// all threads to disable all the Lables
				for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++) {
					unsigned TxOpNo;
					unsigned TxOpNum = ThreadDefArray[ThreadNo].TxDefArray[0].TxOpNum[0];
					for(TxOpNo=0; TxOpNo< TxOpNum ; TxOpNo++) {
						TxOpContainer_t*  TxOpContainer = &(ThreadDefArray[ThreadNo].TxDefArray[0].TxOpList[0][TxOpNo]);
						if( TxOpContainer -> TxOperation == LABEL_OP)
						TxOpContainer -> LabelEnabled = FALSE;
					}
				}


				#ifndef  NO_STM
					printf("Initializing STM...\n");
				#endif
				TM_INIT(0);

				for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++) {
					//	printf("Triggering thread %u...\n",ThreadNo);
					pthread_create(&(Thrd[ThreadNo]),NULL,ThreadStart,(void *)&(th_input[ThreadNo]) );
				}

				// The Scheduler thread first waits for all threads to start
				// and to become active (barrier initialized to ThreadNum+1).
				barrier_cross(&barrier);

				// Scheduler thread is allowed to start. It passes from initialization mode
				// to "Schedule Execution" mode.

				Schedule* CurrentSchedStruct = (Schedule*)GetElement_DynamicArray(&Dyn_ScheduleList, SelectedScheduleNo , sizeof(Schedule));
				ScheduleElement* CurrentSchedule = CurrentSchedStruct -> Schedule;

				printf("\n\n"
						"-----------------------------------------------------\n"
						"			   EXECUTING SCHEDULE '%s'			   \n"
						"-----------------------------------------------------\n"
						"\n", CurrentSchedStruct->Name);

				unsigned ContextSwitchNo,
				ContextSwitchNum = CurrentSchedStruct -> ScheduleLength;
				for(ContextSwitchNo=0; ContextSwitchNo< ContextSwitchNum; ContextSwitchNo++ ) {
					ScheduleElement* SchedElement = &(CurrentSchedule[ContextSwitchNo]);
					if( SchedElement->Assertion ) {
						VarExpr* VarExprList = ThreadDefArray[0].VarExprList;
						unsigned VarExprNum  = ThreadDefArray[0].VarExprNum;
						assert( SchedElement-> AssertionExprID < VarExprNum);

						VarExpr* AssertionExpr = &(VarExprList[SchedElement-> AssertionExprID]);
						assert(AssertionExpr != NULL);

						bool AssertionSatisfied = (bool)VAR_EXPR_Evaluate(AssertionExpr, VarExprList, VarExprNum);
						if(!AssertionSatisfied) {
							printf("Interruption in Schedule: Assertion [%s] not satisfied.\n"
									"\n\n"
									"-----------------------------------------------------\n"
									"					TEST FAILS					   \n"
									"-----------------------------------------------------\n"
									"\n", AssertionExpr->Name);
							exit(1);
						}


					}
					else if(SchedElement->VarAssignList != NULL) {
						// Current element is a variable assignment list (representing non transactional code between transactions)
						VarExpr* VarExprList = ThreadDefArray[0].VarExprList;
						unsigned VarExprListSize  = ThreadDefArray[0].VarExprNum;

						unsigned VarAssignNo;
						for(VarAssignNo=0; VarAssignNo< SchedElement-> VarAssignNum; VarAssignNo++) {
							var_assign_t* CurrentVarAssign = &(SchedElement->VarAssignList[VarAssignNo]);
							VarExpr*  ExprToEvaluate  = &( VarExprList[CurrentVarAssign->EvaluatedVarExprID] );
							assert(ExprToEvaluate !=NULL);
							signed long ValueToAssign = VAR_EXPR_Evaluate( ExprToEvaluate, VarExprList, VarExprListSize);
							VarExpr* AssignedVar	  = &( VarExprList[CurrentVarAssign->AssignedVarID] );
							assert(AssignedVar !=NULL);

							// Should check what kind of variable /variable expression is in AssignedVar
							// If SHARED VAR => Should call evaluated to get the address of shared var and write into that address.
							// If SHARED ARRAY ACCESS => Should again call Evaluate to get address and write into it
							// If LOCAL VAR  => write into Value fields as done below
							// If LOCAL_ARRAY ACCESS => Should call Evaluate to get address and write into it
							// If a CONSTANT => Assignment not valid (bit this should be found out during parsing)
							bool LocalVariable = (AssignedVar -> Type == VAR_LOCAL_SIMPLE );
							if( LocalVariable) {
								AssignedVar -> Value = ValueToAssign;
							}
							else if (AssignedVar -> Type == VAR_SHARED_UNMANAGED) {
								// If shared variable is encountered
								// Find the managed version of the shared variable
								char* SharedVariableName = dupstr("&");
								SharedVariableName = strext(SharedVariableName,AssignedVar->Name);

								unsigned ManagedVersionPos = VAR_EXPR_FindPos(SharedVariableName, VarExprList, VarExprListSize);
								assert(ManagedVersionPos < VarExprListSize);
								VarExpr* ManagedVersion =  &(VarExprList[ ManagedVersionPos]);

								Word* AddressToAssign = (Word*)VAR_EXPR_Evaluate( ManagedVersion, VarExprList, VarExprListSize);
								*AddressToAssign	  = (Word)ValueToAssign;
							}
							else {
								// Should  be elaborated  more because  to get
								// addresses  of  shared  variables or  arrays
								// requires Evaluation on Managed versions of
								// variables/arrays.

				/* 				bool ArrayAccess	= (AssignedVar -> Type == OP_UNMANAGED_ARRAY_ACCESS); */
				/* 				bool SharedVariable = (AssignedVar -> Type == VAR_SHARED_UNMANAGED);				 */
				/* 				if( ArrayAccess || SharedVariable) */
				/* 				{ */
				/* 					Word* AddressToAssign = (Word*)VAR_EXPR_Evaluate( AssignedVar, VarExprList, VarExprListSize); */
				/* 					*AddressToAssign	  = (Word)ValueToAssign; */
				/* 				} */
				/* 				else */
				/* 				{ */
				/* 					fprintf(stderr,"ExecuteTransaction: ERROR in '%s': Neither local/shared variable nor array assignment.\nCan not perform assignement.\n", CurrentTx -> Name); */
				/* 					assert(0); */
				/* 				} */
							}

							if(EnableTrace) {
								// For trace display purposes only
								Word AssignedVarUpdatedValue = (Word)VAR_EXPR_Evaluate( AssignedVar, VarExprList, VarExprListSize);
								printf("-------  %s = %lu  -------\n", AssignedVar -> Name, AssignedVarUpdatedValue);
								fflush(NULL);
							}

							bool UnsatisfiedInvariantsExist = FALSE;
							// Validate all invariants
							unsigned InvariantNo;
							for(InvariantNo=0; InvariantNo< InvariantNum; InvariantNo++) {
								Invariant* CurrentInvariant = GetElement_DynamicArray(&Dyn_InvariantArray, InvariantNo, sizeof(Invariant)) ;
								VarExpr* CurrentInvariantExpr = &(VarExprList[ CurrentInvariant -> VarExprID] );
								bool InvariantSatisfied = VAR_EXPR_Evaluate(CurrentInvariantExpr, VarExprList, VarExprListSize);
								if( !InvariantSatisfied ){
									UnsatisfiedInvariantsExist = TRUE;
									printf( "Invariant '%s' not satisfied.\n", CurrentInvariant->Name);
								}
							}

							if(UnsatisfiedInvariantsExist) {
								printf("Interruption in Schedule: One or more invariants not satisfied in non-transactional code.\n"
										"\n\n"
										"-----------------------------------------------------\n"
										"					TEST FAILS					   \n"
										"-----------------------------------------------------\n"
										"\n");
								exit(1);
							}
						}
					}
					else {
						unsigned ThreadToEnable = SchedElement->ThreadID;

						bool ThreadToEnableActive = ThreadDefArray[ThreadToEnable].Active;
						#ifdef COMPILE_FOR_TEST
							printf("ThreadToEnable=%u, Active=%u\n", ThreadToEnable, ThreadToEnableActive);
						#endif
						if( ThreadToEnableActive) {
							// Enabling the barrier for the label pointed by the SchedElement (for the next context switch occurs at this point)
							bool LabelShoulBeEnabled = (ThreadDefArray[ThreadToEnable].TxDefArray[SchedElement->TxID].TxOpNum[0] > SchedElement->LabelTxOpContainerNo) ;
							if(LabelShoulBeEnabled)
							ThreadDefArray[ThreadToEnable].TxDefArray[SchedElement->TxID].TxOpList[0][SchedElement->LabelTxOpContainerNo].LabelEnabled=TRUE;

							#ifdef COMPILE_FOR_TEST
								if ( ContextSwitchNo != 0)
								printf("Performing context switch...\n");
							#endif

							// Switch to ThreadToEnable
							barrier_cross(ThreadBarriers[ThreadToEnable]);
							barrier_cross(SchedulerBarrier);

							// ThreadToEnable returns control to this thread (scheduler thread)
							// Disabling the barrier for the label pointed by the SchedElement (all labels become disabled)
							if(LabelShoulBeEnabled)
								ThreadDefArray[ThreadToEnable].TxDefArray[SchedElement->TxID].TxOpList[0][SchedElement->LabelTxOpContainerNo].LabelEnabled=FALSE;
						}
					}
				}

				for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++)
					pthread_join(Thrd[ThreadNo],NULL);

				printf("\n\n"
						"-----------------------------------------------------\n"
						"			 TEST COMPLETES SUCCESFULLY			  \n"
						"-----------------------------------------------------\n\n");

				#ifndef  NO_STM
					printf("Shutting STM engine down...\n");
				#endif
				TM_EXIT(0);

				free(SchedulerBarrier);
				for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++)
					free(ThreadBarriers[ThreadNo]);

				#ifdef COMPILE_FOR_TEST
					PrintDevelopperTestWarning();
					printf("\n\n"
							"-------------------------------------------------------\n"
							"The warning above is repeated to increase visibility.\n"
							"-------------------------------------------------------\n"
							"\n"
							"\n");
				#endif


			}
			else { // ExecuteSchedule
				TransformToExecutableRepresentation();

				unsigned ThreadNum = ThreadDefNum ;
				InitializeThreadSeeds(ThreadNum);

				pthread_t	   Thrd[ThreadNum];
				thread_input_t  th_input[ThreadNum];

				unsigned ThreadNo=0;
				for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++) {
					th_input[ThreadNo].thread_ID  = ThreadNo;
			//		th_input[ThreadNo].MaxTxNumToExecute = TxToExecute;
					th_input[ThreadNo].ThreadSeed = ThreadSeed[ThreadNo];
				}

				if (signal(SIGHUP, signal_catcher) == SIG_ERR ||
					signal(SIGINT, signal_catcher) == SIG_ERR ||
					signal(SIGTERM, signal_catcher) == SIG_ERR ) {
					perror("Signal setup problem occured.\n");
					exit(1);
				}

// If a user defined signal is included than use this part
//
/* 		struct sigaction UserSigHandlingStruct; */
/* 		UserSigHandlingStruct.sa_handler = UserSigHandler;		 */
/* 		sigaction(10,&UserSigHandlingStruct,NULL); */

				PrintEffectiveSimulationParameters();

				if( SerialThreadExecution ) {
					#ifndef  NO_STM
						printf("Initializing STM...\n");
					#endif
					TM_INIT(0);

					unsigned ThreadNo;
					for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++ ) {
						ThreadStart((void *)&(th_input[ThreadNo]));
					}
					#ifndef  NO_STM
						printf("Shutting STM engine down...\n");
					#endif
					TM_EXIT(0);

					#ifdef COMPILE_FOR_TEST
						PrintDevelopperTestWarning();
						printf("\n\n"
								"-------------------------------------------------------\n"
								"The warning above is repeated to increase visibility.\n"
								"-------------------------------------------------------\n"
								"\n"
								"\n");
					#endif
				}
				else { //  Parallel Thread Execution
					#ifndef  NO_STM
						printf("Initializing STM...\n");
					#endif
					TM_INIT(0);
					barrier_init(&barrier, ThreadNum+1);
					for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++){
						// printf("Triggering thread %u...\n",ThreadNo);
						pthread_create(&(Thrd[ThreadNo]),NULL,ThreadStart,(void *)&(th_input[ThreadNo]) );
					}

					barrier_cross(&barrier);
				//	printf("STARTING EXECUTION...\n");

					if( WaitForTimeOut ) {
						struct timespec time_out;
						struct timespec left_time_out;
						time_out.tv_sec = TimeOut/1000000;
						time_out.tv_nsec = (long)((TimeOut%1000000)*1000);

			//			printf("TimeOut=%u, time_out= (%ld,%ld)\n",TimeOut, time_out.tv_sec,time_out.tv_nsec);

						while( nanosleep(&time_out,&left_time_out) == -1) {
							if(TerminateRequestedBySignal)
							break;
							printf("left_time_out= (%ld,%ld)\n", left_time_out.tv_sec,left_time_out.tv_nsec);

							time_out.tv_sec  = left_time_out.tv_sec;
							time_out.tv_nsec = left_time_out.tv_nsec;
						}

						AO_store_full(&TerminateRequestedBySignal, TRUE);
						printf("\n"
								"--------------------------\n"
								"EXECUTION TIMEOUT REACHED.\n"
								"--------------------------\n");
					}

					for(ThreadNo=0; ThreadNo< ThreadNum; ThreadNo++)
						pthread_join(Thrd[ThreadNo],NULL);

					#ifndef  NO_STM
						printf("Shutting STM engine down...\n");
					#endif
					TM_EXIT(0);

					if( PrintStats)
						PrintStatistics();

					#ifdef COMPILE_FOR_TEST
						PrintDevelopperTestWarning();
						printf("\n\n"
								"-------------------------------------------------------\n"
								"The warning above is repeated to increase visibility.\n"
								"-------------------------------------------------------\n"
								"\n"
								"\n");
					#endif
				}
			}
		}
		free(ConfigFileName);
	}
	sprintf(CommandString,"rm -f %s",PreprocessedFileName);
	system(CommandString);
	free(CommandString);
	return 0;
}



void PrintStatistics() {
	printf("\n\n ------------------ Statistics ------------------\n\n");

/* 	long long t_duration =  13987654321 ; */
/* 	long t_time_rest; */
/* 	long t_duration_s	= (long)(t_duration/1000000000) ;  t_time_rest = (long)(t_duration%1000000000); */
/* 	long t_duration_ms   = t_time_rest/1000000 ;			t_time_rest = t_time_rest%1000000; */
/* 	long t_duration_us   = t_time_rest/1000 ;			   t_time_rest = t_time_rest%1000; */
/* 	long t_duration_ns   = t_time_rest ; */
/* 	printf("Trial partitioning = (%lld,%ld,%ld,%ld),",t_duration_s, t_duration_ms, t_duration_us, t_duration_ns); */

	long unsigned AggregateCommitNum =00, AggregateAbortNum  = 0;
	double TxCommitRate, TxAbortRate  ;
	double execution_duration_s = 0;


	 #ifdef STATISTICS_TEST
	   unsigned AggregateUnfinishedTxNum = 0;
	 #endif

	unsigned long GlobalMaxRetryNum=0;
	unsigned ThreadNo;
	for(ThreadNo=0; ThreadNo< ThreadDefNum; ThreadNo++) {
		struct timeval start_time = ThreadDefArray[ThreadNo].start_time;
		struct timeval   end_time = ThreadDefArray[ThreadNo].end_time;

		long long duration = (end_time.tv_sec * 1000000 + end_time.tv_usec) - (start_time.tv_sec * 1000000 + start_time.tv_usec) ;
	//		long long duration = 987654 + 1000000*ThreadNo;
		long time_rest;
		long duration_s	= (long)(duration/1000000) ;  time_rest = (long)(duration%1000000);
		long duration_ms   = time_rest/1000 ;			time_rest = time_rest%1000;
		long duration_us   = time_rest ;
		long total_duration_ms = duration_s*1000 + duration_ms;
		double total_duration_s = duration_s + (double)((double)(duration_ms)/(double)(1000));

		unsigned long CommitSum=0, AbortSum =0;
		unsigned ThreadMaxRetries = 0;
		unsigned CurrentTxID;
		for(CurrentTxID=0; CurrentTxID< ThreadDefArray[ThreadNo].TxDefNum ; CurrentTxID++) {
			bool CurrentTxIsFoundInThread = FALSE;
			unsigned ContainerNo, ContainerNum = ThreadDefArray[ThreadNo].TxContainerNum ;
			for(ContainerNo=0; ContainerNo< ContainerNum; ContainerNo++) {
				TxContainer_t* CurrentTxContainer = &(ThreadDefArray[ThreadNo].TxContainerList[ContainerNo]);
				unsigned CurrentCandidateNum = CurrentTxContainer -> CandidateTxNum;
				unsigned CandidateNo;
				for(CandidateNo=0; CandidateNo< CurrentCandidateNum ; CandidateNo++) {
					CurrentTxIsFoundInThread = ( CurrentTxID == CurrentTxContainer -> TxCandidateList[CandidateNo].TxID );
					if( CurrentTxIsFoundInThread )
						break;
				}
				if( CurrentTxIsFoundInThread )
					break;
			}
			if( CurrentTxIsFoundInThread ) {
				TxInfo_t* CurrentTx = &(ThreadDefArray[ThreadNo].TxDefArray[CurrentTxID]);

				CommitSum = CommitSum + CurrentTx -> CommitNum;
				AbortSum  = AbortSum  + CurrentTx -> AbortNum;
				if( ThreadMaxRetries <  CurrentTx -> MaxRetryNum )
					ThreadMaxRetries = CurrentTx -> MaxRetryNum;
	//			NaturalApplicationDelay += (CurrentTx -> CommitNum) * CurrentTx -> InherentDelay * DelayUnit;
			}
		}
		if( GlobalMaxRetryNum < ThreadMaxRetries)
			GlobalMaxRetryNum = ThreadMaxRetries;

		printf("Th[%u]: Cmmt= %ld, Abrt= %ld Duration=%ld.%ld.%ldns, %ldms, %.3fs\n", ThreadNo, CommitSum, AbortSum,duration_s,duration_ms,duration_us,total_duration_ms,total_duration_s);
		double CommitRate = (double) CommitSum / total_duration_s;
		double AbortRate  = (double) AbortSum / total_duration_s;
		printf("Th[%u]: Cmmt/s= %.3lf, Abrt/s= %.3lf, MaxRetries= %u\n", ThreadNo, CommitRate, AbortRate, ThreadMaxRetries);
		if (execution_duration_s < total_duration_s)
			execution_duration_s = total_duration_s;

		for(CurrentTxID=0; CurrentTxID< ThreadDefArray[ThreadNo].TxDefNum ; CurrentTxID++){
			bool CurrentTxIsFoundInThread = FALSE;
			unsigned ContainerNo, ContainerNum = ThreadDefArray[ThreadNo].TxContainerNum;
			for(ContainerNo=0; ContainerNo< ContainerNum; ContainerNo++){
				TxContainer_t* CurrentTxContainer = &(ThreadDefArray[ThreadNo].TxContainerList[ContainerNo]);

				unsigned CurrentCandidateNum = CurrentTxContainer -> CandidateTxNum;
				unsigned CandidateNo;
				for(CandidateNo=0; CandidateNo< CurrentCandidateNum ; CandidateNo++){
					CurrentTxIsFoundInThread = ( CurrentTxID == CurrentTxContainer -> TxCandidateList[CandidateNo].TxID );
					if( CurrentTxIsFoundInThread )
						break;
				}
				if( CurrentTxIsFoundInThread )
					break;
			}
			if( CurrentTxIsFoundInThread ) {
				TxInfo_t* CurrentTx = &(ThreadDefArray[ThreadNo].TxDefArray[CurrentTxID]);

				double TxCommitRate = (double)(CurrentTx -> CommitNum) / total_duration_s;
				double TxAbortRate  = (double)(CurrentTx -> AbortNum ) / total_duration_s;

				char* TxType[2];
				TxType[0] = dupstr("U");
				TxType[1] = dupstr("RO");
				printf("\t%s(%s): Cmmt=%ld, Abrt=%ld, Cmmt/s= %.3f, Abrt/s= %.3f, MaxRetries= %lu\n",CurrentTx -> Name, TxType[CurrentTx -> ReadOnly], CurrentTx -> CommitNum, CurrentTx -> AbortNum, TxCommitRate, TxAbortRate, CurrentTx -> MaxRetryNum);
		//		NaturalApplicationDelay += (CurrentTx -> CommitNum) * CurrentTx -> InherentDelay * DelayUnit;
			}
		}

		//	unsigned NaturalApplicationDelay = 0;

		printf("\n");

		//	printf("NaturalApplicationDelay= %u\n",NaturalApplicationDelay);
		//	assert(CommitSum == ThreadDefArray[ThreadNo].CommitNum);
		//	assert(AbortSum  == ThreadDefArray[ThreadNo].AbortNum );

		AggregateCommitNum = AggregateCommitNum + CommitSum  ;
		AggregateAbortNum  = AggregateAbortNum  + AbortSum  ;

		#ifdef STATISTICS_TEST
			AggregateUnfinishedTxNum += ThreadDefArray[ThreadNo].UnfinishedTxNum;
		#endif
	}

	printf("Aggregate Statistics:\n\n");

	TxCommitRate = (double)((double)(AggregateCommitNum)/execution_duration_s)	;
	TxAbortRate  = (double)((double)(AggregateAbortNum)/execution_duration_s)	;

		#ifdef STATISTICS_TEST
	printf("\tTotal Commit Num  = %lu\n"
	   "\tTotal Abort  Num  = %lu\n"
	   "\tUnfinishedTx Num  = %u\n"
	   "\tExection Duration = %lf\n"
	   "\tGlobal Commit/s   = %lf\n"
	   "\tGlobal Abort/s	= %lf\n"
	   "\tGlobal MaxRetries = %ld\n\n\n",\
	   AggregateCommitNum,   \
	   AggregateAbortNum,	\
	   AggregateUnfinishedTxNum, \
	   execution_duration_s, \
	   TxCommitRate,		 \
	   TxAbortRate,		  \
	   GlobalMaxRetryNum);
		#else
	printf("\tTotal Commit Num  = %lu\n"
	   "\tTotal Abort  Num  = %lu\n"
	   "\tExection Duration = %lf\n"
	   "\tGlobal Commit/s   = %lf\n"
	   "\tGlobal Abort/s	= %lf\n"
	   "\tGlobal MaxRetries = %ld\n\n\n",\
	   AggregateCommitNum,   \
	   AggregateAbortNum,	\
	   execution_duration_s, \
	   TxCommitRate,		 \
	   TxAbortRate,		  \
	   GlobalMaxRetryNum);
		#endif
}

void PrintEffectiveSimulationParameters() {
	// Printing the current values of the simulation parameters
	printf("\n-------------------------------------------------\n"
	   "	 Simulation Parameters:\n"
	   "-------------------------------------------------\n"
	   "\n"
	   "JustGenerateTrace	  : %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "SerialThreadExecution  : %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "WaitForTimeOut		 : %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "TransmitReadOnlyTxHint : %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "EnableTrace			: %d  (0: FALSE, 1: TRUE; DEFAULT:0)\n"
	   "PrintStats			 : %d  (0: FALSE, 1: TRUE; DEFAULT:1)\n"
	   "MainSeed			   : %u  (0: seed from clock; DEFAULT: 1)\n"
	   "TimeOut				: %u  (in microseconds, valid only if WaitForTimeOut is 1)\n"
	   "\n"
	   "\n",						\
	   JustGenerateTrace,					\
	   SerialThreadExecution,				\
	   WaitForTimeOut,					\
	   TransmitReadOnlyTxHint,				\
	   EnableTrace,						\
	   PrintStats,						\
	   MainSeed,						\
	   TimeOut						\
	);
}

void PrintDevelopperTestWarning() {
	printf("\n*************************************************************\n"
	   "*************************************************************\n"
	   "*						WARNING:						   *\n"
	   "*														   *\n"
	   "*														   *\n"
	   "*  THIS PROGRAM IS COMPILED TO RUN IN DEVELOPER TEST MODE.  *\n"
	   "*														   *\n"
	   "*  This mode has some missing/modified features. If you	 *\n"
	   "*  did not mean to execute developping tests to verify/test *\n"
	   "*  TMunit, please type									  *\n"
	   "*														   *\n"
	   "*	  make clean										   *\n"
	   "*	  make												 *\n"
	   "*														   *\n"
	   "* on the command line in order to compile for simulations   *\n"
	   "* (and user defined unit tests).							*\n"
	   "*														   *\n"
	   "*************************************************************\n"
	   "*************************************************************\n"
	);
}
