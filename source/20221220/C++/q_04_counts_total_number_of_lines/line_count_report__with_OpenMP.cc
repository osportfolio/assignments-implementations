/*
 * Builds the tree corresponding to a
 * directory hierarchy, and counts the
 * total number of lines in the files
 * residing in the hierarchy.
 * */

/*
 * Worked on this code on
 *   Dec 26, 2022 / Mon
 * */

#include "dir_info.hh"
#include "line_counter__with_OpenMP.hh"

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
  
  std::shared_ptr<DirTreeBuilder>
    obj_dtb_ptr;
    
  try
  {
    obj_dtb_ptr
      = std::make_shared<DirTreeBuilder> ( path_topmost );
    obj_dtb_ptr
      ->build();
  }
  catch ( Dir_IO_Exception &  obj_exc )
  {
    cout << endl << obj_exc.what() << endl;
    return 1;
  }
  
  MassCounterOfLines_WithOpenMP 
    obj_mcol ( obj_dtb_ptr.get() );
  obj_mcol
    .setup_data_structures()
    .count()
    .report();
  
  return 0;
}