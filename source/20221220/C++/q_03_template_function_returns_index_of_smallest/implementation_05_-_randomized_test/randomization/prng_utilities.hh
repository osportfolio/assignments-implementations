/*
 * Class definition for generation of
 * random variable instances that as an
 * ensemble obey the uniform distribution.
 * */

/*
 * Worked on this code on
 *   Dec 22, 2022 / Thu
 * */

#pragma once

#include <chrono>
#include <random>
#include <vector>

namespace  os_prng_utils
{
  
class PRNG_Uniform
{
// typedefs
public:
  using  LocalClassType =
    PRNG_Uniform;
#define  LocalClassTypeName  \
    PRNG_Uniform

// member variables
private:
  /*
   * Vectors (of single elements) below enable
   * in-place construction of class instances,
   * through 'emplace_back', which makes use
   * of variadic templates and perfect forwarding
   * to redirect ctor arguments to the ctor of
   * the class in question.
   * */
  
  unsigned
    seed_;
  std::vector< std::default_random_engine > 
    v_generator_;
  
  // distributions
  std::vector< std::uniform_real_distribution<double> > 
    v_dist_uniform_;
    
// ctor dtor
public:
  LocalClassTypeName
  ()
  {
    /*
     * Set the seed, based on the current time information.
     * */
    seed_ 
      = std::chrono::high_resolution_clock::now()
          .time_since_epoch().count();
    
    /*
     * Construct generator and distribution.
     * */
    v_generator_.clear();
    v_generator_.emplace_back( seed_ );
    
    // initialize commonly used distributions
    v_dist_uniform_.emplace_back( 0.0 , 1.0 );
  }
  
  ~LocalClassTypeName
  ()
  {}
  
// member functions
public:
  
  /*
   * 'rand_int' will implicitly make use of 'rand'.
   * */
  
  std::vector<double>
  rand
  (
    const unsigned int howMany ,
    const double       val_a = 0.0 , // inclusive
    const double       val_b = 1.0   // exclusive
  );
  
  std::vector<int>
  rand_int
  (
    const unsigned int howMany ,
    const int          val_a = 0 , // inclusive
    const int          val_b = 1   // exclusive
  );
  
// static member functions for demonstrations
public:
  
  static
  void
  print_random_doubles
  (
    const unsigned int howMany ,
    const double       val_a = 0.0 , // inclusive
    const double       val_b = 1.0   // exclusive
  );
  
  static
  void
  print_random_integers
  (
    const unsigned int howMany ,
    const int          val_a = 0 , // inclusive
    const int          val_b = 1   // exclusive
  );
  
#undef  LocalClassTypeName
}; // class PRNG_Uniform
  
} // namespace os_prng_utils