/*
 * Abstract classes for random number generators.
 * */

/*
 * Worked on this code on
 *   Dec 24-27, 2022 / Sat-Tue
 * */

#pragma once

#include <memory>
#include <cassert>

namespace os_core
{
namespace random_sequence_generators
{

/*
 * Topmost class in the hierarchy with a
 * single purely virtual member function.
 * */
template
<typename ComparableType>
class ArrayRNG
{
public:
  
  ArrayRNG  () = default;
  
  virtual
  ~ArrayRNG () = default;
  
  virtual
  std::shared_ptr<ComparableType>
  generate
  (const unsigned int howMany) = 0;
  
}; // class ArrayRNG


/*
 * A subclass that is still abstract,
 * with functionality for setting the interval
 * in which the randomly generated numbers
 * will reside. Concrete subclasses for
 * integer and double array generation will
 * be derived from this one.
 * */
template
<typename ComparableType>
class ArrayRNG_withIntervalSetting
:
public
ArrayRNG<ComparableType>
{
// member variables
protected:
  ComparableType
    interval_limit_left_  ,
    interval_limit_right_ ;
  
// ctor dtor
public:
  ArrayRNG_withIntervalSetting
  (
    const ComparableType  interval_limit_left  ,
    const ComparableType  interval_limit_right
  )
  :
  ArrayRNG<ComparableType>()
  {
    set_interval_limits
      (
        interval_limit_left ,
        interval_limit_right
      );
  }
  
  virtual
  ~ArrayRNG_withIntervalSetting
  () = default;
  
// member functions
public:
  
  void
  set_interval_limits
  (
    const ComparableType  interval_limit_left  ,
    const ComparableType  interval_limit_right
  )
  {
    assert
      ( interval_limit_left < interval_limit_right );
    
    interval_limit_left_
      = interval_limit_left;
    interval_limit_right_
      = interval_limit_right;
  }
  
}; // class ArrayRNG_withIntervalSetting
  
} // namespace random_sequence_generators
} // namespace os_core