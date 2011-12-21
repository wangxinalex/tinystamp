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

#include "user_interface_console.h"

dyn_arr_t Dyn_ThreadDefConfigList;

int PrintHelpMessage()
{

    printf("\n"
	   "--------------------------------------------\n"
	   "tmunit -- STM Unit Testing & Evaluation Tool\n"
	   "--------------------------------------------\n"
	   "\n"
	   "Usage:\n"
	   "  tmunit [options] ConfigurationFileName\n"
	   "\n"
/* 	   "Attention:\n" */
/* 	   "  If none of the options below is given as the first argument, the first\n" */
/*            "  argument will be interpreted as the ConfigurationFileName and any\n" */
/* 	   "  argument following the first argument will be ignored.\n" */
/* 	   "\n" */
	   "Options:\n"
	   "  -d, --duration <int>\n"
	   "        Simulation duration in microseconds\n"
	   "  -g, --generate\n"
	   "        Generates a C file that corresponds to the input configuration file.\n"
	   "  -h, --help\n"
	   "        Print this message\n"
	   "  -s, --seed <int>\n"
	   "        Random Number Generator Seed (0=time-based, default=%d)\n"
	   "  -m, --max <int>\n"
	   "        Max amount of threads (if 0 it will be 10 :-) )\n"
	   "  -S, --schedule <string>\n"
	   "        Schedule to apply on the transactions and threads. The name of\n"
	   "        the given schedule should be defined in the Schedules section of\n"
	   "        configuration file.\n"
	   "  -t, --threads <ThreadConfigurationList>\n"
	   "        <ThreadConfigurationList> is a list of the format\n"
	   "\n"
           "               ThreadDefName:Num,ThreadDefName:Num,...\n"
	   "\n"
	   "        The list specifies how many threads should be created for each\n"
	   "        thread definition 'ThreadDefName'. The 'ThreadDefName's given in\n"
	   "        the list should appear as a definition in the configuration file.\n"
	   "        The list need not cover all the thread definitions declared in\n"
           "        configuration file. The list only effects the threads definitions\n"
	   "        appearing in the list, while for the remaining thread definitions\n"
	   "        only one thread will created (which is the default for a thread\n"
	   "        definition).\n"
	   "  -v, --verbose <string>\n"
	   "        <string> parameter is one of the following:\n"
	   "             parser\n"
	   "             trace\n"
	   "             all\n"
	   "        With 'parser' parameter, a verbose output of input file parsing \n"
           "        will be activated.\n"
	   "        With 'trace' parameter, the output of a trace of all the accesses\n"
	   "        performed by all threads on the standart output is activated.\n"
	   "        With 'all' parameter, both 'parser' and 'trace' parameters will be\n"
	   "        activated.\n"
	   "\n"
	   ,DEFAULT_SEED);

       return 0;
}

int PrintHowToGetHelp()
{
    char* Message= malloc(sizeof(char)*MAX_CONSOLE_MESSAGE_LENGHT);
    sprintf(Message,"\nTo get help type: \n\ttmunit  -h \n");
    fprintf(stderr,"%s",Message);
    free(Message);

    return 0;
}



// The  structure of  the  function is  the  courtesy of  Pascal Felber  (from
// tinySTM test/intset.c). The function is adapted to the needs of TMunit
int ProcessCommandLineArguments(int argc, char*  argv[]) {
	struct option long_options[] = {
		// These options don't set a flag
		{"help",                      no_argument,       NULL, 'h'},
		{"generate",                  no_argument,       NULL, 'g'},
		{"duration",                  required_argument, NULL, 'd'},
		{"threads",                   required_argument, NULL, 't'},
		{"seed",                      required_argument, NULL, 's'},
		{"max",                       required_argument, NULL, 'm'},
		{"schedule",                  required_argument, NULL, 'S'},
		{"verbose",                   required_argument, NULL, 'v'},
		{NULL, 0, NULL, 0}
	};

	int i,c,duration,seed,max;
	int ObligatoryArgumentStartPos;
	while(1) {
		i = 0;
		c = getopt_long(argc, argv, "hgd:t:s:m:S:v:", long_options, &i);

		if(c == -1) {
			ObligatoryArgumentStartPos = optind;
			break;
		}

	if(c == 0 && long_options[i].flag == 0)
		c = long_options[i].val;

    // Following declarations are for use in -t option
	char* ThreadDefinitionConfigList;
	char* intermediate_info;
    char* ElementPtr;
//    char* ElementString;
//    char* ElementParseIntermediateString;

	switch(c) {
		case 0:
			/* Flag is automatically set */
			break;
		case 'h':
			PrintHelpMessage();
			exit(0);
		case 'g':
			Generate_C_output = TRUE;
			break;
		case 'd':
			duration = atoi(optarg);
			if( duration == 0) {
				bool optargIsZeroString = (strcmp(optarg,"0") == 0);
				if( !optargIsZeroString) {
					// If we are here it means that a string which does not correspond to an integer value is encountered
					printf("tmunit: Unexpected string '%s'.\n"
							"        Expecting integer argument for -d (--duration) option instead.\n",optarg);
					PrintHowToGetHelp();
					exit(1);
				}
			}
			CommandLineDuration  = duration;
			DurationSetInCommandLine = TRUE;
			break;
		case 's':
			seed = atoi(optarg);
			if( seed == 0) {
				bool optargIsZeroString = (strcmp(optarg,"0") == 0);
				if( !optargIsZeroString ) {
					// If we are here it means that a string which does not correspond to an integer value is encountered
					printf("tmunit: Unexpected string '%s'.\n"
							"        Expecting integer argument for -s (--seed) option instead.\n",optarg);
					PrintHowToGetHelp();
					exit(1);
				}
			}
			CommandLineSeed = seed;
			SeedSetInCommandLine = TRUE;
			break;
		case 'm':
			max = atoi(optarg);
			if( max == 0) {
				bool optargIsZeroString = (strcmp(optarg,"0") == 0);
				if( !optargIsZeroString ) {
					// If we are here it means that a string which does not correspond to an integer value is encountered
					printf("tmunit: Unexpected string '%s'.\n"
							"        Expecting integer argument for -m (--max) option instead.\n",optarg);
					max=10;
				}
			}
			CommandLineMax = max;
			MaxSetInCommandLine= TRUE;
			break;
     case 'S':
	 ExecuteSchedule=TRUE;
	 SelectedScheduleName= dupstr(optarg);
       break;

     case 't':
	 ThreadDefinitionConfigList = dupstr(optarg);

	 Initialize_DynamicArray(&Dyn_ThreadDefConfigList);
	 // Traversing the elements of the ThreadDefinitionConfigList (which is comma seperated)
	 ElementPtr = strtok_r(ThreadDefinitionConfigList,",",&intermediate_info);
	 while(ElementPtr !=NULL)
	 {
	     // Current element is in ElementPtr

	     // HARMANCI DEBUG
	     //printf("\t%s\n",ElementPtr);
	     char* ElementString  = dupstr(ElementPtr);
	     char* ElementParseIntermediateString;
	     char* ThreadDefName = strtok_r(ElementString,":",&ElementParseIntermediateString);
	     if(ThreadDefName == NULL)
	     {
		 printf("Unexpected EMPTY Thread Configuration List Element '%s'\n"
		        "Format for the elements of this list is:\n"
		        "\n"
		        "\tThreadDefName:Number\n"
		        "\n"
			,ElementPtr);
		 PrintHowToGetHelp();
		 exit(1);
	     }
	     else
	     {
		 // HARMANCI DEBUG
		 // printf("\tThreadDefName:%s\n",ThreadDefName);

	     }
	     char* NumToGenerate = strtok_r(NULL,":",&ElementParseIntermediateString);
	     if(NumToGenerate == NULL)
             {
		 printf("Unexpected FORMAT for Thread Configuration List Element '%s'\n"
		        "Format for the elements of this list is:\n"
		        "\n"
		        "\tThreadDefName:Number\n"
		        "\n"
			,ElementPtr);
		 PrintHowToGetHelp();
		 exit(1);
	     }
	     else
	     {
		 // HARMANCI DEBUG
		 // printf("\tNumToGenerate:%d\n",atoi(NumToGenerate));

		 Extend_DynamicArray(&Dyn_ThreadDefConfigList,sizeof(thread_def_config_t));
		 unsigned LastElementPos = GetSize_DynamicArray(&Dyn_ThreadDefConfigList) - 1 ;
		 thread_def_config_t* CurrentElement = GetElement_DynamicArray(&Dyn_ThreadDefConfigList, LastElementPos, sizeof(thread_def_config_t));
		 CurrentElement ->  ThreadDefName  = dupstr(ThreadDefName);
		 CurrentElement ->  ReplicationNum = atoi(NumToGenerate);

	     }

	     free(ElementString);

	     // Getting the next element in ThreadDefinitionConfigList
	     ElementPtr = strtok_r(NULL,",",&intermediate_info);
	 }
	 free(ThreadDefinitionConfigList);

       break;
     case 'v':
	 if( strcmp(optarg,"parser") == 0 )
	     VerboseParserOutput = TRUE;
	 else if( strcmp(optarg,"trace") == 0 )
	     EnableTraceFromCommandLine=TRUE;
	 else if( strcmp(optarg,"all") == 0 )
	 {
	     VerboseParserOutput = TRUE;
	     EnableTraceFromCommandLine=TRUE;
	 }
	 else
	 {
	     printf("Unexpected parameter '%s' for -v option. Expecting 'parser', 'trace' or 'all' instead of '%s'\n",optarg, optarg);
	     PrintHowToGetHelp();
	     exit(1);
	 }
       break;
     case '?':
	 PrintHowToGetHelp();
	 exit(1);
     default:
       exit(1);
    }
  }


  if ( argv[ObligatoryArgumentStartPos] == NULL)
  {
      char* ErrorMessage= malloc(sizeof(char)*MAX_CONSOLE_MESSAGE_LENGHT);
      sprintf(ErrorMessage,"tmunit: No input configuration file is given as input.\n");
      fprintf(stderr,"%s",ErrorMessage);
      free(ErrorMessage);

      PrintHowToGetHelp();

      exit(1);
  }
  else
  {
/*       bool NoOptionalArgumentEntered = (ObligatoryArgumentStartPos == 1); */
/*       if( NoOptionalArgumentEntered ) */
/* 	  printf("No optional argument entered.\n");  */
      return ObligatoryArgumentStartPos;
  }

}
