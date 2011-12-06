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

#ifndef __SEMANTIC_ERROR_____
#define __SEMANTIC_ERROR_____

#include <stdlib.h>
#include <stdio.h>
#include "syntax_error.h"


#define REPORT_SEMANTIC_ERROR(...)   char ErrorMessage[1000]; \
                                     sprintf(ErrorMessage,__VA_ARGS__); \
                                     yyerror(ErrorMessage); 		\
				     exit(1)                      

#endif 
