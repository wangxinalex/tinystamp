/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "bison_grammar.y"


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


#ifndef  __GRAMMAR_H__
#define  __GRAMMAR_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "syntax_error.h"
#include "syntax_debug.h"
#include "general.h"
#include "simulation_parameters.h"
#include "intermediate_representation.h"
#include "thread_execution_structure_generator.h"
#include "transaction_execution_structure_generator.h"
#include "schedule_execution_structure_generator.h"
#include "invariant_execution_structure_generator.h"  // For Invariant data structure
#include "variable_expression.h"
#include <ctype.h>  // for isupper function
#include "tm_interface.h" // for using TM functions in VarExprTestDefinitions


extern int yylex();
extern char* yytext;



unsigned TxDefElementNo;
unsigned TxOpNo;
unsigned TxBlockNo;
unsigned ScheduleNo;
unsigned InvariantNo;

struct TxBlockListReturnStruct
{
    bool BoundedRepetition;
    char* string;
};


struct ExpressionReturnStruct
{
    char* string;
    short int  Token;
    unsigned ExpressionType;
} ;

struct EvaluatedVariableExpressionStruct
{
    char* string;
    signed long  Value;
} ;

struct RangeInfoStruct
{
    char* string;
    unsigned long  MinValExpressionID;
    unsigned long  MaxValExpressionID;
    unsigned Increment;
} ;

struct ConditionReturnStruct
{
    char* string;
    unsigned ConditionTxOpContainerPos;
};

enum VariableTypeEnum
{
    SHARED,
    LOCAL,
    SHARED_CONSTANT,
    LOCAL_CONSTANT,
    SHARED_ARRAY,
    LOCAL_ARRAY,
    LOCAL_CONSTANT_ARRAY,
    SCOPED_LOCAL,
    SCOPED_LOCAL_CONSTANT,
    SCOPED_LOCAL_ARRAY,
    SCOPED_LOCAL_CONSTANT_ARRAY,
    VARIABLE_TYPE_NUM
};

struct VariableReturnStruct
{
    char* string;
    enum VariableTypeEnum VariableType;
};

#endif



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 187 of yacc.c.  */
#line 334 "grammar.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 347 "grammar.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   458

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  93
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNRULES -- Number of states.  */
#define YYNSTATES  370

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   312

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      20,    22,    26,    27,    30,    34,    38,    42,    46,    52,
      58,    62,    67,    72,    76,    77,    80,    84,    88,    92,
      93,    96,    99,   103,   107,   111,   115,   119,   123,   127,
     131,   136,   142,   148,   153,   159,   163,   164,   167,   171,
     176,   177,   179,   183,   185,   187,   189,   191,   193,   195,
     197,   201,   203,   205,   207,   209,   213,   219,   223,   229,
     233,   239,   243,   249,   256,   257,   259,   263,   267,   271,
     273,   277,   281,   286,   287,   290,   291,   295,   297,   299,
     303,   307,   312,   314,   318,   323,   325,   329,   334,   335,
     337,   341,   345,   349,   351,   353,   355,   357,   359,   361,
     363,   365,   367,   369,   371,   373,   375,   377,   379,   381,
     385,   389,   395,   397,   399,   401,   404,   406,   409,   413,
     417,   421,   425,   431,   437,   439,   441,   443,   445,   448,
     452,   454,   458,   460,   464,   466,   468,   470,   472,   476,
     477,   480,   484,   489,   490,   492,   496,   498,   502,   504,
     506,   508,   510,   514,   519,   524,   529,   535,   541,   544,
     549,   555,   556,   558,   562,   565,   567,   571,   575,   579,
     580,   583,   587,   591,   593,   597,   599,   602,   606,   608,
     612,   613,   616,   620,   624
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      59,     0,    -1,    60,    -1,    60,    59,    -1,    65,    -1,
      69,    -1,    75,    -1,   127,    -1,   141,    -1,   147,    -1,
      61,    -1,    49,    62,    63,    -1,    -1,    64,     3,    -1,
      63,    64,     3,    -1,    33,    11,   113,    -1,    36,    11,
     113,    -1,    73,    11,   112,    -1,    34,   124,    22,    11,
     112,    -1,    37,   124,    22,    11,   112,    -1,   114,    11,
     113,    -1,    50,    23,   124,    24,    -1,    50,    23,    99,
      24,    -1,     5,    66,    67,    -1,    -1,    68,     3,    -1,
      67,    68,     3,    -1,    33,    11,   113,    -1,     6,    70,
      71,    -1,    -1,    74,     3,    -1,    72,     3,    -1,    71,
      74,     3,    -1,    71,    72,     3,    -1,    73,    11,   112,
      -1,    34,   117,    22,    -1,    37,   117,    22,    -1,    36,
      11,   113,    -1,    33,    11,   112,    -1,   114,    11,   112,
      -1,   139,    36,    11,   112,    -1,    34,   124,    22,    11,
     112,    -1,    37,   124,    22,    11,   112,    -1,   139,   119,
      11,   112,    -1,    36,    11,    48,   117,    47,    -1,     7,
      76,    77,    -1,    -1,    78,     3,    -1,    77,    78,     3,
      -1,   115,    79,    12,    80,    -1,    -1,    81,    -1,    80,
      25,    81,    -1,    83,    -1,    88,    -1,    92,    -1,   104,
      -1,    32,    -1,   108,    -1,    82,    -1,    15,   124,    24,
      -1,    84,    -1,    85,    -1,    86,    -1,    87,    -1,    13,
     124,    24,    -1,    13,   124,    25,   124,    24,    -1,    14,
     124,    24,    -1,    14,   124,    25,   124,    24,    -1,    16,
     113,    24,    -1,    17,   124,    25,   124,    24,    -1,    18,
     124,    24,    -1,    19,    33,    25,    33,    24,    -1,    29,
      90,    89,    40,    80,    28,    -1,    -1,    98,    -1,   118,
      11,    91,    -1,    21,   117,    22,    -1,    30,    93,    28,
      -1,    94,    -1,    93,    26,    94,    -1,    93,    26,    96,
      -1,    98,    95,    40,    80,    -1,    -1,    97,    80,    -1,
      -1,    21,    99,    22,    -1,   100,    -1,   103,    -1,   124,
     109,   124,    -1,    23,   100,    24,    -1,   111,    23,   100,
      24,    -1,   101,    -1,    23,   103,    24,    -1,   111,    23,
     103,    24,    -1,   102,    -1,   102,   110,   102,    -1,    27,
     105,   106,    28,    -1,    -1,   107,    -1,   106,    25,   107,
      -1,   118,    11,   124,    -1,    20,    32,    24,    -1,    43,
      -1,    44,    -1,    48,    -1,    47,    -1,    46,    -1,    45,
      -1,    57,    -1,    56,    -1,    55,    -1,    57,    -1,   113,
      -1,   116,    -1,    38,    -1,    35,    -1,    33,    -1,    35,
      -1,    48,   117,    47,    -1,   124,    31,   124,    -1,   124,
      31,   124,     3,   124,    -1,    33,    -1,    36,    -1,   114,
      -1,   139,    36,    -1,   119,    -1,   139,   119,    -1,    34,
     124,    22,    -1,    37,   124,    22,    -1,    13,   124,    24,
      -1,    14,   124,    24,    -1,    13,   124,    25,   124,    24,
      -1,    14,   124,    25,   124,    24,    -1,   112,    -1,   118,
      -1,   120,    -1,   123,    -1,    52,   123,    -1,   122,   126,
     123,    -1,   121,    -1,    23,   124,    24,    -1,   122,    -1,
     124,   125,   122,    -1,    51,    -1,    52,    -1,    54,    -1,
      53,    -1,     8,   128,   129,    -1,    -1,   130,     3,    -1,
     129,   130,     3,    -1,   132,   131,    12,   133,    -1,    -1,
     115,    -1,   132,    25,   115,    -1,   134,    -1,   133,    25,
     134,    -1,   135,    -1,   136,    -1,   115,    -1,    82,    -1,
      48,   138,    47,    -1,    48,   138,    47,   113,    -1,    48,
     138,    47,   118,    -1,    23,   137,   133,    24,    -1,    23,
     137,   133,    24,   113,    -1,    23,   137,   133,    24,   124,
      -1,   115,    54,    -1,    48,   138,    47,    54,    -1,    23,
     137,   133,    24,    54,    -1,    -1,   140,    -1,   138,    26,
     140,    -1,   115,    40,    -1,   115,    -1,   139,   113,    41,
      -1,   139,    39,    41,    -1,     9,   142,   143,    -1,    -1,
     144,     3,    -1,   143,   144,     3,    -1,   115,    12,   145,
      -1,   146,    -1,   145,    25,   146,    -1,   115,    -1,   115,
      32,    -1,    21,    99,    22,    -1,   104,    -1,    10,   148,
     149,    -1,    -1,   150,     3,    -1,   149,   150,     3,    -1,
      21,    42,    22,    -1,    21,    99,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   184,   184,   185,   189,   189,   189,   190,   190,   190,
     190,   195,   203,   211,   212,   216,   222,   228,   243,   294,
     344,   382,   390,   407,   413,   421,   422,   426,   437,   443,
     452,   453,   454,   455,   460,   479,   539,   603,   644,   690,
     729,   734,   785,   835,   840,   915,   970,   987,   988,   992,
    1095,  1105,  1114,  1124,  1130,  1136,  1141,  1174,  1204,  1209,
    1217,  1225,  1225,  1225,  1225,  1229,  1259,  1289,  1318,  1351,
    1372,  1378,  1385,  1393,  1415,  1423,  1429,  1526,  1535,  1559,
    1564,  1569,  1578,  1606,  1622,  1626,  1631,  1673,  1678,  1685,
    1731,  1737,  1771,  1776,  1785,  1819,  1824,  1876,  1883,  1889,
    1895,  1905,  1992,  1999,  2005,  2012,  2019,  2026,  2032,  2038,
    2047,  2054,  2064,  2074,  2080,  2090,  2102,  2110,  2110,  2114,
    2122,  2143,  2153,  2169,  2206,  2222,  2255,  2261,  2294,  2359,
    2434,  2490,  2496,  2501,  2510,  2515,  2528,  2541,  2553,  2616,
    2666,  2678,  2695,  2731,  2818,  2824,  2833,  2840,  2851,  2858,
    2866,  2867,  2871,  2902,  2912,  2925,  2942,  2956,  2984,  2998,
    3016,  3031,  3048,  3063,  3080,  3088,  3106,  3131,  3174,  3192,
    3213,  3238,  3250,  3255,  3263,  3271,  3280,  3289,  3306,  3311,
    3320,  3321,  3325,  3346,  3351,  3360,  3388,  3439,  3474,  3498,
    3504,  3513,  3518,  3526,  3530
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "EOF_TOKEN",
  "PROPERTIES_HEADER", "DEFINITIONS_HEADER", "TRANSACTIONS_HEADER",
  "THREADS_HEADER", "SCHEDULES_HEADER", "INVARIANTS_HEADER",
  "VALUE_ASSIGN", "DEFINITION_ASSIGN", "READ_ACCESS_OP", "WRITE_ACCESS_OP",
  "DELAY_OP", "ABORT_OP", "MEM_ALLOC_OP", "MEM_FREE_OP", "MEM_BARRIER_OP",
  "JUMP_OP", "OPEN_BRACKETS", "CLOSE_BRACKETS", "OPEN_PARANTHESES",
  "CLOSE_PARANTHESES", "COMMA", "BAR", "OPEN_CURLY_BRACKETS",
  "CLOSE_CURLY_BRACKETS", "LOOP_START", "CONDITION_START",
  "RANGE_SEPERATOR", "LABEL", "NAME", "ARRAY_NAME", "NAME_ALL_CAPITALS",
  "LOCAL_VARIABLE_NAME", "LOCAL_ARRAY_NAME", "NUMBER", "FLOAT_NUMBER",
  "COLON", "PERCENTAGE", "NO_ABORT_INVARIANT_TOKEN", "EQUAL", "NOT_EQUAL",
  "GREATER_EQUAL", "SMALLER_EQUAL", "GREATER_THAN", "SMALLER_THAN",
  "VAR_EXPR_TEST_SECT_HEADER", "VAR_EXPR_EVAL", "PLUS", "MINUS", "DIVIDE",
  "MULTIPLY", "OR", "AND", "NOT", "$accept", "Config", "Section",
  "VarExprTestSection", "_varExprTestSectstart_act", "VarExprTestDefList",
  "VarExprTestDef", "PropertiesSection", "__prop_sec_act_1",
  "PropertyDefList", "PropertyDef", "DefinitionsSection",
  "__def_sec_act_1", "VariableDefList", "ArrayInit", "ArrayDef",
  "VariableDef", "TransactionsSection", "__tx_sec_act_1", "TxDefList",
  "TxDef", "__tx_sec_act_2", "TxSpec", "TxSpecElement", "Delay", "TxOp",
  "MemAccessOp", "AbortOp", "MemAllocOp", "MemBarrierOp", "TxLoopDef",
  "__txLoopDef_act_1", "LoopCondition", "LoopRange", "TxConditionalDef",
  "ConditionalTxSpec", "ConditionalTxSpecElement",
  "__conditionalTxSpecElement_act_1", "DefaulfConditionTxSpecElement",
  "__defaultCondTxSpecElement_act_1", "Condition", "ConditionalExpression",
  "SimpleConditionalExpression", "ComplexConditionalExpressionElement",
  "ComplexConditionalUnit", "ComplexConditionalExpression", "VarAssigns",
  "__varAssigns_act_1", "VarAssignList", "VarAssignment", "Jump",
  "RelationalOp", "BooleanOp", "UnaryBooleanOp", "Value", "FixedValue",
  "Constant", "DescriptionName", "RandomizedRange", "Range", "Variable",
  "ArrayAccess", "ManagedMemAccess", "VariableExpressionElement",
  "MultiplicativeVariableExpressionElementAccess", "MultiplicativeFactor",
  "VariableExpression", "AdditiveArithmeticOp",
  "MultiplicativeArithmeticOp", "ThreadsSection", "__th_sec_act_1",
  "ThreadDefList", "ThreadDef", "__threadDef_act_1", "ThreadType",
  "TxBlockList", "TxBlockListElement",
  "BoundedRepetitionTxBlockListElement",
  "UnboundedRepetitionTxBlockListElement", "__txBlockStart_act",
  "TxChoiceList", "Scope", "TxChoiceListElement", "SchedulesSection",
  "__sch_sec_act_1", "ScheduleDefList", "ScheduleDef", "ScheduleSpec",
  "TxPortion", "InvariantsSection", "__inv_sec_act_1", "InvariantDefList",
  "InvariantDef", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    61,    62,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    65,    66,    67,    67,    68,    69,    70,
      71,    71,    71,    71,    72,    73,    73,    74,    74,    74,
      74,    74,    74,    74,    74,    75,    76,    77,    77,    78,
      79,    80,    80,    81,    81,    81,    81,    81,    81,    81,
      82,    83,    83,    83,    83,    84,    84,    84,    84,    85,
      86,    86,    87,    88,    89,    90,    90,    91,    92,    93,
      93,    93,    94,    95,    96,    97,    98,    99,    99,   100,
     101,   101,   102,   102,   102,   103,   103,   104,   105,   106,
     106,   107,   108,   109,   109,   109,   109,   109,   109,   109,
     110,   110,   111,   112,   112,   113,   114,   115,   115,   116,
     117,   117,   118,   118,   118,   118,   118,   118,   119,   119,
     120,   120,   120,   120,   121,   121,   121,   122,   122,   122,
     123,   123,   124,   124,   125,   125,   126,   126,   127,   128,
     129,   129,   130,   131,   132,   132,   133,   133,   134,   134,
     135,   135,   135,   135,   135,   135,   135,   135,   136,   136,
     136,   137,   138,   138,   139,   140,   140,   140,   141,   142,
     143,   143,   144,   145,   145,   146,   146,   146,   146,   147,
     148,   149,   149,   150,   150
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     2,     3,     3,     3,     3,     5,     5,
       3,     4,     4,     3,     0,     2,     3,     3,     3,     0,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     5,     5,     4,     5,     3,     0,     2,     3,     4,
       0,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     3,     5,     3,     5,     3,
       5,     3,     5,     6,     0,     1,     3,     3,     3,     1,
       3,     3,     4,     0,     2,     0,     3,     1,     1,     3,
       3,     4,     1,     3,     4,     1,     3,     4,     0,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     5,     1,     1,     1,     2,     1,     2,     3,     3,
       3,     3,     5,     5,     1,     1,     1,     1,     2,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     3,     0,
       2,     3,     4,     0,     1,     3,     1,     3,     1,     1,
       1,     1,     3,     4,     4,     4,     5,     5,     2,     4,
       5,     0,     1,     3,     2,     1,     3,     3,     3,     0,
       2,     3,     3,     1,     3,     1,     2,     3,     1,     3,
       0,     2,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    24,    29,    46,   149,   179,   190,    12,     0,     2,
      10,     4,     5,     6,     7,     8,     9,     0,     0,     0,
       0,     0,     0,     0,     1,     3,     0,    23,     0,   117,
       0,   116,     0,     0,    28,     0,     0,     0,     0,     0,
       0,   117,   118,    45,     0,    50,   154,   148,     0,   153,
       0,   178,     0,     0,   189,     0,     0,     0,   116,     0,
       0,     0,    11,     0,     0,     0,     0,     0,    25,     0,
       0,     0,     0,   122,     0,   123,     0,   115,     0,     0,
     134,   113,   124,   114,     0,   135,   126,   136,   140,   142,
     137,     0,     0,     0,     0,     0,     0,     0,    31,     0,
      30,     0,   174,     0,     0,     0,    47,     0,     0,   150,
       0,     0,     0,     0,   180,     0,     0,   112,     0,    87,
      92,    95,    88,     0,     0,     0,   191,     0,     0,     0,
       0,     0,     0,    13,     0,     0,    27,    26,    38,     0,
       0,     0,     0,     0,     0,     0,   138,    35,   147,   146,
       0,     0,     0,   144,   145,     0,   125,   127,     0,    37,
      36,     0,    33,    32,    34,    39,     0,     0,    48,     0,
     151,   155,     0,     0,    98,   188,   185,   182,   183,   181,
       0,     0,     0,   193,   194,   111,   110,     0,     0,   103,
     104,   108,   107,   106,   105,   109,     0,   192,    15,     0,
      16,     0,     0,     0,    14,    17,    20,   130,     0,   131,
       0,   141,   128,   129,   119,   139,     0,   120,   143,     0,
       0,    40,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    57,    49,    51,    59,    53,    61,    62,
      63,    64,    54,    55,    56,    58,   171,     0,   161,   160,
     152,   156,   158,   159,     0,     0,   186,     0,    90,    93,
       0,    96,     0,     0,    89,     0,     0,    22,    21,     0,
       0,    41,     0,    44,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    74,    75,     0,     0,    79,    83,
       0,     0,   175,     0,     0,   172,   168,     0,   187,     0,
      99,     0,   184,    91,    94,    18,    19,   132,   133,   121,
      65,     0,    67,     0,    60,    69,     0,    71,     0,   102,
       0,     0,     0,    85,    78,     0,    52,     0,     0,   162,
       0,     0,   157,     0,    97,     0,     0,     0,     0,     0,
      86,     0,     0,    76,    80,    81,     0,     0,   165,   173,
     169,   163,   164,   177,   176,   100,   101,    66,    68,    70,
      72,     0,     0,    84,    82,   170,   113,   167,    73,    77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    23,    62,    63,    11,    17,    27,
      28,    12,    18,    34,    35,    36,    37,    13,    19,    43,
      44,   107,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   321,   284,   343,   243,   287,   288,   325,   345,   346,
     289,   118,   119,   120,   121,   122,   244,   255,   299,   300,
     245,   196,   187,   123,    80,    81,    82,    39,    83,    84,
      85,    86,    87,    88,    89,    90,   124,   155,   150,    14,
      20,    47,    48,   111,    49,   250,   251,   252,   253,   291,
     293,    92,   295,    15,    21,    51,    52,   177,   178,    16,
      22,    54,    55
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -322
static const yytype_int16 yypact[] =
{
      50,  -322,  -322,  -322,  -322,  -322,  -322,  -322,    19,    50,
    -322,  -322,  -322,  -322,  -322,  -322,  -322,     3,   362,    39,
      39,    39,     7,   287,  -322,  -322,    36,     3,    73,    70,
     121,    43,    76,   121,   362,    99,    97,   110,   106,   102,
     109,  -322,  -322,    39,   122,  -322,  -322,    39,   147,   138,
     153,    39,   164,   148,     7,   171,   166,   121,  -322,   168,
     121,   165,   287,   196,   190,   193,   175,   213,  -322,    -5,
     121,   121,   121,   181,   121,  -322,   121,  -322,   121,   220,
    -322,  -322,  -322,  -322,   207,  -322,  -322,  -322,  -322,   216,
    -322,    89,   155,    32,   210,   197,   241,   244,  -322,    -5,
    -322,    -5,  -322,   225,   248,   249,  -322,   253,   259,  -322,
      39,   270,    94,   281,  -322,   189,   303,  -322,   310,  -322,
    -322,   232,  -322,   316,   337,   335,  -322,   175,   209,   175,
     258,   189,   359,  -322,    -5,   175,  -322,  -322,  -322,   226,
     239,   124,    44,   101,   317,    53,  -322,  -322,  -322,  -322,
     220,   354,   121,  -322,  -322,   121,  -322,  -322,   121,  -322,
    -322,   355,  -322,  -322,  -322,  -322,    -5,    -5,  -322,   341,
    -322,  -322,    91,   189,  -322,  -322,   340,   349,  -322,  -322,
     343,   363,   163,  -322,  -322,  -322,  -322,     6,   189,  -322,
    -322,  -322,  -322,  -322,  -322,  -322,   121,  -322,  -322,   375,
    -322,   379,   368,   250,  -322,  -322,  -322,  -322,   121,  -322,
     121,  -322,  -322,  -322,  -322,  -322,    -5,    13,   216,   344,
      -5,  -322,  -322,   121,   121,   121,   175,   121,   121,   360,
     373,   342,   385,  -322,   382,  -322,  -322,  -322,  -322,  -322,
    -322,  -322,  -322,  -322,  -322,  -322,  -322,    39,  -322,   356,
     383,  -322,  -322,  -322,   387,   367,  -322,    94,  -322,  -322,
     189,  -322,   388,   389,   224,    -5,    -5,  -322,  -322,   215,
     282,  -322,   121,  -322,  -322,   275,   279,   284,   390,    85,
     289,   386,   391,   189,  -322,  -322,   405,   105,  -322,  -322,
     341,    91,   102,    -2,   233,  -322,  -322,    91,  -322,    24,
    -322,   406,  -322,  -322,  -322,  -322,  -322,  -322,  -322,   224,
    -322,   121,  -322,   121,  -322,  -322,   121,  -322,   392,  -322,
     396,   380,   398,   385,  -322,   381,  -322,   304,    39,   315,
     393,   394,  -322,   367,  -322,   121,   291,   293,   295,   399,
    -322,   341,   121,  -322,  -322,  -322,   341,   341,    55,  -322,
    -322,  -322,  -322,  -322,  -322,  -322,   224,  -322,  -322,  -322,
    -322,    69,   400,   382,   382,  -322,  -322,   224,  -322,  -322
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -322,   415,  -322,  -322,  -322,  -322,   364,  -322,  -322,  -322,
     401,  -322,  -322,  -322,   395,    -1,   397,  -322,  -322,  -322,
     384,  -322,  -321,   140,  -159,  -322,  -322,  -322,  -322,  -322,
    -322,  -322,  -322,  -322,  -322,  -322,   113,  -322,  -322,  -322,
     201,  -119,  -113,  -322,   246,  -111,  -106,  -322,  -322,   104,
    -322,  -322,  -322,  -322,   -48,   -56,     0,   -12,  -322,   -28,
    -217,   -25,  -322,  -322,   283,   -68,   -30,  -322,  -322,  -322,
    -322,  -322,   402,  -322,  -322,   149,   142,  -322,  -322,  -322,
    -322,   -17,   114,  -322,  -322,  -322,   403,  -322,   184,  -322,
    -322,  -322,   404
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -119
static const yytype_int16 yytable[] =
{
      91,    40,   180,    95,   181,    94,   175,    45,    46,    50,
     136,   146,   202,   248,   286,   104,   272,    40,    38,    24,
     361,   138,    64,    65,   328,   363,   364,   128,    53,   260,
     130,    45,    94,    77,    38,    46,    26,   159,   301,    50,
     139,   140,   141,    78,   142,   329,   143,    66,   145,   333,
     144,   164,   334,   165,   254,     1,     2,     3,     4,     5,
       6,    64,    65,   117,   153,   154,   212,   157,    70,    71,
      77,   198,    41,   200,    42,   262,    68,   263,    72,   206,
     158,    69,   215,  -118,   152,   182,   205,    93,    73,    74,
      31,    75,    76,    77,   290,   153,   154,   368,   171,     7,
     176,   203,    98,    78,   153,   154,   225,    79,    99,   365,
     316,   151,   352,   100,   246,   173,   301,   101,   221,   222,
     152,   174,   217,   213,    41,   106,    42,    41,   145,    42,
     219,   323,   248,   324,    70,    71,   153,   154,   248,   247,
     153,   154,   102,    74,    72,   103,    76,   180,   211,   181,
     109,   175,   153,   154,    73,    74,    31,    75,    76,    77,
     249,    70,    71,   110,   320,   112,   264,   114,   271,    78,
     278,   115,   274,    79,   126,   153,   154,   127,   269,   129,
     270,    73,    74,    31,    75,    76,    77,   211,   131,    74,
     116,   156,    76,   275,   276,   277,    78,   279,   280,   133,
      79,   134,    70,    71,   135,   117,   189,   190,   191,   192,
     193,   194,   115,    77,   153,   154,   137,   305,   306,   161,
     195,  -117,    73,    74,    31,    75,    76,    77,   152,   147,
     294,   199,   160,    70,    71,   292,   166,    78,   331,   307,
     152,    79,   309,    72,   162,   176,   117,   163,   153,   154,
     207,   208,   168,    73,    74,    31,    75,    76,    77,   167,
     153,   154,   170,   209,   210,   169,   153,   154,    78,   148,
     149,    77,   330,   351,   268,   153,   154,   153,   154,   249,
     201,   336,   172,   337,   179,   249,   338,   185,   186,   152,
     153,   154,   366,   189,   190,   191,   192,   193,   194,   310,
     311,   153,   154,   312,   313,   356,   308,   195,   314,   153,
     154,   294,   145,   317,   362,   357,   292,   358,   367,   359,
      56,    57,    58,    59,    60,   183,   153,   154,   348,   297,
     153,   154,   184,   153,   154,   153,   154,    61,   197,   188,
     153,   154,   153,   154,   153,   154,   153,   154,    73,    74,
      31,    75,    76,    77,   223,   224,   225,   226,   227,   228,
     229,   230,   204,   283,   214,   216,   220,   258,   174,   350,
     231,   232,   256,   233,   257,    73,    74,    31,    75,    76,
     189,   190,   191,   192,   193,   194,   265,   259,   153,   154,
     266,   273,   267,   281,   195,    29,    30,    31,    32,    33,
      73,    74,    31,    75,    76,   282,   283,   290,   297,   298,
     296,   318,   303,   304,   315,   319,   322,   335,   340,   342,
     341,   347,   369,   360,    25,   339,   132,   105,    67,    96,
     326,    97,   285,   261,   353,   354,   344,   355,   218,   332,
     327,   302,   349,     0,     0,     0,     0,     0,     0,   108,
       0,     0,     0,     0,   113,     0,     0,     0,   125
};

static const yytype_int16 yycheck[] =
{
      30,    18,   115,    33,   115,    33,   112,    19,    20,    21,
      66,    79,   131,   172,   231,    40,     3,    34,    18,     0,
     341,    69,    23,    23,    26,   346,   347,    57,    21,    23,
      60,    43,    60,    38,    34,    47,    33,    93,   255,    51,
      70,    71,    72,    48,    74,    47,    76,    11,    78,    25,
      78,    99,    28,   101,   173,     5,     6,     7,     8,     9,
      10,    62,    62,    57,    51,    52,    22,    92,    13,    14,
      38,   127,    33,   129,    35,   188,     3,   188,    23,   135,
      48,    11,   150,    40,    31,   115,   134,    11,    33,    34,
      35,    36,    37,    38,    25,    51,    52,    28,   110,    49,
     112,   131,     3,    48,    51,    52,    15,    52,    11,    54,
      25,    22,   329,     3,    23,    21,   333,    11,   166,   167,
      31,    27,   152,    22,    33,     3,    35,    33,   158,    35,
     158,    26,   291,    28,    13,    14,    51,    52,   297,    48,
      51,    52,    40,    34,    23,    36,    37,   260,    24,   260,
       3,   257,    51,    52,    33,    34,    35,    36,    37,    38,
     172,    13,    14,    25,   283,    12,   196,     3,   216,    48,
     226,    23,   220,    52,     3,    51,    52,    11,   208,    11,
     210,    33,    34,    35,    36,    37,    38,    24,    23,    34,
      42,    36,    37,   223,   224,   225,    48,   227,   228,     3,
      52,    11,    13,    14,    11,    57,    43,    44,    45,    46,
      47,    48,    23,    38,    51,    52,     3,   265,   266,    22,
      57,    40,    33,    34,    35,    36,    37,    38,    31,    22,
     247,    22,    22,    13,    14,   247,    11,    48,   294,    24,
      31,    52,   272,    23,     3,   257,    57,     3,    51,    52,
      24,    25,     3,    33,    34,    35,    36,    37,    38,    11,
      51,    52,     3,    24,    25,    12,    51,    52,    48,    53,
      54,    38,    39,   329,    24,    51,    52,    51,    52,   291,
      22,   311,    12,   313,     3,   297,   316,    55,    56,    31,
      51,    52,   348,    43,    44,    45,    46,    47,    48,    24,
      25,    51,    52,    24,    25,   335,    24,    57,    24,    51,
      52,   328,   342,    24,   342,    24,   328,    24,   348,    24,
      33,    34,    35,    36,    37,    22,    51,    52,    24,    25,
      51,    52,    22,    51,    52,    51,    52,    50,     3,    23,
      51,    52,    51,    52,    51,    52,    51,    52,    33,    34,
      35,    36,    37,    38,    13,    14,    15,    16,    17,    18,
      19,    20,     3,    21,    47,    11,    11,    24,    27,    54,
      29,    30,    32,    32,    25,    33,    34,    35,    36,    37,
      43,    44,    45,    46,    47,    48,    11,    24,    51,    52,
      11,    47,    24,    33,    57,    33,    34,    35,    36,    37,
      33,    34,    35,    36,    37,    32,    21,    25,    25,    22,
      54,    25,    24,    24,    24,    24,    11,    11,    22,    21,
      40,    40,    22,    24,     9,    33,    62,    43,    27,    34,
     290,    34,   231,   187,    41,    41,   323,   333,   155,   297,
     291,   257,   328,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     7,     8,     9,    10,    49,    59,    60,
      61,    65,    69,    75,   127,   141,   147,    66,    70,    76,
     128,   142,   148,    62,     0,    59,    33,    67,    68,    33,
      34,    35,    36,    37,    71,    72,    73,    74,   114,   115,
     139,    33,    35,    77,    78,   115,   115,   129,   130,   132,
     115,   143,   144,    21,   149,   150,    33,    34,    35,    36,
      37,    50,    63,    64,    73,   114,    11,    68,     3,    11,
      13,    14,    23,    33,    34,    36,    37,    38,    48,    52,
     112,   113,   114,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   139,    11,   117,   124,    72,    74,     3,    11,
       3,    11,    40,    36,   119,    78,     3,    79,   130,     3,
      25,   131,    12,   144,     3,    23,    42,    57,    99,   100,
     101,   102,   103,   111,   124,   150,     3,    11,   124,    11,
     124,    23,    64,     3,    11,    11,   113,     3,   112,   124,
     124,   124,   124,   124,   117,   124,   123,    22,    53,    54,
     126,    22,    31,    51,    52,   125,    36,   119,    48,   113,
      22,    22,     3,     3,   112,   112,    11,    11,     3,    12,
       3,   115,    12,    21,    27,   104,   115,   145,   146,     3,
     100,   103,   124,    22,    22,    55,    56,   110,    23,    43,
      44,    45,    46,    47,    48,    57,   109,     3,   113,    22,
     113,    22,    99,   124,     3,   112,   113,    24,    25,    24,
      25,    24,    22,    22,    47,   123,    11,   124,   122,   117,
      11,   112,   112,    13,    14,    15,    16,    17,    18,    19,
      20,    29,    30,    32,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    92,   104,   108,    23,    48,    82,   115,
     133,   134,   135,   136,    99,   105,    32,    25,    24,    24,
      23,   102,   100,   103,   124,    11,    11,    24,    24,   124,
     124,   112,     3,    47,   112,   124,   124,   124,   113,   124,
     124,    33,    32,    21,    90,    98,   118,    93,    94,    98,
      25,   137,   115,   138,   139,   140,    54,    25,    22,   106,
     107,   118,   146,    24,    24,   112,   112,    24,    24,   124,
      24,    25,    24,    25,    24,    24,    25,    24,    25,    24,
      99,    89,    11,    26,    28,    95,    81,   133,    26,    47,
      39,   113,   134,    25,    28,    11,   124,   124,   124,    33,
      22,    40,    21,    91,    94,    96,    97,    40,    24,   140,
      54,   113,   118,    41,    41,   107,   124,    24,    24,    24,
      24,    80,   117,    80,    80,    54,   113,   124,    28,    22
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 11:
#line 196 "bison_grammar.y"
    {
       TM_EXIT_THREAD(TxDesc);
       TM_EXIT(TxDesc);
   ;}
    break;

  case 12:
#line 203 "bison_grammar.y"
    {
	   VarExprTestEnabled = TRUE;
//	   Initialize_DynamicArray(&Dyn_VariableExpressionArray);
	   TM_INIT(TxDesc);
	   TM_INIT_THREAD(TxDesc);
      ;}
    break;

  case 15:
#line 217 "bison_grammar.y"
    {
	AddSharedVariableToVarExprList((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));

	FREE_RULE_STRINGS(3);
    ;}
    break;

  case 16:
#line 223 "bison_grammar.y"
    {
	AddLocalVariableToVarExprList((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));

	FREE_RULE_STRINGS(3);
    ;}
    break;

  case 17:
#line 230 "bison_grammar.y"
    {
	  VarExpr* ArrayVarExpr = (yyvsp[(1) - (3)].VarExprPtr);
	  int ArrayElementNum = (int) (ArrayVarExpr -> OperandID[1] - ArrayVarExpr -> OperandID[0] +1) ;
	  assert(ArrayElementNum > 0);

	  int  ElementNo;
	  for( ElementNo=0; ElementNo < ArrayElementNum; ElementNo ++)
	  {
	      ((Word*)(ArrayVarExpr -> Addr))[ElementNo] = atoi((yyvsp[(3) - (3)].string));
	  }

	  REPORT_READ_INPUT("'%s' is assigned to all elements of array '%s'\n",(yyvsp[(3) - (3)].string), ArrayVarExpr->Name);
      ;}
    break;

  case 18:
#line 244 "bison_grammar.y"
    {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr((yyvsp[(1) - (5)].string));
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';

	  // Checking array's existence
	  VarExpr* ArrayVarExpr;
	  FindVarExpr(ActualArrayName,&ArrayVarExpr);
	  bool ArrayExists = (ArrayVarExpr != NULL);
	  if( !ArrayExists)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Can NOT SET element of UNKNOWN ARRAY  '%s'. Terminating...\n", ActualArrayName);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  VarExpr* ElementVarExpr;
	  FindVarExpr((yyvsp[(2) - (5)].string),&ElementVarExpr);
	  if(ElementVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", (yyvsp[(2) - (5)].string));
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  signed long ElementNoToAccess = EvaluateVarExpr(ElementVarExpr);
	  unsigned ArrayLowerLimit = ArrayVarExpr -> OperandID[0];
	  unsigned ArrayUpperLimit = ArrayVarExpr -> OperandID[1];
	  if( ElementNoToAccess >  ArrayUpperLimit )
	  {
	      fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
	      assert(0);
	  }
	  else if(  ElementNoToAccess < ArrayLowerLimit)
	  {
	      fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
	      assert(0);
	  }
	  signed long ElementIndexToAccess = ElementNoToAccess - ArrayLowerLimit;

	  // The following can be done with an Evaluation on the managed version of ArrayVarExpr
	  ((Word*)(ArrayVarExpr -> Addr))[ElementIndexToAccess] = atoi((yyvsp[(5) - (5)].string));


    ;}
    break;

  case 19:
#line 295 "bison_grammar.y"
    {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr((yyvsp[(1) - (5)].string));
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';

	  // Checking array's existence
	  VarExpr* ArrayVarExpr;
	  FindVarExpr(ActualArrayName,&ArrayVarExpr);
	  bool ArrayExists = (ArrayVarExpr != NULL);
	  if( !ArrayExists)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Can NOT SET element of UNKNOWN ARRAY  '%s'. Terminating...\n", ActualArrayName);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  VarExpr* ElementVarExpr;
	  FindVarExpr((yyvsp[(2) - (5)].string),&ElementVarExpr);
	  if(ElementVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", (yyvsp[(2) - (5)].string));
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  signed long ElementNoToAccess = EvaluateVarExpr(ElementVarExpr);
	  unsigned ArrayLowerLimit = ArrayVarExpr -> OperandID[0];
	  unsigned ArrayUpperLimit = ArrayVarExpr -> OperandID[1];
	  if( ElementNoToAccess >  ArrayUpperLimit )
	  {
	      fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
	      assert(0);
	  }
	  else if(  ElementNoToAccess < ArrayLowerLimit)
	  {
	      fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
	      assert(0);
	  }
	  signed long ElementIndexToAccess = ElementNoToAccess - ArrayLowerLimit;

	  ((Word*)(ArrayVarExpr -> Addr))[ElementIndexToAccess] = atoi((yyvsp[(5) - (5)].string));


    ;}
    break;

  case 20:
#line 345 "bison_grammar.y"
    {
	void* SharedVarAddr = (void *)malloc(sizeof(Word));


	VarExpr* CurrentVarExpr;
	FindVarExpr((yyvsp[(1) - (3)].string),&CurrentVarExpr);
	bool LocalVariableAlreadyExist = (CurrentVarExpr != NULL);
	if( !LocalVariableAlreadyExist)
	{
	    Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	    unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	    CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	    VAR_EXPR_Initialize(CurrentVarExpr);
	    CurrentVarExpr -> Name = dupstr((yyvsp[(1) - (3)].string));
	    CurrentVarExpr -> Type = VAR_SHARED_CONSTANT_UNMANAGED;
	    CurrentVarExpr -> Addr = SharedVarAddr;

	    Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	    LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	    CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	    unsigned ManagedVersionNameLength = strlen("&") + strlen((yyvsp[(1) - (3)].string)) + 1 ;
	    char* ManagedVersionName = malloc(ManagedVersionNameLength*sizeof(char));
	    sprintf(ManagedVersionName,"&%s",(yyvsp[(1) - (3)].string));

	    VAR_EXPR_Initialize(CurrentVarExpr);
	    CurrentVarExpr -> Name = dupstr(ManagedVersionName);
	    CurrentVarExpr -> Type = VAR_SHARED_CONSTANT_MANAGED;
	    CurrentVarExpr -> Addr = SharedVarAddr;
	}
	*((Word*)(CurrentVarExpr -> Addr)) = (Word)atoi((yyvsp[(3) - (3)].string));
	if(VerboseParserOutput)
	    VAR_EXPR_Print(CurrentVarExpr);

	FREE_RULE_STRINGS(3);
    ;}
    break;

  case 21:
#line 383 "bison_grammar.y"
    {
       VarExpr* EvaluatedVarExpr;
       FindVarExpr((yyvsp[(3) - (4)].string), &EvaluatedVarExpr);
       assert(EvaluatedVarExpr != NULL);
       signed long AccessedVarExprValue = EvaluateVarExpr(EvaluatedVarExpr);
       printf("Value evaluated for '%s'= %ld\n", (yyvsp[(3) - (4)].string) , AccessedVarExprValue);
   ;}
    break;

  case 22:
#line 391 "bison_grammar.y"
    {
       VarExpr* EvaluatedVarExpr;
       FindVarExpr((yyvsp[(3) - (4)].string), &EvaluatedVarExpr);
       assert(EvaluatedVarExpr != NULL);

       START_TX(TxDesc,0);
       signed long AccessedVarExprValue = EvaluateVarExpr(EvaluatedVarExpr);
       printf("Value evaluated for '%s'= %ld\n", (yyvsp[(3) - (4)].string) , AccessedVarExprValue);
       COMMIT_TX(TxDesc);
   ;}
    break;

  case 23:
#line 408 "bison_grammar.y"
    {
   ;}
    break;

  case 24:
#line 413 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     PROPERTIES Section\n"
			     "-----------------------------------------------------------------------------\n" );
       ;}
    break;

  case 27:
#line 427 "bison_grammar.y"
    {
	 REPORT_READ_INPUT("'%s' is assigned to '%s'\n",(yyvsp[(3) - (3)].string),(yyvsp[(1) - (3)].string));
	 const char* ParameterName  = (yyvsp[(1) - (3)].string);
	 unsigned    ParameterValue = (unsigned)atoi((yyvsp[(3) - (3)].string));
	 CheckAndSetSimulationParameter(ParameterName,ParameterValue);
     ;}
    break;

  case 28:
#line 438 "bison_grammar.y"
    {
    ;}
    break;

  case 29:
#line 443 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     DEFINITIONS Section\n"
			     "-----------------------------------------------------------------------------\n" );
       ;}
    break;

  case 34:
#line 461 "bison_grammar.y"
    {
	  VarExpr* ArrayVarExpr = (yyvsp[(1) - (3)].VarExprPtr);
	  int ArrayElementNum = (int) (ArrayVarExpr -> OperandID[1] - ArrayVarExpr -> OperandID[0] +1) ;
	  assert(ArrayElementNum > 0);

	  int  ElementNo;
	  for( ElementNo=0; ElementNo < ArrayElementNum; ElementNo ++)
	  {
	      ((Word*)(ArrayVarExpr -> Addr))[ElementNo] = atoi((yyvsp[(3) - (3)].string));
	  }

	  REPORT_READ_INPUT("'%s' is assigned to all elements of array '%s'\n",(yyvsp[(3) - (3)].string), ArrayVarExpr->Name);
      ;}
    break;

  case 35:
#line 480 "bison_grammar.y"
    {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr((yyvsp[(1) - (3)].string));
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';

//	  ALLOC_AND_RETURN_STRING("%s",ActualArrayName);

	  REPORT_READ_INPUT("\tSHARED Array '%s' with elements in range: '%s'\n",ActualArrayName, (yyvsp[(2) - (3)].RangeInfo)->string);
	  FREE_RULE_STRINGS(3);

	  VarExpr* ArrayVarExpr;
	  FindVarExpr(ActualArrayName, &ArrayVarExpr);
	  if( ArrayVarExpr == NULL)
	  {
	      AllocVarExpr(ActualArrayName, &ArrayVarExpr );
	  }

	  // Are all characters capital letters?
	  unsigned CharNum = strlen(ActualArrayName);
	  unsigned CharNo;
	  bool IsAllCapitals = TRUE;
	  for(CharNo=0; CharNo< CharNum; CharNo++)
	  {
	      int ReturnVal = isupper((ArrayVarExpr -> Name)[CharNo]);
	      bool CharIsCapitalLetter = (ReturnVal > 0);
	      if( !CharIsCapitalLetter)
	      {
		  IsAllCapitals = FALSE;
		  break;
	      }
	  }
	  if(IsAllCapitals)
	      ArrayVarExpr -> Type = VAR_SHARED_ARRAY_CONSTANT;
	  else
	      ArrayVarExpr -> Type = VAR_SHARED_ARRAY;

	  VarExpr* ArrayLowerBoundVarExpr  = GetVarExprPtr((yyvsp[(2) - (3)].RangeInfo) -> MinValExpressionID);
	  assert( ArrayLowerBoundVarExpr != NULL);
	  VarExpr* ArrayUpperBoundVarExpr  = GetVarExprPtr((yyvsp[(2) - (3)].RangeInfo) -> MaxValExpressionID);
	  assert( ArrayUpperBoundVarExpr != NULL);



	  ArrayVarExpr -> OperandID[0] = EvaluateVarExpr(ArrayLowerBoundVarExpr);
	  ArrayVarExpr -> OperandID[1] = EvaluateVarExpr(ArrayUpperBoundVarExpr);

	  int ArrayElementNum = ArrayVarExpr -> OperandID[1] - ArrayVarExpr -> OperandID[0] +1 ;
	  assert(ArrayElementNum >0);  // Checks whether Min and Max limits were not reversed (if they are reversed or smth else goes wrong assertion stops the program)

	  unsigned long ArraySizeInMemory = ArrayElementNum * sizeof(Word);
	  ArrayVarExpr -> Addr = (void*) malloc(ArraySizeInMemory);
	  // Initialize the array with zeros
	  memset(ArrayVarExpr -> Addr, ArraySizeInMemory,0);

	  (yyval.VarExprPtr) = ArrayVarExpr;

	  free(ActualArrayName);
      ;}
    break;

  case 36:
#line 540 "bison_grammar.y"
    {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr((yyvsp[(1) - (3)].string));
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';

//	  ALLOC_AND_RETURN_STRING("%s",ActualArrayName);

	  REPORT_READ_INPUT("\tLOCAL Array '%s' with elements in range: '%s'\n",(yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].RangeInfo)->string);
	  FREE_RULE_STRINGS(3);

	  VarExpr* ArrayVarExpr;
	  FindVarExpr(ActualArrayName, &ArrayVarExpr);
	  if( ArrayVarExpr == NULL)
	  {
	      AllocVarExpr(ActualArrayName, &ArrayVarExpr );
	  }

	  // Are all characters capital letters?
	  unsigned CharNum = strlen(ActualArrayName);
	  unsigned CharNo;
	  bool IsAllCapitals = TRUE;
	  for(CharNo=0; CharNo< CharNum; CharNo++)
	  {
	      int ReturnVal = isupper((ArrayVarExpr -> Name)[CharNo]);
	      bool CharIsCapitalLetter = (ReturnVal > 0);
	      if( !CharIsCapitalLetter)
	      {
		  IsAllCapitals = FALSE;
		  break;
	      }
	  }
	  if(IsAllCapitals)
	      ArrayVarExpr -> Type = VAR_LOCAL_ARRAY_CONSTANT;
	  else
	      ArrayVarExpr -> Type = VAR_LOCAL_ARRAY;

	  VarExpr* ArrayLowerBoundVarExpr  = GetVarExprPtr((yyvsp[(2) - (3)].RangeInfo) -> MinValExpressionID);
	  assert( ArrayLowerBoundVarExpr != NULL);
	  VarExpr* ArrayUpperBoundVarExpr  = GetVarExprPtr((yyvsp[(2) - (3)].RangeInfo) -> MaxValExpressionID);
	  assert( ArrayUpperBoundVarExpr != NULL);



	  ArrayVarExpr -> OperandID[0] = EvaluateVarExpr(ArrayLowerBoundVarExpr);
	  ArrayVarExpr -> OperandID[1] = EvaluateVarExpr(ArrayUpperBoundVarExpr);

	  int ArrayElementNum = ArrayVarExpr -> OperandID[1] - ArrayVarExpr -> OperandID[0] +1 ;
	  assert(ArrayElementNum >0);  // Checks whether Min and Max limits were not reversed (if they are reversed or smth else goes wrong assertion stops the program)

	  unsigned long ArraySizeInMemory = ArrayElementNum * sizeof(Word);
	  ArrayVarExpr -> Addr = (void*) malloc(ArraySizeInMemory);
	  // Initialize the array with zeros
	  memset(ArrayVarExpr -> Addr, ArraySizeInMemory,0);

	  (yyval.VarExprPtr) = ArrayVarExpr;

	  free(ActualArrayName);
      ;}
    break;

  case 37:
#line 604 "bison_grammar.y"
    {
	VarExpr* CurrentVarExpr;
	FindVarExpr((yyvsp[(1) - (3)].string),&CurrentVarExpr);
	bool LocalVariableAlreadyExist = (CurrentVarExpr != NULL);
	if( !LocalVariableAlreadyExist)
	{
	    Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	    unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	    CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	    VAR_EXPR_Initialize(CurrentVarExpr);
	    CurrentVarExpr -> Name = dupstr((yyvsp[(1) - (3)].string));

	    // Are all characters (after the underscore) capital letters?
	    unsigned CharNum = strlen((yyvsp[(1) - (3)].string));
	    unsigned CharNo;
	    bool IsAllCapitals = TRUE;
	    for(CharNo=1; CharNo< CharNum; CharNo++)
	    {
		int ReturnVal = isupper((CurrentVarExpr -> Name)[CharNo]);
		bool CharIsCapitalLetter = (ReturnVal > 0);
		if( !CharIsCapitalLetter)
		{
		    IsAllCapitals = FALSE;
		    break;
		}
	    }
	    if(IsAllCapitals)
		CurrentVarExpr -> Type = VAR_LOCAL_SIMPLE_CONSTANT;
	    else
		CurrentVarExpr -> Type = VAR_LOCAL_SIMPLE;

	}
	CurrentVarExpr -> Value = (unsigned)atoi((yyvsp[(3) - (3)].string));
	if(VerboseParserOutput)
	    VAR_EXPR_Print(CurrentVarExpr);

	FREE_RULE_STRINGS(3);

    ;}
    break;

  case 38:
#line 645 "bison_grammar.y"
    {

	   VarExpr* CurrentVarExpr;
	   FindVarExpr((yyvsp[(1) - (3)].string),&CurrentVarExpr);
	   bool VariableAlreadyExist = (CurrentVarExpr != NULL);
	   if( !VariableAlreadyExist)
	   {
	       void* SharedVarAddr = (void *)malloc(sizeof(Word));

	       // Since we are generating a shared array expression we generate two copies, one for managed and one for unmanaged accesses.
	       // Creating Unmanaged copy
	       Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	       unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	       CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	       VAR_EXPR_Initialize(CurrentVarExpr);
	       CurrentVarExpr -> Name = dupstr((yyvsp[(1) - (3)].string));
	       CurrentVarExpr -> Type = VAR_SHARED_UNMANAGED;
	       CurrentVarExpr -> Addr = SharedVarAddr;
	       if(VerboseParserOutput)
		   VAR_EXPR_Print(CurrentVarExpr);

	       Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));

	       LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	       CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	       // Creating Managed copy
	       unsigned ManagedVersionNameLength = strlen("&") + strlen((yyvsp[(1) - (3)].string)) + 1 ;
	       char* ManagedVersionName = malloc(ManagedVersionNameLength*sizeof(char));
	       sprintf(ManagedVersionName,"&%s",(yyvsp[(1) - (3)].string));

	       VAR_EXPR_Initialize(CurrentVarExpr);
	       CurrentVarExpr -> Name = dupstr(ManagedVersionName);
	       CurrentVarExpr -> Type = VAR_SHARED_MANAGED;
	       CurrentVarExpr -> Addr = SharedVarAddr;

	   }
	   *((Word*)(CurrentVarExpr -> Addr)) = (Word)atoi((yyvsp[(3) - (3)].string));
	   if(VerboseParserOutput)
	       VAR_EXPR_Print(CurrentVarExpr);

	   REPORT_READ_INPUT("'%s' is assigned to '%s'\n", (yyvsp[(3) - (3)].string), (yyvsp[(1) - (3)].string));
	   FREE_RULE_STRINGS(3);
       ;}
    break;

  case 39:
#line 691 "bison_grammar.y"
    {
	   void* SharedVarAddr = (void *)malloc(sizeof(Word));


	   VarExpr* CurrentVarExpr;
	   FindVarExpr((yyvsp[(1) - (3)].string),&CurrentVarExpr);
	   bool LocalVariableAlreadyExist = (CurrentVarExpr != NULL);
	   if( !LocalVariableAlreadyExist)
	   {
	       Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	       unsigned LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	       CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	       VAR_EXPR_Initialize(CurrentVarExpr);
	       CurrentVarExpr -> Name = dupstr((yyvsp[(1) - (3)].string));
	       CurrentVarExpr -> Type = VAR_SHARED_CONSTANT_UNMANAGED;
	       CurrentVarExpr -> Addr = SharedVarAddr;

	       Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	       LastElementPos = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	       CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, LastElementPos, sizeof(VarExpr));

	       unsigned ManagedVersionNameLength = strlen("&") + strlen((yyvsp[(1) - (3)].string)) + 1 ;
	       char* ManagedVersionName = malloc(ManagedVersionNameLength*sizeof(char));
	       sprintf(ManagedVersionName,"&%s",(yyvsp[(1) - (3)].string));

	       VAR_EXPR_Initialize(CurrentVarExpr);
	       CurrentVarExpr -> Name = dupstr(ManagedVersionName);
	       CurrentVarExpr -> Type = VAR_SHARED_CONSTANT_MANAGED;
	       CurrentVarExpr -> Addr = SharedVarAddr;
	   }
	   *((Word*)(CurrentVarExpr -> Addr)) = (Word)atoi((yyvsp[(3) - (3)].string));
	   if(VerboseParserOutput)
	       VAR_EXPR_Print(CurrentVarExpr);

	   REPORT_READ_INPUT("'%s' is assigned to '%s'\n", (yyvsp[(3) - (3)].string), (yyvsp[(1) - (3)].string));
	   FREE_RULE_STRINGS(3);
       ;}
    break;

  case 40:
#line 730 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("'%s' is assigned to '%s:%s'\n", (yyvsp[(4) - (4)].string), (yyvsp[(1) - (4)].string),(yyvsp[(2) - (4)].string));
	   FREE_RULE_STRINGS(4);
       ;}
    break;

  case 41:
#line 735 "bison_grammar.y"
    {
	   // Chopping last character (character '[') of array name
	   char*    ActualArrayName = dupstr((yyvsp[(1) - (5)].string));
	   unsigned LastCharPos     = strlen(ActualArrayName)-1;
	   ActualArrayName[LastCharPos]='\0';

	   // Checking array's existence
	   VarExpr* ArrayVarExpr;
	   FindVarExpr(ActualArrayName,&ArrayVarExpr);
	   bool ArrayExists = (ArrayVarExpr != NULL);
	   if( !ArrayExists)
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT SET element of UNKNOWN ARRAY  '%s'. Terminating...\n", ActualArrayName);
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }

	   VarExpr* ElementVarExpr;
	   FindVarExpr((yyvsp[(2) - (5)].string),&ElementVarExpr);
	   if(ElementVarExpr == NULL)
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", (yyvsp[(2) - (5)].string));
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }

	   signed long ElementNoToAccess = EvaluateVarExpr(ElementVarExpr);
	   unsigned ArrayLowerLimit = ArrayVarExpr -> OperandID[0];
	   unsigned ArrayUpperLimit = ArrayVarExpr -> OperandID[1];
	   if( ElementNoToAccess >  ArrayUpperLimit )
	   {
	       fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
	       assert(0);
	   }
	   else if(  ElementNoToAccess < ArrayLowerLimit)
	   {
	       fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
	       assert(0);
	   }
	   signed long ElementIndexToAccess = ElementNoToAccess - ArrayLowerLimit;

	   // The following can be done with an Evaluation on the managed version of ArrayVarExpr
	   ((Word*)(ArrayVarExpr -> Addr))[ElementIndexToAccess] = atoi((yyvsp[(5) - (5)].string));


       ;}
    break;

  case 42:
#line 786 "bison_grammar.y"
    {
	   // Chopping last character (character '[') of array name
	   char*    ActualArrayName = dupstr((yyvsp[(1) - (5)].string));
	   unsigned LastCharPos     = strlen(ActualArrayName)-1;
	   ActualArrayName[LastCharPos]='\0';

	   // Checking array's existence
	   VarExpr* ArrayVarExpr;
	   FindVarExpr(ActualArrayName,&ArrayVarExpr);
	   bool ArrayExists = (ArrayVarExpr != NULL);
	   if( !ArrayExists)
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT SET element of UNKNOWN ARRAY  '%s'. Terminating...\n", ActualArrayName);
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }

	   VarExpr* ElementVarExpr;
	   FindVarExpr((yyvsp[(2) - (5)].string),&ElementVarExpr);
	   if(ElementVarExpr == NULL)
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", (yyvsp[(2) - (5)].string));
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }

	   signed long ElementNoToAccess = EvaluateVarExpr(ElementVarExpr);
	   unsigned ArrayLowerLimit = ArrayVarExpr -> OperandID[0];
	   unsigned ArrayUpperLimit = ArrayVarExpr -> OperandID[1];
	   if( ElementNoToAccess >  ArrayUpperLimit )
	   {
	       fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of UPPER BOUND. Terminating...\n");
	       assert(0);
	   }
	   else if(  ElementNoToAccess < ArrayLowerLimit)
	   {
	       fprintf(stderr,"ERROR: VAR_EXPR_Evaluate: Array Access out of LOWER BOUND. Terminating...\n");
	       assert(0);
	   }
	   signed long ElementIndexToAccess = ElementNoToAccess - ArrayLowerLimit;

	   ((Word*)(ArrayVarExpr -> Addr))[ElementIndexToAccess] = atoi((yyvsp[(5) - (5)].string));


       ;}
    break;

  case 43:
#line 836 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("'%s' is assigned to '%s:%s'\n", (yyvsp[(4) - (4)].string), (yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].VariableReturn)->string);
	   FREE_RULE_STRINGS(4);
       ;}
    break;

  case 44:
#line 841 "bison_grammar.y"
    {
	   VarExpr* CurrentVarExpr;
	   unsigned CurrentVarExprID = FindVarExpr((yyvsp[(1) - (5)].string),&CurrentVarExpr);
	   bool LocalVariableAlreadyExist = (CurrentVarExpr != NULL);
	   if( !LocalVariableAlreadyExist)
	   {
	       Extend_DynamicArray(&Dyn_VariableExpressionArray,sizeof(VarExpr));
	       CurrentVarExprID = GetSize_DynamicArray(&Dyn_VariableExpressionArray)-1;
	       CurrentVarExpr = GetElement_DynamicArray(&Dyn_VariableExpressionArray, CurrentVarExprID, sizeof(VarExpr));

	       VAR_EXPR_Initialize(CurrentVarExpr);
	       CurrentVarExpr -> Name = dupstr((yyvsp[(1) - (5)].string));

	       // Are all characters (after the underscore) capital letters?
	       unsigned CharNum = strlen((yyvsp[(1) - (5)].string));
	       unsigned CharNo;
	       bool IsAllCapitals = TRUE;
	       for(CharNo=1; CharNo< CharNum; CharNo++)
	       {
		   int ReturnVal = isupper((CurrentVarExpr -> Name)[CharNo]);
		   bool CharIsCapitalLetter = (ReturnVal > 0);
		   if( !CharIsCapitalLetter)
		   {
		       IsAllCapitals = FALSE;
		       break;
		   }
	       }
	       if(IsAllCapitals)
		   CurrentVarExpr -> Type = OP_RANDOM_DIST_CONSTANT;
	       else
		   CurrentVarExpr -> Type = OP_RANDOM_DIST;

	   }
	   else if( CurrentVarExpr -> Type == OP_RANDOM_DIST_CONSTANT )
	   {
	       char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	       sprintf(ErrorMessage,"Can NOT assign new value to CONSTANT LOCAL VARIABLE '%s'. Terminating...\n", (yyvsp[(1) - (5)].string));
	       yyerror(ErrorMessage);
	       free(ErrorMessage);
	       exit(1);
	   }


	   // Operand Map for random variables:
	   //   OperandID[0]: MinValExpressionID
	   //   OperandID[1]: MaxValExpressionID
	   //   OperandID[2]: Seed
	   //   OperandID[3]: Increment between values in the range
	   //   OperandID[4]: Random distribution function pointer
           // OperandID[3] and OperandID[4] are not yet used.

	   struct RangeInfoStruct* ParsedRangeInfo = (yyvsp[(4) - (5)].RangeInfo);
	   CurrentVarExpr -> Operation    = 1; // Operation is set to non-zero for the variable to initially have a random value.
	   CurrentVarExpr -> OperandID[0] = ParsedRangeInfo -> MinValExpressionID ;
	   CurrentVarExpr -> OperandID[1] = ParsedRangeInfo -> MaxValExpressionID ;
	   CurrentVarExpr -> OperandID[2] = 0;
	   CurrentVarExpr -> OperandID[3] = 1;
	   CurrentVarExpr -> OperandID[4] = (unsigned long)NULL;

	   if(VerboseParserOutput)
	       VAR_EXPR_Print(CurrentVarExpr);


	   FREE_RULE_STRINGS(5);

       ;}
    break;

  case 45:
#line 916 "bison_grammar.y"
    {

	 TxDefNum = GetSize_DynamicArray(&Dyn_TxDefArray);
	 TxDefArray = (TxInfo_t*) malloc(sizeof(TxInfo_t)*TxDefNum);

	 unsigned TxDefNo;
	 for(TxDefNo=0; TxDefNo < TxDefNum; TxDefNo++)
	 {
	     TX_INFO_Initialize( &(TxDefArray[TxDefNo]) );

	     TxInfo_t* CurrentTxDef    = GetElement_DynamicArray(&Dyn_TxDefArray,TxDefNo,sizeof(TxInfo_t));
	     unsigned CurrentTxDefOptionNum = 1;
	     TxDefArray[TxDefNo].Name = dupstr(CurrentTxDef ->  Name);

	     TxDefArray[TxDefNo].TxDefOptionNum = CurrentTxDefOptionNum;
	     TxDefArray[TxDefNo].TxOpNum  =  (unsigned*)malloc( CurrentTxDefOptionNum*sizeof(unsigned) );
	     TxDefArray[TxDefNo].TxOpList    =  (TxOpContainer_t**) malloc( CurrentTxDefOptionNum*sizeof(TxOpContainer_t*) ) ;
	     TxDefArray[TxDefNo].VarToUpdateNum  = CurrentTxDef -> VarToUpdateNum;
	     unsigned SizeOfVarToUpdateListInMemory = CurrentTxDef -> VarToUpdateNum * sizeof(unsigned);
	     TxDefArray[TxDefNo].VarListToUpdate = (unsigned*) malloc(SizeOfVarToUpdateListInMemory);
	     memcpy(TxDefArray[TxDefNo].VarListToUpdate, CurrentTxDef ->VarListToUpdate, SizeOfVarToUpdateListInMemory);


	     // We do not need the OptionConditionID list. It is just filled
	     // in for the copying of the data structure works correctly.
	     unsigned CopySizeInMemory = CurrentTxDefOptionNum*sizeof(int);
	     TxDefArray[TxDefNo].OptionConditionID     = (int*) malloc(CopySizeInMemory);
	     TxDefArray[TxDefNo].OutputVariableList    = (int*) malloc(CopySizeInMemory);
	     TxDefArray[TxDefNo].OutputCalculationList = (int*) malloc(CopySizeInMemory);
	     TxDefArray[TxDefNo].OptionConditionID[0]     = 0;
	     TxDefArray[TxDefNo].OutputVariableList[0]    = 0;
	     TxDefArray[TxDefNo].OutputCalculationList[0] = 0;


	     // We do not need any OptionNo. It is put here as a constant for backwards compatibility.
	     unsigned OptionNo=0;
	     unsigned TxOpListSizeInMemory = (CurrentTxDef -> TxOpNum[OptionNo])*sizeof(TxOpContainer_t);
	     TxDefArray[TxDefNo].TxOpList[OptionNo] = (TxOpContainer_t*)malloc(TxOpListSizeInMemory);
	     memcpy(TxDefArray[TxDefNo].TxOpList[OptionNo], CurrentTxDef ->TxOpList[OptionNo], TxOpListSizeInMemory);

	     memcpy(TxDefArray[TxDefNo].TxOpNum, CurrentTxDef -> TxOpNum,  CurrentTxDefOptionNum*sizeof(unsigned));

	     TxDefArray[TxDefNo].ReadOnly = CurrentTxDef ->  ReadOnly;

	     free(CurrentTxDef ->  Name);
	 }
	 Free_DynamicArray(&Dyn_TxDefArray);


     ;}
    break;

  case 46:
#line 970 "bison_grammar.y"
    {

#ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	   InitializeTempThreadStructuresUsedInParsing();
#endif

#ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	   InitializeTempTransactionStructuresUsedInParsing();
#endif

	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     TRANSACTIONS Section\n"
			     "-----------------------------------------------------------------------------\n" );
       ;}
    break;

  case 49:
#line 993 "bison_grammar.y"
    {

#ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	   Extend_DynamicArray(&Dyn_TxDefArray,sizeof(TxInfo_t));
	   unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_TxDefArray) - 1;
	   TxInfo_t* AddedElement = (TxInfo_t*)GetElement_DynamicArray(&Dyn_TxDefArray,LastAddedElementPos,sizeof(TxInfo_t));

	   TX_INFO_Initialize(AddedElement);
	   AddedElement -> Name = dupstr((yyvsp[(1) - (4)].string));
	   AddedElement -> TxDefOptionNum = 1;
	   AddedElement -> TxOpList   = (TxOpContainer_t**)malloc(sizeof(TxOpContainer_t*));
	   AddedElement -> TxOpNum    = (unsigned*)malloc(sizeof(unsigned));
	   AddedElement -> TxOpNum[0] = GetSize_DynamicArray(&CurrentTxOpList);
	   AddedElement -> VarToUpdateNum  =  (unsigned)GetSize_DynamicArray(&Dyn_VarExprToUpdateList);
	   AddedElement -> VarListToUpdate =  MakeStaticCopy_DynamicArray(&Dyn_VarExprToUpdateList, sizeof(unsigned));

	   unsigned SizeOfTxOpListInMemory =  (AddedElement -> TxOpNum[0])*sizeof(TxOpContainer_t);
	   AddedElement -> TxOpList[0] = (TxOpContainer_t*)malloc(SizeOfTxOpListInMemory);
	   unsigned TxOpNo;
	   for(TxOpNo=0; TxOpNo< AddedElement -> TxOpNum[0] ; TxOpNo++)
	   {
	       TxOpContainer_t* SourceTxOpContainer = (TxOpContainer_t*)GetElement_DynamicArray(&CurrentTxOpList,TxOpNo,sizeof(TxOpContainer_t));
	       TxOpContainer_t* TargetTxOpContainer = &(AddedElement -> TxOpList[0][TxOpNo]);
	       TX_OP_CONTAINER_Copy(SourceTxOpContainer, TargetTxOpContainer);
	   }


	   bool TransactionReadOnly = TRUE;
	   AddedElement -> InherentDelay = 0;
	   unsigned TxOpNum = AddedElement -> TxOpNum[0];
	   for(TxOpNo=0; TxOpNo< TxOpNum; TxOpNo++)
	   {
	       TxOpContainer_t* CurrentTxOpContainer = &(AddedElement -> TxOpList[0][TxOpNo]);

	       if(TransactionReadOnly )
	       {
		   bool CurrentTxOpIsAWrite = (CurrentTxOpContainer -> TxOperation == WRITE);
		   if(CurrentTxOpIsAWrite )
		   {
		       TransactionReadOnly = FALSE;
		       // if the inherent delay is also calculated in the same as this then remove this break
		       break;
		   }
	       }

/* 	       CurrentTxInfo -> InherentDelay +=  CurrentTxOpContainer -> PrecedingDelay; */
/* 	       bool LastTxOp = (TxOpNo == TxOpNum -1); */
/* 	       if( LastTxOp ) */
/* 		   CurrentTxInfo -> InherentDelay +=  CurrentTxOpContainer -> DelayBeforeCommit; */

	   }
	   AddedElement -> ReadOnly = TransactionReadOnly;
	   Clear_DynamicArray(&CurrentTxOpList);

	   if(ExecuteSchedule)
	   {
	       // Generate a Thread only containing the current transaction for schedule execution

	       Extend_DynamicArray(&Dyn_ScheduleThreadDefArray, sizeof(ThreadInfo_t));
	       unsigned AddedScheduleThreadInfoPos = GetSize_DynamicArray(&Dyn_ScheduleThreadDefArray)-1;
	       ThreadInfo_t* AddedScheduleThreadInfo = GetElement_DynamicArray(&Dyn_ScheduleThreadDefArray, AddedScheduleThreadInfoPos, sizeof(ThreadInfo_t));
	       AddedScheduleThreadInfo -> ID = AddedScheduleThreadInfoPos;

	       unsigned MaxDigitNumForScheduleThreadNum = 10;
	       unsigned SchedThreadNameLenght = strlen("Th")+ MaxDigitNumForScheduleThreadNum + 1;
	       char* SchedThreadName = malloc(SchedThreadNameLenght*sizeof(char));
	       sprintf(SchedThreadName,"Th%u",AddedScheduleThreadInfoPos+1);
	       AddedScheduleThreadInfo -> Name = SchedThreadName;

	       // There is only one transaction per thread
	       AddedScheduleThreadInfo -> TxContainerNum = 1;
	       AddedScheduleThreadInfo -> TxContainerList = (TxContainer_t*)malloc(sizeof(TxContainer_t));
	       (AddedScheduleThreadInfo -> TxContainerList)-> CandidateTxNum = 1;
	       (AddedScheduleThreadInfo -> TxContainerList)-> TxCandidateList = (TxCandidate_t*)malloc(sizeof(TxCandidate_t));
	       (AddedScheduleThreadInfo -> TxContainerList)-> TxCandidateList -> TxID = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> TxCandidateList -> Percentage = UNSPECIFIED_PERCENTAGE;
	       (AddedScheduleThreadInfo -> TxContainerList)-> NextContainerID[0] = 1;
	       (AddedScheduleThreadInfo -> TxContainerList)-> NextContainerID[1] = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> RepetitionCount = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> InitialRepetitionCount = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> CandidateSeed = 0;
	       (AddedScheduleThreadInfo -> TxContainerList)-> CandidateSelectionFunc = NULL;
	       (AddedScheduleThreadInfo -> TxContainerList)-> PrecedingDelay[0] = 0   ;
	       (AddedScheduleThreadInfo -> TxContainerList)-> PrecedingDelay[1] = 0   ;
	       (AddedScheduleThreadInfo -> TxContainerList)-> LoopStartNode = FALSE   ;

	       AddedScheduleThreadInfo -> TxDefNum = 1;
	       AddedScheduleThreadInfo -> TxDefArray = (TxInfo_t*) malloc(sizeof(TxInfo_t));
	       TX_INFO_Copy(AddedElement, AddedScheduleThreadInfo -> TxDefArray);

	       ScheduleThreadNum++;
	   }

#endif


	   REPORT_READ_INPUT("\n");
       ;}
    break;

  case 50:
#line 1095 "bison_grammar.y"
    {
	 REPORT_READ_INPUT("%s is comprised of the following operations:\n",yytext);
	 Clear_DynamicArray(&Dyn_VarExprToUpdateList);
	 TxDefElementNo=0;
	 TxOpNo=0;
       ;}
    break;

  case 51:
#line 1106 "bison_grammar.y"
    {
	  if ((yyvsp[(1) - (1)].string) != NULL)
	  {
	      REPORT_READ_INPUT("Ele[%u]: %s\n",TxDefElementNo,(yyvsp[(1) - (1)].string));
	      TxDefElementNo++;
	  }
      ;}
    break;

  case 52:
#line 1115 "bison_grammar.y"
    {
	   if ((yyvsp[(3) - (3)].string) != NULL)
	   {
	       REPORT_READ_INPUT("Ele[%u]: %s\n",TxDefElementNo,(yyvsp[(3) - (3)].string));
	       TxDefElementNo++;
	   }
       ;}
    break;

  case 53:
#line 1125 "bison_grammar.y"
    {
	   ALLOC_AND_RETURN_STRING("OpNo[%u]:%s",TxOpNo,(yyvsp[(1) - (1)].string));
	   FREE_RULE_STRINGS(1);
	   TxOpNo++;
       ;}
    break;

  case 54:
#line 1131 "bison_grammar.y"
    {
	   ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
//	   $$=NULL;
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 55:
#line 1137 "bison_grammar.y"
    {
	   ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 56:
#line 1142 "bison_grammar.y"
    {

	   unsigned TxOpListSize  = GetSize_DynamicArray(&CurrentTxOpList);
	   bool     TxOpListEmpty = (TxOpListSize == 0);
	   TxOpContainer_t* TxOpContainerToAttach = NULL;

	   if( TxOpListEmpty  )
	   {
	       // Generate New TxOp and set TxOpContainerToAttach with its pointer
	       TxOpInfo_t  CurrentOpInfo;
	       CurrentOpInfo.Delay = 0 ;
	       CurrentOpInfo.Op    = INVALID ;

	       GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

	       // We set the pointer of the first element of CurrentTxOpList to TxOpContainerToAttach
	       TxOpContainerToAttach = (TxOpContainer_t*) GetElement_DynamicArray(&CurrentTxOpList, 0, sizeof(TxOpContainer_t));
	   }
	   else
	   {
	       unsigned LastTxOpPos = TxOpListSize  - 1 ;
	       TxOpContainerToAttach = GetElement_DynamicArray(&CurrentTxOpList, LastTxOpPos, sizeof(TxOpContainer_t) );
	   }

	   TxOpContainerToAttach -> VarAssignNum = GetSize_DynamicArray(&Dyn_VarAssignList);
	   TxOpContainerToAttach -> VarAssigns   = MakeStaticCopy_DynamicArray(&Dyn_VarAssignList, sizeof(var_assign_t));

	   Clear_DynamicArray(&Dyn_VarAssignList);

	   ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 57:
#line 1175 "bison_grammar.y"
    {

          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = LABEL_OP ;

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

		  // Adding  the label name to the last added TxOpContainer
		  unsigned LastTxOpNo = GetSize_DynamicArray(&CurrentTxOpList) - 1;
		  TxOpContainer_t* LabelOpContainer = (TxOpContainer_t*) GetElement_DynamicArray(&CurrentTxOpList,LastTxOpNo, sizeof(TxOpContainer_t));
		     // We would like to stript the @ sign at the beginning of
		     // LABEL string so we start copying from the element 1 of
		     // $1 instead of its 0th element
		  LabelOpContainer -> Label = dupstr(&((yyvsp[(1) - (1)].string)[1]));


//		  CurrentDelayVal = 0 ;

	      }

	  #endif

	   ALLOC_AND_RETURN_STRING("Label %s",(yyvsp[(1) - (1)].string));
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 58:
#line 1205 "bison_grammar.y"
    {
	   ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 59:
#line 1210 "bison_grammar.y"
    {
	   ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 60:
#line 1218 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("DELAY determined by the following variable expression:'%s'", (yyvsp[(2) - (3)].string));
	  FREE_RULE_STRINGS(3);
	  (yyval.string)= (yyvsp[(2) - (3)].string);
      ;}
    break;

  case 65:
#line 1230 "bison_grammar.y"
    {
          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = READ ;

//		  CurrentOpInfo.AddrGenIDList[0] = CurrentAssociatedAddrGenIDArray[0];
//		  CurrentOpInfo.AddrGenIDList[1] = CurrentAssociatedAddrGenIDArray[1];

		  CurrentOpInfo.AddrOp = GetMemAccessOpAddressParameter((yyvsp[(2) - (3)].string));
		  CurrentOpInfo.AddrGenIDList[0] = (unsigned) -1;

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

//		  CurrentDelayVal = 0 ;

//		  CurrentAssociatedAddrGenIDArray[0] = INVALID_ADDR_GEN_ID;
//		  CurrentAssociatedAddrGenIDArray[1] = INVALID_ADDR_GEN_ID;
//		  CurrentAddrOp = INVALID_ADDR_OP;
	      }

	  #endif

	  ALLOC_AND_RETURN_STRING("READ from address of '%s'", (yyvsp[(2) - (3)].string));
 	  FREE_RULE_STRINGS(3);

       ;}
    break;

  case 66:
#line 1260 "bison_grammar.y"
    {

          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = READ ;

//		  CurrentOpInfo.AddrGenIDList[0] = CurrentAssociatedAddrGenIDArray[0];
//		  CurrentOpInfo.AddrGenIDList[1] = CurrentAssociatedAddrGenIDArray[1];

		  CurrentOpInfo.AddrOp = GetMemAccessOpAddressParameter((yyvsp[(2) - (5)].string));
		  CurrentOpInfo.AddrGenIDList[0] = GetReadAccessTargetParameter((yyvsp[(4) - (5)].string));

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

//		  CurrentDelayVal = 0 ;

//		  CurrentAssociatedAddrGenIDArray[0] = INVALID_ADDR_GEN_ID;
//		  CurrentAssociatedAddrGenIDArray[1] = INVALID_ADDR_GEN_ID;
//		  CurrentAddrOp = INVALID_ADDR_OP;
	      }

	  #endif

	  ALLOC_AND_RETURN_STRING("READ from address of '%s' into '%s'.",(yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].string));
 	  FREE_RULE_STRINGS(5);
       ;}
    break;

  case 67:
#line 1290 "bison_grammar.y"
    {

          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = WRITE ;

//		  CurrentOpInfo.AddrGenIDList[0] = CurrentAssociatedAddrGenIDArray[0];
//		  CurrentOpInfo.AddrGenIDList[1] = CurrentAssociatedAddrGenIDArray[1];
		  CurrentOpInfo.AddrOp = GetMemAccessOpAddressParameter((yyvsp[(2) - (3)].string));
		  CurrentOpInfo.AddrGenIDList[0] = (unsigned) -1;

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

//		  CurrentDelayVal = 0 ;

//		  CurrentAssociatedAddrGenIDArray[0] = INVALID_ADDR_GEN_ID;
//		  CurrentAssociatedAddrGenIDArray[1] = INVALID_ADDR_GEN_ID;
//		  CurrentAddrOp = INVALID_ADDR_OP;
	      }
	 #endif

	  ALLOC_AND_RETURN_STRING("WRITE to address of '%s'.",(yyvsp[(2) - (3)].string));
 	  FREE_RULE_STRINGS(3);

       ;}
    break;

  case 68:
#line 1319 "bison_grammar.y"
    {


          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = WRITE ;

//		  CurrentOpInfo.AddrGenIDList[0] = CurrentAssociatedAddrGenIDArray[0];
//		  CurrentOpInfo.AddrGenIDList[1] = CurrentAssociatedAddrGenIDArray[1];
		  CurrentOpInfo.AddrOp = GetMemAccessOpAddressParameter((yyvsp[(2) - (5)].string));
		  CurrentOpInfo.AddrGenIDList[0] = GetWriteAccessTargetParameter((yyvsp[(4) - (5)].string));

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

//		  CurrentDelayVal = 0 ;

//		  CurrentAssociatedAddrGenIDArray[0] = INVALID_ADDR_GEN_ID;
//		  CurrentAssociatedAddrGenIDArray[1] = INVALID_ADDR_GEN_ID;
//		  CurrentAddrOp = INVALID_ADDR_OP;
	      }
	 #endif

	  ALLOC_AND_RETURN_STRING("WRITE  '%s' to address of '%s'.",(yyvsp[(4) - (5)].string), (yyvsp[(2) - (5)].string));
 	  FREE_RULE_STRINGS(5);
       ;}
    break;

  case 69:
#line 1352 "bison_grammar.y"
    {

          #ifdef NO_TRANSACTION_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  TxOpInfo_t  CurrentOpInfo;
		  CurrentOpInfo.Delay = 0 ;
		  CurrentOpInfo.Op    = ABORT ;

		  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;

	      }
	 #endif


	  ALLOC_AND_RETURN_STRING("ABORT with probability '%s'",(yyvsp[(2) - (3)].string));
 	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 70:
#line 1373 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("ALLOCATE MEMORY of size '%s' (start address '%s')",(yyvsp[(4) - (5)].string), (yyvsp[(2) - (5)].string));
 	  FREE_RULE_STRINGS(5);
      ;}
    break;

  case 71:
#line 1379 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("FREE MEMORY at address '%s'",(yyvsp[(2) - (3)].string));
 	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 72:
#line 1386 "bison_grammar.y"
    {

	  ALLOC_AND_RETURN_STRING("MEMORY BARRIER (Name: '%s', Type: '%s')",(yyvsp[(2) - (5)].string),(yyvsp[(4) - (5)].string));
 	  FREE_RULE_STRINGS(5);
      ;}
    break;

  case 73:
#line 1394 "bison_grammar.y"
    {
	  unsigned LoopConditionTxOpPos = (yyvsp[(2) - (6)].ConditionReturn) -> ConditionTxOpContainerPos  ;
	  unsigned LoopEndTxOpPos = GetSize_DynamicArray(&CurrentTxOpList) - 1 ;
	  char* String = dupstr((yyvsp[(2) - (6)].ConditionReturn)->string);

	  // Make the forward link to the next operation after the loop (Link to jump over the loop)
	  // LOOP_BACK in following function is named like that due to reuse of previous version of tmunit.
	  // Actually it corresponds to a BRANCH or a JUMP in the new design.
	  InsertBranchAmongTxOpContainers(&CurrentTxOpList, LoopConditionTxOpPos, LoopEndTxOpPos+1, LOOP_BACK, 0);

	  // Make the backwards link from last element of the loop to the conditional tx_op_container.
	  // Again NEXT is the reuse of the previous version of tmunit.
	  InsertBranchAmongTxOpContainers(&CurrentTxOpList, LoopEndTxOpPos, LoopConditionTxOpPos,  NEXT, 0);


	  ALLOC_AND_RETURN_STRING("LOOP END (for the loop with condition: '%s')",String);
	  free(String);
 	  FREE_RULE_STRINGS(6);
      ;}
    break;

  case 74:
#line 1415 "bison_grammar.y"
    {
	    // yyvsp[0].string  is the string corresponding to the
	    // 'LoopCondition' in the above 'TxLoopDef' rule
	    REPORT_READ_INPUT("Ele[%u]: LOOP (Looping Condition: '%s')\n",TxDefElementNo, yyvsp[0].ConditionReturn -> string);
	    TxDefElementNo++;
	;}
    break;

  case 75:
#line 1424 "bison_grammar.y"
    {
	   (yyval.ConditionReturn) = (yyvsp[(1) - (1)].ConditionReturn);
//	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 76:
#line 1430 "bison_grammar.y"
    {
	   VarExpr* LoopIteratorVarExpr;
	   unsigned LoopIteratorID = FindVarExpr((yyvsp[(1) - (3)].VariableReturn)->string, &LoopIteratorVarExpr);
	   if(LoopIteratorVarExpr== NULL)
	   {
	       LoopIteratorID = AllocVarExpr((yyvsp[(1) - (3)].VariableReturn)->string, &LoopIteratorVarExpr);
	       assert(LoopIteratorVarExpr != NULL);
	       LoopIteratorVarExpr -> Type = VAR_LOCAL_SIMPLE;
	       LoopIteratorVarExpr -> Value = 0;
	   }

//	   VarExpr* LowerLimitVarExpr = GetVarExprPtr($3 -> MinValExpressionID);
//	   LoopIteratorVarExpr -> Value = EvaluateVarExpr(LowerLimitVarExpr);

	   VarExpr* UpperLimitVarExpr = GetVarExprPtr((yyvsp[(3) - (3)].RangeInfo) -> MaxValExpressionID);

	   unsigned LoopIteratorConditionStringLength = strlen((yyvsp[(1) - (3)].VariableReturn)->string) + strlen("<=") + strlen(UpperLimitVarExpr->Name) + 1;
	   char* LoopIteratorConditionString = malloc(LoopIteratorConditionStringLength*sizeof(char));
	   sprintf(LoopIteratorConditionString,"%s<=%s",(yyvsp[(1) - (3)].VariableReturn)->string,UpperLimitVarExpr->Name);

	   VarExpr* LoopConditionVarExpr;
	   unsigned LoopConditionVarExprID = AllocVarExpr(LoopIteratorConditionString, &LoopConditionVarExpr);
	   LoopConditionVarExpr -> Type = OP_RELATIONAL;
	   LoopConditionVarExpr -> Operation = SMALLER_EQUAL;
	   LoopConditionVarExpr -> OperandID[0] = LoopIteratorID;
	   LoopConditionVarExpr -> OperandID[1] = (yyvsp[(3) - (3)].RangeInfo) -> MaxValExpressionID;
	   LoopConditionVarExpr -> OperandID[2] = (yyvsp[(3) - (3)].RangeInfo) -> MinValExpressionID;

	   unsigned IteratorIncementStringLenght = strlen((yyvsp[(1) - (3)].VariableReturn)->string) + strlen("+") + strlen("9999")+ 1;
	   char* IteratorIncementString = (char *)malloc(IteratorIncementStringLenght * sizeof(char));
	   sprintf(IteratorIncementString,"%s+%u",(yyvsp[(1) - (3)].VariableReturn)->string, (yyvsp[(3) - (3)].RangeInfo)->Increment);

	   unsigned IncrementValueExprStringLenght = strlen("9999")+ 1;
	   char* IncrementValueExprString = (char*) malloc(IncrementValueExprStringLenght*sizeof(char));
	   sprintf(IncrementValueExprString,"%u", (yyvsp[(3) - (3)].RangeInfo)->Increment);


	   VarExpr* IncrementValueExpr;
	   unsigned IncrementValueExprID = FindVarExpr(IncrementValueExprString, &IncrementValueExpr);
	   if( IncrementValueExpr == NULL)
	   {
	       IncrementValueExprID = AllocVarExpr(IncrementValueExprString, &IncrementValueExpr);
	       IncrementValueExpr -> Type = VAR_LOCAL_SIMPLE_CONSTANT;
	       IncrementValueExpr -> Value = (yyvsp[(3) - (3)].RangeInfo)->Increment;
	   }


	   VarExpr* LoopIteratorIncementExpr;
	   unsigned LoopIteratorIncementExprID = FindVarExpr(IteratorIncementString, &LoopIteratorIncementExpr);
	   if(LoopIteratorIncementExpr == NULL)
	   {
	       LoopIteratorIncementExprID = AllocVarExpr(IteratorIncementString, &LoopIteratorIncementExpr);
	       LoopIteratorIncementExpr -> Type = OP_ARITH;
	       LoopIteratorIncementExpr -> Operation = PLUS;
	       LoopIteratorIncementExpr -> OperandID[0] = LoopIteratorID;
	       LoopIteratorIncementExpr -> OperandID[1] = IncrementValueExprID;
	   }


	   // Generating a tx_op_container for the above condition.
	   TxOpInfo_t  CurrentOpInfo;
	   CurrentOpInfo.Delay = 0 ;
	   CurrentOpInfo.Op    = INVALID ;
	   CurrentOpInfo.AddrOp = 0;

	   GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;
	   unsigned LoopConditionTxOpPos = GetSize_DynamicArray(&CurrentTxOpList) - 1 ;
	   TxOpContainer_t* LoopConditionTxOpContainer = GetElement_DynamicArray(&CurrentTxOpList, LoopConditionTxOpPos, sizeof(TxOpContainer_t) );
	   LoopConditionTxOpContainer -> ConditionExprPos =  LoopConditionVarExprID;

	   LoopConditionTxOpContainer -> LoopIteratorContainer = TRUE;
	   LoopConditionTxOpContainer -> LoopExecuting = FALSE;
	   LoopConditionTxOpContainer -> VarAssignNum = 1;
	   LoopConditionTxOpContainer -> VarAssigns = (var_assign_t*)malloc(sizeof(var_assign_t));
	   (LoopConditionTxOpContainer -> VarAssigns[0]).AssignedVarID = LoopIteratorID;
	   (LoopConditionTxOpContainer -> VarAssigns[0]).EvaluatedVarExprID = LoopIteratorIncementExprID;


           struct ConditionReturnStruct* ReturnVal = (struct ConditionReturnStruct*)malloc(sizeof(struct ConditionReturnStruct));

	   unsigned ReturnStringSize = strlen((yyvsp[(1) - (3)].VariableReturn)->string) + strlen((yyvsp[(2) - (3)].string)) + strlen((yyvsp[(3) - (3)].RangeInfo)->string) +1 ;
	   char* ReturnString = (char*) malloc(ReturnStringSize * sizeof(char));
	   sprintf(ReturnString,"'%s%s%s'",(yyvsp[(1) - (3)].VariableReturn)->string, (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].RangeInfo)->string);

	   ReturnVal-> string= ReturnString;
	   ReturnVal-> ConditionTxOpContainerPos = LoopConditionTxOpPos;
	   (yyval.ConditionReturn) = ReturnVal;

//	   ALLOC_AND_RETURN_STRING("'%s%s%s'",$1->string, $2, $3->string);
	   FREE_RULE_STRINGS(3);
       ;}
    break;

  case 77:
#line 1527 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered Range '%s' in LOOP definition.\n", (yyvsp[(2) - (3)].RangeInfo) -> string);
//	  ALLOC_AND_RETURN_STRING("%s", $2 -> string);
	  (yyval.RangeInfo) = (yyvsp[(2) - (3)].RangeInfo);
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 78:
#line 1536 "bison_grammar.y"
    {
	  unsigned  IfElseBlockSuccessorTxOpContainerPos = GetSize_DynamicArray( &CurrentTxOpList );

	  unsigned* ConditionTerminatingTxOpArray = (unsigned*)(ConditionTerminationTxOpList.ArrayStartAddress);
	  unsigned TxOpNum = GetSize_DynamicArray( &ConditionTerminationTxOpList );
	  unsigned TxOpNo = 0;
	  for(TxOpNo =0; TxOpNo< TxOpNum; TxOpNo++)
	  {
	      unsigned ConditionTerminatingTxOpPos     = ConditionTerminatingTxOpArray[TxOpNo];
	      assert(ConditionTerminatingTxOpPos < IfElseBlockSuccessorTxOpContainerPos );
	      InsertBranchAmongTxOpContainers(&CurrentTxOpList, ConditionTerminatingTxOpPos, IfElseBlockSuccessorTxOpContainerPos, NEXT, 0);
	  }

	  Clear_DynamicArray( &ConditionTerminationTxOpList );
	  EndOfIfElseBlock = FALSE;

	  ALLOC_AND_RETURN_STRING("Encountered CONDITIONAL EXECUTION BLOCK with following conditions:\n%s",(yyvsp[(2) - (3)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 79:
#line 1560 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("\t - %s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 80:
#line 1565 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("%s\n\t - %s",(yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 81:
#line 1570 "bison_grammar.y"
    {
	  EndOfIfElseBlock = TRUE;
	  ALLOC_AND_RETURN_STRING("%s\n\t - ELSE",(yyvsp[(1) - (3)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 82:
#line 1579 "bison_grammar.y"
    {
	  struct ConditionReturnStruct* ConditionInfo = (yyvsp[(1) - (4)].ConditionReturn);


	  unsigned ConditionalBlockStartTxOpPos = ConditionInfo-> ConditionTxOpContainerPos;
	  unsigned ConditionalBlockSuccessorTxOpPos =  GetSize_DynamicArray(&CurrentTxOpList) ;
	  // The successor block should be at least 1 tx_op_container further
	  // than the initial conditional tx_op_container ( a distance of 1
          // is  when no tx_op defined in the conditional block)
	  assert( ConditionalBlockSuccessorTxOpPos - ConditionalBlockStartTxOpPos >= 1);

	  // Make the forward link to the next operation after the condition (either another condition or some TxOp)
	  // LOOP_BACK in following function is named like that due to reuse of previous version of tmunit.
	  // Actualy it corresponds to a BRANCH or a JUMP in the new design.
	  InsertBranchAmongTxOpContainers(&CurrentTxOpList, ConditionalBlockStartTxOpPos, ConditionalBlockSuccessorTxOpPos, LOOP_BACK, 0);


	  Extend_DynamicArray( &ConditionTerminationTxOpList,sizeof(unsigned));
	  unsigned LastAddedElementPos = GetSize_DynamicArray(&ConditionTerminationTxOpList) - 1;
	  unsigned * CurrentElement = (unsigned*) GetElement_DynamicArray(&ConditionTerminationTxOpList, LastAddedElementPos , sizeof(unsigned));
	  *CurrentElement = ConditionalBlockSuccessorTxOpPos -1;

	  ALLOC_AND_RETURN_STRING("%s",ConditionInfo-> string);
	  FREE_RULE_STRINGS(4);
      ;}
    break;

  case 83:
#line 1606 "bison_grammar.y"
    {
	     // yyvsp[1].string  indicates the  string returned for the "Condition"  in ConditionalTxSpecElement rule.
	     REPORT_READ_INPUT("Parsing behaviour for  CONDITION: '%s'\n",yyvsp[1].string);

	     if( EndOfIfElseBlock)
	     {
		 char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		 sprintf(ErrorMessage,"Encountered UNEXPECTED CONDITION BLOCK (with condition '%s') after an ELSE block.", yyvsp[1].string );
		 yyerror(ErrorMessage);
		 free(ErrorMessage);
		 exit(1);

	     }

         ;}
    break;

  case 85:
#line 1626 "bison_grammar.y"
    {
	     REPORT_READ_INPUT("Parsing behaviour for  CONDITION: 'ELSE'\n");
	 ;}
    break;

  case 86:
#line 1632 "bison_grammar.y"
    {

	  char* ConditionString = (yyvsp[(2) - (3)].string);

	  VarExpr* ConditionVarExpr;
	  unsigned ConditionVarExprID = FindVarExpr(ConditionString, &ConditionVarExpr);
	  if( ConditionVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN Conditional Expression '%s' is encountered while constructing conditional transaction block.\n", ConditionString);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }

	  TxOpInfo_t  CurrentOpInfo;
	  CurrentOpInfo.Delay = 0 ;
	  CurrentOpInfo.Op    = INVALID ;
	  CurrentOpInfo.AddrOp = 0;

	  GenerateAndAttachNewContainerForSingleTxOp(&CurrentTxOpList,&CurrentOpInfo) ;
	  unsigned ConditionTxOpPos = GetSize_DynamicArray(&CurrentTxOpList) - 1 ;
	  TxOpContainer_t* ConditionTxOpContainer = GetElement_DynamicArray(&CurrentTxOpList, ConditionTxOpPos, sizeof(TxOpContainer_t) );

	  ConditionTxOpContainer -> ConditionExprPos =  ConditionVarExprID;

	  struct ConditionReturnStruct* ReturnVal = (struct ConditionReturnStruct*)malloc(sizeof(struct ConditionReturnStruct));
	  ReturnVal-> string= dupstr(ConditionString);
	  ReturnVal-> ConditionTxOpContainerPos = ConditionTxOpPos;

	  (yyval.ConditionReturn) = ReturnVal;




//	  ALLOC_AND_RETURN_STRING("%s",$2);
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 87:
#line 1674 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 88:
#line 1679 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 89:
#line 1686 "bison_grammar.y"
    {
	 // Check the existence of both Variable Expressions (if they exist, record their IDs)
	 VarExpr* FirstExpr;
	 unsigned FirstExprID = FindVarExpr((yyvsp[(1) - (3)].string), &FirstExpr);
	 if( FirstExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Variable Expression '%s' is encountered in Conditinal Expression. Terminating...\n", (yyvsp[(1) - (3)].string));
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }
	 VarExpr* SecondExpr;
	 unsigned SecondExprID = FindVarExpr((yyvsp[(3) - (3)].string), &SecondExpr);
	 if( SecondExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Variable Expression '%s' is encountered in Conditinal Expression. Terminating...\n", (yyvsp[(3) - (3)].string));
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }



	 unsigned ConditionalExpressionStringLength = strlen((yyvsp[(1) - (3)].string)) + strlen((yyvsp[(2) - (3)].string)) + strlen((yyvsp[(3) - (3)].string)) +1;
	 char* ConditionalExpressionString = (char*)malloc(ConditionalExpressionStringLength*sizeof(char));
	 sprintf(ConditionalExpressionString,"%s%s%s",(yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string));

	 VarExpr* ConditionalVarExpr;
	 FindOrAllocVarExpr(ConditionalExpressionString, &ConditionalVarExpr);
	 assert(ConditionalVarExpr != NULL);
	 ConditionalVarExpr -> Type = OP_RELATIONAL;
	 ConditionalVarExpr -> Operation = ResolveOperationType((yyvsp[(2) - (3)].string));
	 ConditionalVarExpr -> OperandID[0] = FirstExprID;
	 ConditionalVarExpr -> OperandID[1] = SecondExprID;

	 (yyval.string) = ConditionalExpressionString;

	 FREE_RULE_STRINGS(3);
	 REPORT_READ_INPUT("\tEncountered SIMPLE CONDITIONAL EXPRESSION '%s'\n",(yyval.string));
     ;}
    break;

  case 90:
#line 1732 "bison_grammar.y"
    {
	 ALLOC_AND_RETURN_STRING("%s%s%s",(yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].string),(yyvsp[(3) - (3)].string));
	 FREE_RULE_STRINGS(3);
	 REPORT_READ_INPUT("\tEncountered COMPLEX CONDITIONAL EXPRESSION (without any boolean op) : '%s'\n",(yyval.string));
     ;}
    break;

  case 91:
#line 1738 "bison_grammar.y"
    {
	 // Check the existence of the SimpleConditionalExpression (if they exist, record their IDs)
	 VarExpr* SimpleCondExpr;
	 unsigned SimpleCondExprID = FindVarExpr((yyvsp[(3) - (4)].string), &SimpleCondExpr);
	 if( SimpleCondExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Simple Conditional Expression '%s' is encountered in Complex Conditional Expression. Terminating...\n", (yyvsp[(3) - (4)].string));
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }

	 unsigned ConditionalExpressionStringLength = strlen((yyvsp[(1) - (4)].string)) + strlen((yyvsp[(2) - (4)].string)) + strlen((yyvsp[(3) - (4)].string)) + strlen((yyvsp[(4) - (4)].string)) + 1;
	 char* ConditionalExpressionString = (char*)malloc(ConditionalExpressionStringLength*sizeof(char));
	 sprintf(ConditionalExpressionString,"%s%s%s%s",(yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].string), (yyvsp[(3) - (4)].string), (yyvsp[(4) - (4)].string));

	 VarExpr* ConditionalVarExpr;
	 FindOrAllocVarExpr(ConditionalExpressionString, &ConditionalVarExpr);
	 assert(ConditionalVarExpr != NULL);
	 ConditionalVarExpr -> Type = OP_BOOLEAN_UNARY;
	 ConditionalVarExpr -> Operation = ResolveOperationType((yyvsp[(1) - (4)].string));
	 ConditionalVarExpr -> OperandID[0] = SimpleCondExprID;

	 (yyval.string) = ConditionalExpressionString;

	 FREE_RULE_STRINGS(4);
	 REPORT_READ_INPUT("\tEncountered COMPLEX CONDITIONAL EXPRESSION (with a UNARY boolean op) : '%s'\n",(yyval.string));
     ;}
    break;

  case 92:
#line 1772 "bison_grammar.y"
    {
	 ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	 FREE_RULE_STRINGS(1);
    ;}
    break;

  case 93:
#line 1777 "bison_grammar.y"
    {
	    char* AccessedConditionalString = (yyvsp[(2) - (3)].string);
	    unsigned NewStringSize = strlen("(") + strlen(AccessedConditionalString) + strlen(")") +1;
	    char* ReturnString = malloc(NewStringSize*sizeof(char));
	    sprintf(ReturnString,"(%s)",AccessedConditionalString);
	    (yyval.string) = ReturnString;
	    FREE_RULE_STRINGS(1);
     ;}
    break;

  case 94:
#line 1786 "bison_grammar.y"
    {
	 // Check the existence of the SimpleConditionalExpression (if they exist, record their IDs)
	 VarExpr* SimpleCondExpr;
	 unsigned SimpleCondExprID = FindVarExpr((yyvsp[(3) - (4)].string), &SimpleCondExpr);
	 if( SimpleCondExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Complex Conditional Expression '%s' is encountered in Complex Conditional Expression. Terminating...\n", (yyvsp[(3) - (4)].string));
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }

	 unsigned ConditionalExpressionStringLength = strlen((yyvsp[(1) - (4)].string)) + strlen((yyvsp[(2) - (4)].string)) + strlen((yyvsp[(3) - (4)].string)) + strlen((yyvsp[(4) - (4)].string)) + 1;
	 char* ConditionalExpressionString = (char*)malloc(ConditionalExpressionStringLength*sizeof(char));
	 sprintf(ConditionalExpressionString,"%s%s%s%s",(yyvsp[(1) - (4)].string), (yyvsp[(2) - (4)].string), (yyvsp[(3) - (4)].string), (yyvsp[(4) - (4)].string));

	 VarExpr* ConditionalVarExpr;
	 FindOrAllocVarExpr(ConditionalExpressionString, &ConditionalVarExpr);
	 assert(ConditionalVarExpr != NULL);
	 ConditionalVarExpr -> Type = OP_BOOLEAN_UNARY;
	 ConditionalVarExpr -> Operation = ResolveOperationType((yyvsp[(1) - (4)].string));
	 ConditionalVarExpr -> OperandID[0] = SimpleCondExprID;

	 (yyval.string) = ConditionalExpressionString;

	 FREE_RULE_STRINGS(4);
	 REPORT_READ_INPUT("\tEncountered COMPLEX CONDITIONAL EXPRESSION (with a UNARY boolean op) : '%s'\n",(yyval.string));
     ;}
    break;

  case 95:
#line 1820 "bison_grammar.y"
    {
	 ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	 FREE_RULE_STRINGS(1);
     ;}
    break;

  case 96:
#line 1825 "bison_grammar.y"
    {
	 char* FirstExprStr  = (yyvsp[(1) - (3)].string);
	 char* SecondExprStr = (yyvsp[(3) - (3)].string);
	 char* BooleanOpStr  = (yyvsp[(2) - (3)].string);

	 // Check the existence of both Variable Expressions (if they exist, record their IDs)
	 VarExpr* FirstExpr;
	 unsigned FirstExprID = FindVarExpr(FirstExprStr, &FirstExpr);
	 if( FirstExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Complex Conditional Expression '%s' is encountered in a Boolean Expression. Terminating...\n", FirstExprStr);
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }
	 VarExpr* SecondExpr;
	 unsigned SecondExprID = FindVarExpr(SecondExprStr, &SecondExpr);
	 if( SecondExpr == NULL)
	 {
	     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(ErrorMessage,"UNKNOWN Complex Conditional Expression '%s' is encountered in a Boolean Expression. Terminating...\n", SecondExprStr);
	     yyerror(ErrorMessage);
	     free(ErrorMessage);
	     assert(0);
	 }



	 unsigned ConditionalExpressionStringLength = strlen(FirstExprStr) + strlen(BooleanOpStr) + strlen(SecondExprStr) +1;
	 char* ConditionalExpressionString = (char*)malloc(ConditionalExpressionStringLength*sizeof(char));
	 sprintf(ConditionalExpressionString,"%s%s%s", FirstExprStr, BooleanOpStr, SecondExprStr);

	 VarExpr* ConditionalVarExpr;
	 FindOrAllocVarExpr(ConditionalExpressionString, &ConditionalVarExpr);
	 assert(ConditionalVarExpr != NULL);
	 ConditionalVarExpr -> Type = OP_BOOLEAN;
	 ConditionalVarExpr -> Operation = ResolveOperationType(BooleanOpStr);
	 ConditionalVarExpr -> OperandID[0] = FirstExprID;
	 ConditionalVarExpr -> OperandID[1] = SecondExprID;

	 (yyval.string) = ConditionalExpressionString;

	 FREE_RULE_STRINGS(5);
	 REPORT_READ_INPUT("\tEncountered COMPLEX CONDITIONAL EXPRESSION (with a BINARY boolean op) : '%s'\n",(yyval.string));
     ;}
    break;

  case 97:
#line 1877 "bison_grammar.y"
    {
	 ALLOC_AND_RETURN_STRING("ASSIGNMENTS:\n%s",(yyvsp[(3) - (4)].string));
	 FREE_RULE_STRINGS(4);
      ;}
    break;

  case 98:
#line 1883 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered VARIABLE ASSIGNMENT block in Transaction definition\n");
	  ALLOC_AND_RETURN_STRING("Temp");
      ;}
    break;

  case 99:
#line 1890 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("%s\n",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 100:
#line 1896 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("%s%s\n",(yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 101:
#line 1906 "bison_grammar.y"
    {
	  VarExpr* AssignedVar;
	  unsigned AssignedVarExprID = FindVarExpr((yyvsp[(1) - (3)].VariableReturn) -> string, &AssignedVar);
	  if( AssignedVar == NULL)
	  {
	      bool NewLocalVariable = ( ((yyvsp[(1) - (3)].VariableReturn)->string)[0] == '_' );
	      if( !NewLocalVariable )
	      {
		  // Look whether the AssignedVar Name includes scope
		  // IF YES just skip
		  // IF NO  do the following
		  char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		  sprintf(ErrorMessage,"UNKNOWN SHARED VARIABLE '%s'.\n"
			               "Can not define shared variables inside a transaction definition/variable assignment.\n"
			               "Only local variables can be defined at the point where they are first used.\n"
			               "Shared variables should be defined in the 'Definitions' section (before they are used).\n", (yyvsp[(1) - (3)].VariableReturn) -> string);
		  yyerror(ErrorMessage);
		  free(ErrorMessage);
		  exit(1);
	      }

	      // Undefined arrays are caught before this point.
/* 	      unsigned VariableNameLastCharPos = strlen($1->string) - 1 ; */
/* 	      bool NewLocalArrayDefinition =  ($1->string)[VariableNameLastCharPos] == ']'; */
/* 	      if( NewLocalArrayDefinition) */
/* 	      { */
/* 		  char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);  */
/* 		  sprintf(ErrorMessage,"CAN NOT DEFINE LOCAL ARRAY '%s' inside a transaction definition\n" */
/* 			               "(can not known size of array in advance).\n" */
/* 			               "Terminating...\n", $1 -> string); */
/* 		  yyerror(ErrorMessage); */
/* 		  free(ErrorMessage); */
/* 		  exit(1); */

/* 	      } */

	      AssignedVarExprID = AllocVarExpr((yyvsp[(1) - (3)].VariableReturn)->string, &AssignedVar);
	      AssignedVar -> Type = VAR_LOCAL_SIMPLE;
	  }


	  // If variable is random and if it has not been encountered
	  // before, it will be added to Dyn_VarExprToUpdateList
	  ExtendVarExprToUpdate((yyvsp[(1) - (3)].VariableReturn)->string);


	  bool AssignedVariableConstant = ( AssignedVar -> Type == VAR_SHARED_CONSTANT_UNMANAGED   \
					                        ||                                 \
					    AssignedVar -> Type == VAR_SHARED_CONSTANT_MANAGED     \
					                        ||                                 \
					    AssignedVar -> Type == VAR_SHARED_ARRAY_CONSTANT       \
					                        ||                                 \
					    AssignedVar -> Type == VAR_LOCAL_SIMPLE_CONSTANT       \
					                        ||                                 \
					    AssignedVar -> Type == VAR_LOCAL_ARRAY_CONSTANT        \
					                        ||                                 \
					    AssignedVar -> Type == OP_RANDOM_DIST_CONSTANT         \
	                                  );
	  if( AssignedVariableConstant )
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"CAN NOT ASSIGN VALUE to CONSTANT VARIABLE '%s'.Terminating...\n", (yyvsp[(1) - (3)].VariableReturn) -> string);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }


	  VarExpr* EvaluatedVarExpr;
	  unsigned EvaluatedVarExprID = FindVarExpr((yyvsp[(3) - (3)].string), &EvaluatedVarExpr);
	  assert( EvaluatedVarExpr != NULL);

	  Extend_DynamicArray(&Dyn_VarAssignList,sizeof(var_assign_t));
	  unsigned LastAssignPos = GetSize_DynamicArray(&Dyn_VarAssignList) -1 ;
	  var_assign_t* CurrentAssign = (var_assign_t*)GetElement_DynamicArray(&Dyn_VarAssignList, LastAssignPos, sizeof(var_assign_t));
	  CurrentAssign -> AssignedVarID = AssignedVarExprID;
	  CurrentAssign -> EvaluatedVarExprID =  EvaluatedVarExprID;

	  REPORT_READ_INPUT("\tEncountered VARIABLE ASSIGNMENT '%s%s%s'\n", (yyvsp[(1) - (3)].VariableReturn)->string , (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string));
	  ALLOC_AND_RETURN_STRING("\t- %s%s%s", (yyvsp[(1) - (3)].VariableReturn) ->string, (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string) );
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 102:
#line 1993 "bison_grammar.y"
    {
	  ALLOC_AND_RETURN_STRING("JUMP to '%s'",(yyvsp[(2) - (3)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 103:
#line 2000 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered '==' operation\n");
	  ALLOC_AND_RETURN_STRING("==");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 104:
#line 2006 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered '!=' operation\n");
	  ALLOC_AND_RETURN_STRING("!=");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 105:
#line 2013 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered '<' operation\n");
	  ALLOC_AND_RETURN_STRING("<");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 106:
#line 2020 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered '>' operation\n");
	  ALLOC_AND_RETURN_STRING(">");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 107:
#line 2027 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered '<=' operation\n");
	  ALLOC_AND_RETURN_STRING("<=");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 108:
#line 2033 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered '>=' operation\n");
	  ALLOC_AND_RETURN_STRING(">=");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 109:
#line 2039 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered '!' operation\n");
	  ALLOC_AND_RETURN_STRING("!");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 110:
#line 2048 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered LOGICAL AND operation\n");
	  ALLOC_AND_RETURN_STRING("&&");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 111:
#line 2055 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered LOGICAL OR operation\n");
	  ALLOC_AND_RETURN_STRING("||");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 112:
#line 2065 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered LOGICAL NOT operation\n");
	  ALLOC_AND_RETURN_STRING("!");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 113:
#line 2075 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered FIXED VALUE '%s'\n",(yyvsp[(1) - (1)].string));
	  ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
       ;}
    break;

  case 114:
#line 2081 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered '%s'\n",(yyvsp[(1) - (1)].string));
	  ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
       ;}
    break;

  case 115:
#line 2091 "bison_grammar.y"
    {
	  VarExpr* FixedNumVarExpr;
	  FindOrAllocVarExpr((yyvsp[(1) - (1)].string), &FixedNumVarExpr);
	  FixedNumVarExpr -> Type = VAR_LOCAL_SIMPLE_CONSTANT;
	  FixedNumVarExpr -> Value = (Word)atoi((yyvsp[(1) - (1)].string));

	  ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 116:
#line 2103 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered CONSTANT '%s'\n",(yyvsp[(1) - (1)].string));
	  ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 119:
#line 2115 "bison_grammar.y"
    {

	  ALLOC_AND_RETURN_STRING("RANDOMIZED RANGE %s", (yyvsp[(2) - (3)].RangeInfo) -> string);
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 120:
#line 2123 "bison_grammar.y"
    {

	   struct RangeInfoStruct* ReturnedRangeInfo = (struct RangeInfoStruct*)malloc(sizeof(struct RangeInfoStruct));
	   VarExpr* DummyVarExpr;
	   unsigned RangeLimitVarExprID = FindOrAllocVarExpr((yyvsp[(1) - (3)].string),&DummyVarExpr);
	   ReturnedRangeInfo -> MinValExpressionID = RangeLimitVarExprID;

	   RangeLimitVarExprID = FindOrAllocVarExpr((yyvsp[(3) - (3)].string),&DummyVarExpr);
	   ReturnedRangeInfo -> MaxValExpressionID = RangeLimitVarExprID;
	   ReturnedRangeInfo -> Increment = 1 ;

	   char* TempString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	   sprintf(TempString,"'%s' to '%s' (increment 1)",(yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string));
	   ReturnedRangeInfo ->string = TempString;

	   (yyval.RangeInfo) = ReturnedRangeInfo;

	   FREE_RULE_STRINGS(3);
	   REPORT_READ_INPUT("\tEncountered RANGE '%s'\n",(yyval.RangeInfo) -> string);
       ;}
    break;

  case 121:
#line 2144 "bison_grammar.y"
    {
           ALLOC_AND_RETURN_STRING("'%s' to '%s' (increment '%s')", (yyvsp[(1) - (5)].string), (yyvsp[(3) - (5)].string) , (yyvsp[(5) - (5)].string) );
	   FREE_RULE_STRINGS(5);
	   REPORT_READ_INPUT("\tEncountered RANGE '%s'\n",(yyval.RangeInfo) -> string);
       ;}
    break;

  case 122:
#line 2154 "bison_grammar.y"
    {
	   VarExpr* VarExprPtr;
	   FindVarExpr((yyvsp[(1) - (1)].string), &VarExprPtr);
	   bool VariableExists = (VarExprPtr != NULL);
	   if( VariableExists )
	       ExtendVarExprToUpdate((yyvsp[(1) - (1)].string));

	   REPORT_READ_INPUT("\tEncountered SHARED variable '%s'\n",(yyvsp[(1) - (1)].string));
	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   ReturnVal -> string = dupstr((yyvsp[(1) - (1)].string));
	   ReturnVal -> VariableType = SHARED;

	   (yyval.VariableReturn) = ReturnVal;
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 123:
#line 2170 "bison_grammar.y"
    {

	   VarExpr* VarExprPtr;
	   FindVarExpr((yyvsp[(1) - (1)].string), &VarExprPtr);
	   bool VariableExists = (VarExprPtr != NULL);
	   if( VariableExists )
	       ExtendVarExprToUpdate((yyvsp[(1) - (1)].string));

	   REPORT_READ_INPUT("\tEncountered LOCAL variable '%s'\n",(yyvsp[(1) - (1)].string));
	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   ReturnVal -> string = dupstr((yyvsp[(1) - (1)].string));


	   // Are all characters (after the underscore) capital letters?
	   unsigned CharNum = strlen((yyvsp[(1) - (1)].string));
	   unsigned CharNo;
	   bool IsAllCapitals = TRUE;
	   for(CharNo=1; CharNo< CharNum; CharNo++)
	   {
	       int ReturnVal = isupper(((yyvsp[(1) - (1)].string))[CharNo]);
	       bool CharIsCapitalLetter = (ReturnVal > 0);
	       if( !CharIsCapitalLetter)
	       {
		   IsAllCapitals = FALSE;
		   break;
	       }
	   }
	   if(IsAllCapitals)
	       ReturnVal -> VariableType = LOCAL_CONSTANT;
	   else
	       ReturnVal -> VariableType = LOCAL;


	   (yyval.VariableReturn) = ReturnVal;
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 124:
#line 2207 "bison_grammar.y"
    {
	   VarExpr* VarExprPtr;
	   FindVarExpr((yyvsp[(1) - (1)].string), &VarExprPtr);
	   bool VariableExists = (VarExprPtr != NULL);
	   if( VariableExists )
	       ExtendVarExprToUpdate((yyvsp[(1) - (1)].string));

	   REPORT_READ_INPUT("\tEncountered CONSTANT variable '%s'\n",(yyvsp[(1) - (1)].string));
	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   ReturnVal -> string = dupstr((yyvsp[(1) - (1)].string));
	   ReturnVal -> VariableType = SHARED_CONSTANT;

	   (yyval.VariableReturn) = ReturnVal;
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 125:
#line 2223 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("\tEncountered LOCAL variable '%s' in the scope '%s'\n",(yyvsp[(2) - (2)].string),(yyvsp[(1) - (2)].string));

	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   unsigned ScopedVariableNameLength = strlen((yyvsp[(1) - (2)].string)) + strlen(":")  + strlen((yyvsp[(2) - (2)].string)) + 1 ;
	   ReturnVal -> string = malloc( ScopedVariableNameLength * sizeof(char));
	   sprintf(ReturnVal -> string,"%s:%s", (yyvsp[(1) - (2)].string),(yyvsp[(2) - (2)].string));



	   // Are all characters (after the underscore) capital letters?
	   unsigned CharNum = strlen((yyvsp[(2) - (2)].string));
	   unsigned CharNo;
	   bool IsAllCapitals = TRUE;
	   for(CharNo=1; CharNo< CharNum; CharNo++)
	   {
	       int ReturnVal = isupper(((yyvsp[(2) - (2)].string))[CharNo]);
	       bool CharIsCapitalLetter = (ReturnVal > 0);
	       if( !CharIsCapitalLetter)
	       {
		   IsAllCapitals = FALSE;
		   break;
	       }
	   }
	   if(IsAllCapitals)
	       ReturnVal -> VariableType = SCOPED_LOCAL_CONSTANT;
	   else
	       ReturnVal -> VariableType = SCOPED_LOCAL;

	   (yyval.VariableReturn) = ReturnVal;
	   FREE_RULE_STRINGS(3);
       ;}
    break;

  case 126:
#line 2256 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("\tEncountered ARRAY variable '%s'\n",(yyvsp[(1) - (1)].VariableReturn) -> string);
	   (yyval.VariableReturn) = (yyvsp[(1) - (1)].VariableReturn);
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 127:
#line 2262 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("\tEncountered LOCAL ARRAY variable '%s' in the scope '%s'\n",(yyvsp[(2) - (2)].VariableReturn)->string,(yyvsp[(1) - (2)].string));

	   if( (yyvsp[(2) - (2)].VariableReturn)->VariableType == SHARED_ARRAY);
	   {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Scope '%s' encountered before Shared array '%s'.\n"
		                   "Scopes are only allowed for local variables/arrays.\n", (yyvsp[(1) - (2)].string) , (yyvsp[(2) - (2)].VariableReturn) -> string);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);

	   }

	   struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	   unsigned ScopedVariableNameLength = strlen((yyvsp[(1) - (2)].string)) + strlen(":")  + strlen((yyvsp[(2) - (2)].VariableReturn)->string) + 1 ;
	   ReturnVal -> string = malloc( ScopedVariableNameLength * sizeof(char));
	   sprintf(ReturnVal -> string,"%s:%s", (yyvsp[(1) - (2)].string),(yyvsp[(2) - (2)].VariableReturn)->string);

	   if ((yyvsp[(2) - (2)].VariableReturn) -> VariableType == LOCAL_CONSTANT_ARRAY)
	       ReturnVal -> VariableType = SCOPED_LOCAL_CONSTANT_ARRAY;
	   else if((yyvsp[(2) - (2)].VariableReturn) -> VariableType == LOCAL_ARRAY)
	       ReturnVal -> VariableType = SCOPED_LOCAL_ARRAY;

	   (yyval.VariableReturn) = ReturnVal;

	   FREE_RULE_STRINGS(3);
       ;}
    break;

  case 128:
#line 2295 "bison_grammar.y"
    {

	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr((yyvsp[(1) - (3)].string));
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';


	  VarExpr* ArrayVarExpr;
	  unsigned ArrayVarExprID = FindVarExpr(ActualArrayName, &ArrayVarExpr);
	  if( ArrayVarExpr == NULL)
	  {

	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN ARRAY '%s' is encountered  in Array Element access.\n"
		                   "Can not define arrays inside transaction definitions\n"
 		                   "(can not known size of array in advance).\n"
                                   "Arrays should be defined in the 'Definitions' section\n",ActualArrayName);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  VarExpr* IndexVarExpr;
	  unsigned IndexVarExprID = FindVarExpr((yyvsp[(2) - (3)].string), &IndexVarExpr);
	  if( IndexVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN INDEX expression '%s' is encountered in Array Element access. Terminating...\n", (yyvsp[(2) - (3)].string));
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }

	  // Since we are generating a shared array expression we generate two copies, one for managed and one for unmanaged accesses.
	  // Creating Unmanaged copy (if non-existant)
	  VarExpr* ArrayAccessVarExpr;
	  char *ArrayAccessString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ArrayAccessString, "%s%s%s", (yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string));
	  FindOrAllocVarExpr(ArrayAccessString, &ArrayAccessVarExpr);
	  assert(ArrayAccessVarExpr != NULL);
	  ArrayAccessVarExpr -> Type = OP_UNMANAGED_ARRAY_ACCESS;
	  ArrayAccessVarExpr -> OperandID[0] = ArrayVarExprID;
	  ArrayAccessVarExpr -> OperandID[1] = IndexVarExprID;

	  // Creating Managed copy (if non-existant)
	  VarExpr* ManagedArrayAccessVarExpr;
	  char *ManagedArrayAccessString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ManagedArrayAccessString, "&%s%s%s", (yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string));
	  FindOrAllocVarExpr(ManagedArrayAccessString, &ManagedArrayAccessVarExpr);
	  assert(ManagedArrayAccessVarExpr != NULL);
	  ManagedArrayAccessVarExpr -> Type = OP_MANAGED_ARRAY_ACCESS;
	  ManagedArrayAccessVarExpr -> OperandID[0] = ArrayVarExprID;
	  ManagedArrayAccessVarExpr -> OperandID[1] = IndexVarExprID;
	  free(ManagedArrayAccessString);

	  struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	  ReturnVal -> string = ArrayAccessString;
	  ReturnVal -> VariableType = SHARED_ARRAY;

	  (yyval.VariableReturn) = ReturnVal;

	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 129:
#line 2360 "bison_grammar.y"
    {
	  // Chopping last character (character '[') of array name
	  char*    ActualArrayName = dupstr((yyvsp[(1) - (3)].string));
	  unsigned LastCharPos     = strlen(ActualArrayName)-1;
	  ActualArrayName[LastCharPos]='\0';


	  VarExpr* ArrayVarExpr;
	  unsigned ArrayVarExprID = FindVarExpr(ActualArrayName, &ArrayVarExpr);
	  if( ArrayVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN ARRAY '%s' is encountered  in Array Element access.\n"
		                   "Can not define arrays inside transaction definitions\n"
 		                   "(can not known size of array in advance).\n"
                                   "Arrays should be defined in the 'Definitions' section\n",ActualArrayName);
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      exit(1);
	  }

	  VarExpr* IndexVarExpr;
	  unsigned IndexVarExprID = FindVarExpr((yyvsp[(2) - (3)].string), &IndexVarExpr);
	  if( IndexVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN INDEX expression '%s' is encountered in Array Element access. Terminating...\n", (yyvsp[(2) - (3)].string));
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }


	  VarExpr* ArrayAccessVarExpr;
	  char *ArrayAccessString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ArrayAccessString, "%s%s%s", (yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string));
	  FindOrAllocVarExpr(ArrayAccessString, &ArrayAccessVarExpr);
	  assert(ArrayAccessVarExpr != NULL);
	  ArrayAccessVarExpr -> Type = OP_UNMANAGED_ARRAY_ACCESS;
	  ArrayAccessVarExpr -> OperandID[0] = ArrayVarExprID;
	  ArrayAccessVarExpr -> OperandID[1] = IndexVarExprID;


	  struct VariableReturnStruct* ReturnVal = (struct VariableReturnStruct*)malloc(sizeof(struct VariableReturnStruct));
	  ReturnVal -> string = ArrayAccessString;


	   // Are all characters (after the underscore) capital letters?
	   unsigned CharNum = strlen(ActualArrayName);
	   unsigned CharNo;
	   bool IsAllCapitals = TRUE;
	   for(CharNo=1; CharNo< CharNum; CharNo++)
	   {
	       int ReturnVal = isupper((ActualArrayName)[CharNo]);
	       bool CharIsCapitalLetter = (ReturnVal > 0);
	       if( !CharIsCapitalLetter)
	       {
		   IsAllCapitals = FALSE;
		   break;
	       }
	   }
	   if(IsAllCapitals)
	       ReturnVal -> VariableType = LOCAL_CONSTANT_ARRAY;
	   else
	       ReturnVal -> VariableType = LOCAL_ARRAY;

	  (yyval.VariableReturn) = ReturnVal;

	  FREE_RULE_STRINGS(3);
        ;}
    break;

  case 130:
#line 2435 "bison_grammar.y"
    {

	  VarExpr* InputVarExpr;
	  FindVarExpr((yyvsp[(2) - (3)].string), &InputVarExpr);
	  if( InputVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"UNKNOWN VARIABLE EXPRESSION '%s' is encountered in STM_LOAD access. Terminating...\n",(yyvsp[(2) - (3)].string));
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }

	  bool NotSupportedVariableExpression  = (InputVarExpr -> Type > VAR_SHARED_ARRAY_CONSTANT ) && (InputVarExpr -> Type != OP_UNMANAGED_ARRAY_ACCESS);
	  if( NotSupportedVariableExpression )
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage,"Variable Expression '%s' is not an access to a standalone shared variable/array.\n"
		                   "Other kind of variable expression are not allowed in managed accesses.\n",(yyvsp[(2) - (3)].string));
	      yyerror(ErrorMessage);
	      free(ErrorMessage);

	      exit(1);
	  }


	  // Chopping last character (character '[') of array name
	  unsigned ActualAccessedVarExprNameLength = strlen("&") + strlen((yyvsp[(1) - (3)].string)) + 1;
	  char*    ActualAccessedVarExprName = malloc(ActualAccessedVarExprNameLength * sizeof(char));
	  sprintf(ActualAccessedVarExprName,"&%s",(yyvsp[(2) - (3)].string));

	  VarExpr* AccessedVarExpr;
	  unsigned ActualVarExprID = FindVarExpr(ActualAccessedVarExprName, &AccessedVarExpr);
	  if( AccessedVarExpr == NULL)
	  {
	      char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	      sprintf(ErrorMessage, "MANAGED COPY of Variable Expression '%s' can NOT be FOUND. Terminating...\n",(yyvsp[(2) - (3)].string));
	      yyerror(ErrorMessage);
	      free(ErrorMessage);
	      assert(0);
	  }


	  VarExpr* ManagedAccessVarExpr;
	  char *ManagedAccessString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	  sprintf(ManagedAccessString, "%s%s%s", (yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string), (yyvsp[(3) - (3)].string));
	  FindOrAllocVarExpr(ManagedAccessString, &ManagedAccessVarExpr);
	  assert(ManagedAccessVarExpr != NULL);
	  ManagedAccessVarExpr -> Type = OP_MEMORY_READ;
	  ManagedAccessVarExpr -> OperandID[0] = ActualVarExprID;

	  (yyval.string) = ManagedAccessString;
	  FREE_RULE_STRINGS(3);

      ;}
    break;

  case 131:
#line 2491 "bison_grammar.y"
    {
	   yyerror("STM_STORE is not allowed in variable/relational/boolean expression evaluation.\n");
	   exit(1);

      ;}
    break;

  case 132:
#line 2497 "bison_grammar.y"
    {
	   yyerror("The STM_LOAD with explicit value return is not permitted in variable/relational/boolean expression evaluation.\n");
	   exit(1);
       ;}
    break;

  case 133:
#line 2502 "bison_grammar.y"
    {
	   yyerror("STM_STORE is not allowed in variable/relational/boolean expression evaluation.\n");
	   exit(1);
       ;}
    break;

  case 134:
#line 2511 "bison_grammar.y"
    {
	    ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	    FREE_RULE_STRINGS(1);
       ;}
    break;

  case 135:
#line 2516 "bison_grammar.y"
    {
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $1; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */


	    ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].VariableReturn) -> string);
	    FREE_RULE_STRINGS(1);
       ;}
    break;

  case 136:
#line 2529 "bison_grammar.y"
    {
	    ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	    FREE_RULE_STRINGS(1);

      ;}
    break;

  case 137:
#line 2542 "bison_grammar.y"
    {
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $1; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */
	    ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	    FREE_RULE_STRINGS(1);

        ;}
    break;

  case 138:
#line 2554 "bison_grammar.y"
    {
//	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $2;

	     char* AccessedVarExprString = (yyvsp[(2) - (2)].string);
	    unsigned NewStringLength = strlen("-") + strlen(AccessedVarExprString) + 1;
	    char *NewExpressionString = (char*)malloc(NewStringLength*sizeof(char));
	    sprintf(NewExpressionString,"-%s",AccessedVarExprString);


	    VarExpr* CurrentVarExpr;
	    FindVarExpr(NewExpressionString, &CurrentVarExpr);

	    bool Found= (CurrentVarExpr != NULL);
	    if( !Found )
	    {  // If variable expr found, we allocate it.
		unsigned CurrentVarExprID = AllocVarExpr(NewExpressionString, &CurrentVarExpr);

		// We need to construct the VarExpr structure
		CurrentVarExpr -> Type = OP_ARITH;


		// Since we came until this  point the Both of the operands of
                // the Variable expression should be already in the
                // Dyn_VariableExpressionArray
		VarExpr* FirstOperand;
		unsigned FirstOperandID = FindVarExpr("-1", &FirstOperand);
		bool FirstOperandDoesNotExist = (FirstOperand ==NULL);  // Since first operand is a minus sign it may not exist in the Dyn_VariableExpression list (yet)
		if(FirstOperandDoesNotExist)
		{
		    FirstOperandID = AllocVarExpr("-1", &FirstOperand);

		    FirstOperand -> Type = VAR_LOCAL_SIMPLE;
		    FirstOperand -> Value = -1;

		    // Since   a   new  variable   expression   is  added   to
                    // Dyn_VariableExpressionList it is possible that the list
		    // is reallocated  (possibily changing the  pointer to the
                    // current  var expr  that is  constructed). So  we update
                    // CurrentVarExpr.

		    CurrentVarExpr = GetVarExprPtr(CurrentVarExprID);
		}
		VarExpr* SecondOperand;
		unsigned SecondOperandID = FindVarExpr(AccessedVarExprString, &SecondOperand);
		assert(SecondOperand !=NULL);

		CurrentVarExpr -> OperandID[0] = FirstOperandID;
		CurrentVarExpr -> OperandID[1] = SecondOperandID;
		CurrentVarExpr -> Operation    = MULTIPLY;


	    }

/* 	    unsigned long  EvaluatedValue = EvaluateVarExpr(CurrentVarExpr); */
/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string =  NewExpressionString; */
/* 	    ReturnVal->Value  =  EvaluatedValue;  */
/* 	    $$ = ReturnVal ;	   */
	    (yyval.string) = NewExpressionString;
	    FREE_RULE_STRINGS(1);

         ;}
    break;

  case 139:
#line 2617 "bison_grammar.y"
    {
	    char* FirstAccessedVarExprString = (yyvsp[(1) - (3)].string);
	    char* SecondAccessedVarExprString = (yyvsp[(3) - (3)].string);

	    char *NewExpressionString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	    sprintf(NewExpressionString,"%s%s%s",FirstAccessedVarExprString,(yyvsp[(2) - (3)].string),SecondAccessedVarExprString);

	    VarExpr* CurrentVarExpr;
	    FindVarExpr(NewExpressionString, &CurrentVarExpr);

	    bool Found= (CurrentVarExpr != NULL);
	    if( !Found )
	    {  // If variable expr found, we allocate it.
		AllocVarExpr(NewExpressionString, &CurrentVarExpr);

		// We need to construct the VarExpr structure
		CurrentVarExpr -> Type = OP_ARITH;


		// Since we came until this  point the Both of the operands of
                // the Variable expression should be already in the
                // Dyn_VariableExpressionArray
		VarExpr* FirstOperand;
		unsigned FirstOperandID = FindVarExpr(FirstAccessedVarExprString, &FirstOperand);
		assert(FirstOperand !=NULL);
		VarExpr* SecondOperand;
		unsigned SecondOperandID = FindVarExpr(SecondAccessedVarExprString, &SecondOperand);
		assert(SecondOperand !=NULL);

		CurrentVarExpr -> OperandID[0] = FirstOperandID;
		CurrentVarExpr -> OperandID[1] = SecondOperandID;
		CurrentVarExpr -> Operation    = ResolveOperationType((yyvsp[(2) - (3)].string));


	    }


/* 	    unsigned long  EvaluatedValue = EvaluateVarExpr(CurrentVarExpr); */
/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = NewExpressionString; */
/* 	    ReturnVal->Value  = EvaluatedValue; */
/* 	    $$ = ReturnVal ;	     */
	    (yyval.string) = NewExpressionString;
	    FREE_RULE_STRINGS(3);

         ;}
    break;

  case 140:
#line 2667 "bison_grammar.y"
    {
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $1; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */
	    ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	    FREE_RULE_STRINGS(1);

        ;}
    break;

  case 141:
#line 2679 "bison_grammar.y"
    {
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $2; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
	    char* AccessedVarExprString = (yyvsp[(2) - (3)].string);
	    unsigned NewStringSize = strlen("(") + strlen(AccessedVarExprString) + strlen(")") +1;
	    char* ReturnString = malloc(NewStringSize*sizeof(char));
	    sprintf(ReturnString,"(%s)",AccessedVarExprString);
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */
	    (yyval.string) = ReturnString;
	    FREE_RULE_STRINGS(1);
	 ;}
    break;

  case 142:
#line 2696 "bison_grammar.y"
    {
/* VariableExpression:  */
/*      VariableExpressionElement */
/*         {  */
/*  	   REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",$1);  */
/*  	   ALLOC_AND_RETURN_STRING("%s",$1);  */
/*  	   FREE_RULE_STRINGS(1);  */
/*         };  */
/*      | VariableExpression  ArithmeticOp VariableExpressionElement  */
/*         {  */
/*  	   ALLOC_AND_RETURN_STRING("%s%s%s",$1,$2,$3);  */
/*  	   FREE_RULE_STRINGS(3);  */
/*  	   REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",$$);  */
/*         };  */
/*      | OPEN_PARANTHESES VariableExpression  ArithmeticOp VariableExpressionElement CLOSE_PARANTHESES */
/*        { */
/*  	   ALLOC_AND_RETURN_STRING("%s%s%s%s%s",$1,$2,$3,$4,$5);  */
/*  	   FREE_RULE_STRINGS(5);  */
/*  	   REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",$$);  */
/*        } */
/*      ; */



/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $1; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr ->Value; */
/* 	    $$ = ReturnVal ;	     */
	    REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",(yyvsp[(1) - (1)].string));
	    ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	    FREE_RULE_STRINGS(1);

        ;}
    break;

  case 143:
#line 2732 "bison_grammar.y"
    {
	    char* FirstAccessedVarExprString = (yyvsp[(1) - (3)].string);
	    char*  SecondAccessedVarExprString = (yyvsp[(3) - (3)].string);

	    char *NewExpressionString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	    sprintf(NewExpressionString,"%s%s%s",FirstAccessedVarExprString,(yyvsp[(2) - (3)].string),SecondAccessedVarExprString);

	    VarExpr* CurrentVarExpr;
	    FindVarExpr(NewExpressionString, &CurrentVarExpr);

	    bool Found= (CurrentVarExpr != NULL);
	    if( !Found )
	    {  // If variable expr found, we allocate it.
		AllocVarExpr(NewExpressionString, &CurrentVarExpr);

		// We need to construct the VarExpr structure
		CurrentVarExpr -> Type = OP_ARITH;


		// Since we came until this  point the Both of the operands of
                // the Variable expression should be already in the
                // Dyn_VariableExpressionArray
		VarExpr* FirstOperand;
		unsigned FirstOperandID = FindVarExpr(FirstAccessedVarExprString, &FirstOperand);
		assert(FirstOperand !=NULL);
		VarExpr* SecondOperand;
		unsigned SecondOperandID = FindVarExpr(SecondAccessedVarExprString, &SecondOperand);
		assert(SecondOperand !=NULL);

		CurrentVarExpr -> OperandID[0] = FirstOperandID;
		CurrentVarExpr -> OperandID[1] = SecondOperandID;
		CurrentVarExpr -> Operation    = ResolveOperationType((yyvsp[(2) - (3)].string));


	    }
/* 	    unsigned long  EvaluatedValue = EvaluateVarExpr(CurrentVarExpr); */
/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = NewExpressionString; */
/* 	    ReturnVal->Value  = EvaluatedValue; */
/* 	    $$ = ReturnVal ;	     */
	    (yyval.string) = NewExpressionString;
	    REPORT_READ_INPUT("\tEncountered VARIABLE EXPRESSION '%s'\n",NewExpressionString);
	    FREE_RULE_STRINGS(3);
/*      | OPEN_PARANTHESES VariableExpression  ArithmeticOp VariableExpressionElementAccess CLOSE_PARANTHESES */
/*        { */
/* 	    struct EvaluatedVariableExpressionStruct* AccessedVarExpr = $2; */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr(AccessedVarExpr -> string); */
/* 	    ReturnVal->Value  = AccessedVarExpr -> Value; */
/* 	    $$ = ReturnVal ;	     */
/* 	    FREE_RULE_STRINGS(5);  */
/*        } */

/* VariableExpressionElementAccess: */
/*      LOCAL_VARIABLE_NAME  */
/*        { */

/* 	    struct EvaluatedVariableExpressionStruct* ReturnVal = malloc(sizeof(struct EvaluatedVariableExpressionStruct)); */
/* 	    ReturnVal->string = dupstr($1); */

/* 	    VarExpr* CurrentVarExpr;  */
/* 	    FindVarExpr($1, &CurrentVarExpr); */
/* 	    bool VariableExists =  (CurrentVarExpr != NULL); */
/* 	    if(VariableExists ) */
/* 	    { */
/* 		unsigned long EvaluatedValue = EvaluateVarExpr(CurrentVarExpr); */
/* 		ReturnVal->Value  = EvaluatedValue; */
/* 	    }	    */
/* 	    else */
/* 	    { */
/* 		REPORT_SEMANTIC_ERROR("Access to an UNDEFINED LOCAL VARIABLE during evaluation of a variable expression.\n"); */
/* 	    } */

/* 	    $$ = ReturnVal ;	     */
/* 	    FREE_RULE_STRINGS(1); */
/*        }; */


        ;}
    break;

  case 144:
#line 2819 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered PLUS operation\n");
	  ALLOC_AND_RETURN_STRING("+");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 145:
#line 2825 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered MINUS operation\n");
	  ALLOC_AND_RETURN_STRING("-");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 146:
#line 2834 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered MULTIPLY operation (or * sign)\n");
	  ALLOC_AND_RETURN_STRING("*");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 147:
#line 2841 "bison_grammar.y"
    {
	  REPORT_READ_INPUT("\tEncountered DIVIDE operation\n");
	  ALLOC_AND_RETURN_STRING("/");
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 148:
#line 2852 "bison_grammar.y"
    {

     ;}
    break;

  case 149:
#line 2858 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     THREADS Section\n"
			     "-----------------------------------------------------------------------------\n" );
       ;}
    break;

  case 152:
#line 2872 "bison_grammar.y"
    {
	   FREE_RULE_STRINGS(4);

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
/* 		 GenerateAndAttachContainersForForwardTxList(&CurrentTxList,1); */
/* 		 Clear_DynamicArray(&CurrentTxList); */
		 GenerateAndAttachContainersForForwardTxList(&Dyn_TxDefArray,1);
		 Clear_DynamicArray(&Dyn_TxDefArray);


                 // char* ThreadName = $1;
		 unsigned ThreadTypeNo;
		 for(ThreadTypeNo=0; ThreadTypeNo < ThreadTypeNum ; ThreadTypeNo++)
		 {
		     char **ThreadNamePtr = (char**)GetElement_DynamicArray(&Dyn_CurrentThreadDefList, ThreadTypeNo, sizeof(char*));
		     AddNewThreadDef(*ThreadNamePtr);
		 }
		 Clear_DynamicArray(&Dyn_CurrentThreadDefList);
		 Clear_DynamicArray(&CurrentTxContainerList);

		 ThreadTypeNum = 0;

	     }
           #endif

       ;}
    break;

  case 153:
#line 2902 "bison_grammar.y"
    {
	    REPORT_READ_INPUT("'%s' is/are comprised of the following transactional pattern:\n",yyvsp[0].string);
	    TxBlockNo=0;

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
 	       CurrentTxContainerNo = 0;
	   #endif
	;}
    break;

  case 154:
#line 2913 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      Extend_DynamicArray(&Dyn_CurrentThreadDefList,sizeof(char*));
	      unsigned LastElementNo = GetSize_DynamicArray(&Dyn_CurrentThreadDefList) - 1 ;
	      char** CurrentThreadDefListElement = (char**)GetElement_DynamicArray(&Dyn_CurrentThreadDefList, LastElementNo, sizeof(char*));
	      *CurrentThreadDefListElement = dupstr((yyvsp[(1) - (1)].string));
	      ThreadTypeNum++;
	  #endif

	  ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
       ;}
    break;

  case 155:
#line 2926 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      Extend_DynamicArray(&Dyn_CurrentThreadDefList,sizeof(char*));
	      unsigned LastElementNo = GetSize_DynamicArray(&Dyn_CurrentThreadDefList) - 1 ;
	      char** CurrentThreadDefListElement = (char**)GetElement_DynamicArray(&Dyn_CurrentThreadDefList, LastElementNo, sizeof(char*));
	      *CurrentThreadDefListElement = dupstr((yyvsp[(3) - (3)].string));
	      ThreadTypeNum++;
	  #endif

	  ALLOC_AND_RETURN_STRING("%s,%s",(yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));
	  FREE_RULE_STRINGS(3);
       ;}
    break;

  case 156:
#line 2943 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     // The following assignment is for the purpose of passing the
             // BoundedRepetition field to the return value
	     (yyval.TxBlockListReturn) = (yyvsp[(1) - (1)].TxBlockListReturn);
	  #endif

	     // The following line is only for debugging
	     // REPORT_READ_INPUT("TxBlockListElement: Bounded:%d, Block:%s",$1 -> BoundedRepetition,$1->string);
	   REPORT_READ_INPUT("TxBlock[%u]: %s",TxBlockNo,(yyvsp[(1) - (1)].TxBlockListReturn)->string);
	   FREE_RULE_STRINGS(1);
	   TxBlockNo++;
       ;}
    break;

  case 157:
#line 2957 "bison_grammar.y"
    {
	   // The following two lines are only for debugging
	   // REPORT_READ_INPUT("TxBlockList: Bounded:%d, Block:%s",$1 -> BoundedRepetition,$1->string);
	   // REPORT_READ_INPUT("TxBlockListElement: Bounded:%d, Block:%s",$3 -> BoundedRepetition,$3->string);

          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	   if( (yyvsp[(1) - (3)].TxBlockListReturn) -> BoundedRepetition == FALSE)
	   {
	       REPORT_SEMANTIC_ERROR("UNEXPECTED EXECUTABLE ELEMENT (a transaction/ a TxCandidate list / paranthesized block). An infinitely repeating executable element should be the LAST possible executable element in a thread definition!\n");
	   }
	   else
	   {
	     // The following assignment is for the purpose of passing the
             // BoundedRepetition field to the return value
	     (yyval.TxBlockListReturn) = (yyvsp[(3) - (3)].TxBlockListReturn);
	   }
	  #endif


	   REPORT_READ_INPUT("TxBlock[%u]: %s",TxBlockNo,(yyvsp[(3) - (3)].TxBlockListReturn)->string);
	   FREE_RULE_STRINGS(1);
	   TxBlockNo++;
       ;}
    break;

  case 158:
#line 2985 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
             //  ALLOC_AND_RETURN_STRING("%s",$1);
	     char *TempString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(TempString,"%s",(yyvsp[(1) - (1)].string));

	     struct TxBlockListReturnStruct* NewRetVal =  (struct TxBlockListReturnStruct*) malloc(sizeof(struct TxBlockListReturnStruct));
	     NewRetVal -> string = TempString;
	     NewRetVal -> BoundedRepetition = TRUE;
	     (yyval.TxBlockListReturn) = NewRetVal;
	  #endif
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 159:
#line 2999 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
             //  ALLOC_AND_RETURN_STRING("%s",$1);
	     char *TempString = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
	     sprintf(TempString,"%s",(yyvsp[(1) - (1)].string));

	     struct TxBlockListReturnStruct* NewRetVal =  (struct TxBlockListReturnStruct*) malloc(sizeof(struct TxBlockListReturnStruct));
	     NewRetVal -> string = TempString;
	     NewRetVal -> BoundedRepetition = FALSE;
	     (yyval.TxBlockListReturn) = NewRetVal;
	  #endif

	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 160:
#line 3017 "bison_grammar.y"
    {

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 GenerateAndAttachNewContainerForSimpleTxBlock((yyvsp[(1) - (1)].string), &DelayOpEncountered, CurrentDelayVal);
		 CurrentTxContainerNo++;
	     }
	   #endif


  	  ALLOC_AND_RETURN_STRING("%s\n",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 161:
#line 3032 "bison_grammar.y"
    {
	  if( DelayOpEncountered )
	  {
	      yyerror("Consecutive delay operations encountered. Terminating...");
	      exit(1);
	  }
	  else
	  {
	      CurrentDelayVal = atoi((yyvsp[(1) - (1)].string));
	      DelayOpEncountered = TRUE;
	  }


  	  ALLOC_AND_RETURN_STRING("%s\n",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 162:
#line 3049 "bison_grammar.y"
    {

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
 	        if ( !ParseOnly )
 		{
 		    GenerateAndAttachNewContainerForTxChoiceList(&CurrentTxCandidateList, 1,  &DelayOpEncountered, CurrentDelayVal);
 		    Clear_DynamicArray(&CurrentTxCandidateList);
 		    CurrentTxContainerNo++;
 		}
            #endif

  	  ALLOC_AND_RETURN_STRING("Choice List:\n%s",(yyvsp[(2) - (3)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 163:
#line 3064 "bison_grammar.y"
    {

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION

 	        if ( !ParseOnly )
 		{
 		    GenerateAndAttachNewContainerForTxChoiceList(&CurrentTxCandidateList, 1,  &DelayOpEncountered, CurrentDelayVal);
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo, LOOP_BACK, atoi((yyvsp[(4) - (4)].string)) );
 		    Clear_DynamicArray(&CurrentTxCandidateList);
		    CurrentTxContainerNo++;
 		}
            #endif

		ALLOC_AND_RETURN_STRING("%s times repeated Choice List:\n%s",(yyvsp[(4) - (4)].string),(yyvsp[(2) - (4)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 164:
#line 3081 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
          #endif

  	  ALLOC_AND_RETURN_STRING("%s times repeated Choice List:\n%s", (yyvsp[(4) - (4)].VariableReturn)->string, (yyvsp[(2) - (4)].string));
	  FREE_RULE_STRINGS(4);
      ;}
    break;

  case 165:
#line 3089 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 if( VerboseParserOutput)
		     printf("Container no at the end of TxBlock= %u \n",CurrentTxContainerNo-1);
		 if( (yyvsp[(3) - (4)].TxBlockListReturn) -> BoundedRepetition == FALSE)
		 {
		     REPORT_SEMANTIC_ERROR("UNEXPECTED TX BLOCK including an infinitely repeating executable element.\n"
                                           "An infinitely repeating executable element should be the LAST possible executable element in a thread definition!\n");
		 }
	     }
          #endif

  	  REPORT_READ_INPUT("End of SIMPLE TxBlockList\n");
	  FREE_RULE_STRINGS(3);
       ;}
    break;

  case 166:
#line 3107 "bison_grammar.y"
    {

          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 if( VerboseParserOutput )
		     printf("Container no at the end of TxBlock= %u \n",CurrentTxContainerNo-1);

		 if( (yyvsp[(3) - (5)].TxBlockListReturn) -> BoundedRepetition == FALSE)
		 {
		     REPORT_SEMANTIC_ERROR("UNEXPECTED REPEATED TX BLOCK including an infinitely repeating executable element.\n"
                                           "An infinitely repeating executable element should be the LAST possible executable element in a thread definition!\n");
		 }


		 unsigned IterationNum = atoi((yyvsp[(5) - (5)].string));
		 InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo-1, TxBlockStartContainerNo, LOOP_BACK, IterationNum);
	     }
          #endif


  	  REPORT_READ_INPUT("End of  %s times repeated TxBlockList\n",(yyvsp[(5) - (5)].string));
	  FREE_RULE_STRINGS(5);
      ;}
    break;

  case 167:
#line 3132 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 if( VerboseParserOutput )
		     printf("Container no at the end of TxBlock= %u \n",CurrentTxContainerNo-1);

		 if( (yyvsp[(3) - (5)].TxBlockListReturn) -> BoundedRepetition == FALSE)
		 {
		     REPORT_SEMANTIC_ERROR("UNEXPECTED REPEATED TX BLOCK including an infinitely repeating executable element.\n"
                                           "An infinitely repeating executable element should be the LAST possible executable element in a thread definition!\n");
		 }


		 VarExpr* ElementVarExpr;
		 unsigned LoopLimitExprID = FindVarExpr((yyvsp[(5) - (5)].string),&ElementVarExpr);
		 if(ElementVarExpr == NULL)
		 {
		     char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		     sprintf(ErrorMessage,"Can NOT evaluate INEXISTENT Variable Expression '%s'. Terminating...\n", (yyvsp[(5) - (5)].string));
		     yyerror(ErrorMessage);
		     free(ErrorMessage);
		     exit(1);
		 }

		 InsertVarExprBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo-1, TxBlockStartContainerNo, LOOP_BACK, LoopLimitExprID);


	     }



          #endif


  	  REPORT_READ_INPUT("End of  %s times repeated TxBlockList\n", (yyvsp[(3) - (5)].TxBlockListReturn) ->string);
	  FREE_RULE_STRINGS(5);
      ;}
    break;

  case 168:
#line 3175 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 GenerateAndAttachNewContainerForSimpleTxBlock((yyvsp[(1) - (2)].string), &DelayOpEncountered, CurrentDelayVal);
		 #ifdef COMPILE_FOR_TEST
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo, LOOP_BACK, ITERATION_NUM_OF_INFINITE_LOOPS_FOR_TESTS );
		 #else
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo , NEXT, 0);
		 #endif
		 CurrentTxContainerNo++;
	     }
          #endif

  	  ALLOC_AND_RETURN_STRING("INFINITELY REPEATED %s\n",(yyvsp[(1) - (2)].string));
	  FREE_RULE_STRINGS(2);
      ;}
    break;

  case 169:
#line 3193 "bison_grammar.y"
    {

           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      if ( !ParseOnly )
	      {
		  GenerateAndAttachNewContainerForTxChoiceList(&CurrentTxCandidateList, 1,  &DelayOpEncountered, CurrentDelayVal);
                  #ifdef COMPILE_FOR_TEST
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo, LOOP_BACK, ITERATION_NUM_OF_INFINITE_LOOPS_FOR_TESTS );
		  #else
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo, CurrentTxContainerNo , NEXT, 0);
		  #endif
 		  Clear_DynamicArray(&CurrentTxCandidateList);
		  CurrentTxContainerNo++;
 		}
            #endif


  	  ALLOC_AND_RETURN_STRING("INFINITELY REPEATED Choice List:\n%s",(yyvsp[(2) - (4)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 170:
#line 3214 "bison_grammar.y"
    {

          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	     if ( !ParseOnly )
	     {
		 if( VerboseParserOutput)
		     printf("Container no at the end of TxBlock= %u \n",CurrentTxContainerNo-1);

                 #ifdef COMPILE_FOR_TEST
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo-1, TxBlockStartContainerNo, LOOP_BACK, ITERATION_NUM_OF_INFINITE_LOOPS_FOR_TESTS);
		 #else
		    InsertBranchAmongTxContainers(&CurrentTxContainerList, CurrentTxContainerNo-1, TxBlockStartContainerNo, NEXT, 0);
		 #endif

	     }
          #endif


  	  REPORT_READ_INPUT("End of  INFINITELY REPEATED TxBlockList\n");
	  FREE_RULE_STRINGS(4);
       ;}
    break;

  case 171:
#line 3238 "bison_grammar.y"
    {
           #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	    TxBlockStartContainerNo = CurrentTxContainerNo;

	    if ( !ParseOnly && VerboseParserOutput )
		printf("TxBlock Start encountered at Container No %u .\n",TxBlockStartContainerNo);
	   #endif

         ;}
    break;

  case 172:
#line 3251 "bison_grammar.y"
    {
  	  ALLOC_AND_RETURN_STRING("%s\n",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 173:
#line 3256 "bison_grammar.y"
    {
  	  ALLOC_AND_RETURN_STRING("%s%s\n",(yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 174:
#line 3264 "bison_grammar.y"
    {
	ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (2)].string));
	FREE_RULE_STRINGS(1);
    ;}
    break;

  case 175:
#line 3272 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      AddNewTxCanidate(&CurrentTxCandidateList, (yyvsp[(1) - (1)].string), (double)UNSPECIFIED_PERCENTAGE );
	  #endif

  	  ALLOC_AND_RETURN_STRING("\t- EQUAL PROBA : %s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 176:
#line 3281 "bison_grammar.y"
    {
          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      AddNewTxCanidate(&CurrentTxCandidateList, (yyvsp[(1) - (3)].string), (double)atoi((yyvsp[(2) - (3)].string)) );
	  #endif

  	  ALLOC_AND_RETURN_STRING("\t- %f PROBA : %s",atoi((yyvsp[(2) - (3)].string))/(float)100,(yyvsp[(1) - (3)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 177:
#line 3290 "bison_grammar.y"
    {

          #ifdef NO_THREAD_INTERMEDIATE_REPRESENTATION
	      AddNewTxCanidate(&CurrentTxCandidateList, (yyvsp[(1) - (3)].string), atof((yyvsp[(2) - (3)].string)) );
	  #endif

	   ALLOC_AND_RETURN_STRING("\t- %.12f PROBA : %s",atof((yyvsp[(2) - (3)].string))/(double)100,(yyvsp[(1) - (3)].string));
	   FREE_RULE_STRINGS(1);


       ;}
    break;

  case 178:
#line 3307 "bison_grammar.y"
    {
     ;}
    break;

  case 179:
#line 3311 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     SCHEDULES Section\n"
			     "-----------------------------------------------------------------------------\n" );
	   ScheduleNo=0;
       ;}
    break;

  case 182:
#line 3326 "bison_grammar.y"
    {

	  Extend_DynamicArray(&Dyn_ScheduleList,sizeof(Schedule));
	  unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_ScheduleList) - 1;
	  Schedule* CurrentSchedule = (Schedule*) GetElement_DynamicArray(&Dyn_ScheduleList, LastAddedElementPos, sizeof(Schedule));

	  CurrentSchedule -> Name     = dupstr((yyvsp[(1) - (3)].string));
	  CurrentSchedule -> Schedule = (ScheduleElement*)MakeStaticCopy_DynamicArray(&Dyn_Schedule, sizeof(ScheduleElement));
	  CurrentSchedule -> ScheduleLength = GetSize_DynamicArray(&Dyn_Schedule);
	  ScheduleNum++;
	  Clear_DynamicArray(&Dyn_Schedule);


	  REPORT_READ_INPUT("Sched[%u]: (%s)\n\t%s\n",ScheduleNo,(yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));
	  ScheduleNo++;
      ;}
    break;

  case 183:
#line 3347 "bison_grammar.y"
    {
  	  ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	  FREE_RULE_STRINGS(1);
      ;}
    break;

  case 184:
#line 3352 "bison_grammar.y"
    {
  	  ALLOC_AND_RETURN_STRING("%s,%s",(yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 185:
#line 3361 "bison_grammar.y"
    {

	   Extend_DynamicArray(&Dyn_Schedule,sizeof(ScheduleElement));
	   unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_Schedule) - 1;
	   ScheduleElement* SchedElement = (ScheduleElement*) GetElement_DynamicArray(&Dyn_Schedule, LastAddedElementPos, sizeof(ScheduleElement));

	   unsigned FoundTxNo = FindTxByName((yyvsp[(1) - (1)].string), TxDefArray, TxDefNum);
	   if(FoundTxNo == TxDefNum )
	   {
       	       REPORT_SEMANTIC_ERROR("UNKNOWN Transaction Name %s in schedule\n",(yyvsp[(1) - (1)].string));
	   }
	   else
	   {
	       SchedElement->ThreadID = FoundTxNo;
	       SchedElement->TxID     = 0;
	       SchedElement-> LabelTxOpContainerNo = TxDefArray[FoundTxNo].TxOpNum[0];

	       SchedElement-> Assertion = FALSE;
	       SchedElement-> AssertionExprID = 0;
	       SchedElement -> VarAssignList = NULL;
	       SchedElement -> VarAssignNum  = 0;

	   }

	   ALLOC_AND_RETURN_STRING("%s",(yyvsp[(1) - (1)].string));
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 186:
#line 3389 "bison_grammar.y"
    {

	   Extend_DynamicArray(&Dyn_Schedule,sizeof(ScheduleElement));
	   unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_Schedule) - 1;
	   ScheduleElement* SchedElement = (ScheduleElement*) GetElement_DynamicArray(&Dyn_Schedule, LastAddedElementPos, sizeof(ScheduleElement));

	   unsigned FoundTxNo = FindTxByName((yyvsp[(1) - (2)].string), TxDefArray, TxDefNum);
	   if(FoundTxNo == TxDefNum )
	   {
       	       REPORT_SEMANTIC_ERROR("UNKNOWN Transaction Name %s in schedule\n",(yyvsp[(1) - (2)].string));
	   }
	   else
	   {
	       SchedElement->ThreadID = FoundTxNo;
	       SchedElement->TxID     = 0;


	       char* LabelStringToMatch = &((yyvsp[(2) - (2)].string)[1]);
	       unsigned TxOpNo;
	       unsigned FoundTxOpNo= TxDefArray[FoundTxNo].TxOpNum[0];
	       for(TxOpNo=0; TxOpNo< TxDefArray[FoundTxNo].TxOpNum[0]; TxOpNo++)
	       {
		   TxOpContainer_t* CurrentTxOpContainer = &(TxDefArray[FoundTxNo].TxOpList[0][TxOpNo]);
		   if(  CurrentTxOpContainer -> TxOperation == LABEL_OP )
		   {
		       bool LabelFound = (strcmp(LabelStringToMatch, CurrentTxOpContainer -> Label ) == 0);
		       if(LabelFound)
		       {
			   FoundTxOpNo = TxOpNo;
			   break;
		       }
		   }
	       }
	       if( FoundTxOpNo == TxDefArray[FoundTxNo].TxOpNum[0] )
	       {
		   REPORT_SEMANTIC_ERROR("Label %s could not be found in Transaction %s (for generating schedule)\n",LabelStringToMatch,(yyvsp[(1) - (2)].string));
	       }

	       SchedElement-> LabelTxOpContainerNo = FoundTxOpNo;

	       SchedElement-> Assertion = FALSE;
	       SchedElement-> AssertionExprID = 0;
	       SchedElement -> VarAssignList = NULL;
	       SchedElement -> VarAssignNum  = 0;

	   }

	   ALLOC_AND_RETURN_STRING("%s%s",(yyvsp[(1) - (2)].string),(yyvsp[(2) - (2)].string));
	   FREE_RULE_STRINGS(1);
       ;}
    break;

  case 187:
#line 3440 "bison_grammar.y"
    {
	  char* AssertionExpressionString = (yyvsp[(2) - (3)].string);

	    VarExpr* CurrentAssertionExpr;
	    unsigned AssertionExprID = FindVarExpr(AssertionExpressionString, &CurrentAssertionExpr);

	    bool Found= (CurrentAssertionExpr != NULL);
	    if( !Found )
	    {
		char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		sprintf(ErrorMessage,"UNKNOWN CONDITIONAL EXPRESSION '%s' is encountered in Schedule definition. Terminating...\n",AssertionExpressionString);
		yyerror(ErrorMessage);
		free(ErrorMessage);
		assert(0);
	    }


	   Extend_DynamicArray(&Dyn_Schedule,sizeof(ScheduleElement));
	   unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_Schedule) - 1;
	   ScheduleElement* SchedElement = (ScheduleElement*) GetElement_DynamicArray(&Dyn_Schedule, LastAddedElementPos, sizeof(ScheduleElement));


	   SchedElement-> Assertion = TRUE;
	   SchedElement-> AssertionExprID = AssertionExprID ;
	   SchedElement -> VarAssignList = NULL;
	   SchedElement -> VarAssignNum  = 0;

	   SchedElement->ThreadID = 0;
	   SchedElement->TxID     = 0;
	   SchedElement-> LabelTxOpContainerNo = 0;

	  ALLOC_AND_RETURN_STRING("%s%s%s",(yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].string),(yyvsp[(3) - (3)].string));
	  FREE_RULE_STRINGS(3);
      ;}
    break;

  case 188:
#line 3475 "bison_grammar.y"
    {

	  Extend_DynamicArray(&Dyn_Schedule,sizeof(ScheduleElement));
	  unsigned LastAddedElementPos = GetSize_DynamicArray(&Dyn_Schedule) - 1;
	  ScheduleElement* SchedElement = (ScheduleElement*) GetElement_DynamicArray(&Dyn_Schedule, LastAddedElementPos, sizeof(ScheduleElement));

	  SchedElement -> VarAssignNum  = GetSize_DynamicArray(&Dyn_VarAssignList);
	  SchedElement -> VarAssignList = MakeStaticCopy_DynamicArray(&Dyn_VarAssignList, sizeof(var_assign_t));

	  SchedElement-> Assertion = FALSE;
	  SchedElement-> AssertionExprID = 0 ;
	  SchedElement->ThreadID = 0;
	  SchedElement->TxID     = 0;
	  SchedElement-> LabelTxOpContainerNo = 0;

	  Clear_DynamicArray(&Dyn_VarAssignList);
      ;}
    break;

  case 189:
#line 3499 "bison_grammar.y"
    {
     ;}
    break;

  case 190:
#line 3504 "bison_grammar.y"
    {
	   REPORT_READ_INPUT("\n\n-----------------------------------------------------------------------------\n"
			     "     INVARIANTS Section\n"
			     "-----------------------------------------------------------------------------\n" );
       ;}
    break;

  case 191:
#line 3514 "bison_grammar.y"
    {
	 REPORT_READ_INPUT("Invariant[%u]: %s\n",InvariantNo,(yyvsp[(1) - (2)].string));
	 InvariantNo++;
     ;}
    break;

  case 192:
#line 3519 "bison_grammar.y"
    {
	 REPORT_READ_INPUT("Invariant[%u]: %s\n",InvariantNo,(yyvsp[(2) - (3)].string));
	 InvariantNo++;
     ;}
    break;

  case 193:
#line 3527 "bison_grammar.y"
    {
	  NoAbortInSchedule = TRUE;
      ;}
    break;

  case 194:
#line 3531 "bison_grammar.y"
    {
	  char* InvariantExpressionString = (yyvsp[(2) - (3)].string);

	    VarExpr* CurrentInvariantExpr;
	    unsigned InvariantExprID = FindVarExpr(InvariantExpressionString, &CurrentInvariantExpr);

	    bool Found= (CurrentInvariantExpr != NULL);
	    if( !Found )
	    {
		char* ErrorMessage = malloc(sizeof(char)*MAX_RETURN_STRING_SIZE);
		sprintf(ErrorMessage,"UNKNOWN CONDITIONAL EXPRESSION '%s' is encountered in STM_LOAD access. Terminating...\n",InvariantExpressionString);
		yyerror(ErrorMessage);
		free(ErrorMessage);
		assert(0);
	    }

	    Extend_DynamicArray(&Dyn_InvariantArray,sizeof(Invariant));
	    unsigned LastAddedInvariantPos = GetSize_DynamicArray(&Dyn_InvariantArray) - 1;
	    Invariant* CurrentInvariant = GetElement_DynamicArray(&Dyn_InvariantArray, LastAddedInvariantPos, sizeof(Invariant));

	    unsigned CondExprStringLength = strlen((yyvsp[(1) - (3)].string)) +  strlen(InvariantExpressionString) + strlen((yyvsp[(3) - (3)].string)) +1 ;
	    CurrentInvariant -> Name = (char*)malloc(CondExprStringLength*sizeof(char));
	    sprintf(CurrentInvariant -> Name,"%s%s%s",(yyvsp[(1) - (3)].string), InvariantExpressionString, (yyvsp[(3) - (3)].string));
	    CurrentInvariant -> VarExprID = InvariantExprID;

	    InvariantNum++;


	    (yyval.string) = dupstr(CurrentInvariant -> Name);

//	  ALLOC_AND_RETURN_STRING("%s%s%s",$1,$2,$3);
	  FREE_RULE_STRINGS(3);
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 5477 "grammar.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 3565 "bison_grammar.y"










