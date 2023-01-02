/*
 * Builds the tree corresponding to a
 * directory hierarchy, and counts the
 * total number of lines in the files
 * residing in the hierarchy.
 * */

/*
 * Worked on this code on
 *   Jan  1, 2023 / Sun
 * */

#include "dir_info.hh"
#include "line_counter__with_threads.hh"

#include <cstdlib>
#include <iostream>
#include <memory>

int
main( int argc, char *argv[] )
{
  using namespace std;
  using namespace os_core::dir_utils;
  
  std::string  path_topmost
    (   std::string( getenv( "HOME" ) )
      + std::string( "/wdr/tasks/reports/all/00priority/urgent/stuff/work_in_progress/jobs/coding_test/dev/text_files" ) );
    
  if ( argc >= 2 )
    path_topmost = argv[1];
    
  /*
  DirTreeBuilder::flag_breadth_first_search = false;
  */
  
  try
  {
    DirTreeBuilder  obj_dtb( path_topmost );
    obj_dtb
      .build();
    
    /*
     * Shared pointer managing polymorphic pointer.
     * */
    std::shared_ptr<MassCounterOfLines>  obj_mcol_ptr
      = std::make_shared<MassCounterOfLines_WithThreads> 
          ( & obj_dtb );
    ( *obj_mcol_ptr )
      .setup_data_structures()
      .count()
      .report_brief();
  }
  catch ( Dir_IO_Exception &  obj_exc )
  {
    cout << endl << obj_exc.what() << endl;
    return 1;
  }
  
  return 0;
}