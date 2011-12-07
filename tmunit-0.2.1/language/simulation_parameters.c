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

#include "simulation_parameters.h"


unsigned MainSeed;
bool JustGenerateTrace;
bool EnableTrace;
bool SerialThreadExecution;
bool ReadConfigOnly;
bool ParseOnly;
bool PrintStats;
unsigned DelayUnit;
unsigned TimeOut;
bool WaitForTimeOut;
bool TimeOutValueSet;
bool TransmitReadOnlyTxHint; 

bool VerboseParserOutput;
bool EnableTraceFromCommandLine;
bool DurationSetInCommandLine;
bool SeedSetInCommandLine;
unsigned CommandLineDuration;
unsigned CommandLineSeed;


bool RandomDebug;

bool ExecuteSchedule;
bool NoAbortInSchedule;

bool VarExprTestEnabled;

bool Generate_C_output;