/*
 * Member function bodies for tester classes.
 * */

/*
 * Worked on this code on
 *   Dec 22-23, 2022 / Thu-Fri
 * */

#include "updaters_testing.hh"

#include "implementations/updaters_in_C.h"
#include "implementations/updaters_in_CPP.hh"

#include "randomization/prng_utilities.hh"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

#include <cstdio>

namespace updaters_testing
{
  
  UpdaterFunctionsTester &
  UpdaterFunctionsTester
    ::demo_calls_all_available_functions
  (
    const int  i_1st ,
    const int  i_2nd
  )
  {
    /*
     * The plus just after equals is not necessary in this
     * context, but it enables 'fh_print' to be cast into
     * a function pointer.
     * */
    auto fh_print
      = + []
          ( 
            const int     a , 
            const int     b , 
            const char *  notifier 
          ) -> void
          {
            printf( 
              "%36s :    a = %4d  b = %4d\n" ,
              notifier , a , b );
            return;
          };
    const std::string
      originals_notifier_str
        ( "Original Integers" );
    const std::string
      func_notifier_str
        ( "Updates by Function in" );
        
    std::cout << std::endl;
    fh_print( i_1st , i_2nd , originals_notifier_str.c_str() );
    
    /*
     * Iterate through the C functions.
     * */
    int cnt = 0;
    for ( auto * c_func_ptr : c_func_ptr_vec_ )
    {
      std::stringstream ss;
      ss 
        << func_notifier_str
        << " in C [" << std::setw(2) << ++cnt << "]";
        
      int
        i_1st_copy = i_1st ,
        i_2nd_copy = i_2nd ;
      c_func_ptr( &i_1st_copy , &i_2nd_copy );
      
      fh_print( i_1st_copy , i_2nd_copy , 
                ss.str().c_str() );
    } // for c_func_ptr
    
    /*
     * Reset 'cnt', and iterate through the C++
     * functions.
     * */
    cnt = 0;
    for ( auto * cpp_func_ptr : cpp_func_ptr_vec_ )
    {
      std::stringstream ss;
      ss 
        << func_notifier_str
        << " in C++ [" << std::setw(2) << ++cnt << "]";
        
      int
        i_1st_copy = i_1st ,
        i_2nd_copy = i_2nd ;
      cpp_func_ptr( i_1st_copy , i_2nd_copy );
      
      fh_print( i_1st_copy , i_2nd_copy , 
                ss.str().c_str() );
    } // for cpp_func_ptr
    
    return *this;
  } // demo_calls_all_available_functions

  void
  UpdaterFunctionsTester
    ::demo_calls_all_available_functions_for_random_integers
  (
    const 
    int           interval_limit_left  ,
    const 
    int           interval_limit_right ,
    const 
    unsigned int  no_tests
  )
  {
    assert
      (
        interval_limit_left
        <
        interval_limit_right
      );
    assert( no_tests > 0 );
    
    using namespace os_prng_utils;
      
    UpdaterFunctionsTester
      obj_test;
    PRNG_Uniform
      obj_rng;
          
    /*
     * In each iteration, generate a pair
     * of random variable realizations, and
     * call the member function applying these
     * integers to each registered function
     * and reporting the result.
     * */
    for ( unsigned int kk=0 ; kk<no_tests ; ++kk )
    {
      auto temp_vec
        = obj_rng.rand_int
            ( 2 , 
              interval_limit_left , 
              interval_limit_right );
    
      obj_test.
        demo_calls_all_available_functions
          (
            temp_vec[0] , temp_vec[1]
          );
    } // for kk
        
    return;
  } // function - demo_calls_all_available_functions_for_random_integers
  
  UpdaterFunctionsTester &
  UpdaterFunctionsTester
    ::populate_function_ptr_vectors_
  ()
  {
    /*
     * Simply push into the vector.
     * */
    c_func_ptr_vec_.push_back( update__with_pointers_in_C );
    c_func_ptr_vec_.push_back( update__with_ternary_operator_in_C );
    c_func_ptr_vec_.push_back( update__with_abs_in_C );
    
    /*
     * The function below is expected to fail miserably.
     * */
    /*
    c_func_ptr_vec_.push_back( update__doomed_to_fail_in_C );
    */
    
    /*
     * Now push the C++ functions into the relevant vector.
     * */
    cpp_func_ptr_vec_.push_back
      ( os_core::updaters::ns__with_references_in_CPP::update );
    
    /*
     * One of the C++ functions needs an adapter lambda
     * expression as illustrated below. The plus just after
     * equals is critical. With the indicated plus,
     * 'fh_tuple_arg_adapter' is able to be cast into
     * a function pointer type, and one must note that
     * there are no variables captured either by value
     * or reference inside the lambda expression.
     * 
     * Coding a lambda expression as the one below is
     * easier than the alternative of a detached function.
     * */
    auto fh_tuple_arg_adapter
      = + []
          ( int &  i_1st , int &  i_2nd ) -> void
            {
              os_core::updaters::
              ns__with_tuples_holding_references_in_CPP::update
                (
                  std::forward_as_tuple( i_1st , i_2nd )
                );
            };
      
    /*
     * Now push the lambda expression into the vector.
     * */
    cpp_func_ptr_vec_.push_back
      ( fh_tuple_arg_adapter );
    
    return *this;
  } // function - populate_function_ptr_vectors_
  
  
  UpdaterFunctionsRandomizedTester &
  UpdaterFunctionsRandomizedTester
    ::run_randomized_test
  ()
  {
    using namespace std;
    using namespace os_prng_utils;
    
    PRNG_Uniform  obj_rng;
    
    /*
     * Each function accepting two integers.
     * Define this enum for readability in the
     * main testing loop.
     * */
    enum FunctionArgID
      {
        ARG_1ST = 0 ,
        ARG_2ND = 1
      };
      
    /*
     * Designed to hold the random arguments into
     * the functions.
     * */
    std::vector
      < std::vector<int> >
        args_vec;
    args_vec.clear();
    
    /*
     * Allocate memory a priori for there are
     * known to be 2 arguments to the functions.
     * */
    args_vec.reserve(2);
        
    /*
     * Avoiding code duplication during random number
     * generation.
     * */
    for ( 
          unsigned int 
              kk = 0 ;
              kk < 2 ;
            ++kk  
        )
    {
      auto temp_vec
        = obj_rng.rand_int
            ( ensemble_volume_ , 
              interval_limit_left_ , 
              interval_limit_right_ );
      args_vec.push_back( temp_vec );
    }
        
    /*
     * Compute the common size of results vectors.
     * '- 1' since I will accept outputs of the function
     * pointed to by the first element in 'c_func_ptr_vec_'
     * as the golden reference.
     * */
    unsigned int results_vectors_common_size
      = c_func_ptr_vec_.size()
      + cpp_func_ptr_vec_.size()
      - 1;
    
    (this->results_).clear();
    for ( unsigned int kk = 0 ; kk < 2 ; ++kk )
      (this->results_).push_back
        ( 
          std::vector<unsigned int>
            ( results_vectors_common_size , 0 )
        );
      
    /*
     * Sequence of tests and storage. Go through the whole
     * ensemble.
     * */
    for ( unsigned int 
            kk_ensemble = 0 ;
            kk_ensemble < args_vec[0].size() ;
          ++kk_ensemble
        )
    {
      /*
       * Get a and b.
       * */
      int a = args_vec[ARG_1ST][kk_ensemble] ,
          b = args_vec[ARG_2ND][kk_ensemble] ;
          
      /*
       * Copy for modification.
       * */
      int a_modified = a ,
          b_modified = b ;
          
      /*
       * Call 0th C function in c_func_ptr_vec_, whose
       * outputs are to be used as the golden reference.
       * Do not modify 'a_modified' and 'b_modified' in
       * the loops below.
       * */
      c_func_ptr_vec_[0] ( &a_modified , &b_modified );
      
      /*
       * Define a lambda expression to be used commonly
       * inside the two 'for_each' statements. The lambda 
       * expression below captures the 'this' pointer by
       * value. 'cnt_func_ptr', captured by reference,
       * has to be incremented inside the lambda expression.
       * 
       * Prevents code duplication.
       * */
      int cnt_func_ptr = 0;
      auto fh_check_store
        = [ a_modified , b_modified ,
            &cnt_func_ptr ,
            this ]
            ( 
              const int a_local ,
              const int b_local
            ) -> void
            {
              bool flag_success
                = ( (a_local == a_modified) 
                    && 
                    (b_local == b_modified) );
              
              /*
               * enum used for readability below.
               * */
              if ( flag_success )
                (*this).results_
                  [TrialConsequence::SUCCESS][cnt_func_ptr] += 1;
              else
                (*this).results_
                  [TrialConsequence::FAILURE][cnt_func_ptr] += 1;
              
              ++cnt_func_ptr;
            };
      
      /*
       * Call the other C functions. Check and store
       * success or failure events. 
       * */
      std::for_each
        (
          c_func_ptr_vec_.begin() + 1 , // skip the 1st function
          c_func_ptr_vec_.end() ,
          [ a , b , fh_check_store ]
            ( UpdaterFunctionsTester
                ::CFunctionPtrType  func_ptr )->void
            {
              int a_local = a ,
                  b_local = b ;
                  
              /*
               * The invocation syntax for the C functions.
               * */
              func_ptr( &a_local , &b_local );
              
              /*
               * Common to both of the lambda expressions
               * in the two 'for_each' statements.
               * */
              fh_check_store( a_local , b_local );
            } // lambda
        ); // for_each
        
      /*
       * Now call the C++ functions. No need to set 'cnt_func_ptr'
       * as we continue where we left off.
       * */
      std::for_each
        (
          cpp_func_ptr_vec_.begin() , // do not skip the 1st
          cpp_func_ptr_vec_.end() ,
          [ a , b , fh_check_store ]
            ( UpdaterFunctionsTester
                ::CPPFunctionPtrType  func_ptr )->void
            {
              int a_local = a ,
                  b_local = b ;
                  
              /*
               * The invocation syntax for the C++ functions.
               * */
              func_ptr( a_local , b_local );
              
              /*
               * Common call.
               * */
              fh_check_store( a_local , b_local );
            } // lambda
        ); // for_each
    } // for kk_ensemble
    
    return *this;
  } // function - run_randomized_test
  
  UpdaterFunctionsRandomizedTester &
  UpdaterFunctionsRandomizedTester
    ::report_results
  ()
  {
    using namespace std;
  
    cout << endl;
    printf( "%36s%10s%10s%10s%10s\n" , 
            "" , "SUCCESS" , "FAILURE" ,
            "TOTAL" , "RATE"
          );
    
    auto fh_print
      = + []
          ( 
            const unsigned int  no_success , 
            const unsigned int  no_failure , 
            const char *        notifier 
          )
          {
            unsigned int no_total
              = no_success + no_failure;
            double rate
              = ((double) no_success) / no_total
              * 100. ;
            printf
              ( 
                "%36s%10d%10d%10d%10.2f\n" ,
                notifier , no_success , no_failure ,
                no_total , rate
              );
            return;
          };
          
    const std::string
      func_notifier_str
        ( "Events for Function" );
        
    for 
      ( 
        unsigned int 
          kk = 1 ;
          kk < c_func_ptr_vec_.size() ;
        ++kk  
      )
    {
      std::stringstream ss;
      ss 
        << func_notifier_str
        << " in C [" << std::setw(2) << (1+kk) << "]";
        
      fh_print
        (
          results_[SUCCESS][kk-1] ,
          results_[FAILURE][kk-1] ,
          ss.str().c_str()
        );
    } // for c_func_ptr
    
    for
      (
        unsigned int
          kk = 0 ;
          kk < cpp_func_ptr_vec_.size() ;
        ++kk  
      )
    {
      std::stringstream ss;
      ss 
        << func_notifier_str
        << " in C++ [" << std::setw(2) << (1+kk) << "]";
        
      /*
       * The data structure instance 'results_' holds
       * the results for both the C and the C++
       * functions. Therefore adding the necessary
       * offset below.
       * */  
      unsigned int index_internal
        = kk + c_func_ptr_vec_.size() - 1;
        
      fh_print
        (
          results_[SUCCESS][index_internal] ,
          results_[FAILURE][index_internal] ,
          ss.str().c_str()
        );
    } // for cpp_func_ptr
        
    return *this;
  } // function - report_results
  
} // namespace updaters_testing
