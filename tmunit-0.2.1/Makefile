include environment.include


CC ?= gcc
LIB += -lfl  -lpthread
LFLAGS +=   -L$(LIBAO_HOME)/lib  

ifeq ($(DEFINES),COMPILE_FOR_TEST)
LFLAGS +=  -Lgeneral/rng
#ifeq ($(STM),RSTM)
#	LIB += -lrng++_32b
#else
#	LIB += -lrng
#endif
	LIB += -lrng
endif

ifeq ($(STATISTICS_TEST),YES) 
  STAT_TEST = TRUE
endif


ifeq ($(MATCH_STM_ABORT_NUM),YES) 
  VERIFY_ABORT_NUM = TRUE
endif


DEFAULT_STM = TINY_ETL

ifdef  STM
   ifeq ($(STM),NO_STM)
	STM = NO_STM
   endif	
   ifeq ($(STM),TINY_ETL)
	STM_HOME = $(TINY_STM_0_9_5_HOME)
	LFLAGS += -L$(STM_HOME)/lib 
#	LIB    += -latomic_ops -lstm_ETL_64b 
	LIB    += -latomic_ops -lstm 
   endif	
   ifeq ($(STM),TINY_CTL)
	STM_HOME = $(TINY_STM_0_9_5_HOME)
	LFLAGS += -L$(STM_HOME)/lib 
	LIB    += -latomic_ops -lstm_CTL_64b 
   endif	
   ifeq ($(STM),TINY_WT)
	STM_HOME = $(TINY_STM_0_9_5_HOME)
	LFLAGS += -L$(STM_HOME)/lib 
	LIB    += -latomic_ops -lstm_WT_64b 
   endif	
   ifeq ($(STM),TL2)
	STM_HOME = $(TL2_HOME)
	LFLAGS += -L$(STM_HOME)
	LIB    += -latomic_ops -ltl2
   endif	
   ifeq ($(STM),SWISS_TM)
	STM_HOME = $(SWISS_TM_HOME)
 	LFLAGS += -m32 -latomic_ops -L$(STM_HOME)/lib -L$(LIBAO_HOME)/../libatomic_32b/lib
 	LIB    += -lwlpdstm
 	CC = g++
   endif	
   ifeq ($(STM),RSTM)
	STM_HOME = $(RSTM_HOME)
	LFLAGS += -m32 -L$(STM_HOME)/obj
	LIB    += -lstm
	CC = g++
   endif	
   ifeq ($(STM),WSTM)
	STM_HOME = $(WSTM_HOME)
	LFLAGS += -m32 -L$(STM_HOME)
	LIB    += -lstm
   endif	


else
  	STM = $(DEFAULT_STM)
	STM_HOME = $(TINY_STM_0_9_5_HOME)
	LFLAGS += -L$(STM_HOME)/lib
	LIB    += -lstm
endif

PATH_DEFINES  = -DENV_SRC_DIR_PATH="$(SRC_DIR_PATH)"
PATH_DEFINES += -DENV_PREPROCESSOR_SCRIPT_PATH="$(PREPROCESSOR_SCRIPT_PATH)" 
PATH_DEFINES += -DENV_POST_PATMAP_SCRIPT_PATH="$(POST_PATMAP_SCRIPT_PATH)"
PATH_DEFINES += -DENV_GENERATED_C_OUTPUT_PATH="$(GENERATED_C_OUTPUT_PATH)"
PATH_DEFINES += -DENV_INTERMEDIATE_GENERATED_C_OUTPUT_PATH="$(INTERMEDIATE_GENERATED_C_OUTPUT_PATH)"


export STM
export STM_HOME
export LIBAO_HOME
export PATH_DEFINES
export STAT_TEST
export VERIFY_ABORT_NUM

VPATH := language


#ALL_OBJS := $(patsubst %.c,%.o,$(wildcard language/*.c))
CREATED_OBJS := language/grammar.o language/parser.o
ALL_OBJS := $(CREATED_OBJS) $(filter-out $(CREATED_OBJS), $(patsubst %.c,%.o,$(wildcard language/*.c))  )
ALL_OBJS += $(patsubst %.c,%.o,$(wildcard execution/*.c))
ALL_OBJS += $(patsubst %.c,%.o,$(wildcard general/*.c))
ALL_OBJS += $(patsubst %.c,%.o,$(wildcard code_generation/*.c))

ifdef DIR
	StartDir=$(DIR)
else	
	StartDir=.
endif	



tmunit: lang exec gnrl  codegen
#	$(MAKE) -C * 
	$(CC)  $(LFLAGS) -o $@  $(ALL_OBJS)  $(LIB)

lang: 
	$(MAKE) -C language 

exec:
	$(MAKE) -C execution

codegen:
	$(MAKE) -C code_generation

gnrl: 
	$(MAKE) -C general 


cgen:
ifeq ($(CONFIG),)
	@echo  ""
	@echo  "CONFIG variable not defined." 
	@echo  "Please add CONFIG=<name of configuration file> to your 'make' command"
	@echo  ""
else
ifeq ($(STM),$(DEFAULT_STM))
	@echo  ""
	@echo  ""
	@echo  "********************************************************"
	@echo  ""
	@echo  "Assuming $(DEFAULT_STM) as desired STM". 
	@echo  "If you like to compile for another STM,"
	@echo  "add STM=<name of desired STM> to your 'make' command"
	@echo  ""
	@echo  "********************************************************"
	@echo  ""
	@echo  ""
endif
	if [ ! -f tmunit ]; \
	then \
	 $(MAKE) -C . STM=TINY_ETL ;  \
	fi
	./tmunit $(C_GEN_OP)  -g   $(CONFIG) 
	$(MAKE) -C c_output STM=$(STM) ARCH=$(ARCH) LIB=$(STMLIB) 
	rm -f benchrun
	ln -s c_output/benchrun
endif




semtests:
	$(MAKE) -C semantic_test_suite

tests:
	@echo "-------------------------------------------------"
	@echo "     Cleaning and recompiling for tests"
	@echo "-------------------------------------------------"
	@echo ""
	
	$(MAKE) -C . clean > test_compilation
	$(MAKE) -C . DEFINES=COMPILE_FOR_TEST >> test_compilation
	

	@echo ""
	@echo "-------------------------------------------------"
	@echo "     Executing tests"
	@echo "-------------------------------------------------"
	@echo ""

	$(MAKE) -C test  -s  DIR=$(StartDir) 

	@echo ""
	@echo ""
	@echo "-------------------------------------------------"
	@echo "     Cleaning and recompiling for simulations"
	@echo "-------------------------------------------------"
	@echo ""

	$(MAKE) -C . clean > compilation.log
	$(MAKE) -C . >> compilation.log

	@echo ""


test_mode:
	$(MAKE) -C . clean
	$(MAKE) DEFINES=COMPILE_FOR_TEST


con-tests: 
	make tests DIR=development_tests/console_ui

clean:
	$(MAKE) -C language clean
	$(MAKE) -C execution clean
	$(MAKE) -C general clean
	$(MAKE) -C code_generation clean
	rm -rf  *~
	rm -f tmunit
	rm -f test_compilation
