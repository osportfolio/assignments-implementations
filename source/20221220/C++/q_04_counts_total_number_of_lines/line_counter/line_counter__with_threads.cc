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
  
} // namespace dir_utils
} // namespace os_core