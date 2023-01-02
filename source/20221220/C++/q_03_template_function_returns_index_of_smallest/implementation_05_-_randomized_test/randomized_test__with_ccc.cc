/*
 * Randomized test with a custom container class whose
 * instances are comparable only through the 'less than'
 * operator.
 * */

/*
 * Worked on this code on
 *   Jan  2, 2023 / Mon
 * */

#include "index_of_smallest_testing.hh"
#include "random_sequence_derived_ccc.hh"

#include <iostream>
#include <memory>

namespace os_test
{
  void
  single_array_check_with_ccc
  ()
  {
    using namespace std;
    using namespace 
      index_of_smallest_testing;
      
    using local_type
      = os_core::custom_containers::ComparableItemContainer<int>;
    
    /*
     * Default construction from an initializer list of integers 
     * works. Check the second and more concise initialization for
     * 'ccc_array' that is actually uncommented below.
     * */
    /*
    local_type ccc_array[] 
      = { local_type( 1) , 
          local_type(-7) , 
          local_type( 0) , 
          local_type( 3) };
    */
    local_type ccc_array[] = { 1 , -7 , 0 , 3 };
  
    IndexOfSmallestTester<local_type> obj_t;
  
    obj_t.demo_calls_all_available_functions
      ( ccc_array , sizeof(ccc_array) / sizeof(local_type) );
  }
  
  void
  randomized_test_with_ccc
  ()
  {
    using namespace std;
    using namespace 
      index_of_smallest_testing;
    using namespace
      os_core::random_sequence_generators;
      
    using local_type
      = os_core::custom_containers::ComparableItemContainer<int>;
      
    cout
      << endl << "  *** Randomized Tests with Integer Holders "
      << "( Random Integers in [-2, 2) ) ***" << endl;
    
    IndexOfSmallestTester<local_type>  obj_t;
  
    obj_t
      .reset()
      .set_ensemble_volume( 10000 )
      .set_size_of_array_limits( 1 , 100 )
      
      /*
       * The array generator class also works with
       * integer arguments for default construction.
       * */
      .set_array_generator
        (
          std::make_shared
            <ArrayRNG_CustomContainerOfIntegers>
              ( -2 , 2 )
              // ( local_type(-2) , local_type( 2) )
        )
        
      .run_randomized_test()
      .report_results();
      
    auto & a_g_ptr 
      = obj_t.get_array_generator();
    auto   a_g_ptr__cast
      = std::dynamic_pointer_cast
          <ArrayRNG_CustomContainerOfIntegers>
            ( a_g_ptr );
            
    /*
     * Again making use of default construction from
     * integers for the custom class.
     * */
    a_g_ptr__cast->set_interval_limits(-100, 100);
    
    cout
      << endl << "  *** Randomized Tests with Integer Holders "
      << "( Random Integers in [-100, 100) ) ***" << endl;
    
    obj_t
      .reset()
      .set_ensemble_volume( 1000 )
      .set_size_of_array_limits( 1 , 200 )
      .run_randomized_test()
      .report_results();
  }
}

int
main (void)
{
  using namespace os_test;
  
  // single_array_check_with_ccc();
  randomized_test_with_ccc();
  
  return 0;
}