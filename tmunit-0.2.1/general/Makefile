CC ?= gcc
CFLAGS += -g
CFLAGS += -Wall -Wno-unused-function -fno-strict-aliasing -D_REENTRANT


   ifeq ($(STM),RSTM)
	CFLAGS += -m32 -fpermissive
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
	general.c \
	dynamic_array.c

OBJ = $(patsubst %.c,%.o,$(SRC))

#%.o: %.c
#	$(CC) $(CFLAGS) -c  $< 

all: librng $(OBJ)

librng:
	$(MAKE) -C rng 

#dyn_arr_test: Generates the binary test that tests the DynamicArray data structure
tests:  
	$(MAKE) -C  test
	$(MAKE) -C  test clean

clean:
	rm -f *.o *~
	$(MAKE) -C  rng clean