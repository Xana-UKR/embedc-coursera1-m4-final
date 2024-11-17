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
 * @file data.c 
 * @brief This file should do some very basic data manipulation.
 *
 * @author Oksana Vynokurova
 * @date 11/2024
 *
 */

#include "data.h"
#include <math.h>

uint32_t get_max_digit_position(int32_t data, uint32_t base)
{
    /* 
    base ^ x = data
    log(base^x)=log(data)
    x*log(base)=log(data)
    x=log(data)/log(base)
    Then we round the result to the closest higher int
    */

   /* handle incorrect arguments */
   if ((data == 0) || (base == 0) || (base == 1)) {return 0;}

   return (uint32_t) round( log((double) data) / log((double)base) );
}

/** Converts digit [0 -9] to a character ['0' - '9']
 * In case of wrong digit returns 0 (null terminator)
 **/
uint8_t digit_to_ch(uint8_t curr_digit)
{
    if (curr_digit < 10) // for 0,1,2,3.., 9
    {
        return (curr_digit + 48); //ASCII value of digits [0 – 9] ranges from [48 – 57]
    }
    else
    {
        return 0; //error
    }
}

/**
 * @brief Convert data from a standard integer type into an ASCII string
 *
 * @param int32_t data - number to convert
 * @param uint8_t * ptr - pointer where we can save resulting string 
 * @param uint32_t base - number base from2 to 16
 * 
 * @return uint8_t - number of characters in the resulting sting, including end \0
 */
uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base) 
{
    uint8_t curr_digit; //digit on a current position
    int32_t base_pow_i; //base ^i
    uint8_t ch_num = 0; //number fo characters written to a string
    uint8_t i; // position of a current digit

    if (data < 0)
    {
        *ptr = '-';
        ptr++;
        ch_num ++;
    }
    data = abs(data);
    
    // log of 0 is undefined
    if (base < 2) {return 0;} //unsuported situation, base should be [2;16]
    if (data == 0 ) 
    { 
        i = 0; 
    }
    else
    {
        i = get_max_digit_position(data, base);// i = max position of a digit
    }
    

    /* Handle the situation of leading zeroes -
    when get_max_digit_position() returns bigger position then required,
    we should just skip them */
    while (i > 0)
    {
        base_pow_i = (int32_t) pow ((double)base,(double)i); // base^i
        curr_digit = data / base_pow_i;
        
        if (curr_digit != 0) { break;}
        i--;
    }
    
    /* Here we should not skip zeroes, because they are not leading */
    /* Before this loop i is pointing to the first(!) non-zero digit */
    while( i >  0)
    {
        base_pow_i = (int32_t) pow ((double)base,(double)i); // base^i
        curr_digit = data / base_pow_i;
        
        *ptr = digit_to_ch(curr_digit);
        ptr++;
        ch_num ++;

        i --;
        data = data % base_pow_i;
    }
 

    /* for  i == 0; base_pow_i == 1;  curr_digit == data; */
    *ptr = digit_to_ch(data);
    ptr++;
    ch_num ++;

    *ptr = 0;
    ch_num ++;

    return ch_num;
}

/** Converts character ['0' - '9'] to a digit [0 -9]
 * In case of wrong character returns 0 
 **/
uint8_t ch_to_digit (uint8_t ch)
{
    if ( (ch >= 48) && (ch <= 57)) // for '0','1','2'.., '9'
    {
        return (ch - 48); //ASCII value of digits [0 – 9] ranges from [48 – 57]
    }
    else
    {
        return 0; //all incorrect characters are treated as 0
    }
}

/**
 * @brief  Converts data back from an ASCII represented string into an 
 * integer type.
 *
 * @param uint8_t * ptr - pointer to a number in a form of string to convert
 * @param uint8_t digits - number of characters in the given sting, including terminator \0 and '-'
 * @param uint32_t base - number base from 2 to 16
 * 
 * @return int32_t - converted number
 **/
int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base) 
{
    uint8_t negative;
    int32_t result = 0;

    if (*ptr == '-')
    {
        negative = 1;
        ptr++;
        digits--;
    }
    else
    {
        negative = 0;
    }
    
    /* Incorrect arguments handling */
    /* There should be at least 2 characters, where the last one is a strign null terminator */
    if (digits < 2) return 0; 
    if ((base < 2) || (base > 16)) return 0;

    /* 
    digits will show current digit position (starting from 0)
    
    The biggest (=starting) current position equals number of string characters 
    minus the terminal null and minus 1, because position number starts with zero, not one */
    digits = digits -2;

    while ((digits >= 1) && (*ptr != 0))
    {
        /*
        curr_multipier = pow(base, curr_position);
        curr_digit = ch_to_digit(*ptr);
        */
        result += ch_to_digit(*ptr) * pow(base, digits);
        ptr++;
        digits--;
    }

    result += ch_to_digit(*ptr); // the last digit character, it doesn't need pow
    
    if (negative) result = -result;
    
    return result;
}