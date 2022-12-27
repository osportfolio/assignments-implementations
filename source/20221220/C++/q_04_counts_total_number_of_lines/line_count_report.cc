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

#include "line_counter.hh"

#include <cstdlib>

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
  
  DirTreeBuilder  obj_dtb( path_topmost );
  obj_dtb
    .build();
    
  MassCounterOfLines obj_mcol ( & obj_dtb );
  obj_mcol
    .setup_data_structures()
    .count()
    .report();
  
  return 0;
}