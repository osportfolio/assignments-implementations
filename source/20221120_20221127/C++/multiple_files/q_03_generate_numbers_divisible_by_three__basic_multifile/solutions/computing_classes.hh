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
 * Reorganized code into a multiple source file project
 *              on Dec 2, 2022 / Fri
 * */

#pragma once

#include "utilities/character_operations.hh"

#include <set>
#include <vector>
#include <string>

namespace os_core
{
  
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
  std::vector<int>
    checker_, range_of_int_;
  
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
