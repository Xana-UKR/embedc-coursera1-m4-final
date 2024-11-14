/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file memory.c
 * @brief Abstraction of memory read and write operations
 *
 * This implementation file provides an abstraction of reading and
 * writing to memory via function calls. There is also a globally
 * allocated buffer array used for manipulation.
 *
 * @author Alex Fosdick, Oksana Vynokurova  
 * @date April 1 2017, 11/2024
 *
 */
#include "memory.h"

/***********************************************************
 Function Definitions
***********************************************************/
void set_value(char * ptr, unsigned int index, char value){
  ptr[index] = value;
}

void clear_value(char * ptr, unsigned int index){
  set_value(ptr, index, 0);
}

char get_value(char * ptr, unsigned int index){
  return ptr[index];
}

void set_all(char * ptr, char value, unsigned int size){
  unsigned int i;
  for(i = 0; i < size; i++) {
    set_value(ptr, i, value);
  }
}

void clear_all(char * ptr, unsigned int size){
  set_all(ptr, 0, size);
}

/************************** my FUNCTIONS*********************/

/**
 * @brief Moves (length) bytes from (src) to (dest) 
 *
 * The behavior should handle overlap of source and destination. 
 * Copy should occur, with no data corruption.
 *
 * @param uint8_t * src - Pointer to source
 * @param uint8_t * dst - Pointer to destination
 * @param size_t length - Number of bytes to move
 *
 * @return - a pointer to the destination (dst)
 */
uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length)
{
  size_t i;
  uint8_t *s;
  uint8_t *d;

  if (dst == src) {return dst;}

  if ( dst > src )
  {
    /* Handles the situation when src is the first block but dst 
    overlaps it. In this case copying from the first element to the last 
    will corrupt data. Copying from the last to the first is required */
    i = length;
    d = dst + length - 1;
    s = src + length - 1;
    while (i > 0)
    {
      *d = *s;
      --d;
      --s;
      --i;
    }
    /* other variant:
     * i = len; d =dst+len; s=src+len;
     * while (--i) { *(--d) = * (--s); } 
     */
  }
  else
  {
    /* we should copy from start to end - it handles not-overlapped src and dst
    and it handles overlapping, when dst if the first memory block by it's address */
    i = 0;
    d = dst;
    s = src;
    while (i < length)
    {
      *d = *s;
      d++;
      s++;
      i++;
    }
  }

  return dst;

}

/**
 * @brief Copies (length) bytes from (src) to (dest) 
 * 
 * The behavior is undefined if there is overlap of source and 
 * destination. Copy should still occur, but will likely corrupt
 * your data.
 *
 * @param uint8_t * src - Pointer to source
 * @param uint8_t * dst - Pointer to destination
 * @param size_t length - Number of bytes to copy
 *
 * @return - a pointer to the destination (dst)
 */
uint8_t * my_memcopy(uint8_t * src, uint8_t * dst, size_t length)
{
  uint8_t * dst_orig = dst;

  while (length != 0)
  {
    *dst=*src;
    dst++;
    src++;
    length--;
  }
  return dst_orig;
}

/**
 * @brief Set all (length) bytes at address (src) to a given (value)
 *
 * @param uint8_t * src - Pointer to source
 * @param size_t length - Number of bytes to set to a value
 * @param uint8_t value - Value to be set
 *
 * @return - a pointer to the source (src)
 */
uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value)
{
  uint8_t * ptr = src;  

  while (length != 0 )
  {
    *ptr = value;
    ptr++;
    length--;
  }

  return src;
}

/**
 * @brief Set all (length) bytes at address (src) to a zero
 *
 * @param uint8_t * src - Pointer to source
 * @param size_t length - Number of bytes to set to 0
 *
 * @return - a pointer to the source (src)
 */
uint8_t * my_memzero(uint8_t * src, size_t length)
{
  return my_memset(src,length,0);
};

/**
 * @brief Allocate in dynamic memory
 *
 * This should take number of words to allocate 
 * in dynamic memory.
 *
 * @param size_t length - Number of words to reserve
 *
 * @return - a pointer to memory if successful,
 *            or a Null Pointer if not successful
 */
int32_t * reserve_words(size_t length)
{
  return (int32_t * ) malloc(length*sizeof(int32_t));
}


/**
 * @brief Free a dynamic memory allocation 
 *
 * Should free a dynamic memory allocation by providing 
 * the pointer src to the function
 *
 * @param size_t length - Number of words to reserve
 */
void free_words(int32_t * src)
{
  free(src);
}


/**
 * @brief Reverse the order of all of the bytes
 *
 * This should take a pointer to a memory location 
 * and a length in bytes and reverse the order of all of the bytes.
 *
 * @param uint8_t * src - Pointer to source
 * @param size_t length - Number of bytes to reverse
 *
 * @return - a pointer to the source (src)
 */
uint8_t * my_reverse(uint8_t * src, size_t length)
{
  size_t const half_length = length / 2.0; // length of help memory required

  uint8_t help_mem[half_length]; // additional memory to help reversing 
  uint8_t* dst_ptr;
  uint8_t* src_ptr;
  
  size_t i;

  /* copy firts half or the source memory to help memory */
  dst_ptr = help_mem;
  src_ptr = src;
  i = 0;
  while (i < half_length)
  {
    *dst_ptr = *src_ptr;
    dst_ptr++;
    src_ptr++;
    i++;  
  }
  
  /* copy in reverse order second half or source memory 
     to the first half of source memory  */
  src_ptr = src + length - 1; //put source pointer to the last element
  dst_ptr = src;
  i = 0;
  while (i < half_length)
  {
    *dst_ptr = *src_ptr;
    dst_ptr++;
    src_ptr--;
    i++;  
  }

  /* copy in reverse order first half or source memory,
  saved in the help_mem to the second half of source memory  */
  src_ptr = help_mem; 
  dst_ptr = src + length -1; //put destination pointer to the last element
  i = 0;
  while (i < half_length)
  {
    *dst_ptr = *src_ptr;
    dst_ptr--;
    src_ptr++;
    i++;  
  }

return src;
  
}