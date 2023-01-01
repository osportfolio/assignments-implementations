/*
 * Class definition for line counter class
 * with 'std::thread'.
 * */

/*
 * Worked on this code on
 *   Jan  1, 2023 / Sun
 * */

#pragma once

#include "line_counter.hh"

/*
#include <mutex>
*/

namespace os_core
{
namespace dir_utils
{
  
class MassCounterOfLines_WithThreads
:
public
MassCounterOfLines
{
// typedefs
public:
  using LocalClassType
    = MassCounterOfLines_WithThreads;
#define LocalClassTypeName \
      MassCounterOfLines_WithThreads
      
// member variables
private:
/*  
  std::mutex  
    mtx_;
*/

// ctor dtor
public:
  
  LocalClassTypeName
  (
    DirTreeBuilder *  builder
  )
  :
  MassCounterOfLines ( builder )
  {}
  
  virtual
  ~LocalClassTypeName
  ()
  {}
  
// member functions
public:
  
  virtual
  LocalClassType &
  count
  ();
  
// member functions
private:
  
  void
  count_lines_for_single_file
  (
    unsigned int  index
  );
      
#undef  LocalClassTypeName
}; // class MassCounterOfLines_WithThreads
  
} // namespace dir_utils
} // namespace os_core