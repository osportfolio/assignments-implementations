/*
 * Member function class bodies for line counter class
 * with 'std::thread'.
 * */

/*
 * Worked on this code on
 *   Jan  1, 2023 / Sun
 * */


#include "line_counter__with_threads.hh"

#include <thread>
#include <vector>
#include <algorithm>
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
  
  MassCounterOfLines_WithThreads &
  MassCounterOfLines_WithThreads
    ::count
  ()
  {
    using namespace std;
    
    std::vector<std::thread>  threads_vec;
    threads_vec.reserve( lcic_vec_.size() );
    
    for ( unsigned int
            kk = 0 ;
            kk < lcic_vec_.size() ;
          ++kk
        )
    {
      threads_vec.emplace_back
        (
          std::move
            (
              thread( & MassCounterOfLines_WithThreads
                          ::count_lines_for_single_file , 
                      this , kk )
            )
        );
    } // for kk
    
    for ( auto & item : threads_vec )
      item.join();
    
    return *this;
  } // function - count
  
  void
  MassCounterOfLines_WithThreads
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
  
} // namespace dir_utils
} // namespace os_core