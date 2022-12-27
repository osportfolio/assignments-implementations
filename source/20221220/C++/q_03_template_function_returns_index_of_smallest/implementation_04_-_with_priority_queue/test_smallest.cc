/*
 * A function template 'index_for_smallest' returning
 * index of the the smallest element in an array of
 * instances of the type indicated by the template 
 * parameter.
 * 
 * A priority queue is utilized in this version.
 * */

/*
 * Worked on this code on
 *   Dec 21, 2022 / Wed
 * */

#include <iostream>
#include <queue>

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
  return 0;
}