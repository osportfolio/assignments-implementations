/*
 * Class wrapper for C library functions. The library
 * is not indeed a library technically; the source code
 * file and header, "string_array.c" and "string_array.h",
 * respectively, are in the same project as this wrapper
 * class.
 * 
 * The wrapper makes use of a private shared pointer
 * with a custom deleter (since StringArrayContainer
 * pointer cannot be freed right away). Also I made
 * use of a macro of my design, with variadic template
 * and perfect forwarding features, to avoid clutter
 * in calling C functions with the wrapped object
 * pointer and additional arguments. The macro
 * automatically takes care of input parameter numbers
 * and individual types, and also the return type.
 * */

/*
 * Worked on this code on
 *                       Dec 13, 2022 / Tue
 * */

#pragma once

#include "string_array.h"

#include <memory>

#define PERFECT_FORWARDER_TO_WRAPPED_OBJ(prefix_,method_name_) \
  template <typename ... Args> \
  auto method_name_(Args && ... args) \
    -> decltype( prefix_##_##method_name_( this->managed_ptr_ , std::forward<Args>(args)... ) ) \
  { \
    return  prefix_##_##method_name_( this->managed_ptr_ , std::forward<Args>(args)... ); \
  }

namespace os_wrappers
{
  
class StringArrayWrapper
{
public:
  using LocalClassType
    = StringArrayWrapper;
#define LocalClassTypeName \
      StringArrayWrapper

private:
  using  wrapped_type
    = StringArrayContainer;
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
                StringArray_initialize() ,
                [] (wrapped_type * ptr)->void
                  {
                    StringArray_destroy(ptr);
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
  
  LocalClassTypeName             (const  LocalClassTypeName &)  = delete;
  LocalClassTypeName &  operator=(const  LocalClassTypeName &)  = delete;

// member functions
public:

  PERFECT_FORWARDER_TO_WRAPPED_OBJ(StringArray,add_string)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(StringArray,is_given_string_present)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(StringArray,get_length)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(StringArray,get_string_at_index)
  PERFECT_FORWARDER_TO_WRAPPED_OBJ(StringArray,print_information_and_content)
  
// static test function
public:
  static
  void
  test
  ();
  
#undef  LocalClassTypeName
}; // class StringArrayWrapper

#undef  PERFECT_FORWARDER_TO_WRAPPED_OBJ

} // namespace os_wrappers