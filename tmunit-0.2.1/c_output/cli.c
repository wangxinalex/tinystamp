#include "cli.h"

int PrintHelpMessage() {
    printf("\n"
	   "--------------------------------------------------\n"
	   "  benchrun -- STM Unit Testing & Evaluation Tool  \n"
	   "           Generated C code executable            \n"
	   "--------------------------------------------------\n"
	   "\n"
	   "Usage:\n"
	   "  benchrun [options]\n"
	   "\n"
	   "Options:\n"
	   "  -d, --duration <int>\n"
	   "        Sets simulation duration (in microseconds)\n"
	   "  -h, --help\n"
	   "        Print this message\n"
	   "  -p, --print-stats <int>\n"
	   "        Enables/disables the printing of statistiscs\n"
           "        (0=disable, 1=enable)\n"
	   "  -s, --seed <int>\n"
	   "        Random Number Generator Seed (0=time-based, default=%d)\n"
	   "  -v, --verbose\n"
	   "        By enabling verbose output, a trace of transactional operations\n"
	   "        performed by all threads is printed on the standart output.\n"
	   "        The operations indicate the START and COMMITs of transactions\n"
	   "        as well as the transactional reads/writes together with the\n"
	   "        memory addresses accessed by those reads/writes and the values\n"
	   "        read/written by those transactional operations.\n"
	   "\n"
	   "        If you would like to generate a trace where the accessed\n"
	   "        address values of transactional reads/writes are replaced by\n"
	   "        the corresponding variables of the input configuration file,\n"
	   "        use 't_benchrun' (type './t_benchrun -h' to get help on\n"
	   "        't_benchrun')\n"
	   "\n"
	   "\n"
	   "NOTATION AND FORMAT OF TRACES\n"
	   "\n"
	   "   Each line of the trace corresponds to a transactional action\n"
	   "   of a transaction. The lines are prefixed with the name of the\n"
	   "   transaction in the  [ThreadName:TransactionName]  format. This\n"
	   "   is followed by the transactional operation that is executed.\n"
	   "   The possible transactional operation outputs are as follows:\n"
	   "\n"
	   "     - S\n"
	   "          Start/restart of a transaction.\n"
	   "     - R(Addr)\n"
	   "          The beginning of an TM READ on address 'Addr'.\n"
	   "     - R(Addr,Val)\n"
	   "          The end of an TM READ on address 'Addr'. The value\n"
	   "          returned by the TM READ appears on the 'Val' field.\n"
	   "     - W(Addr)\n"
	   "          The beginning of an TM WRITE on address 'Addr'.\n"
	   "     - W(Addr,Val)\n"
	   "          The end of an TM WRITE on address 'Addr'. The value\n"
	   "          stored by the TM WRITE appears on the 'Val' field.\n"
	   "     - Try C\n"
	   "          The beginning of a TM COMMIT operation.\n"
	   "     - C\n"
	   "          The end of a TM COMMIT operation.\n"
	   "\n"
	   "\n"
	   ,DEFAULT_SEED);
       return 0;
}

int PrintHowToGetHelp() {
    char* Message= malloc(sizeof(char)*100);
    sprintf(Message,"\nTo get help type: \n\tbenchrun  -h \n");
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
		{"duration",                  required_argument, NULL, 'd'},
		{"print-stats",               required_argument, NULL, 'p'},
		{"seed",                      required_argument, NULL, 's'},
		{"verbose",                   no_argument,       NULL, 'v'},
		{NULL, 0, NULL, 0}
	};

	int i,c,duration,seed;
	int ObligatoryArgumentStartPos;
	bool OptArgIsBoolean ;
	bool OptArgIsZero;
	bool OptArgIsOne ;

	while(1) {
		i = 0;
		c = getopt_long(argc, argv, "hd:p:s:v", long_options, &i);

		if(c == -1) {
			break;
		}

		if(c == 0 && long_options[i].flag == 0)
			c = long_options[i].val;

		switch(c) {
			case 0:
				/* Flag is automatically set */
				break;
			case 'h':
				PrintHelpMessage();
				exit(0);
			case 'd':
				duration = atoi(optarg);
				if( duration == 0){
					bool optargIsZeroString = (strcmp(optarg,"0") == 0);
					if( !optargIsZeroString ){
						// If we are here it means that a string which does not correspond to an integer value is encountered
						printf("benchrun: Unexpected string '%s'.\n"
								"          Expecting integer argument for -d (--duration) option instead.\n",optarg);
						PrintHowToGetHelp();
						exit(1);
					}
				}

				WaitForTimeOut = TRUE;
				TimeOut = duration;
				break;

			case 'p':
				OptArgIsBoolean = FALSE;
				OptArgIsZero = (strcmp(optarg,"0") == 0);
				OptArgIsOne  = (strcmp(optarg,"1") == 0);
				OptArgIsBoolean = (OptArgIsZero | OptArgIsOne);

				if ( OptArgIsBoolean )
					PrintStats=(bool)atoi(optarg);
				else {
					printf("benchrun: Unexpected string '%s'.\n"
							"          Expecting 0 or 1 as argument for -p (--print-stat) option instead.\n",optarg);
					PrintHowToGetHelp();
					exit(1);
				}
				break;

			case 's':
				seed = atoi(optarg);
				if( seed == 0) {
					bool optargIsZeroString = (strcmp(optarg,"0") == 0);
					if( !optargIsZeroString ){
						// If we are here it means that a string which does not correspond to an integer value is encountered
						printf("benchrun: Unexpected string '%s'.\n"
								"          Expecting integer argument for -s (--seed) option instead.\n",optarg);
						PrintHowToGetHelp();
						exit(1);
					}
				}
				MainSeed=seed;
				break;

			case 'v':
				EnableTrace=TRUE;
				break;
			case '?':
				PrintHowToGetHelp();
				exit(1);
			default:
				exit(1);
		}
	}

	return 0;
}
