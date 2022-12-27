/*
 * The function 'update' gets a tuple holding
 * references to each of two integers, and sets the 
 * first integer as the sum and the second one as 
 * the absolute difference of the original two 
 * integers. Makes use of the C++ tuple, 
 * 'forward_as_tuple', and the 'abs' function.
 * */

/*
 * Worked on this code on
 *     Dec 20, 2022 / Tue
 * */

#include <cstdio>
#include <cstdlib>
#include <tuple>

namespace os_core
{
  
void
update
(
  std::tuple<int &, int &>  arg_tuple
);

} // namespace os_core

int
main(void)
{
  int a, b;

  printf( "\nEnter Two Integers :\n" );
  scanf ( "%d %d" , &a , &b );
  
  os_core::update
    ( std::forward_as_tuple( a , b ) );
  
  printf( "\nThe Updated Integers :\n" );
  printf( "a: %+8d    b: %+8d\n" , a , b );
  return 0;
}

namespace os_core
{
  
void
update
(
  std::tuple<int &, int &>  arg_tuple
)
{
  auto & i_1st = std::get<0>( arg_tuple );
  auto & i_2nd = std::get<1>( arg_tuple );
  
  int
    i_1st_original = i_1st ,
    i_2nd_original = i_2nd ;
  
  i_1st
    = i_1st_original + i_2nd_original;
  
  i_2nd 
    = abs( i_1st_original - i_2nd_original );
    
  return;
}

} // namespace os_core