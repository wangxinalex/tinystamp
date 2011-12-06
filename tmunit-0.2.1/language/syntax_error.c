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

#include "syntax_error.h"


/*!  \fn  int yyerror(char* ErrorMessage)
     \brief   Function that prints out an error message together with its position
     \todo    If the current printed line does not have a new line the position indicator fails to show the correct position
     \todo    If the current printed line is empty no error is reported
  */
int yyerror(char* ErrorMessage)
{
    // Printing the error and its cause
    printf("\nERROR: %s\n",ErrorMessage);

    // Printing the line number of the error
    char PrefixString[100];
    sprintf(PrefixString,"      @ line %d: ",yylineno);
    printf("%s",PrefixString);
    fflush(NULL);

    // Printing the line where the error occurs 
    char LinePrintingCommand[1000];
    sprintf(LinePrintingCommand,"sed -n '%dp' %s",yylineno, PreprocessedFileName); 
    system(LinePrintingCommand);
    
    // On the next line, printing an indicator to the coloumn where the error occurs
    int ErrorPositionPointerPos = strlen(PrefixString) + (int)TokenPosition - yyleng +1  ;    
    printf("%*s\n",ErrorPositionPointerPos,"^");

    return 0;
}

