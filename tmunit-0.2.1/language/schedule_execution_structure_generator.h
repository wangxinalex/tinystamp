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

#ifndef ____SCHEDULE_EXECUTION_STRUCTURE_GENERATOR_H___
#define ____SCHEDULE_EXECUTION_STRUCTURE_GENERATOR_H___

#include "dynamic_array.h"
#include "tx_op_container.h"

extern dyn_arr_t Dyn_ScheduleThreadDefArray;
extern unsigned  ScheduleThreadNum;

extern dyn_arr_t Dyn_Schedule;

extern dyn_arr_t Dyn_ScheduleList;
extern unsigned  ScheduleNum;


typedef struct ScheduleElement_struct
{
    bool Assertion;
    unsigned ThreadID,
	     TxID,
   	     LabelTxOpContainerNo,
	     AssertionExprID;
    var_assign_t* VarAssignList;
    unsigned VarAssignNum;
} ScheduleElement;


typedef struct Schedule_struct
{
    char* Name;
    unsigned ScheduleLength;
    ScheduleElement* Schedule;
} Schedule;


extern char*    SelectedScheduleName;
extern unsigned SelectedScheduleNo;

#define INVALID_SCHEDULE_NO  (unsigned) -1

#endif
