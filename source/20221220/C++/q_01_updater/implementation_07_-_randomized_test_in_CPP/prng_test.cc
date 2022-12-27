/*
 * Call static member functions generating
 * random doubles and integers. The right
 * limit is exclusive.
 * */

/*
 * Worked on this code on
 *   Dec 23, 2022 / Fri
 * */

#include "prng_utilities.hh"

int
main (void)
{
  using namespace os_prng_utils;
  
  PRNG_Uniform::print_random_doubles
    ( 8 );
  PRNG_Uniform::print_random_doubles
    ( 8 , -50 , 63 );
  
  /*
   * This one below generates random
   * integers in [0, 1). Therefore,
   * it should always print zeros.
   * */
  PRNG_Uniform::print_random_integers
    ( 8 );
    
  PRNG_Uniform::print_random_integers
    ( 8 , -2 , 5 );
  
  return 0;
}