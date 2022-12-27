/*
 * Generate two random integers between
 * -50 inclusive and 50 exclusive. Call
 * the registered functions and report
 * the results. Repeat 5 times in 
 * succession.
 * */

/*
 * Worked on this code on
 *   Dec 23, 2022 / Fri
 * */

#include "updaters_testing.hh"

int 
main (void)
{
  using namespace updaters_testing;
  
  UpdaterFunctionsTester
    ::demo_calls_all_available_functions_for_random_integers
      ( -50 , 50 , 5 );
      
  return 0;
}