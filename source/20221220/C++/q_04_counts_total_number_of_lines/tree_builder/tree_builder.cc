/*
 * Member function bodies for tree builder.
 * */

/*
 * Worked on this code on
 *   Dec 26, 2022 / Mon
 * */

#include "tree_builder.hh"
#include "dir_info_extraction/dir_info.hh"

#include <iostream>
#include <iomanip>

namespace os_core
{
namespace dir_utils
{
  // static member variable initialization  
  bool  
  DirTreeBuilder::flag_breadth_first_search = true;
    
  
  UIntStringTupleType
  DirTreeNode
    ::get_depth_and_path
  ()
  {
    std::vector<std::string>  
      path_contents_vec;
    path_contents_vec.push_back( this->name );
    
    /*
     * Traverses the tree upwards until the topmost
     * node is found.
     * */
    unsigned int cnt = 0;
    if ( this->flag_has_parent )
    {
      auto node_current = this->parent;
      
      while ( true )
      {
        ++cnt;
        path_contents_vec.push_back( node_current->name );
        
        if ( node_current->flag_has_parent )
          node_current = node_current->parent;
        else
          break;
      } // while
    } // if
    
    return
      UIntStringTupleType
        (
          cnt ,
          os_core::str_utils::join_with_iterator
            (
              path_contents_vec.rbegin() ,
              path_contents_vec.rend() ,
              "/"
            )
        );
  } // function - get_depth_and_path
  
  DirTreeBuilder &
  DirTreeBuilder
    ::build
  ()
  {
    DTNPtrDeqType  nodes_deq;
    nodes_deq.clear();
    nodes_deq.push_back( node_topmost_ptr_ );
    
    /*
     * Designed to make use of either breadth-first
     * or depth-first approach.
     * */
    while ( ! nodes_deq.empty() )
    {
      /*
       * Get the node to be processed.
       * */
      auto node_current = nodes_deq.front();
      nodes_deq.pop_front();
      
      /*
       * Files and subdirectories information
       * extraction.
       * */
      auto depth_path_tuple
        = node_current->get_depth_and_path();
      FilesDirsExtractor obj_f_d_ext
        ( std::get<1>(depth_path_tuple) );
        
      /*
       * Record files in directory.
       * */
      node_current->files_vec
        = obj_f_d_ext.get_files_vec();
        
      /*
       * Record subdirectories in directory.
       * */
      ( node_current->subdirs_vec ).clear();
      for ( auto subdir_str : obj_f_d_ext.get_subdirs_vec() )
      {
        /*
         * In-place construction of subdirectory node.
         * */
        ( node_current->subdirs_vec ).emplace_back
          ( 
            std::make_shared<DirTreeNode>( subdir_str  ) 
          );
        /*
         * Set parent.
         * */
        ( ( node_current->subdirs_vec ).back() )
          -> flag_has_parent = true;
        ( ( node_current->subdirs_vec ).back() )
          -> parent = node_current;
      } // for subdir_str
      
      if ( flag_breadth_first_search )
      {
        /*
         * Operations for breadth first search,
         * with push_back.
         * */
        for ( auto item : node_current->subdirs_vec )
          nodes_deq.push_back( item );
      }
      else
      {
        /*
         * Operations for depth first search,
         * with push_front.
         * */
        for
          (
            auto it  = ( node_current->subdirs_vec ).rbegin() ;
                 it != ( node_current->subdirs_vec ).rend() ;
                 it++
          )
          nodes_deq.push_front( *it );
      }
    } // while
    
    return *this;
  } // function - build
  
  DirTreeBuilder &
  DirTreeBuilder
   ::print
  ()
  {
    using namespace std;
    
    auto nodes_all_deq
      = get_deque_of_all_nodes();
    
    for ( auto & item : nodes_all_deq )
    {
      cout << endl;
      cout 
        << "Directory :" << endl
        << "  " << item->name << endl;
        
      auto depth_path_tuple
        = item->get_depth_and_path();
      cout 
        << "Depth :" << endl
        << "  " << std::get<0>( depth_path_tuple ) << endl;
      cout 
        << "Path :" << endl
        << "  " << std::get<1>( depth_path_tuple ) << endl;
      
      std::string parent_name( "None" );
      if ( item->flag_has_parent )
        parent_name = item->parent->name;
      cout 
        << "Parent :" << endl
        << "  " << parent_name << endl;
        
      cout 
        << "Files :" << endl;
      for ( auto f_name : item->files_vec )
        cout << "  " << f_name;
      cout << endl;
      
      cout 
        << "Subdirectories :" << endl;
      for ( auto s_d : item->subdirs_vec )
        cout << "  " << s_d->name;
      cout << endl;
    } // for item
    
    return *this;
  } // function - print
  
  DTNPtrDeqType
  DirTreeBuilder
    ::get_deque_of_all_nodes
  ()
  {
    DTNPtrDeqType  nodes_all_deq ,
                   nodes_processed_deq;
    
    nodes_all_deq       .clear();
    nodes_processed_deq .clear();
    nodes_all_deq
      . push_back( node_topmost_ptr_ );
    nodes_processed_deq
      . push_back( node_topmost_ptr_ );
      
    while ( ! nodes_processed_deq.empty() )
    {
      auto node_current
        = nodes_processed_deq.front();
      nodes_processed_deq.pop_front();
      
      if ( flag_breadth_first_search )
      {
        /*
         * Operations for breadth first search,
         * with push_back.
         * */
        for ( auto item : node_current->subdirs_vec )
        {
          nodes_processed_deq . push_back( item );
          nodes_all_deq       . push_back( item );
        }
      } // if
      else
      {
        /*
         * Operations for depth first search,
         * with push_front.
         * */
        for
          (
            auto it  = ( node_current->subdirs_vec ).rbegin() ;
                 it != ( node_current->subdirs_vec ).rend() ;
                 it++
          )
        {
          nodes_processed_deq . push_front( *it );
          nodes_all_deq       . push_front( *it );
        }
      } // else
    } // while
    
    return nodes_all_deq;
  } // function - get_deque_of_all_nodes
  
} // namespace dir_utils
} // namespace os_core