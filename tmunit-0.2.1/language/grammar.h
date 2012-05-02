/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
/* Tokens.  */
#define SEMICOLON 258
#define EOF_TOKEN 259
#define PROPERTIES_HEADER 260
#define DEFINITIONS_HEADER 261
#define TRANSACTIONS_HEADER 262
#define THREADS_HEADER 263
#define SCHEDULES_HEADER 264
#define INVARIANTS_HEADER 265
#define VALUE_ASSIGN 266
#define DEFINITION_ASSIGN 267
#define READ_ACCESS_OP 268
#define WRITE_ACCESS_OP 269
#define DELAY_OP 270
#define ABORT_OP 271
#define MEM_ALLOC_OP 272
#define MEM_FREE_OP 273
#define MEM_BARRIER_OP 274
#define JUMP_OP 275
#define OPEN_BRACKETS 276
#define CLOSE_BRACKETS 277
#define OPEN_PARANTHESES 278
#define CLOSE_PARANTHESES 279
#define COMMA 280
#define BAR 281
#define OPEN_CURLY_BRACKETS 282
#define CLOSE_CURLY_BRACKETS 283
#define LOOP_START 284
#define CONDITION_START 285
#define RANGE_SEPERATOR 286
#define LABEL 287
#define NAME 288
#define ARRAY_NAME 289
#define NAME_ALL_CAPITALS 290
#define LOCAL_VARIABLE_NAME 291
#define LOCAL_ARRAY_NAME 292
#define NUMBER 293
#define FLOAT_NUMBER 294
#define COLON 295
#define PERCENTAGE 296
#define NO_ABORT_INVARIANT_TOKEN 297
#define EQUAL 298
#define NOT_EQUAL 299
#define GREATER_EQUAL 300
#define SMALLER_EQUAL 301
#define GREATER_THAN 302
#define SMALLER_THAN 303
#define VAR_EXPR_TEST_SECT_HEADER 304
#define VAR_EXPR_EVAL 305
#define PLUS 306
#define MINUS 307
#define DIVIDE 308
#define MULTIPLY 309
#define OR 310
#define AND 311
#define NOT 312




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 116 "bison_grammar.y"
{
   char*     string;
   struct TxBlockListReturnStruct* TxBlockListReturn;
   struct EvaluatedVariableExpressionStruct* EvaluatedVarExpr;
   struct RangeInfoStruct*   RangeInfo;
   struct VariableExpressionStruct*   VarExprPtr;
   struct ConditionReturnStruct*  ConditionReturn;
   struct VariableReturnStruct*   VariableReturn;
}
/* Line 1489 of yacc.c.  */
#line 173 "grammar.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

