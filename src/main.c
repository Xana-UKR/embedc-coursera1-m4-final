/******************************************************************************
 * Copyright (C) 2024 by Oksana Vynokurova
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Oksana Vynokurova is not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file main.c
 * @brief Main entry point to the C1M4 - Final Course 1 Assessment
 *
 * This file contains the main code for the C1M4 assesment.
 *
 * @author Oksana Vynokurova
 * @date 11/ 2024
 *
 */

#ifdef COURSE1
  #include "course1.h"
#endif

int main(void) {
  #ifdef COURSE1
    course1();
  #endif
  
  

}

