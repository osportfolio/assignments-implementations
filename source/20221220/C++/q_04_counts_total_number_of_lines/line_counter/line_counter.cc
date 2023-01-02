/*
 * Member function bodies for the
 * line counter class.
 * */

/*
 * Worked on this code on
 *   Dec 26, 2022 / Mon
 * */

#include "line_counter.hh"

#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

namespace os_core
{
namespace dir_utils
{

  /*
   * Populates a vector of
   * structure containers, each of
   * which will be used to store
   * computation results for a file.
   * */
  MassCounterOfLines &
  MassCounterOfLines
    ::setup_data_structures
  ()
  {
    auto nodes_deq
      = builder_->get_deque_of_all_nodes();
      
    lcic_vec_.clear();
    for ( auto & item : nodes_deq )
    {
      if ( (item->files_vec) . empty() )
        continue;
      
      auto depth_path_tuple
        = item->get_depth_and_path();
      for ( auto fname : item->files_vec )
      {
        lcic_vec_.emplace_back();
        lcic_vec_.back().file_path 
          = std::get<1>( depth_path_tuple ) + "/" + fname;
      } // for fname
    } // for item
      
    return  *this;
  }
  
  /*
   * Inspired by solutions at
   *   https://stackoverflow.com/questions/55977686/how-to-read-text-file-lines-into-vectors
   *   https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c
   *   https://stackoverflow.com/questions/10058606/splitting-a-string-by-a-character
   * */
  void
  MassCounterOfLines
    ::count_lines_for_single_file
  (
    unsigned int  index
  )
  {
    auto & item = lcic_vec_[index];
      
    std::ifstream  file_in ( item.file_path );
    if ( file_in )
    {
      /*
       * Read whole file into a string.
       * */
      std::ostringstream  
        ss;
      ss << file_in.rdbuf();
      std::string  
        content_str = ss.str();
          
      /*
       * Total number of lines in file is
       * "1 + cnt".
       * */
      unsigned int cnt
        = std::count_if
            (
              content_str.c_str() ,
              content_str.c_str()
                + strlen( content_str.c_str() ),
              []  ( const char c ) -> bool
                  { return ( c == '\n' ); }
            );
      item.no_lines = 1 + cnt;
        
      /*
       * Count the number of blank lines.
       * */
      cnt = 0;
      std::stringstream  ss_for_blank;
      ss_for_blank << content_str;
      std::string  segment;
      while ( std::getline(ss_for_blank, segment, '\n') )
      {
        if ( segment == std::string( "" ) )
          ++cnt;
      } // while
      /*
       * A fix for files ending with '\n'.
       * */
      if ( content_str.c_str()
             [ -1 + strlen( content_str.c_str() ) ] == '\n' )
        ++cnt;
      item.no_lines_blank = cnt;
        
      /*
       * Close.
       * */
      file_in.close();
    } // if
    else
    {
      /*
      cout << "Could not open file." << endl;
      */
    } // else
      
    return;
  } // function - count_lines_for_single_file
  
  
  /*
   * Used to report findings.
   * */
  MassCounterOfLines &
  MassCounterOfLines
    ::report
  ()
  {
    using namespace std;
    
    /*
     * Computations for threading.
     * */
    auto thread_index__iterators_for_min_max
      = std::minmax_element
          (
            lcic_vec_.begin() ,
            lcic_vec_.end() ,
            []( 
                const LineCountInfoContainer & 
                  container_item_1st ,
                const LineCountInfoContainer & 
                  container_item_2nd
              )
              {
                return
                  ( 
                    container_item_1st.thread_index
                    <
                    container_item_2nd.thread_index
                  );
              }
          );
    
    /*
     * A map to hold the number of times each thread index 
     * was at work in the computation of results.
     * */
    std::map<int, unsigned int>
      thread_index_to_count_map;
    auto & pair_temp
      = thread_index__iterators_for_min_max;
    for ( 
          int kk =  (*(pair_temp.first)) .thread_index ;
              kk <= (*(pair_temp.second)).thread_index ;
            ++kk  
        )
    {
      thread_index_to_count_map[kk]
        = std::count_if
            (
              lcic_vec_.begin() ,
              lcic_vec_.end() ,
              [kk] 
                ( const LineCountInfoContainer & 
                     container_item )
                {
                  return ( container_item.thread_index == kk );
                }
            );
    } // for kk
          
    /*
     * Report
     * */
    unsigned int  
      total_no_lines = 0 ,
      total_no_lines_blank = 0 ;
    
    cout << endl;
    for ( auto & item : lcic_vec_ )
    {
      cout << endl
        << "File :" << endl
        << "  " << item.file_path << endl
        << "Number of Lines :" << endl
        << "  " << item.no_lines << endl
        << "Number of Blank Lines :" << endl
        << "  " << item.no_lines_blank << endl;
      total_no_lines 
        += item.no_lines;
      total_no_lines_blank
        += item.no_lines_blank;
    }
    
    cout << endl;
    for ( 
          int kk =  (*(pair_temp.first)) .thread_index ;
              kk <= (*(pair_temp.second)).thread_index ;
            ++kk  
        )
    {
      cout 
        << "Total Number of Computations Marked with Thread Index "
        << kk << " :" << endl
        << "  " << thread_index_to_count_map[kk] << endl;
    } // for kk
    
    cout << endl;
    cout 
      << "Total Number of Files :" << endl
      << "  " << lcic_vec_.size() << endl
      << "Total Number of Lines :" << endl
      << "  " << total_no_lines << endl
      << "Total Number of Blank Lines :" << endl
      << "  " << total_no_lines_blank << endl;
    
    return  *this;
  } // function - report
  
  MassCounterOfLines &
  MassCounterOfLines
    ::report_brief
  ()
  {
    using namespace std;
    
    unsigned int  
      total_no_lines = 0 ,
      total_no_lines_blank = 0 ;
    
    for ( auto & item : lcic_vec_ )
    {
      total_no_lines 
        += item.no_lines;
      total_no_lines_blank
        += item.no_lines_blank;
    }
    
    cout << endl;
    cout 
      << "Total Number of Files :" << endl
      << "  " << lcic_vec_.size() << endl
      << "Total Number of Lines :" << endl
      << "  " << total_no_lines << endl
      << "Total Number of Blank Lines :" << endl
      << "  " << total_no_lines_blank << endl;
    
    return *this;
  } // function - report_brief
  
} // namespace dir_utils
} // namespace os_core