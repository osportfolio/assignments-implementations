/*
 * Randomized tests for 'index_of_smallest' implementations.
 * The implementation for which the corresponding row appears
 * empty in the displayed tables is the one selected as the
 * golden reference.
 * */

/*
 * Worked on this code on
 *   Dec 24-27, 2022 / Sat-Tue
 * */

#include "index_of_smallest_testing.hh"
#include "random_sequence_derived.hh"

#include <iostream>
#include <memory>

namespace os_test
{
  
  void
  randomized_test_with_integers
  ()
  {
    using namespace std;
    using namespace 
      index_of_smallest_testing;
    using namespace
      os_core::random_sequence_generators;
      
    cout
      << endl << "  *** Randomized Tests with Integers "
      << "( Random Integers in [-2, 2) ) ***" << endl;
    
    IndexOfSmallestTester<int>  obj_t;
  
    obj_t
      .reset()
      .set_ensemble_volume( 10000 )
      .set_size_of_array_limits( 1 , 100 )
      .set_array_generator
        (
          std::make_shared<ArrayRNG_Integer>( -2 , 2 )
        )
      .run_randomized_test()
      .report_results();
      
    /*
     * It does not matter if I obtain the array generator
     * by reference or value. The shared pointers manage
     * the same raw pointer.
     * 
     * In order to set the new interval for random number
     * realizations, a shared pointer managing a non-polymorphic
     * pointer is necessary, hence the dynamic pointer
     * casting operation below.
     * */
    auto & a_g_ptr 
      = obj_t.get_array_generator();
    auto   a_g_ptr__cast
      = std::dynamic_pointer_cast<ArrayRNG_Integer>( a_g_ptr );
    a_g_ptr__cast->set_interval_limits(-100, 100);
    
    cout
      << endl << "  *** Randomized Tests with Integers "
      << "( Random Integers in [-100, 100) ) ***" << endl;
    
    /*
     * No need to set the array generator again.
     * 
     * The success rates in indices are almost sure to increase
     * with respect to the randomized test above, since
     * the interval for random number realizations is now wider.
     * */
    obj_t
      .reset()
      .set_ensemble_volume( 1000 )
      .set_size_of_array_limits( 1 , 200 )
      .run_randomized_test()
      .report_results();
  }
  
  void
  randomized_test_with_doubles
  ()
  {
    using namespace std;
    using namespace 
      index_of_smallest_testing;
    using namespace
      os_core::random_sequence_generators;
    
    /*
     * Two double random number realizations can be
     * equal to each other with very small probability.
     * Therefore, not many success rates in indices
     * lower than 100% might be encountered in the tests
     * below.
     * */
      
    cout
      << endl << "  *** Randomized Tests with Doubles ***" << endl;
      
    IndexOfSmallestTester<double>  obj_t;
  
    obj_t
      .reset()
      .set_ensemble_volume( 10000 )
      .set_size_of_array_limits( 1 , 100 )
      .set_array_generator
        (
          std::make_shared<ArrayRNG_Double>( -2. , 2. )
        )
      .run_randomized_test()
      .report_results();
  }
  
} // namespace os_test

int 
main (void)
{
  using namespace  os_test;
  
  randomized_test_with_doubles();
  randomized_test_with_integers();
  
  return 0;
}
