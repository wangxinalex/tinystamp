# ==============================================================================
#
# Defines.common.mk
#
# ==============================================================================


CC       := gcc
CFLAGS   += -Wall -pthread
CFLAGS   += -O3
CFLAGS   += -ggdb3
CFLAGS   += -DNDEBUG
CFLAGS   += -DOTHERTHREADBARRIER
CFLAGS   += -DDYNAMC_THREAD_MANAGEMENT
CFLAGS   += -march=native
CFLAGS   += -pipe
CFLAGS   += -I$(LIB)
CPP      := g++
CPPFLAGS += $(CFLAGS)
LD       := g++
LIBS     += -lpthread

# Remove these files when doing clean
OUTPUT +=

LIB := ../lib

STM := ../../tinySTM

LOSTM := ../../OpenTM/lostm


# ==============================================================================
#
# End of Defines.common.mk
#
# ==============================================================================
