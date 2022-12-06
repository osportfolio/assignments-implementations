/*
 * Reorganized code into a multiple source file project
 *              on Dec 2, 2022 / Fri
 * */

#include "character_operations.hh"
#include "computing_classes.hh"

#include <memory>
#include <iostream>

int
main(void)
{
  using namespace os_utilities;
  using namespace os_core;
  using namespace std;
  
  using local_base_type
    = DivisibleByThreeGeneratorBase;
  using local_derived_type
    = DivisibleByThreeGeneratorWithListComputer;
  
  local_base_type::flag_debug
//     = true;
    = false;
    
  std::vector<std::string> s_inputs = 
    {
      "0081" ,
      "23" ,
      "22454"
    };

  std::vector< std::shared_ptr< local_base_type > >
    vec_of_sh_ptr;
    
  cout << endl;
  for ( auto item : s_inputs )
  {
    vec_of_sh_ptr.emplace_back
      ( 
        std::make_shared<local_base_type> 
          ( item )
      );
    ( vec_of_sh_ptr.back() )->solve();
      
    vec_of_sh_ptr.emplace_back
      ( 
        std::make_shared<local_derived_type> 
          ( item )
      );
    ( vec_of_sh_ptr.back() )->solve();
  } // for
  
  for ( auto & obj : vec_of_sh_ptr )
  {
    cout 
      << "Original String for Object:" << endl
      << "  " << obj->get_original_string() << endl
      << "Total Number of Generated Strings:" << endl
      << "  " 
      << obj->get_total_number_of_generated_strings() << endl;
      
    auto  sh_ptr_for_derived =
      std::dynamic_pointer_cast<local_derived_type>(obj);
    bool flag_can_be_dynamically_cast
      = ! ( ! sh_ptr_for_derived );
    
    cout
      << "Shared Pointer Can Be Dynamically Cast into That for Subclass:"
      << endl
      << "  " << ( flag_can_be_dynamically_cast ? "YES" : "NO" )
      << endl;
    
    if ( flag_can_be_dynamically_cast )
    {
      print_container_of_items
        (
          sh_ptr_for_derived
            ->get_list_of_generated_strings() ,
          "vector of generated strings"
        );
    } // if
    
    cout << endl;
  } // for
  
  return 0;
}