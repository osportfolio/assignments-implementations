/*
 * Call each function registered with the same input
 * integers, and report the results.
 * */

/*
 * Worked on this code on
 *   Dec 22, 2022 / Thu
 * */

#include "updaters_testing.hh"

int 
main (void)
{
  using namespace updaters_testing;
  
  UpdaterFunctionsTester  obj_t;
  
  obj_t
    .demo_calls_all_available_functions( 2 , 3 )
    .demo_calls_all_available_functions( -44 , 13 );
  
  return 0;
}