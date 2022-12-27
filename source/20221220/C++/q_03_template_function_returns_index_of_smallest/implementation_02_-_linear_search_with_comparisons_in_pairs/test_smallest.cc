/*
 * A function template 'index_for_smallest' returning
 * index of the the smallest element in an array of
 * instances of the type indicated by the template 
 * parameter.
 * 
 * Linear search with item comparisons in pairs utilized
 * in this version.
 * */

/*
 * Worked on this code on
 *   Dec 21, 2022 / Wed
 * */

#include <iostream>

namespace os_core
{
  
/*
 * Inspired by the code posted at
 *   https://www.geeksforgeeks.org/maximum-and-minimum-in-an-array/
 * */
template
< typename T >
unsigned int
index_for_smallest
(
  T *           array_ptr ,
  unsigned int  size_of_array
)
{
  using namespace std;
  
  unsigned int kk;
  
  /*
   * Index to be returned
   * */
  unsigned int index_stored 
    = -1;
    
  /*
   * Degenerate case.
   * */
  if ( size_of_array <= 0 )
    return index_stored;
    
  /*
   * Initialization for 'index_stored' based on
   * the size being even or odd.
   * */
  if ( size_of_array % 2 == 0 )
  {
    index_stored
      = ( array_ptr[0] < array_ptr[1] ) 
          ? 0 : 1 ;
    kk = 2;
  }
  else
  {
    index_stored = 0;
    kk = 1;
  }
    
  /*
   * Each iteration of the while loop below processes
   * the elements in pairs. Ternary operator for conciseness.
   * Utilization of only the "less than" operator in case
   * of restrictions.
   * */
  while ( kk < size_of_array - 1 )
  {
    if ( array_ptr[kk] < array_ptr[kk+1] )
    {
      index_stored
        = ( array_ptr[kk] < array_ptr[index_stored] ) 
            ? ( kk ) : ( index_stored ) ;
    } // if
    else
    {
      index_stored
        = ( array_ptr[kk+1] < array_ptr[index_stored] ) 
            ? ( kk+1 ) : ( index_stored ) ;
    } // else
    
    kk += 2;
  } // while
    
  /*
   * Simply return the index.
   * */
  return index_stored;
} // function index_for_smallest
  
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
}
