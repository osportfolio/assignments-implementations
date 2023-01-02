/*
 * Random sequence generator for the custom
 * comparable class.
 * */

/*
 * Worked on this code on
 *   Jan  2, 2023 / Mon
 * */

#pragma once

#include "random_sequence_base.hh"
#include "rng_engine_static.hh"

#include "custom_comparable_class.hh"

namespace os_core
{
namespace random_sequence_generators
{

class ArrayRNG_CustomContainerOfIntegers
:
public
ArrayRNG_withIntervalSetting
  < os_core::custom_containers::ComparableItemContainer<int> >
{
// typedefs
public:
  using ContainerType
    = os_core::custom_containers::ComparableItemContainer<int>;

// ctor dtor
public:
  
  ArrayRNG_CustomContainerOfIntegers  
  (
    const ContainerType  interval_limit_left  ,
    const ContainerType  interval_limit_right
  )
  :
  ArrayRNG_withIntervalSetting<ContainerType>
    (
      interval_limit_left  ,
      interval_limit_right
    )
  {}
  
  virtual
  ~ArrayRNG_CustomContainerOfIntegers () = default;
  
// member functions
public:
  
  virtual
  std::shared_ptr<ContainerType>
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
            interval_limit_left_  . get_contained() , 
            interval_limit_right_ . get_contained() );
          
    /*
     * Define and initialize 'shared_ptr' with custom deleter.
     * Invoke move constructor of 'shared_ptr'. Custom deleters
     * cannot be set via 'make_shared'.
     * */
    auto  ptr 
      = std::move( std::shared_ptr<ContainerType>
          ( 
            /*
             * The parentheses in 'new ... () ,' is
             * necessary, and the 'ContainerType' class
             * should be constructed with zero arguments.
             * */
            new ContainerType[howMany]() ,
            [] ( ContainerType * managed_raw_ptr ) -> void
              {
                delete  []  managed_raw_ptr;
              }
          ) );
    
    /*
     * Copy the content of random custom type realizations
     * in the vector into the memory pointed to by the
     * raw pointer, which is in turn managed by 'ptr'.
     * */
    unsigned int cnt = 0;
    for ( const auto item : random_int_vec )
    {
      /*
       * Either of the below works. The second one invokes
       * the copy assignment operator.
       * */
      ptr.get()[ cnt++ ].set_contained ( item );
      // ptr.get()[ cnt++ ] = ContainerType( item );
    }
    
    return ptr;
  }
  
};

} // namespace random_sequence_generators
} // namespace os_core
