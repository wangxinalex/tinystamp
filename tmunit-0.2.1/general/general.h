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

#ifndef ___GENERAL_____
#define ___GENERAL_____

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __cplusplus
typedef enum {FALSE,TRUE} bool;
#else
#define TRUE true    
#define FALSE false    
#endif

#define MAX_CONSOLE_MESSAGE_LENGHT 1000

#define STR(s) #s
#define XSTR(s) STR(s)

char* dupstr(const char* InputString);
char* strext(char* ExtendedString, const char* AddedString);

void GenereateUnsignedListOutput(const unsigned* ListPtr, unsigned ListSize, char** OutputString);
void GenereateIntegerListOutput(int* ListPtr, unsigned ListSize, char** OutputString);


#endif  
