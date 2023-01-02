/*
 * OpenMP implementation for parallelizing
 * line counts. Class member function bodies
 * in this file.
 * */

/*
 * Worked on this code on
 *   Jan  2, 2023 / Mon
 * */

#include "line_counter__with_OpenMP.hh"

/*
 * Utilizing OpenMP for multithreading.
 * */
#include <omp.h>

namespace os_core
{
namespace dir_utils
{
  
  MassCounterOfLines_WithOpenMP &
  MassCounterOfLines_WithOpenMP
    ::count
  ()
  {
    using namespace std;
    
    int thread_index;
    
    /*
     * OpenMP for multithreading.
     * */
    #pragma omp parallel private(thread_index)
    {
      #pragma omp for schedule(static) nowait
      for ( unsigned int
              kk = 0 ;
              kk < lcic_vec_.size() ;
            ++kk
          )
      {
        auto & item = lcic_vec_[kk];
      
        thread_index      = omp_get_thread_num();
        item.thread_index = thread_index;
      
        count_lines_for_single_file(kk);
      
      } // for item
    } // pragma omp
    
    return *this;
  } // function - count
  
} // namespace dir_utils
} // namespace os_core