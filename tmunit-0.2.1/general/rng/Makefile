
CC = gcc
AR = ar
CFLAGS = -Wall 

ifeq ($(DEFINES),VERBOSE)
RNG_FLAG +=-DVERBOSE 
endif

   ifeq ($(STM),RSTM)
	CFLAGS += -m32 -fpermissive
	CC = g++
   endif	
   ifeq ($(STM),SWISS_TM)
	CFLAGS +=  -m32 -fpermissive 
 	CC = g++
   endif	
   ifeq ($(STM),WSTM)
	CFLAGS +=  -m32 
   endif	


all: clean librng.a randgen

rng.o:
	$(CC) -c $(CFLAGS) $(RNG_FLAG)  rng.c 


librng.a: rng.o
	$(AR) cru $@ $^
 
randgen: librng.a
	$(CC) $(CFLAGS) -L.  randgen.c -lrng -o test_randgen
	$(CC) $(CFLAGS)  system_randgen.c    -o system_randgen


verbose: 
	$(MAKE) clean
	$(MAKE) -C . DEFINES=VERBOSE


clean:
	rm -rf rng.o librng.a  randgen
	rm -f *~
