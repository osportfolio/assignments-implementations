/*
 * Comparable type container class template.
 * Only the 'less than' operator is overloaded
 * for comparisons.
 * */

/*
 * Worked on this code on
 *   Jan  2, 2023 / Mon
 * */

#pragma once

#include <utility>

namespace os_core
{
namespace custom_containers
{
  
template
< typename ComparableType >
class ComparableItemContainer
{
// typedefs
public:
  using  LocalClassType =
    ComparableItemContainer;
#define  LocalClassTypeName  \
    ComparableItemContainer
  
// member variables 
private:
  ComparableType  contained_;
  
// ctor dtor
public:
  
  LocalClassTypeName
  ()
  {}
  
  LocalClassTypeName
  (
    ComparableType  to_be_contained
  )
  :
  contained_( to_be_contained )
  {}
  
  ~LocalClassTypeName
  () = default;
  
  // copy ctor
  LocalClassTypeName             
  (const  LocalClassTypeName &  other)
  {
    contained_ = other.contained_;
  }
  
  // copy assignment operator
  LocalClassTypeName &  operator=
  (       LocalClassTypeName    other)
  {
    other.swap( *this );
    return  *this;
  }
  
// swap
private:
  
  /*
   * swap function used in the copy and swap
   * idiom.
   * */
  void 
  swap
  (
    LocalClassTypeName &  other
  )
  {
    using std::swap;
    swap ( this->contained_ , other.contained_ );
  }
  
// setters getters
public:
  
  ComparableType
  get_contained
  ()
  const
  {
    return contained_;
  }
  
  LocalClassType &
  set_contained
  (
    const
    ComparableType  to_be_contained
  )
  {
    contained_ = to_be_contained;
    return *this;
  }
  
#undef  LocalClassTypeName
}; // class ComparableItemContainer

/*
 * Non-member and non-friend operator overload
 * */
template
< typename ComparableType >
bool 
operator < 
( 
  const 
    ComparableItemContainer<ComparableType> &  lhs , 
  const 
    ComparableItemContainer<ComparableType> &  rhs 
)
{
    return lhs.get_contained() < rhs.get_contained();
}
  
} // namespace custom_containers
} // namespace os_core