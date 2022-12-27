/*
 * A function template 'index_for_smallest' returning
 * index of the the smallest element in an array of
 * instances of the type indicated by the template 
 * parameter.
 * 
 * Linear search with single item comparisons utilized
 * in this version.
 * */

/*
 * Worked on this code on
 *   Dec 21, 2022 / Wed
 * */

#include <iostream>

namespace os_core
{
  
template
< typename T >
unsigned int
index_for_smallest
(
  T *           array_ptr ,
  unsigned int  size_of_array
);
  
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

namespace os_core
{
  
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
  
  /*
   * Index to be returned
   * */
  unsigned int index_stored 
    = -1;
  
  /*
   * Flag indicating if 'index_stored' has been
   * assigned at the beginning of the 'for' loop
   * below.
   * */
  bool flag_1st_item_was_treated 
    = false;

  for ( unsigned int kk = 0 ; kk < size_of_array ; ++kk )
  {
    if ( ! flag_1st_item_was_treated )
    {
      /*
       * Update.
       * */
      index_stored = kk;
      
      /*
       * Will not enter this conditional again.
       * */
      flag_1st_item_was_treated = true;
      continue;
    }
    
    /*
     * Update if a smaller value is encountered.
     * */
    if ( array_ptr[kk] < array_ptr[index_stored] )
      index_stored = kk;
  } // for kk
  
  /*
   * Simply return the index.
   * */
  return  index_stored;
} // index_for_smallest
  
} // namespace os_core
