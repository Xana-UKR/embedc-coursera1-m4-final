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
DEFAULT_PLAFORM = HOST

ifeq ($(PLATFORM), MSP432)
	# Source files to this variable for MSP432 platform
	SOURCES = main.c \
		  memory.c \
		  startup_msp432p401r_gcc.c \
		  system_msp432p401r.c \
		  interrupts_msp432p401r_gcc.c
		
	# Include paths to this variable for MSP432 platform 
	INCLUDES = -I../include/common \
		   -I../include/CMSIS \
		   -I../include/msp432 
		   
else
	ifneq ($(PLATFORM), HOST)
                $(info Define PTALFORM=HOST or PLATFORM=MSP432, \
                by defualt HOST is used)
	endif

	# Source files for HOST platform
	SOURCES =  main.c \
	 	   memory.c
		 	   
	# Include paths for HOST platform
	INCLUDES = -I../include/common

endif


