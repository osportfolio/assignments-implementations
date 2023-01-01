/*
 * Class definition for line counter.
 * */

/*
 * Worked on this code on
 *   Dec 26, 2022 / Mon
 * */

#pragma once

#include "tree_builder/tree_builder.hh"

#include <vector>
#include <string>

namespace os_core
{
namespace dir_utils
{
  
using LCICVecType
  = std::vector< struct LineCountInfoContainer >;
  
/*
 * Structure for holding the results
 * of the computation concerning each file.
 * */
struct LineCountInfoContainer
{
  std::string   file_path;
  unsigned int  no_lines;
  unsigned int  no_lines_blank;
  int           thread_index;
  
  LineCountInfoContainer  ()
  {
    reset();
  }
  ~LineCountInfoContainer () = default;
  
  LineCountInfoContainer &
  reset
  ()
  {
    file_path      = "";
    no_lines       = 0;
    no_lines_blank = 0;
    thread_index   = 0;
    return  *this;
  }
};
  
/*
 * Class definition for counting the lines
 * in each file residing in a directory
 * hierarchy.
 * */
class MassCounterOfLines
{
// typedefs
public:
  using LocalClassType
    = MassCounterOfLines;
#define LocalClassTypeName \
      MassCounterOfLines
   
// member variables
protected:
  
  DirTreeBuilder *  
    builder_;
  
  LCICVecType
    lcic_vec_;
   
// ctor dtor
public:
  
  LocalClassTypeName
  (
    DirTreeBuilder *  builder
  )
  :
  builder_ ( builder )
  {
    lcic_vec_.clear();
  }
  
  virtual
  ~LocalClassTypeName
  ()
  {}

// member functions
public:
  
  LocalClassType &
  reset
  ()
  {
    builder_ = NULL;
    lcic_vec_.clear();
    return  *this;
  }
  
  LocalClassType &
  set_builder
  (
    DirTreeBuilder *  builder
  )
  {
    builder_ = builder;
    return  *this;
  }
  
  LocalClassType &
  setup_data_structures
  ();
  
  virtual
  LocalClassType &
  count
  ();
  
  LocalClassType &
  report
  ();
  
  LocalClassType &
  report_brief
  ();
  
#undef  LocalClassTypeName
};
  
} // namespace dir_utils
} // namespace os_core