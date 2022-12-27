/*
 * A function template 'index_for_smallest' returning
 * index of the the smallest element in an array of
 * instances of the type indicated by the template 
 * parameter.
 * 
 * A recurrence based divide-and-conquer type algorithm
 * used in this version.
 * */

/*
 * Worked on this code on
 *   Dec 22, 2022 / Thu
 * */

#include <iostream>

namespace os_core
{
  
/*
 * Prototype for the function template implementing
 * the core algorithm.
 * */
template
< typename T >
unsigned int
index_for_smallest__d_a_d
(
  T *           array_ptr ,
  unsigned int  index_lower ,
  unsigned int  index_higher
);
  
template
< typename T >
unsigned int
index_for_smallest
(
  T *           array_ptr ,
  unsigned int  size_of_array
)
{
  /*
   * Degenerate case.
   * */
  if ( size_of_array <= 0 )
    return -1;
  
  /*
   * Invoke the recurrence based algorithm.
   * */
  return
    index_for_smallest__d_a_d
      ( array_ptr , 0 , size_of_array-1 );
} // function - index_for_smallest
  
  
/*
 * Adapted from a solution at
 *   https://www.geeksforgeeks.org/maximum-and-minimum-in-an-array/
 * 
 * Making use of only the "less than" operator in comparisons.
 * */
template
< typename T >
unsigned int
index_for_smallest__d_a_d
(
  T *           array_ptr ,
  unsigned int  index_lower ,
  unsigned int  index_higher
)
{
  /*
   * Single element.
   * */
  if ( index_lower == index_higher )
    return  index_lower;
  
  /*
   * Two elements. Ternary operator for conciseness.
   * */
  if ( ( index_lower + 1 ) == index_higher )
    return
      ( array_ptr[index_lower] < array_ptr[index_higher] )
        ? index_lower : index_higher;
   
  /*
   * In case of more than two elements, break the interval
   * into two and recur.
   * */
  unsigned int index_middle 
    = ( index_lower + index_higher ) / 2;
    
  unsigned int index_from_lower_interval
    = index_for_smallest__d_a_d
        (array_ptr, index_lower, index_middle);
  unsigned int index_from_higher_interval
    = index_for_smallest__d_a_d
        (array_ptr, index_middle + 1, index_higher);
  
  /*
   * Compare the results obtained from the two recurrent
   * calls above.
   * 
   * Again ternary operator for conciseness.
   * */
  return
    ( array_ptr[index_from_lower_interval] 
        < array_ptr[index_from_higher_interval] )
      ? index_from_lower_interval : index_from_higher_interval;
} // function - index_for_smallest__d_a_d
  
} // namespace os_core

int
main (void)
{
  using namespace std;
  using namespace os_core;
  
  int int_array[4] = { 1 , -7 , 0 , 3 };
  auto i_smallest 
    = index_for_smallest
        ( int_array , sizeof(int_array) / sizeof(int) );
  
  cout 
    << endl << "Item " << int_array[i_smallest] 
    << " at index " << i_smallest << " is the smallest in the array."
    << endl;
    
  return 0;
} // main