#ifndef ____USER_INTERFACE_CONSOLE____
#define ____USER_INTERFACE_CONSOLE____

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simulation_parameters.h"
#include <getopt.h>     // For ProcessCommandLineArguments function
#define DEFAULT_DURATION                1000000
#define DEFAULT_SEED                    1


int PrintHelpMessage();
int PrintHowToGetHelp();
int ProcessCommandLineArguments(int argc, char*  argv[]);




#endif
