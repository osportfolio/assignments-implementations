/*
 * Tree builder class definition for a
 * directory tree, with nodes to hold
 * subdirectory and files information.
 * */

/*
 * Worked on this code on
 *   Dec 26, 2022 / Mon
 * */

#pragma once

#include <vector>
#include <deque>
#include <tuple>
#include <string>
#include <sstream>
#include <memory>

namespace os_core
{

namespace str_utils
{
  
/*
 * A function template to provide the
 * join functionality for iterable containers
 * of particularly strings.
 * */
template
< typename IteratorType >
std::string
join_with_iterator
(
  IteratorType  begin ,
  IteratorType  end ,
  std::string   delimiter
)
{
  unsigned int no_total = 0;
  for ( auto it = begin ; it != end ; it++ )
    ++no_total;
  
  using namespace std;
  stringstream  ss;
  
  unsigned int  cnt = 0;
  for ( auto it = begin ; it != end ; it++ )
  {
    ss << *it;
    if ( ++cnt < no_total )
      ss << delimiter;
  }
  
  return ss.str();
} // function - join_with_iterator
  
} // namespace str_utils
  
namespace dir_utils
{
  
using DTNPtrType
  = std::shared_ptr< class DirTreeNode >;
using DTNPtrVecType
  = std::vector< DTNPtrType >;
using DTNPtrDeqType
    = std::deque< DTNPtrType >;
  
using UIntStringTupleType
  = std::tuple< unsigned int , std::string >;
  
/*
 * Structure definition for the nodes
 * to be used in building the tree.
 * */
struct DirTreeNode
{
/*
 * typedefs
 * */  
  using LocalClassType
    = DirTreeNode;
#define LocalClassTypeName \
      DirTreeNode
      
/*
 * Member variables
 * */      
  DTNPtrType  parent;
  
  DTNPtrVecType
    subdirs_vec;
  std::vector< std::string >
    files_vec;
  
  std::string name;
  
  bool flag_has_parent;
      
/*
 * ctor dtor
 * */  
  LocalClassTypeName  
  (
    std::string  name
  )
  :
  name(name)
  {
    reset();
  }
  
  ~LocalClassTypeName () {}
  
/*
 * Member functions
 * */

  LocalClassType &
  reset
  ()
  {
    subdirs_vec.clear();
    files_vec  .clear();
    
    flag_has_parent = false;
    
    return *this;
  }
  
  UIntStringTupleType
  get_depth_and_path
  ();
      
#undef  LocalClassTypeName
}; // struct DirTreeNode
  

/*
 * The tree builder class.
 * */
class DirTreeBuilder
{
// typedefs
public:
  using LocalClassType
    = DirTreeBuilder;
#define LocalClassTypeName \
      DirTreeBuilder
  
// member variables - static
public:
  
  static
  bool  flag_breadth_first_search;
  
// member variables
private:
  
  std::string  path_topmost_;
  DTNPtrType   node_topmost_ptr_;
  
// ctor dtor
public:
  
  LocalClassTypeName
  (
    std::string  path_topmost
  )
  :
  path_topmost_
    (path_topmost) ,
  node_topmost_ptr_
    ( std::make_shared<DirTreeNode>( path_topmost ) )
  {}
  
  ~LocalClassTypeName
  ()
  {}
  
// member functions
public:
  
  DTNPtrType
  get_node_topmost_ptr
  ()
  {
    return node_topmost_ptr_;
  }
  
  DTNPtrDeqType
  get_deque_of_all_nodes
  ();
  
// member functions
public:
  
  DirTreeBuilder &
  build
  ();
  
  DirTreeBuilder &
  print
  ();
  
#undef  LocalClassTypeName
}; // class DirTreeBuilder

} // namespace dir_utils
} // namespace os_core