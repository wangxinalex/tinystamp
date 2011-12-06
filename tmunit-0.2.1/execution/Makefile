# LIBAO_HOME := /local_home/harmanci/Codes/RunDir/libatomic

CC ?= gcc

ifeq ($(DEFINES),COMPILE_FOR_TEST)
TESTING_FLAGS=-DSUPPRESS_ASSERT_BEHAVIOUR  -DCOMPILE_FOR_TEST
endif

ifeq ($(STAT_TEST), TRUE) 
TESTING_FLAGS += -DSTATISTICS_TEST
endif


ifeq ($(VERIFY_ABORT_NUM), TRUE) 
TESTING_FLAGS += -DMATCH_STM_ABORT_NUM
endif


CFLAGS += -g
CFLAGS += -Wall -Wno-unused-function -fno-strict-aliasing -D_REENTRANT
CFLAGS += -I../language  -I../general  -I../general/rng -I../code_generation -I.
CFLAGS += -I$(LIBAO_HOME)/include
CFLAGS += -DNO_THREAD_INTERMEDIATE_REPRESENTATION 
CFLAGS += -DNO_TRANSACTION_INTERMEDIATE_REPRESENTATION 
CFLAGS += $(TESTING_FLAGS)
CFLAGS += $(PATH_DEFINES)


   ifeq ($(STM),NO_STM)
	STM = NO_STM
	CFLAGS += -D$(STM)
   endif	
   ifeq ($(STM),TINY_ETL)
	STM_TYPE = TINY_STM_NEW
	CFLAGS += -D$(STM_TYPE) -I$(STM_HOME)/include 
   endif	
   ifeq ($(STM),TINY_CTL)
	STM_TYPE = TINY_STM_NEW
	CFLAGS += -D$(STM_TYPE) -I$(STM_HOME)/include 
   endif	
   ifeq ($(STM),TINY_WT)
	STM_TYPE = TINY_STM_NEW
	CFLAGS += -D$(STM_TYPE) -I$(STM_HOME)/include 
   endif	
   ifeq ($(STM),NEXTGEN)
	STM_TYPE = TINY_STM_NEW
	CFLAGS += -D$(STM_TYPE) -I$(STM_HOME)/include 
   endif	
   ifeq ($(STM),TL2)
	STM = TL2
	CFLAGS += -D$(STM) -I$(STM_HOME) 
   endif	
   ifeq ($(STM),RSTM)
	STM = RSTM
	CFLAGS += -D$(STM) -I$(STM_HOME) -I$(STM_HOME)/.. -fpermissive -m32
	CC = g++
   endif	
   ifeq ($(STM),SWISS_TM)
	CFLAGS += -D$(STM) -I$(STM_HOME)/src/stm  -I$(STM_HOME)/include  -I$(LIBAO_HOME)/include  -fpermissive -m32
 	CC = g++
   endif	
   ifeq ($(STM),WSTM)
	CFLAGS += -m32 -D$(STM) -DENV_IA32 -I$(STM_HOME)/../include  -I$(STM_HOME)  
   endif	
   ifeq ($(STM),ENNALS)
	STM = ENNALS
	CFLAGS += -m32 -DINTEL -D$(STM) -I$(STM_HOME) 
   endif	


SRC = \
	tmunit.c \
	thread.c \
	user_interface_console.c

OBJ = $(patsubst %.c,%.o,$(SRC))

#%.o: %.c
#	$(CC) $(CFLAGS) -c  $< 

all: $(OBJ)

clean:
	rm -f *.o *~