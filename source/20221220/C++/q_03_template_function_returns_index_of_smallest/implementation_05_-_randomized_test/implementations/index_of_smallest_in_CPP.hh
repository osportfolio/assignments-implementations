/*
 * Available implementations for
 * "index_of_smallest".
 * */

/*
 * Worked on this code on
 *   Dec 24-27, 2022 / Sat-Tue
 * */

#pragma once

#include <tuple>
#include <queue>

namespace os_core
{
  
namespace index_of_smallest__implementations
{
  
namespace ns__storing_index_only
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
  
} // namespace ns__storing_index_only

namespace ns__with_tuple
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

} // namespace ns__with_tuple

namespace ns__with_tuple_and_lambda_expression
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
  
  using local_tuple_type
    = std::tuple< T * , unsigned int >;
    
  local_tuple_type info_holder
    = std::make_tuple< T * , unsigned int >( NULL , -1 );
  bool flag_1st_item_was_treated = false;
  
  /*
   * Initialize lambda expression. 'info_holder' is
   * captured by reference, 'array_ptr' by value.
   * */
  auto update_holder
    = [ &info_holder , array_ptr ]
      ( unsigned int kk ) -> void
        {
          std::get<0>( info_holder )
            = array_ptr + kk;
          std::get<1>( info_holder )
            = kk;
        };
  
  for ( unsigned int kk = 0 ; kk < size_of_array ; ++kk )
  {
    if ( ! flag_1st_item_was_treated )
    {
      /*
       * Compact and minimalist update statement.
       * */
      update_holder( kk );
      
      flag_1st_item_was_treated = true;
      continue;
    }
    
    /*
     * Update if a smaller value is encountered.
     * */
    if ( array_ptr[kk] < *( std::get<0>( info_holder ) ) )
      update_holder( kk );
  } // for kk
  
  return  std::get<1>( info_holder );
} // index_for_smallest
  
} // namespace ns__with_tuple_and_lambda_expression

namespace ns__with_comparisons_in_pairs
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
  
} // namespace ns__with_comparisons_in_pairs

namespace ns__with_divide_and_conquer
{
  
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
  
} // namespace ns__with_divide_and_conquer

namespace ns__with_priority_queue
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
   * Degenerate case.
   * */
  if ( size_of_array <= 0 )
    return -1;
  
  /*
   * Flag to modify the behavior of the lambda expression
   * below, on the fly. With the flag set to false, the
   * setup in this function template computes the index of
   * the smallest element in the given array. With that
   * set to true, the setup would yield the index of the
   * biggest, in an array without duplicates.
   * */
  bool  flag_uses_less_than = false;
  
  /*
   * 'array_ptr' is captured by value, and 'flag_uses_less_than'
   * is captured by reference. If the flag is toggled, the
   * behavior of the lambda expression below is automatically
   * reversed, even if the toggle comes after the lambda
   * expression declaration below.
   * */
  auto fh_compare
    = [ array_ptr , &flag_uses_less_than ]
        (
          unsigned int  index_1st ,
          unsigned int  index_2nd
        ) -> bool
        {
          /*
           * Intending to resort to only the "less than"
           * operator, in case of restrictions.
           * */
          bool flag_less
            = ( array_ptr[index_1st] < array_ptr[index_2nd] );
          
          /*
           * Ternary operator instead of "if else".
           * */
          return
            flag_uses_less_than
              ? ( flag_less ) : ( ! flag_less );
        };
  
  /*
   * Type definition in view of an answer at
   *    https://stackoverflow.com/questions/5807735/c-priority-queue-with-lambda-comparator-error
   * */
  using local_pq_type
    = std::priority_queue
        < unsigned int , std::vector<unsigned int>, 
          decltype( fh_compare ) >;
  
  /*
   * Instantiate the priority queue, and push just the
   * indices in order, not the values themselves.
   * */
  local_pq_type  indices_pq( fh_compare );
  for ( unsigned int kk = 0 ; kk < size_of_array ; ++kk )
    indices_pq.push( kk );
  
  /*
   * Returns the desired index.
   * */
  return indices_pq.top();
} // function index_for_smallest
  
} // namespace ns__with_priority_queue

} // namespace index_of_smallest__implementations
  
} // namespace os_core