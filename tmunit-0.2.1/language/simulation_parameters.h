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

#ifndef ____SIMULATION_PARAMETERS___
#define ____SIMULATION_PARAMETERS___

#include "general.h"

extern unsigned MainSeed;
extern unsigned MainMax;
extern bool JustGenerateTrace;
extern bool EnableTrace;
extern bool SerialThreadExecution;
extern bool ReadConfigOnly;
extern bool ParseOnly;
extern bool PrintStats;
extern unsigned DelayUnit;
extern unsigned TimeOut;
extern bool WaitForTimeOut;
extern bool TimeOutValueSet;
extern bool TransmitReadOnlyTxHint;

extern bool VerboseParserOutput;
extern bool EnableTraceFromCommandLine;
extern bool DurationSetInCommandLine;
extern bool SeedSetInCommandLine;
extern bool MaxSetInCommandLine;
extern unsigned CommandLineDuration;
extern unsigned CommandLineSeed;
extern unsigned CommandLineMax;

extern bool RandomDebug;

extern bool ExecuteSchedule;
extern bool NoAbortInSchedule;

extern bool VarExprTestEnabled;

extern bool Generate_C_output;
#endif
