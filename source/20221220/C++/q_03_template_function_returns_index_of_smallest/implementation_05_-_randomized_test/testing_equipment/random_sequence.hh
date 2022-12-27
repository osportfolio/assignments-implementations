/*
 * Concrete random integer and double
 * array generator classes.
 * */

/*
 * Worked on this code on
 *   Dec 24-27, 2022 / Sat-Tue
 * */

#pragma once

#include "random_sequence_base.hh"
#include "rng_engine_static.hh"

#include <vector>
#include <cassert>

namespace os_core
{
namespace random_sequence_generators
{

class ArrayRNG_Integer
:
public
ArrayRNG_withIntervalSetting<int>
{
// ctor dtor
public:
  
  ArrayRNG_Integer  
  (
    const int  interval_limit_left  ,
    const int  interval_limit_right
  )
  :
  ArrayRNG_withIntervalSetting<int>
    (
      interval_limit_left  ,
      interval_limit_right
    )
  {}
  
  virtual
  ~ArrayRNG_Integer () = default;
  
// member functions
public:
  
  virtual
  std::shared_ptr<int>
  generate
  (
    const unsigned int howMany
  )
  {
    using namespace
      os_prng_utils_addenda;
      
    /*
     * Get reference to rng engine.
     * */
    auto & rng_engine 
      = os_prng_utils_addenda
          ::StaticPRNGInstanceHolder
          ::get();
    
    auto  random_int_vec
      = rng_engine.rand_int
          ( howMany , 
            interval_limit_left_ , interval_limit_right_ );
          
    /*
     * Define and initialize 'shared_ptr' with custom deleter.
     * Invoke move constructor of 'shared_ptr'. Custom deleters
     * cannot be set via 'make_shared'.
     * */
    auto  ptr 
      = std::move( std::shared_ptr<int>
          ( 
            new int[howMany] ,
            [] ( int * managed_raw_ptr ) -> void
              {
                delete  []  managed_raw_ptr;
              }
          ) );
    
    /*
     * Copy the content of random integer realizations
     * in the vector into the memory pointed to by the
     * raw pointer, which is in turn managed by 'ptr'.
     * */
    unsigned int cnt = 0;
    for ( const auto item : random_int_vec )
      ptr.get()[ cnt++ ] = item;
    
    return ptr;
  }
  
};
  

class ArrayRNG_Double
:
public
ArrayRNG_withIntervalSetting<double>
{
// ctor dtor
public:
  
  ArrayRNG_Double  
  (
    const double  interval_limit_left  ,
    const double  interval_limit_right
  )
  :
  ArrayRNG_withIntervalSetting<double>
    (
      interval_limit_left  ,
      interval_limit_right
    )
  {}
  
  virtual
  ~ArrayRNG_Double () = default;
  
// member functions
public:
  
  virtual
  std::shared_ptr<double>
  generate
  (
    const unsigned int howMany
  )
  {
    using namespace
      os_prng_utils_addenda;
      
    /*
     * Get reference to rng engine.
     * */
    auto & rng_engine 
      = os_prng_utils_addenda
          ::StaticPRNGInstanceHolder
          ::get();
    
    auto  random_double_vec
      = rng_engine.rand
          ( howMany , 
            interval_limit_left_ , interval_limit_right_ );
          
    /*
     * Define and initialize 'shared_ptr' with custom deleter.
     * Invoke move constructor of 'shared_ptr'. Custom deleters
     * cannot be set via 'make_shared'.
     * */
    auto  ptr 
      = std::move( std::shared_ptr<double>
          ( 
            new double[howMany] ,
            [] ( double * managed_raw_ptr ) -> void
              {
                delete  []  managed_raw_ptr;
              }
          ) );
    
    /*
     * Copy the content of random double realizations
     * in the vector into the memory pointed to by the
     * raw pointer, which is in turn managed by 'ptr'.
     * */
    unsigned int cnt = 0;
    for ( const auto item : random_double_vec )
      ptr.get()[ cnt++ ] = item;
    
    return ptr;
  }
  
};

} // namespace random_sequence_generators
} // namespace os_core
