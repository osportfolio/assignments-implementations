/*
 * The function 'update' gets two
 * integers, and sets the first integer as the
 * sum and the second one as the absolute difference
 * of the original two integers. Makes use of the C++
 * tuple as return type and the 'abs' function.
 * 
 * This implementation is possibly not in line
 * with the requirements of the task in hand,
 * since the integers a and b cannot be modified
 * in place with the 'update' version below.
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
  
std::tuple<int, int>
update
(
  const int   i_1st ,
  const int   i_2nd
);

} // namespace os_core

int
main(void)
{
  int a, b;

  printf( "\nEnter Two Integers :\n" );
  scanf ( "%d %d" , &a , &b );
  
  auto  res_tuple =
    os_core::update( a , b );
  a = std::get<0>( res_tuple );
  b = std::get<1>( res_tuple );
  
  printf( "\nThe Updated Integers :\n" );
  printf( "a: %+8d    b: %+8d\n" , a , b );
  return 0;
}

namespace os_core
{
  
std::tuple<int, int>
update
(
  const int   i_1st ,
  const int   i_2nd
)
{
  int i_sum
    = i_1st + i_2nd;
  
  int i_abs_difference 
    = abs( i_1st - i_2nd );
    
  return  std::tuple<int, int>
            ( i_sum , i_abs_difference );  
}

} // namespace os_core