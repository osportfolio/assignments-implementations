/*
 * Another test with a different main function.
 * */

/*
 * Reorganized code into a multiple source file project
 *              on Dec 2, 2022 / Fri
 * */

#include "character_operations.hh"
#include "computing_classes.hh"

#include <iostream>

int
main(void)
{
  using namespace os_utilities;
  using namespace os_core;
  using namespace std;
  
  using local_base_type
    = DivisibleByThreeGeneratorBase;
    
  local_base_type::flag_debug
//     = true;
    = false;
  
  std::string 
    s_input( "23" );
  local_base_type
    obj( s_input );
  
  obj.solve();
  
  cout 
    << "Original String for Object:" << endl
    << "  " << obj.get_original_string() << endl
    << "Total Number of Generated Strings:" << endl
    << "  " 
    << obj.get_total_number_of_generated_strings() << endl;
      
  return 0;
}