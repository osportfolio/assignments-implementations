/*
 * Class defitions for 'update' functions testers.
 * */

/*
 * Worked on this code on
 *   Dec 22-23, 2022 / Thu-Fri
 * */

#pragma once

#include <vector>
#include <cassert>

namespace updaters_testing
{
  
class UpdaterFunctionsTester
{
// typedefs
public:
  using  LocalClassType =
    UpdaterFunctionsTester;
#define  LocalClassTypeName  \
    UpdaterFunctionsTester
    
  /*
   * 'update' function pointer types
   * for functions implemented in C and C++.
   * */
  using  CFunctionPtrType =
    void(*)(int *, int *);
  using  CPPFunctionPtrType =
    void(*)(int &, int &);

// member variables
protected:
  
  /*
   * Vectors of function pointers.
   * */
  std::vector<CFunctionPtrType>
    c_func_ptr_vec_;
  std::vector<CPPFunctionPtrType>
    cpp_func_ptr_vec_;
    
// ctor dtor
public:
  
  LocalClassTypeName
  ()
  {
    populate_function_ptr_vectors_();
  }
  
  virtual
  ~LocalClassTypeName
  ()
  {}
  
// member functions
public:
  
  LocalClassType &
  demo_calls_all_available_functions
  (
    const int  i_1st ,
    const int  i_2nd
  );

// static member functions
public:
  
  /*
   * Instantiates 'UpdaterFunctionsTester',
   * the class whose definition we are now in,
   * and makes use of the rng engine to generate
   * input integers, then calls
   * 'demo_calls_all_available_functions'.
   * Repeats 'no_tests' times.
   * */
  static
  void
  demo_calls_all_available_functions_for_random_integers
  (
    const 
    int           interval_limit_left  ,
    const 
    int           interval_limit_right ,
    const 
    unsigned int  no_tests
  );
  
// member functions
private:
  
  LocalClassType &
  populate_function_ptr_vectors_
  ();
  
#undef  LocalClassTypeName  
}; // class UpdaterFunctionsTester
  
class UpdaterFunctionsRandomizedTester
:
public
UpdaterFunctionsTester
{
  
// typedefs
public:
  using  LocalClassType =
    UpdaterFunctionsRandomizedTester;
#define  LocalClassTypeName  \
    UpdaterFunctionsRandomizedTester
  
// member variables
private:
  
  /*
   * Defines how many sets of input
   * arguments are to be generated
   * in the randomized test.
   * */
  unsigned int
    ensemble_volume_;
    
  /*
   * Defines the interval in which
   * the random integer instances will
   * reside.
   * */
  int
    interval_limit_left_  , // inclusive
    interval_limit_right_ ; // exclusive
  
  /*
   * For readability.
   * */
  enum TrialConsequence
    {
      SUCCESS = 0 ,
      FAILURE = 1
    };
    
  /*
   * Designed to hold the number
   * of successes and failures for
   * each of the registered functions.
   * */
  std::vector
    < std::vector< unsigned int > >
      results_;
    
// ctor dtor
public:
  
  LocalClassTypeName
  ()
  :
  UpdaterFunctionsTester()
  {
    reset();
  }
  
  virtual
  ~LocalClassTypeName
  ()
  {}
  
// member functions
public:
  
  /*
   * Reset function. Ensemble and interval
   * related information is to be determined
   * as desired by setters.
   * */
  LocalClassType &
  reset
  ()
  {
    ensemble_volume_ = 0;
    
    interval_limit_left_  = 0;
    interval_limit_right_ = 1;
    
    results_.clear();
    
    return *this;
  }
  
  LocalClassType &
  set_ensemble_volume
  (
    unsigned int  ensemble_volume
  )
  {
    ensemble_volume_
      = ensemble_volume;
    return *this;
  }
  
  LocalClassType &
  set_interval_limits
  (
    int  interval_limit_left  ,
    int  interval_limit_right
  )
  {
    assert
      ( interval_limit_left < interval_limit_right );
      
    interval_limit_left_
      = interval_limit_left;
    interval_limit_right_
      = interval_limit_right;
    
    return *this;
  }
  
  LocalClassType &
  run_randomized_test
  ();
  
  LocalClassType &
  report_results
  ();
  
#undef  LocalClassTypeName
}; // class UpdaterFunctionsRandomizedTester

} // namespace updaters_testing
