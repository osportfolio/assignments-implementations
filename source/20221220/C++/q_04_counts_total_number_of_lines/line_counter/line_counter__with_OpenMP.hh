/*
 * OpenMP implementation for parallelizing
 * line counts. Class definition in this file.
 * */

/*
 * Worked on this code on
 *   Jan  2, 2023 / Mon
 * */

#pragma once

#include "line_counter.hh"

namespace os_core
{
namespace dir_utils
{
  
class MassCounterOfLines_WithOpenMP
:
public
MassCounterOfLines
{
// typedefs
public:
  using LocalClassType
    = MassCounterOfLines_WithOpenMP;
#define LocalClassTypeName \
      MassCounterOfLines_WithOpenMP
      
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
      
#undef  LocalClassTypeName
}; // class MassCounterOfLines_WithOpenMP
  
} // namespace dir_utils
} // namespace os_core