#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Makefile for the MSP432 or HOST build system
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      <FILE>.i 	- Builds <FILE>.i preprocessed file
#      <FILE>.asm 	- Builds <FILE>.asm assembly file
#      <FILE>.o 	- Builds <FILE>.o object file
#      compile-all 	- Compiles all object files, but do not link
#      build 		- Compile and link all into a final executable c1m4.out
#      all 		- Same as build
#      c1m4.out		- Same as build
#      clean 		- Removes all generated files (*.map, *.out, *.o, *.asm, *.i, *.dep)
#
# Platform Overrides:
#      PLATFORM		- HOST or MPS432, deafult is HOST
#	   VERBOSE - YES or NO, default is YES
#
#------------------------------------------------------------------------------
include sources.mk

# Platform Overrides
PLATFORM = HOST
VERBOSE = YES

TARGET = c1m4

ifeq ($(VERBOSE), YES)
	VERBOSE_FLAG = -DVERBOSE	
endif


ifeq ($(PLATFORM), MSP432)
	# Architectures Specific Flags
	LINKER_FILE = -T msp432p401r.lds

	ARCH_SPEC =-mcpu=cortex-m4 \
	           -mthumb \
	           -march=armv7e-m \
	           -mfloat-abi=hard \
	           -mfpu=fpv4-sp-d16 \
	           --specs=nosys.specs
	      
	TARGET_PLATF = -DMSP432
	
	# Compiler Flags and Defines
	CC = arm-none-eabi-gcc
	LD = arm-none-eabi-ld
else
	# Architectures Specific Flags
	LINKER_FILE = #no linker file for host

	ARCH_SPEC = #no architecture-specific flags for host
	      
	TARGET_PLATF = -DHOST
	
	# Compiler Flags and Defines
	CC = gcc
	LD = ld
endif

LDFLAGS = -Wl,-Map=$(TARGET).map $(LINKER_FILE)
CFLAGS = -Wall -g -O0 -std=c99 $(ARCH_SPEC)
CPPFLAGS = $(INCLUDES) $(TARGET_PLATF) $(VERBOSE_FLAG) -DCOURSE1
#DEPFLAGS = -MM -MP -MF $(basename $@).dep
DEPFLAGS = -MM -MP 


OBJS = $(SOURCES:.c=.o)
ASMS = $(SOURCES:.c=.asm)
PREPS=$(SOURCES:.c=.i)
DEPS=$(SOURCES:.c=.dep)


# Create preprocessed files
%.dep : %.c
	$(CC) $< $(CPPFLAGS) $(DEPFLAGS) -MF $@

%.i : %.c
	$(CC) -E $< $(CPPFLAGS) -o $@
	
# Create assemly files
%.asm : %.c
	$(CC) -S $< $(CPPFLAGS) $(CFLAGS) -o $@

# Create object files
%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
#$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Full build

.PHONY: compile-all
compile-all: $(SOURCES)
	$(CC) -c $^ $(CPPFLAGS) $(CFLAGS) -o $(OBJS)
	
.PHONY: build
build: all

.PHONY: all
all: $(TARGET).out

$(TARGET).out: $(OBJS) $(DEPS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(OBJS) -lm -o $@ -g
#I have added -lm to tell the linker to include the math library, resolving the reference to the sqrt function.

# Full clean
.PHONY: clean
clean: 
	rm -f $(OBJS) $(TARGET).out $(TARGET).map $(ASMS) $(PREPS) $(DEPS)
	
