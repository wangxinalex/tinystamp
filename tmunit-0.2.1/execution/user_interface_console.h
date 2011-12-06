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

#ifndef ____USER_INTERFACE_CONSOLE____
#define ____USER_INTERFACE_CONSOLE____

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simulation_parameters.h"
#include <getopt.h>     // For ProcessCommandLineArguments function
#define DEFAULT_DURATION                10000000
#define DEFAULT_SEED                    1

#include "schedule_execution_structure_generator.h"  // for SelectedScheduleName variable
extern char*    SelectedScheduleName;


#include "general.h"       // for MAX_CONSOLE_MESSAGE_LENGHT constant
#include "dynamic_array.h" // for Dyn_ThreadDefConfigList

typedef struct ThreadDefConfigElementStruct
{
    char*    ThreadDefName;
    unsigned ReplicationNum;
} thread_def_config_t;


int PrintHelpMessage();
int PrintHowToGetHelp();
int ProcessCommandLineArguments(int argc, char*  argv[]);




#endif
