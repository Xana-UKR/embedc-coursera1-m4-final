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
 * @file stats.h 
 * @brief Functions' definicions for some statistics functions
 *
 * Includes functions, that perform some statistical calculations
 * print_statistics() - A function that prints the statistics of an array including minimum, maximum, mean, and median.
 * print_array() -  Given an array of data and a length, prints the array to the screen
 * find_median() - Given an array of data and a length, returns the median value
 * find_mean() -  Given an array of data and a length, returns the mean
 * find_maximum() -  Given an array of data and a length, returns the maximum
 * find_minimum() -  Given an array of data and a length, returns the minimum
 * sort_array() - Given an array of data and a length, sorts the array from largest to smallest.
 *
 * @author Oksana Vynokurova
 * @date 27.10.24
 *
 */
#ifndef __STATS_H__
#define __STATS_H__

/**************************Statistics functions**************************/

/**
 * @brief Given an array of data and a length, returns the minimum element's value
 *
 * This functions takes in an array of char elements 
 * and returns one char value equal to minimum element, found in the array.
 * Array stays unchanged.
 *
 * @param unsigned char* ch_arr - pointer to an array of unsigned char elements;
 * @param int arr_length - length of an array ch_arr - number of elements in it;
 *
 * @return unsigned char - minimum value, found in the array
 */

unsigned char find_minimum (unsigned char* ch_arr, int arr_length);


/**
 * @brief Given an array of data and a length, returns the maximum element's value
 *
 * This functions takes in an array of char elements 
 * and returns one char value equal to maximum element, found in the array.
 * Array stays unchanged.
 *
 * @param unsigned char* ch_arr - pointer to an array or char elements;
 * @param int arr_length - length of an array ch_arr - number of elements in it;
 *
 * @return unsigned char - maximum value, found in the array
 */

unsigned char find_maximum (unsigned char* ch_arr, int arr_length);


/**
 * @brief Given an array of data and a length, returns the mean of elements
 *
 * This functions takes in an array of char elements 
 * and returns one char value equal to the mean of all elements of the array.
 * Array stays unchanged.
 *
 * @param unsigned char* ch_arr - pointer to an array or char elements;
 * @param int arr_length - length of an array ch_arr - number of elements in it;
 *
 * @return double - teh mean of the all elemets of the array
 */

double find_mean (unsigned char* ch_arr, int arr_length);

/**
 * @brief Given an array of data and a length, finds it's median
 *
 * This functions takes in an array of char elements 
 * and returns double value equal to the meadian of all elements of the array.
 * Array stays unchanged.
 * It uses VLA - variable length array - that could be unsupported by some compilers.
 *
 * @param unsigned char* ch_arr - pointer to an array or char elements;
 * @param int arr_length - length of an array ch_arr - number of elements in it;
 *
 * @return double - teh mean of the all elemets of the array
 */
double find_median (unsigned char* arr, int arr_length);


/**************************Print and copy functions**************************/

/**
 * @brief Prints an array of chars
 * 
 * Given an array of data and a length, prints its element
 * 
 * @param unsigned char* ch_arr - pointer to an array or char elements;
 * @param int arr_length - number of elemets in arr
 * 
 * @return nothing
 */
void print_arr (unsigned char* ch_arr, int arr_length);

/**
 * @brief Copies one char array to another 
 * 
 * @param unsigned char* arr_orig - pointer to the orignal char array
 * @param unsigned char* arr_copy - pointer to the char array where we will copy to
 * @param int arr_length - length of the both arrays 
 * 
 **/
void copy_ch_arr (unsigned char* arr_orig, unsigned char* arr_copy, int arr_length);


/**************************Sort functions****************************************/
/**
 * @brief Selection Sort of an array of chars
 * 
 * Given an array of data and a length, sort its element from biggets to smallest
 * Sorting is done by Selection Sort algorithm.
 * 
 * @param unsigned char* arr - pointer to an array or char elements to sort;
 * @param int arr_length - number of elemets in arr
 * 
 */
void sort_selection (unsigned char* arr, int arr_length);

/**
 * @brief Bubble Sort of an array of chars
 * 
 * Given an array of data and a length, sort its element from biggets to smallest
 * Sorting is done by Bubble Sort algorithm.
 * 
 * @param unsigned char* arr - pointer to an array or char elements;
 * @param int arr_length - number of elemets in arr
 * 
 */
void sort_bubble (unsigned char* arr, int arr_length);

/**
 * @brief Insertion Sort of an array of chars
 * 
 * Given an array of data and a length, sort its element from biggets to smallest
 * Sorting is done by Insertion Sort algorithm.
 * 
 * @param unsigned char* arr - pointer to an array or char elements;
 * @param int arr_length - number of elemets in arr
 * 
 */
void sort_insertion (unsigned char* arr, int arr_length);


/**
 * @brief Merge Sort of an array of chars
 * 
 * Given an array of data and a length, sort its element from biggets to smallest
 * Sorting is done by Merge Sort algorithm.
 * 
 * @param unsigned char* arr - pointer to an array or char elements;
 * @param int arr_length - number of elemets in arr
 * 
 */
void sort_merge (unsigned char* arr, int arr_length);

/**
 * @brief Merge Sort of an array of chars
 * 
 * Given an array of data and a length, sort its element from biggets to smallest
 * Sorting is done by Quick Sort algorithm.
 * 
 * @param unsigned char* arr - pointer to an array or char elements;
 * @param int arr_length - number of elemets in arr
 * 
 */
void sort_quick (unsigned char* arr, int arr_length);


#endif /* __STATS_H__ */

