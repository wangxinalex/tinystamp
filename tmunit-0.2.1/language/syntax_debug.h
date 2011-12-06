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

#ifndef __SYNTAX_DEBUG_____
#define __SYNTAX_DEBUG_____

#include <stdlib.h>
#include <stdio.h>
#include "grammar.h"

#define MAX_RETURN_STRING_SIZE  1000

#define REPORT_READ_INPUT(...)   if(VerboseParserOutput)              \
                                 {                                    \
                                    printf(__VA_ARGS__); fflush(NULL);\
				 }
   
#define ALLOC_AND_RETURN_STRING(...)  char *TempString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE); \
	                              sprintf(TempString,__VA_ARGS__);	\
 				      (yyval.string)=TempString
#define FREE_RULE_STRINGS( StringNumToFree )
/* #define FREE_RULE_STRINGS( StringNumToFree ) unsigned StringNo; \ */
/*                                       for(StringNo=1; StringNo <= StringNumToFree; StringNo++) \ */
/* 	                              {                                                         \ */
/* 					  printf("StringNo=%u, StringNumToFree=%u\n",StringNo,StringNumToFree); \ */
/* 					  printf("yyvsp[(%u)-(%u)].string= ",StringNo,StringNumToFree); fflush(NULL); \ */
/* 					  printf("%p\n",yyvsp[(StringNo)-(StringNumToFree)].string); \ */
/* 				      }				 	                        */
/* //					  free( yyvsp[(StringNo)-(StringNumToFree)].string);  */
/* void free_rule_strings(YYSTYPE* yyvsp, unsigned StringNumToFree); */

#endif
