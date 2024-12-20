/******************************************************************************
 * Copyright (C) 2017 by Oksana Vynokurova
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Oksana Vynokurova is not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file data.h
 * @brief Does some very basic data manipulation.
 *
 *
 * @author Oksana  Vynokurova
 * @date 11/2024
 *
 */
#ifndef __DATA_H__
#define __DATA_H__

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Convert data from a standard integer type into an ASCII string
 *
 * Integer-to-ASCII needs to convert data from a standard integer type 
 * 	into an ASCII string.
 *
 * All operations need to be performed using pointer arithmetic, not array indexing
 * The number you wish to convert is passed in as a signed 32-bit integer.
 * You should be able to support bases 2 to 16 by specifying the integer value 
 *	of the base you wish to convert to (base).
 * Copy the converted character string to the uint8_t* pointer passed in as 
 *	a parameter (ptr)
 * The signed 32-bit number will have a maximum string size (Hint: Think base 2).
 * You must place a null terminator at the end of the converted c-string
 * 
 * Function should return the length of the converted data 
 * (including a negative sign). 
 * Example my_itoa(ptr, 1234, 10) should return an ASCII string length of 5 
 * (including the null terminator).
 * This function needs to handle signed data.
 * You may not use any string functions or libraries
 * 
 * @param int32_t data - number to convert
 * @param uint8_t * ptr - pointer where we can save resulting string 
 * @param uint32_t base - number base from2 to 16
 * 
 * @return uint8_t - number of characters in the resulting sting, including end \0
 */
 uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);
 
 
/**
 * @brief  Converts data back from an ASCII represented string into an 
 * integer type.
 *
 * All operations need to be performed using pointer arithmetic, not array indexing
 * The character string to convert is passed in as a uint8_t * pointer (ptr).
 * The number of digits in your character set is passed in as a 
 *	uint8_t integer (digits).
 * You should be able to support bases 2 to 16.
 * The converted 32-bit signed integer should be returned.
 * This function needs to handle signed data.
 * You may not use any string functions or libraries
 *
 * @param uint8_t * ptr - pointer to a number in a form of string to convert
 * @param uint8_t digits - number of characters in the given sting, including terminator \0 and '-'
 * @param uint32_t base - number base from 2 to 16
 * 
 * @return int32_t - converted number
 **/
 int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);
 
#endif /* __DATA_H__ */
