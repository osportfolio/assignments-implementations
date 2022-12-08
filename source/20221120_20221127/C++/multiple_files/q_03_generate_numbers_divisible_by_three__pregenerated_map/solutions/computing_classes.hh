/*
 * Given a string of digits each in the range from
 * 0 to 9, generates all the strings that correspond
 * to numbers that are divisible by three, which
 * are allowed to be devised only through modifications
 * on each of the digits in the original string.
 * Returns the total number of such strings; naturally
 * the original string is not included in the count
 * even if its corresponding number is divisible by three.
 * */

/*
 * Incorporated a pre-generated map into the class definitions.
 *              on Dec 8, 2022 / Thu
 * */

#pragma once

#include "utilities/character_operations.hh"

#include <set>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <string>
#include "boost/functional/hash.hpp"

namespace os_types
{

using digit_remainder_tuple_type
  = std::tuple<int, int>;
  
using vector_of_int_type
  = std::vector<int>;

/* See the answer at:
 *   https://stackoverflow.com/questions/20834838/using-tuple-in-unordered-map
 * */
using KeyInMapType 
  = digit_remainder_tuple_type;
struct KeyHash {
  std::size_t operator()(const KeyInMapType & key) const
  {
    return boost::hash_value(key);
  }
};

using tuple_to_vec_of_int_map_type
  = std::unordered_map< KeyInMapType ,
                        vector_of_int_type ,
                        KeyHash >;

} // namespace os_types


namespace os_core
{
using namespace os_types;

class PregeneratedCheckerContainer
{
// typedefs
public:
  using LocalClassType =
    PregeneratedCheckerContainer;
#define  LocalClassTypeName  \
    PregeneratedCheckerContainer

// static member variables
private:
  static
  std::vector<int>
    checker_, range_of_int_;
    
  tuple_to_vec_of_int_map_type
    tuple_to_vec_map_;

// ctor dtor
public:
  
  LocalClassTypeName
  ();
  
  virtual
  ~LocalClassTypeName
  () = default;
  
// getters
public:
  
  tuple_to_vec_of_int_map_type &
  get_checker_map
  ()
  {
    return tuple_to_vec_map_;
  }
  
#undef  LocalClassTypeName
}; // class PregeneratedCheckerContainer
  
class DivisibleByThreeGeneratorBase
{
// typedefs
public:
  using LocalClassType =
    DivisibleByThreeGeneratorBase;
#define  LocalClassTypeName  \
    DivisibleByThreeGeneratorBase

// static member variables
public:
  static
  bool  flag_debug;
  
// static member variables
protected:
  static
  PregeneratedCheckerContainer
    checker_map_container_obj_;
  
// member variables
protected:
  std::string
    s_input_;
  
  std::vector<int>
    num_;
  int
    sum_of_num_;
  int
    rem_;
    
  int 
    total_;
    
// ctor dtor  
public:
  
  LocalClassTypeName
  (
    std::string  S
  );
  
  virtual
  ~LocalClassTypeName
  () = default;
  
public:
  
  LocalClassType &
  solve
  ();
  
  int
  get_total_number_of_generated_strings
  ()
  const
  {
    return  total_;
  }
  
  std::string
  get_original_string
  ()
  const
  {
    return  s_input_;
  }
  
protected:
  
  virtual
  LocalClassType &
  append_to_set_of_generated_strings
  (
    int 
      cnt ,
    const std::vector<int> & 
      checker_current
  )
  {
    return *this;
  }
  
  virtual
  LocalClassType &
  compute_list_of_generated_strings
  ()
  {
    return *this;
  }
  
#undef  LocalClassTypeName  
}; // class DivisibleByThreeGeneratorBase


class DivisibleByThreeGeneratorWithListComputer
:
public
DivisibleByThreeGeneratorBase
{
// typedefs
public:
  using LocalClassType =
    DivisibleByThreeGeneratorWithListComputer;
#define  LocalClassTypeName  \
    DivisibleByThreeGeneratorWithListComputer

// member variables
protected:
  std::set<std::string>  
    generated_strings__set_;
  std::vector<std::string>
    generated_strings_;
    
// ctor dtor
public:

  LocalClassTypeName
  (
    std::string  S
  )
  :
  DivisibleByThreeGeneratorBase(S)
  {
    generated_strings__set_.clear();
    generated_strings_.clear();
  } // ctor
  
  virtual
  ~LocalClassTypeName
  () {}
  
// getters
public:
  
  const std::vector<std::string> &
  get_list_of_generated_strings
  ()
  const
  {
    return  generated_strings_;
  }
  
// computing member functions
protected:
  virtual
  LocalClassType &
  append_to_set_of_generated_strings
  (
    int 
      cnt ,
    const std::vector<int> &
      checker_current
  );
  
  virtual
  LocalClassType &
  compute_list_of_generated_strings
  ();
  
#undef  LocalClassTypeName
}; // class DivisibleByThreeGeneratorWithListComputer

} // namespace os_core
