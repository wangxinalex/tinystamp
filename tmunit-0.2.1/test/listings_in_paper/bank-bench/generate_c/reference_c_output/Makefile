include ../environment.include


DEFAULT_STM = TINY_STM_NEW

ifdef  STM
   ifeq ($(STM),NO_STM)
	STM = NO_STM
   endif	
   ifeq ($(STM),TINY_STM_NEW)
	STM = $(DEFAULT_STM)
	STM_HOME = $(TINY_STM_0_9_5_HOME)
	STM_C_INCLUDE = -I$(STM_HOME)/include
	STM_LIB_INCLUDE = -L$(STM_HOME)/lib
	STM_LIB_NAME = -lstm
   endif	
   ifeq ($(STM),TINY_ETL)
	STM = $(DEFAULT_STM)
	STM_TYPE = TINY_STM_NEW
	STM_HOME = $(TINY_STM_0_9_5_HOME)
	STM_C_INCLUDE =  -D$(STM_TYPE) -I$(STM_HOME)/include
	STM_LIB_INCLUDE = -L$(STM_HOME)/lib
	STM_LIB_NAME = -lstm_ETL_64b
   endif	
   ifeq ($(STM),TINY_CTL)
	STM = $(DEFAULT_STM)
	STM_TYPE = TINY_STM_NEW
	STM_HOME =  $(TINY_STM_0_9_5_HOME)
	STM_C_INCLUDE = -D$(STM_TYPE) -I$(STM_HOME)/include
	STM_LIB_INCLUDE = -L$(STM_HOME)/lib
	STM_LIB_NAME = -lstm_CTL_64b
   endif	
   ifeq ($(STM),TINY_WT)
	STM = $(DEFAULT_STM)
	STM_TYPE = TINY_STM_NEW
	STM_HOME =  $(TINY_STM_0_9_5_HOME)
	STM_C_INCLUDE = -D$(STM_TYPE) -I$(STM_HOME)/include
	STM_LIB_INCLUDE = -L$(STM_HOME)/lib
	STM_LIB_NAME = -lstm_WT_64b
   endif	
   ifeq ($(STM),TL2)
	STM_HOME = $(TL2_HOME)
	STM_C_INCLUDE = -I$(STM_HOME)
	STM_LIB_INCLUDE = -L$(STM_HOME)
	STM_LIB_NAME = -ltl2
   endif
   ifeq ($(STM),SWISS_TM)
	STM_HOME = $(SWISS_TM_HOME)
	CC       = g++
	override ARCH     := 32b
	CFLAGS += -D$(STM) -I$(STM_HOME)/src/stm  -I$(STM_HOME)/include  -I$(LIBAO_HOME)/include  -fpermissive 
	STM_LIB_INCLUDE = -L$(STM_HOME)/lib -L$(LIBAO_HOME)/../libatomic_32b/lib
	STM_LIB_NAME += -lwlpdstm
   endif	
   ifeq ($(STM),RSTM)
	STM_HOME = $(RSTM_HOME)
	CC       = g++
	override ARCH     := 32b
	CFLAGS += -D$(STM)  -I$(STM_HOME) -I$(STM_HOME)/.. -fpermissive
	STM_LIB_INCLUDE = -L$(STM_HOME)/obj -L$(LIBAO_HOME)/../libatomic_32b/lib
	STM_LIB_NAME += -lstm
   endif	

else
	STM = $(DEFAULT_STM)
	STM_HOME = $(TINY_STM_0_9_5_HOME)
	STM_C_INCLUDE = -I$(STM_HOME)/include
	LFLAGS += -L$(STM_HOME)/lib
	STM_LIB_INCLUDE = -L$(STM_HOME)/lib
	STM_LIB_NAME = -lstm
endif


ifeq ($(DEFINES),COMPILE_FOR_TEST)
	RNG = test_rng
	RNG_LIB = -lrng
	RNG_INCLUDE = -I../general/rng
	RNG_LIB_INCLUDE = -L../general/rng
	CFLAGS += -DCOMPILE_FOR_TEST
else
	RNG = system_rng
	RNG_LIB = 
	RNG_INCLUDE =
	RNG_LIB_INCLUDE = 
endif


ifeq ($(TRACE),ENABLE)
	CFLAGS += -DENABLE_TRACE_CODE
endif


ifdef ARCH
ifeq ($(ARCH),32b)
	CFLAGS += -m32
	LFLAGS += -m32
	LIBAO_LIB_INCLUDE = -L$(LIBAO_32b_HOME)/lib
endif
ifeq ($(ARCH),64b)
	CFLAGS += -m64
	LFLAGS += -m64
	LIBAO_LIB_INCLUDE = -L$(LIBAO_HOME)/lib
endif
else
	LIBAO_LIB_INCLUDE = -L$(LIBAO_HOME)/lib
endif

ifdef LIB
	STM_LIB_NAME = -$(LIB)
endif



CC ?= gcc

#CFLAGS += -D_GNU_SOURCE
# CFLAGS += -g
CFLAGS += -O3 -DNDEBUG
CFLAGS += -I$(LIBAO_HOME)/include $(STM_C_INCLUDE) -I../execution $(RNG_INCLUDE) -D$(STM)

LFLAGS +=  $(STM_LIB_INCLUDE) $(LIBAO_LIB_INCLUDE) -L$(LIBAO_HOME)/lib  $(RNG_LIB_INCLUDE)  $(STM_LIB_NAME) -latomic_ops -lpthread $(RNG_LIB)

SRC = \
	simulation_parameters.c \
	shared_var_definitions.c \
	barrier.c         \
	initialization.c  \
	cli.c             \
	random.c 	  \
	threads.c 	  \
	transactions.c 	  \
	main.c

OBJ = $(patsubst %.c,%.o,$(SRC))

benchrun:	$(OBJ)  
	$(CC) -o $@ $^ $(LFLAGS)

%.o:	%.c $(RNG)
	$(CC) $(CFLAGS) -c -o $@ $<

test_rng:
	cp ../general/rng/test_rng_interface.h  rng_interface.h

system_rng:
	cp ../general/rng/system_rng_interface.h  rng_interface.h


clean:
	rm -f benchrun *.o 
