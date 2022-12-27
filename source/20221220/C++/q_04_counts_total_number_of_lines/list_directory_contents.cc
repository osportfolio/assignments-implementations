/*
 * Builds tree and prints information on
 * a directory hierarchy, with the files
 * and subdirectories residing in it.
 * */

/*
 * Worked on this code on
 *   Dec 26, 2022 / Mon
 * */

#include "tree_builder.hh"

#include <iostream>

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
  DirTreeBuilder  obj( path_topmost );
  obj
    .build()
    .print();
    
  return 0;
}