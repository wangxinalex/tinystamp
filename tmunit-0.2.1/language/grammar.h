/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SEMICOLON = 258,
     EOF_TOKEN = 259,
     PROPERTIES_HEADER = 260,
     DEFINITIONS_HEADER = 261,
     TRANSACTIONS_HEADER = 262,
     THREADS_HEADER = 263,
     SCHEDULES_HEADER = 264,
     INVARIANTS_HEADER = 265,
     VALUE_ASSIGN = 266,
     DEFINITION_ASSIGN = 267,
     READ_ACCESS_OP = 268,
     WRITE_ACCESS_OP = 269,
     DELAY_OP = 270,
     ABORT_OP = 271,
     MEM_ALLOC_OP = 272,
     MEM_FREE_OP = 273,
     MEM_BARRIER_OP = 274,
     JUMP_OP = 275,
     OPEN_BRACKETS = 276,
     CLOSE_BRACKETS = 277,
     OPEN_PARANTHESES = 278,
     CLOSE_PARANTHESES = 279,
     COMMA = 280,
     BAR = 281,
     OPEN_CURLY_BRACKETS = 282,
     CLOSE_CURLY_BRACKETS = 283,
     LOOP_START = 284,
     CONDITION_START = 285,
     RANGE_SEPERATOR = 286,
     LABEL = 287,
     NAME = 288,
     ARRAY_NAME = 289,
     NAME_ALL_CAPITALS = 290,
     LOCAL_VARIABLE_NAME = 291,
     LOCAL_ARRAY_NAME = 292,
     NUMBER = 293,
     FLOAT_NUMBER = 294,
     COLON = 295,
     PERCENTAGE = 296,
     NO_ABORT_INVARIANT_TOKEN = 297,
     EQUAL = 298,
     NOT_EQUAL = 299,
     GREATER_EQUAL = 300,
     SMALLER_EQUAL = 301,
     GREATER_THAN = 302,
     SMALLER_THAN = 303,
     VAR_EXPR_TEST_SECT_HEADER = 304,
     VAR_EXPR_EVAL = 305,
     PLUS = 306,
     MINUS = 307,
     DIVIDE = 308,
     MULTIPLY = 309,
     OR = 310,
     AND = 311,
     NOT = 312
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 116 "bison_grammar.y"

   char*     string;
   struct TxBlockListReturnStruct* TxBlockListReturn;
   struct EvaluatedVariableExpressionStruct* EvaluatedVarExpr;
   struct RangeInfoStruct*   RangeInfo;     
   struct VariableExpressionStruct*   VarExprPtr;
   struct ConditionReturnStruct*  ConditionReturn;
   struct VariableReturnStruct*   VariableReturn;



/* Line 1685 of yacc.c  */
#line 120 "grammar.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


