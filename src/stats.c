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
 * @file stats.c 
 * @brief Shows some statistics for char data ites, given in the program 
 * 
 * This program analyze an array of given const unsigned char data items and 
 * report analytics on the maximum, minimum, mean, and median of the data set. 
 * In addition, it reorders this data set from large to small. 
 * All statistics are rounded down to the nearest integer. 
 * After analysis and sorting is done, statistics are print to the screen 
 * in nicely formatted presentation. 
 * 
 * @author Oksana Vynokurova
 * @date 27.10.2024
 *
 */


#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h> 
#include "stats.h"
#include "platform.h"


/**************************Functions to help sort functions***********************/
/**
 * @brief Given pointers to char variables, swaps their values 
 * using elegant XOR method 
 * 
 * @param unsigned char* a, b - pointers to char variants to swap
 * 
 */
void swap_ch_values(unsigned char* a, unsigned char* b);

/**
 * @brief This function is used by Quick sort algorythm 
 * 
 * It divides array rom start index to finish index on two parts
 * bigger and lower than the pivot - the last [finish index] element
 * We will get the pivot on the correct place in the array.
 * 
 * @param unsigned char* arr - pointer to a char array
 * @param int start_idx - index in the array to start with (leftmost)
 * @param int start_idx - index in the array to finish with (rightmost) 
 */
 int put_pivot(unsigned char* arr, int start_idx, int finish_idx);
 
/**
 * @brief This function is used by Quick sort algorythm 
 * 
 * It performs recursive quick sort algorithm
 * 
 * @param unsigned char* arr - pointer to a char array
 * @param int start_idx - index in the array to start with (leftmost)
 * @param int start_idx - index in the array to finish with (rightmost) 
 */
void quick_sort_recursive(unsigned char* arr, int start_idx, int finish_idx);

/**
 * @brief This function is used by Merge sort algorythm 
 * 
 * It merges to arrays: first from arr[start_idx] to arr[middle_idx]
 * and second from arr[middle_idx + 1] to arr [finish_idx]
 * This subarrays (branches) are supposed to be sorted from biggest to smallest
 * As a result it writes down into the same arr[start_idx, finish_idx]
 * all values from both branches in sort order from biggest to smallest.
 * This funstion uses malloc/free.
 * 
 * @param unsigned char* arr - array to sort (partlially)
 * @param start_idx - index of the first element of the 1st subarray to sort
 * @param middle_idx - index of the last element of the 1st subarray to sort
 * @param finish_idx - index of the last element of the 2st subarray to sort
 */
void mergesort_merge(unsigned char* arr, int start_idx, int middle_idx, int finish_idx);

/**
 * @brief This function is used by Merge sort algorythm 
 * 
 * It divides subarray arr[start_idx, finish idx]
 * on two (almost) equal branches recursively, 
 * until all branches consist of a signgle element only.
 * Then it merges branches in correct sort order.
 * 
 * @param unsigned char* arr - array to sort (partlially)
 * @param start_idx - index of the first element the subarray to sort
 * @param finish_idx - index of the last element of the subarray to sort
 */
void mergesort (unsigned char* arr, int start_idx, int finish_idx);

/**
 * @brief Given an array of data and a length, returns the maximum element's index
 *
 * This functions takes in an array of char elements 
 * and returns (int) index of the biggest elements' value
 * Array stays unchanged.
 *
 * @param unsigned char* ch_arr - pointer to an array or char elements;
 * @param int arr_length - length of an array ch_arr - number of elements in it;
 *
 * @return int - index of the maximum value, found in the array
 */
int find_index_of_maximum_el (unsigned char* ch_arr, int arr_length);

/********End of decription of Functions to help sort functions***************/


/* Size of the Data Set */
#define SIZE (40) // (8)

/* int main() 
{
  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  87,  25,  23,
                              200, 122, 150, 90,   92,  87, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};

//  unsigned char test[SIZE] = {9, 2, 1, 8, 5, 1, 9, 3};
  
  unsigned char min; //minimum array's element
  unsigned char max; //maximum array's element
  double mean, median; // mean of the array's elements
  
  unsigned char sorted_arr[SIZE]; // aray of sorted elements

  if (SIZE <= 0)
  {
    PRINTF("Incorrect size of the given array");
    return 1;
  }

  max = find_minimum (test, SIZE);
  PRINTF("Minimum element is %d \n", max);
  
  max = find_maximum (test, SIZE);
  PRINTF("Maximum element is %d \n", max);

  mean = find_mean (test, SIZE);
  PRINTF("Mean is %.2f \n", mean);

  median = find_median (test, SIZE);
  PRINTF("Median is %.2f \n", median);


  copy_ch_arr(test, sorted_arr, SIZE);
  sort_selection(sorted_arr, SIZE);
  PRINTF ("\n Array was sorted with Selection Sort:");
  print_array(sorted_arr, SIZE);

  copy_ch_arr(test, sorted_arr, SIZE);
  sort_bubble(sorted_arr, SIZE);
  PRINTF ("\n Array was sorted with Bubble Sort:");
  print_array(sorted_arr, SIZE);

  copy_ch_arr(test, sorted_arr, SIZE);
  sort_bubble(sorted_arr, SIZE);
  PRINTF ("\n Array was sorted with Insertion Sort:");
  print_array(sorted_arr, SIZE);

  copy_ch_arr(test, sorted_arr, SIZE);
  sort_quick(sorted_arr, SIZE);
  PRINTF ("\n Array was sorted with Quick Sort:");
  print_array(sorted_arr, SIZE);

  copy_ch_arr(test, sorted_arr, SIZE);
  sort_merge(sorted_arr, SIZE);
  PRINTF ("\n Array was sorted with Merge Sort:");
  print_array(sorted_arr, SIZE);

  return 0;
}
*/

/****************Statistics  functions****************************************/

/*Given an array of data and a length, returns the minimum element's value */
unsigned char find_minimum (unsigned char* ch_arr, int arr_length)
{
  unsigned char min = 0xFF;
  int i;
  
  for (i =0 ; i < arr_length; i++)
  {
    if (ch_arr[i] < min)
    {
      min = ch_arr[i];
    }
  }
  return min;
}

/* Given an array of data and a length, returns the maximum element's value */
unsigned char find_maximum (unsigned char* ch_arr, int arr_length)
{
  unsigned char max = 0;
  int i;
  
  for (i =0 ; i < arr_length; i++)
  {
    if (ch_arr[i] > max)
    {
      max = ch_arr[i];
    }
  }
  return max;
}

/* Given an array of data and a length, returns the mean of elements */
double find_mean (unsigned char* ch_arr, int arr_length)
{
  double mean =0;
  int i;
  
  for (i =0 ; i < arr_length; i++)
  {
    mean += ch_arr[i];
  }

  if (arr_length != 0)
  {
    mean = mean / arr_length;
  }

  return mean;
}

/* Given an array of data and a length, finds it's median element
 * It uses VLA - variable length array - that could be unsupported by some compilers
 */
double find_median (unsigned char* arr, int arr_length)
{
  unsigned char sorted_arr[arr_length]; //VLA!!!
  int median_idx;
  double median;

  copy_ch_arr(arr, sorted_arr, arr_length);
  sort_quick(sorted_arr, arr_length);
  median_idx = arr_length/2;
  if(arr_length % 2 != 0)
  {
    median = sorted_arr[median_idx];
  }
  else
  {
    median = (sorted_arr[median_idx] + sorted_arr[median_idx - 1])/(double)2;
  }

  return median;

}

/****************Print functions**********************************************/

/* Prints an array of chars */
void print_array (unsigned char* ch_arr, int arr_length)
{
#ifdef VERBOSE
  int i, j;
  int rows_num, cols_num;

  //define number of rows and columns for beutiful table print
  rows_num = sqrt(arr_length);   
  if (rows_num == 0)
  {
    rows_num = 1;
    cols_num = arr_length;
  }
  else
  {
    cols_num = arr_length/rows_num;
  }

  PRINTF ("\n");
  for (i=0; i < rows_num; i++)
  {
    for (j = 0; j < cols_num; j++)
    {
      PRINTF ("%d\t", ch_arr[i*cols_num+j] );
    }
    PRINTF ("\n");
  }
  // if we were not able to put all elemnts in a table, print the rest  
  i= arr_length - rows_num*cols_num;
  for ( j = 0; j < i; j++ )
  {
    PRINTF("%d\t", ch_arr[rows_num*cols_num + j]); 
  }
  
  PRINTF ("\n");
#endif
}


/****************Sort functions****************************************/

/***************************************/

/* Given an array of data and a length, returns the maximum element's index */
int find_index_of_maximum_el (unsigned char* ch_arr, int arr_length)
{
  int max_el_index = 0;
  int i;
  
  for (i =1 ; i < arr_length; i++)
  {
    if (ch_arr[i] > ch_arr[max_el_index])
    {
      max_el_index = i;
    }
  }
  return max_el_index;
}

/* Selection Sort of an array of chars */
void sort_selection (unsigned char* arr, int arr_length)
{
  int i;
  int curr_max_index;

  for (i=0; i < arr_length; i++)
  {
    curr_max_index = find_index_of_maximum_el(&arr[i], arr_length - i);
    if (curr_max_index !=0 )
    {
       swap_ch_values(&arr[i], &arr[i+curr_max_index]);
    }
    
  }

}

/**************************************/
/* Bubble Sort of an array of chars */
void sort_bubble (unsigned char* arr, int arr_length)
{
  int i, last_index;
  bool not_sorted;

  do
  {
    last_index = arr_length;
    not_sorted = false;
    for (i = 1; i < last_index; i++)
    {
      if (arr[i-1] < arr[i])
      {
        swap_ch_values(&arr[i-1], &arr[i]);
        not_sorted = true;
      }
    }
    last_index--;
  }
  while (not_sorted);

}

/**************************************/

/**This function is used by Merge sort algorythm 
 * It merges to arrays: first from arr[start_idx] to arr[middle_idx]
 * and second from arr[middle_idx + 1] to arr [finish_idx]
 * This subarrays (branches) are supposed to be sorted from biggest to smallest
 * As a result it writes down into the same arr[start_idx, finish_idx]
 * all values from both branches in sort order from biggest to smallest.
 * This funstion uses malloc/free.
 */
void mergesort_merge(unsigned char* arr, int start_idx, int middle_idx, int finish_idx)
{
  int i, j, k;
  unsigned char* sorted_arr;
  
  if ((start_idx >= finish_idx) || (start_idx > middle_idx)) {return;}
  
  i = start_idx; //index for the first branch to merge
  j = middle_idx+1; //index for the second branch to merge

  // we need to allocate memory for temporary array of sorted elements
  sorted_arr = (unsigned char*) malloc(sizeof(char) * (finish_idx - start_idx + 1) );
  if (sorted_arr == NULL) {return;}
  
  k=0;
  do
  {
    if (arr[i] >= arr[j])
    {
      sorted_arr[k] = arr[i];
      i++;
    }
    else
    {
      sorted_arr[k] = arr[j];
      j++;
    }
    k++;

  } while ((i <= middle_idx) && (j <= finish_idx ));

  while (i <= middle_idx)
  {
    sorted_arr[k] = arr[i];
    i++;
    k++;
  };

  while (j <= finish_idx)
  {
    sorted_arr[k] = arr[j];
    j++;
    k++;
  };
    
  copy_ch_arr(sorted_arr, &arr[start_idx], finish_idx-start_idx +1);

  free(sorted_arr);
}

/**This function is used by Merge sort algorythm 
 * It divides array rom start index to finish index 
 * on two (almost) equal branches recursively, until a branch
 * consists of a signgle element only.
 * Then it merges branches in correct sort order
 */
void mergesort (unsigned char* arr, int start_idx, int finish_idx)
{
  int middle_idx;
  
  if (start_idx >= finish_idx) {return;}
  
  middle_idx = start_idx + (finish_idx-start_idx)/2;
  mergesort(arr, start_idx, middle_idx); // devide for 2 branches here
  mergesort(arr, middle_idx+1, finish_idx); // devide for 2 bracnhes here

  //merge of banches here
  mergesort_merge(arr, start_idx, middle_idx, finish_idx);
}

/* Merge Sort of an array of chars */
void sort_merge (unsigned char* arr, int arr_length)
{
  mergesort(arr, 0, arr_length -1);
}

/**************************************/
/**This function is used by Quick sort algorythm 
 * It divides array rom start index to finish index on two parts
  * bigger and lower than the pivot - the last [finish index] element
  * We will get the pivot on the correct place in the array.
  */
 int put_pivot(unsigned char* arr, int start_idx, int finish_idx)
 {
  int i, right_idx;
  unsigned char pivot;

  right_idx = start_idx;
  pivot = arr[finish_idx]; //pivot is the last element
  for (i = start_idx; i < finish_idx; i++)
  {
    if (arr[i] > pivot)
    {
      swap_ch_values(&arr[i], &arr[right_idx]);
      right_idx++;
    }
  }
  swap_ch_values(&arr[finish_idx], &arr[right_idx]);

  return right_idx; //returns pivot poistion
 }

 /** This function is used by Quick sort algorythm 
   * It performs recursive quick sort algorithm
   */
void quick_sort_recursive(unsigned char* arr, int start_idx, int finish_idx)
{
  int pivot_idx;
  if (start_idx < finish_idx)
  {
    pivot_idx = put_pivot(arr, start_idx, finish_idx);
    quick_sort_recursive(arr, start_idx, pivot_idx - 1);
    quick_sort_recursive(arr, pivot_idx + 1, finish_idx);
  }
}

/* Quick Sort of an array of chars */
void sort_quick (unsigned char* arr, int arr_length)
{
  quick_sort_recursive(arr, 0, arr_length-1);
}

/**************************************/
/* Insertion Sort of an array of chars */
void sort_insertion (unsigned char* arr, int arr_length)
{
  int i, j;
  for (i = 1; i < arr_length; i++)
  {
    for (j= i-1; j >=0; j--)
    {
      if (arr[i]>arr[j])
      {
        swap_ch_values(&arr[i], &arr[j]);
      }
    }
  }
}

/****************Help functions****************************************/

/* Given pointers to char variables, swaps their values 
using elegant XOR method */
void swap_ch_values(unsigned char* a, unsigned char* b)
{
  if ((a == NULL) || (b == NULL) || (a == b)) {return;}

  *a = *a ^ *b;
  *b = *b ^ *a;
  *a = *a ^ *b;
  
/*
  unsigned char tmp;
  tmp = *a;
  *a= *b;
  *b=tmp;
*/

}

/* Copies one char array to another */
void copy_ch_arr (unsigned char* arr_orig, unsigned char* arr_copy, int arr_length)
{
  int i;

  for (i=0; i < arr_length; i++)
  {
    arr_copy[i] = arr_orig[i];
  }
}
