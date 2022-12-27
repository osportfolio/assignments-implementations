/*
 * Static member variable initialization.
 * */

/*
 * Worked on this code on
 *   Dec 24-27, 2022 / Sat-Tue
 * */

#include "rng_engine_static.hh"

namespace os_prng_utils_addenda
{
  
std::shared_ptr
  < os_prng_utils::PRNG_Uniform >
    StaticPRNGInstanceHolder::rng_engine_ptr_
      = std::make_shared<os_prng_utils::PRNG_Uniform> ();
  
} // namespace os_prng_utils_addenda