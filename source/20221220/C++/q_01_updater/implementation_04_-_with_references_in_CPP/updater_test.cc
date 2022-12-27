/*
 * The function 'update' gets the references of two
 * integers, and sets the first integer as the
 * sum and the second one as the absolute difference
 * of the original two integers. Makes use of C++
 * references and the 'abs' function.
 * */

/*
 * Worked on this code on
 *     Dec 20, 2022 / Tue
 * */

#include <cstdio>
#include <cstdlib>

namespace os_core
{
  
void
update
(
  int & i_1st ,
  int & i_2nd
);

} // namespace os_core

int
main(void)
{
  int a, b;

  printf( "\nEnter Two Integers :\n" );
  scanf ( "%d %d" , &a , &b );
  
  os_core::update( a , b );
  
  printf( "\nThe Updated Integers :\n" );
  printf( "a: %+8d    b: %+8d\n" , a , b );
  return 0;
}

namespace os_core
{
  
void
update
(
  int &  i_1st ,
  int &  i_2nd
)
{
  int
    i_1st_original = i_1st ,
    i_2nd_original = i_2nd ;
    
  i_1st 
    = i_1st_original + i_2nd_original;
  
  int i_difference 
    = i_1st_original - i_2nd_original;
    
  i_2nd = abs( i_difference );
  
  return;  
}

} // namespace os_core