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

#include "syntax_debug.h"

/* void free_rule_strings(YYSTYPE* yyvsp, unsigned StringNumToFree) */
/* { */
/*     unsigned StringNo;							 */
/*     for(StringNo=1; StringNo <= StringNumToFree; StringNo++)  */
/*     {                                                          */
/* 	printf("StringNo=%u, StringNumToFree=%u\n",StringNo,StringNumToFree);  */
/* 	printf("yyvsp[(%u)-(%u)].string= ",StringNo,StringNumToFree); fflush(NULL);  */
/* 	printf("%p\n",&(yyvsp[(StringNo)-(StringNumToFree)].string));  */
/*     }		  */
/* } */
