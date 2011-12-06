CC ?= gcc

ifeq ($(DEFINES),COMPILE_FOR_TEST)
TESTING_FLAGS=-DSUPPRESS_ASSERT_BEHAVIOUR  -DCOMPILE_FOR_TEST
endif

CFLAGS += -g
CFLAGS += -Wall -Wno-unused-function -fno-strict-aliasing -D_REENTRANT
CFLAGS += -I../language  -I../general  -I../general/rng -I../execution
CFLAGS += -DNO_THREAD_INTERMEDIATE_REPRESENTATION 
CFLAGS += -DNO_TRANSACTION_INTERMEDIATE_REPRESENTATION 
CFLAGS += $(TESTING_FLAGS)
CFLAGS += $(PATH_DEFINES)


   ifeq ($(STM),RSTM)
	CFLAGS +=  -m32 -fpermissive
	CC = g++
   endif	
   ifeq ($(STM),SWISS_TM)
	CFLAGS +=  -m32 -fpermissive 
 	CC = g++
   endif	
   ifeq ($(STM),WSTM)
	CFLAGS += -m32 
   endif	
   ifeq ($(STM),ENNALS)
	CFLAGS += -m32 
   endif	



SRC = \
	generate_files.c 

OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(OBJ)

clean:
	rm -f *.o *~