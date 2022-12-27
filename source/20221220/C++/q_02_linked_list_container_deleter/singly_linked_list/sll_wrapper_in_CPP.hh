/*
 * Class wrapper for C library functions. The library
 * is not indeed a library technically; the source code
 * file and header are in the same project as this wrapper
 * class.
 * 
 * The wrapper makes use of a private shared pointer
 * with a custom deleter. Also I made use of two macros 
 * of my design that are very similar, with variadic template
 * and perfect forwarding features, to avoid clutter
 * in calling C functions with the wrapped object
 * pointer and additional arguments. The macro design
 * automatically takes care of input parameter numbers
 * and individual types, and also the return type.
 * */

/*
 * Worked on this code on
 *   Dec 25, 2022 / Sun
 * */

#pragma once

#include "singly_linked_list_in_C.h"

#include <memory>

#define PERFECT_FORWARDER_TO_WRAPPED_OBJ(prefix_,method_name_) \
  template <typename ... Args> \
  auto method_name_(Args && ... args) \
    -> decltype( prefix_##_##method_name_( this->managed_ptr_ , std::forward<Args>(args)... ) ) \
  { \
    return  prefix_##_##method_name_( this->managed_ptr_ , std::forward<Args>(args)... ); \
  }
  
#define PERFECT_FORWARDER_TO_WRAPPED_OBJ_WITH_FREE(prefix_,method_name_) \
  template <typename ... Args> \
  auto method_name_##_with_free(Args && ... args) \
    -> void \
  { \
    auto * ptr = prefix_##_##method_name_( this->managed_ptr_ , std::forward<Args>(args)... ); \
    if ( ptr ) free( ptr ); \
    return; \
  }

namespace os_wrappers
{

class SinglyLinkedListWrapper
{
public:
  using LocalClassType
    = SinglyLinkedListWrapper;
#define LocalClassTypeName \
      SinglyLinkedListWrapper
      
private:
  using  wrapped_type
    = SLL_Node *;
  using  local_sh_ptr_type
    = std::shared_ptr<wrapped_type>;
  
  local_sh_ptr_type
    internal_sh_ptr_;
    
  wrapped_type *
    managed_ptr_;

// ctor dtor
public:
  LocalClassTypeName
  ()
  {
    // Shared pointer with custom deleter
    internal_sh_ptr_
      = std::move
          (
            local_sh_ptr_type
              ( 
                SinglyLinkedList_construct() ,
                [] (wrapped_type * ptr)->void
                  {
                    SinglyLinkedList_destruct(ptr);
                  }
              )
          );
    managed_ptr_
      = internal_sh_ptr_.get();
  }
  
  ~LocalClassTypeName
  ()
  {
    // Custom deleter takes care of destruction.
  }
  
  /*
   * Copy Ctor
   * */
  LocalClassTypeName             
  (const  LocalClassTypeName &  other)
  {
    internal_sh_ptr_
      = std::move( generate_value_copy_(other) );
    managed_ptr_
      = internal_sh_ptr_.get();
  }
  
  /*
   * Copy Assignment Operator - Value Copy Preferred
   * */
  LocalClassTypeName &  operator=
  (const  LocalClassTypeName &  other)
  {
    internal_sh_ptr_
      = std::move( generate_value_copy_(other) );
    managed_ptr_
      = internal_sh_ptr_.get();
      
    return *this;
  }
  
// ctor helpers
private:
  
  local_sh_ptr_type
  generate_value_copy_
  (
    const  LocalClassTypeName &  other
  )
  {
    // Shared pointer with custom deleter
    return
      local_sh_ptr_type
        ( 
          SinglyLinkedList_copy( other.managed_ptr_ ) ,
          [] (wrapped_type * ptr)->void
            {
              SinglyLinkedList_destruct(ptr);
            }
        );
  } // function - generate_value_copy_

// member functions
public:
  
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,isEmpty)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,size)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,front)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,back)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,insertAtIndex)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,push_back)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,push_front)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,removeAtIndex)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,pop_back)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,pop_front)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(SinglyLinkedList,getAtIndex)
  
  PERFECT_FORWARDER_TO_WRAPPED_OBJ_WITH_FREE(SinglyLinkedList,removeAtIndex)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ_WITH_FREE(SinglyLinkedList,pop_back)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ_WITH_FREE(SinglyLinkedList,pop_front)
  
public:

  void
  print
  ();
  
#undef  LocalClassTypeName
}; // class SinglyLinkedListWrapper
  
#undef  PERFECT_FORWARDER_TO_WRAPPED_OBJ
#undef  PERFECT_FORWARDER_TO_WRAPPED_OBJ_WITH_FREE
  
} // namespace os_wrappers