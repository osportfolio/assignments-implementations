/*
 * A demo for calling each implementation for
 * "index_of_smallest" on a given array.
 * */

/*
 * Worked on this code on
 *   Dec 24-27, 2022 / Sat-Tue
 * */

#include "index_of_smallest_testing.hh"

int
main (void)
{
  using namespace std;
  using namespace 
    index_of_smallest_testing;
  
  int int_array[4] = { 1 , -7 , 0 , 3 };
  
  IndexOfSmallestTester<int> obj_t;
  
  obj_t.demo_calls_all_available_functions
    ( int_array , sizeof(int_array) / sizeof(int) );

  return 0;
}