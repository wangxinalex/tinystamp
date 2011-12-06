%{
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


#include "grammar.h"
#include "general.h"

#define RETURN_STR(T)   yylval.string = dupstr(yytext);  return  T
#define UPDATE_TOKEN_POS   TokenPosition += yyleng

unsigned TokenPosition=0;

%}

%option yylineno


SemiColon                      ";"
Whitespace	               [ \t]+
EndOfLine                      \n

PropertiesHeader               "Properties:" 
DefinitionsHeader              "Definitions:" 
TransactionsHeader             "Transactions:" 
ThreadsHeader                  "Threads:" 
SchedulesHeader                "Schedules:" 
InvariantsHeader               "Invariants:" 
VariableExprTestSectHeader     "TestedVariableExpressions:"

ValueAssign                    "="
DefinitionAssign               ":=" 

VarExprEval                    "EVAL"

Label                          "@"[a-zA-Z][a-zA-Z0-9_]*
LocalVariable                  "_"[a-zA-Z][a-zA-Z0-9_]*
LocalArray                     "_"[a-zA-Z][a-zA-Z0-9_]*"[" 
NameAllCapitals                [A-Z][A-Z0-9_]* 
Name                           [a-zA-Z][a-zA-Z0-9_]*
ArrayName                      [a-zA-Z][a-zA-Z0-9_]*"[" 
Number		               [0-9]+
Float_Number                   [0-9]+"."[0-9]+
Colon                          ":"
Percentage                     "%"

Plus                           "+"
Minus                          "-"
Multiply                       "*"
Divide                         "/" 
And                            "&&"
Or                             "||"
Not                            "!"


ReadAccessOp                   "R("
WriteAccessOp                  "W("
DlyOp                          "D("
AbortOp                        "A("
AllocMemoryOp                  "G("
FreeMemoryOp                   "F("
MemoryBarrierOp                "B("
JumpOp                         "J("
OpenParantheses                "("
CloseParantheses               ")"
OpenBrackets                   "["
CloseBrackets                  "]"
OpenCurlyBrackets              "{" 
CloseCurlyBrackets             "}"
LoopStart                      "{#"
ConditionStart                 "{?"
RangeSeperator                 ".."

Comma                          ","
Bar                            "|" 
Equals                         "=="
NotEqual                       "!="
GreaterEqual                   ">="
SmallerEqual                   "<="
GreaterThan                    ">"
SmallerThan                    "<"

NoAbortInvariant               "No-abort"


%%

{Whitespace}           { UPDATE_TOKEN_POS; } // { printf("Ignoring Whitespace\n"); }
{EndOfLine}            { TokenPosition=0; } // { printf("Ignoring Newline\n"); }

{PropertiesHeader}     { UPDATE_TOKEN_POS; RETURN_STR(PROPERTIES_HEADER  ); }   
{DefinitionsHeader}    { UPDATE_TOKEN_POS; RETURN_STR(DEFINITIONS_HEADER ); }  
{TransactionsHeader}   { UPDATE_TOKEN_POS; RETURN_STR(TRANSACTIONS_HEADER); } 
{ThreadsHeader}        { UPDATE_TOKEN_POS; RETURN_STR(THREADS_HEADER     ); }	   
{SchedulesHeader}      { UPDATE_TOKEN_POS; RETURN_STR(SCHEDULES_HEADER   ); } 
{InvariantsHeader}     { UPDATE_TOKEN_POS; RETURN_STR(INVARIANTS_HEADER  ); }
{VariableExprTestSectHeader}  { UPDATE_TOKEN_POS; RETURN_STR(VAR_EXPR_TEST_SECT_HEADER  ); }
			                  
{ValueAssign}          { UPDATE_TOKEN_POS; RETURN_STR(VALUE_ASSIGN       ); }
{DefinitionAssign}     { UPDATE_TOKEN_POS; RETURN_STR(DEFINITION_ASSIGN  ); }

{VarExprEval}          { UPDATE_TOKEN_POS; RETURN_STR(VAR_EXPR_EVAL      ); } 

			                  
{Label}                { UPDATE_TOKEN_POS; RETURN_STR(LABEL              ); } 
{LocalVariable}        { UPDATE_TOKEN_POS; RETURN_STR(LOCAL_VARIABLE_NAME); } 
{LocalArray}           { UPDATE_TOKEN_POS; RETURN_STR(LOCAL_ARRAY_NAME   ); } 
{NameAllCapitals}      { UPDATE_TOKEN_POS; RETURN_STR(NAME_ALL_CAPITALS  ); }
{Name}                 { UPDATE_TOKEN_POS; RETURN_STR(NAME               ); } 
{ArrayName}            { UPDATE_TOKEN_POS; RETURN_STR(ARRAY_NAME         ); }
{Number}               { UPDATE_TOKEN_POS; RETURN_STR(NUMBER             ); }
{Float_Number}         { UPDATE_TOKEN_POS; RETURN_STR(FLOAT_NUMBER       ); }
{Colon}                { UPDATE_TOKEN_POS; RETURN_STR(COLON              ); }
{Percentage}           { UPDATE_TOKEN_POS; RETURN_STR(PERCENTAGE         ); }


{Plus}                 { UPDATE_TOKEN_POS; RETURN_STR(PLUS    ); }      
{Minus}                { UPDATE_TOKEN_POS; RETURN_STR(MINUS   ); }      
{Multiply}             { UPDATE_TOKEN_POS; RETURN_STR(MULTIPLY); }      
{Divide}               { UPDATE_TOKEN_POS; RETURN_STR(DIVIDE  ); }       
{And}                  { UPDATE_TOKEN_POS; RETURN_STR(AND     ); }      
{Or}                   { UPDATE_TOKEN_POS; RETURN_STR(OR      ); }      
{Not}                  { UPDATE_TOKEN_POS; RETURN_STR(NOT     ); }      


{ReadAccessOp}         { UPDATE_TOKEN_POS; RETURN_STR(READ_ACCESS_OP   ); }         
{WriteAccessOp}        { UPDATE_TOKEN_POS; RETURN_STR(WRITE_ACCESS_OP  ); }         
{DlyOp}                { UPDATE_TOKEN_POS; RETURN_STR(DELAY_OP         ); }         
{AbortOp}              { UPDATE_TOKEN_POS; RETURN_STR(ABORT_OP         ); }         
{AllocMemoryOp}        { UPDATE_TOKEN_POS; RETURN_STR(MEM_ALLOC_OP     ); }         
{FreeMemoryOp}         { UPDATE_TOKEN_POS; RETURN_STR(MEM_FREE_OP      ); }         
{MemoryBarrierOp}      { UPDATE_TOKEN_POS; RETURN_STR(MEM_BARRIER_OP   ); }         
{JumpOp}               { UPDATE_TOKEN_POS; RETURN_STR(JUMP_OP          ); }         

{OpenParantheses}      { UPDATE_TOKEN_POS; RETURN_STR(OPEN_PARANTHESES   ); }
{CloseParantheses}     { UPDATE_TOKEN_POS; RETURN_STR(CLOSE_PARANTHESES  ); }
{OpenBrackets}         { UPDATE_TOKEN_POS; RETURN_STR(OPEN_BRACKETS      ); }
{CloseBrackets}        { UPDATE_TOKEN_POS; RETURN_STR(CLOSE_BRACKETS     ); }

{OpenCurlyBrackets}    { UPDATE_TOKEN_POS; RETURN_STR(OPEN_CURLY_BRACKETS  ); }          
{CloseCurlyBrackets}   { UPDATE_TOKEN_POS; RETURN_STR(CLOSE_CURLY_BRACKETS ); }          
{LoopStart}            { UPDATE_TOKEN_POS; RETURN_STR(LOOP_START           ); }          
{ConditionStart}       { UPDATE_TOKEN_POS; RETURN_STR(CONDITION_START      ); }          
{RangeSeperator}       { UPDATE_TOKEN_POS; RETURN_STR(RANGE_SEPERATOR      ); }           
{SemiColon}            { UPDATE_TOKEN_POS; RETURN_STR(SEMICOLON            ); }

{Comma}                { UPDATE_TOKEN_POS; RETURN_STR(COMMA         ); }        
{Bar}                  { UPDATE_TOKEN_POS; RETURN_STR(BAR           ); }           
{Equals}               { UPDATE_TOKEN_POS; RETURN_STR(EQUAL         ); }          
{NotEqual}             { UPDATE_TOKEN_POS; RETURN_STR(NOT_EQUAL     ); }          
{GreaterEqual}         { UPDATE_TOKEN_POS; RETURN_STR(GREATER_EQUAL ); }          
{SmallerEqual}         { UPDATE_TOKEN_POS; RETURN_STR(SMALLER_EQUAL ); }          
{GreaterThan}          { UPDATE_TOKEN_POS; RETURN_STR(GREATER_THAN  ); }          
{SmallerThan}          { UPDATE_TOKEN_POS; RETURN_STR(SMALLER_THAN  ); }          


{NoAbortInvariant}     { UPDATE_TOKEN_POS; RETURN_STR(NO_ABORT_INVARIANT_TOKEN); }          



%%

