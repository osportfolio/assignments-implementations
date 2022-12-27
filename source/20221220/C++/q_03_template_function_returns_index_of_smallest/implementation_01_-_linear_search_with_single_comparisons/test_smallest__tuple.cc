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
#include <tuple>

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
   * Type definition. Both the pointer and the
   * corresponding index stored.
   * */
  using local_tuple_type
    = std::tuple< T * , unsigned int >;
    
  /*
   * Declaration and initialization for the
   * immutable tuple type.
   * */
  local_tuple_type info_holder
    = std::make_tuple< T * , unsigned int >( NULL , -1 );
  bool flag_1st_item_was_treated = false;
    
  for ( unsigned int kk = 0 ; kk < size_of_array ; ++kk )
  {
    if ( ! flag_1st_item_was_treated )
    {
      /*
       * Update. Two statements in succession.
       * */
      std::get<0>( info_holder )
        = array_ptr + kk;
      std::get<1>( info_holder )
        = kk;
        
      flag_1st_item_was_treated = true;
      continue;
    }
    
    /*
     * Update if the current value is smaller.
     * */
    if ( array_ptr[kk] < *( std::get<0>( info_holder ) ) )
    {
      /*
       * Again the same update.
       * */
      std::get<0>( info_holder )
        = array_ptr + kk;
      std::get<1>( info_holder )
        = kk;
    }
  } // for kk
  
  /*
   * Return index only.
   * */
  return  std::get<1>( info_holder );
} // index_for_smallest
  
} // namespace os_core
