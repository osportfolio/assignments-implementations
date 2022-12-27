/*
 * A class that possesses an rng engine instance
 * as a static member variable, so that initialization
 * for the indicated instance will be carried out
 * only once. The engine is to be used through its
 * references communicated to various scopes within
 * the current project.
 * */

/*
 * Worked on this code on
 *   Dec 24-27, 2022 / Sat-Tue
 * */

#pragma once

#include "randomization/prng_utilities.hh"

#include <memory>

namespace os_prng_utils_addenda
{
  
class StaticPRNGInstanceHolder
{
// typedefs
public:
  using  LocalClassType =
    StaticPRNGInstanceHolder;
#define  LocalClassTypeName  \
    StaticPRNGInstanceHolder
    
// member variables
private:
  
  static
  std::shared_ptr
    < os_prng_utils::PRNG_Uniform >
      rng_engine_ptr_;
    
// ctor dtor
public:
  LocalClassTypeName  () = delete;
  ~LocalClassTypeName () = delete;

// member functions
public:
  
  static
  os_prng_utils::PRNG_Uniform &
  get
  ()
  {
    return  *rng_engine_ptr_;
  }
  
#undef  LocalClassTypeName
};
  
} // namespace os_prng_utils_addenda
