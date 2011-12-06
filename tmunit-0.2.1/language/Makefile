
CC ?= gcc
BISON ?= bison
FLEX ?= flex
DOCGEN ?= doxygen

ifeq ($(DEFINES),COMPILE_FOR_TEST)
TESTING_FLAGS=-DSUPPRESS_ASSERT_BEHAVIOUR  -DCOMPILE_FOR_TEST
endif

ifeq ($(STAT_TEST), TRUE) 
TESTING_FLAGS += -DSTATISTICS_TEST
endif

ifeq ($(VERIFY_ABORT_NUM), TRUE) 
TESTING_FLAGS += -DMATCH_STM_ABORT_NUM
endif



ifdef  STM
   ifeq ($(STM),NO_STM)
	STM_FLAGS =
   endif	
   ifeq ($(STM),TINY_ETL)
	STM_TYPE = TINY_STM_NEW
	STM_FLAGS = -D$(STM_TYPE) -I$(STM_HOME)/include  -I$(LIBAO_HOME)/include  

   endif	
   ifeq ($(STM),TINY_CTL)
	STM_TYPE = TINY_STM_NEW
	STM_FLAGS = -D$(STM_TYPE) -I$(STM_HOME)/include -I$(LIBAO_HOME)/include  
   endif	
   ifeq ($(STM),TINY_WT)
	STM_TYPE = TINY_STM_NEW
	STM_FLAGS = -D$(STM_TYPE) -I$(STM_HOME)/include -I$(LIBAO_HOME)/include  
   endif	
   ifeq ($(STM),NEXTGEN)
	STM_TYPE = TINY_STM_NEW
	STM_FLAGS += -D$(STM_TYPE) -I$(STM_HOME)/include -I$(LIBAO_HOME)/include 
   endif	
   ifeq ($(STM),TL2)
	STM_FLAGS = -D$(STM) -I$(STM_HOME) -I$(LIBAO_HOME)/include
   endif	
   ifeq ($(STM),RSTM)
	STM_FLAGS += -D$(STM) -I$(STM_HOME)  -I$(STM_HOME)/..  -I$(LIBAO_HOME)/include  -fpermissive -m32
	CC = g++
   endif	
   ifeq ($(STM),SWISS_TM)
	STM_FLAGS += -D$(STM) -I$(STM_HOME)/src/stm  -I$(STM_HOME)/include  -I$(LIBAO_HOME)/include  -fpermissive -m32
 	CC = g++
   endif	
   ifeq ($(STM),WSTM)
	STM_FLAGS += -m32 -D$(STM) -DENV_IA32 -I$(STM_HOME)/../include  -I$(STM_HOME)  
   endif	

   ifeq ($(STM),ENNALS)
	STM_FLAGS += -m32 -DINTEL -D$(STM) -I$(STM_HOME)  
   endif	


else
	STM = TINY_STM_NEW
	STM_HOME = $(TINY_STM_0_9_5_HOME)
	STM_FLAGS = -D$(STM) -I$(STM_HOME)/include
endif



# CFLAGS += -O3 -DNDEBUG
CFLAGS += -g
CFLAGS += -Wall -Wno-unused-function -fno-strict-aliasing -D_REENTRANT
CFLAGS += -I../general -I../general/rng -I../execution 
CFLAGS += -DNO_THREAD_INTERMEDIATE_REPRESENTATION 
CFLAGS += -DNO_TRANSACTION_INTERMEDIATE_REPRESENTATION 
CFLAGS += $(TESTING_FLAGS)
CFLAGS += $(STM_FLAGS)

LIB += -lfl

BFLAGS = -d -t -v
FFLAGS = -I

SRC = \
	syntax_error.c \
	syntax_debug.c \
	simulation_parameters.c \
	intermediate_representation.c \
	thread_execution_structure_generator.c \
	transaction_execution_structure_generator.c \
	schedule_execution_structure_generator.c \
	invariant_execution_structure_generator.c \
	txdef.c \
	tx_op_container.c \
	variable_expression.c

GENERATED_SRC= \
	grammar.c \
	parser.c  

OBJ = $(patsubst %.c,%.o,$(SRC))
GENERATED_OBJ = $(patsubst %.c,%.o,$(GENERATED_SRC))


   ifeq ($(STM),NO_STM)
	STM = NO_STM
	CFLAGS += -D$(STM)
   endif	
   ifeq ($(STM),TINY_STM_NEW)
	STM = TINY_STM_NEW
	CFLAGS += -D$(STM) -I$(STM_HOME)/include 
   endif	



all:  $(GENERATED_OBJ)  $(OBJ) 

$(GENERATED_OBJ): $(GENERATED_SRC)

grammar.c:	bison_grammar.y
	$(BISON) $(BFLAGS) -o $@ $<

parser.c:	flex_parser.l grammar.c
	$(FLEX) $(FFLAGS) -o $@ $<

clean:
	rm -f  *.o
	rm -f  grammar.*  
	rm -f  parser.c
	rm -f  *~ 

