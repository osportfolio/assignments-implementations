/*
 * Member function bodies for 'PRNG_Uniform'.
 * */

/*
 * Worked on this code on
 *   Dec 22, 2022 / Thu
 * */

#include "prng_utilities.hh"

#include <algorithm>
#include <cmath>
#include <cassert>

#include <iostream>
#include <iomanip>
#include <cstdio>

namespace  os_prng_utils
{
  
  std::vector<double>
  PRNG_Uniform
    ::rand
  (
    const unsigned int howMany ,
    const double       val_a , // inclusive
    const double       val_b   // exclusive
  )
  {
    assert( howMany > 0 );
    assert( val_b > val_a );
    
    using namespace std;
    
    vector<double> current( howMany , 0.0 );
    
    unsigned int  cnt = 0;
    while ( cnt < howMany )
    {
      double  temp_val
        = v_dist_uniform_.front()( v_generator_.front() );
        
      /*
       * Eliminating an event with zero probability in theory.
       * */
      if ( temp_val == 1.0 )
        continue;
      
      current[cnt++] 
        = val_a + ( val_b - val_a ) * temp_val;
    } // while cnt
    
    return current;
  } // function - rand
  
  std::vector<int>
  PRNG_Uniform
    ::rand_int
  (
    const unsigned int howMany ,
    const int          val_a , // inclusive
    const int          val_b   // exclusive
  )
  {
    assert( howMany > 0 );
    assert( val_b > val_a );
    
    using namespace std;
    
    vector<int> i_vec;
    i_vec.clear();
    i_vec.reserve( howMany );
    
    /*
     * Generate double random variable instances first
     * with 'rand', and then process through 'transform'
     * into the vector 'i_vec' to be returned.
     * */
    auto double_vec = rand( howMany );
    transform
      (
        double_vec.begin() ,
        double_vec.end() ,
        back_inserter( i_vec ) ,
        [ val_a , val_b ]
          ( const double  item )->int
            {
              return
                (int) floor( val_a + ( val_b - val_a ) * item );
            }
      );
    
    return  i_vec;
  } // function - rand_int
  
  void
  PRNG_Uniform
    ::print_random_doubles
  (
    const unsigned int howMany ,
    const double       val_a , // inclusive
    const double       val_b   // exclusive
  )
  {
    using namespace std;
    
    PRNG_Uniform  obj;
    auto values_vec 
      = obj.rand( howMany , val_a , val_b );
      
    printf( 
      "\nRandom Doubles  Requested between %+8.2f and %+8.2f (%4d of them) :\n" ,
      val_a , val_b , howMany );
    for ( auto item : values_vec )
      printf( "  %+8.2f" , item );
    cout << endl;
  } // function - print_random_doubles
  
  void
  PRNG_Uniform
    ::print_random_integers
  (
    const unsigned int howMany ,
    const int          val_a , // inclusive
    const int          val_b   // exclusive
  )
  {
    using namespace std;
    
    PRNG_Uniform  obj;
    auto values_vec 
      = obj.rand_int( howMany , val_a , val_b );
      
    printf( 
      "\nRandom Integers Requested between %+8d and %+8d (%4d of them) :\n" ,
      val_a , val_b , howMany );
    for ( auto item : values_vec )
      printf( "  %+8d" , item );
    cout << endl;
  } // function - print_random_integers
  
} // namespace os_prng_utils