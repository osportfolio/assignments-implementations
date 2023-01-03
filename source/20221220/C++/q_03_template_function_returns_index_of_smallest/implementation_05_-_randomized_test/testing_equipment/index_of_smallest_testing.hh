/*
 * Class template implementation for testing
 * available versions of "index_of_smallest".
 * Able to operate with various comparable types
 * that support the less than operator for
 * comparisons.
 * */

/*
 * Worked on this code on
 *   Dec 24-27, 2022 / Sat-Tue
 * */

#pragma once

#include "implementations/index_of_smallest_in_CPP.hh"
#include "durations/durations.hh"
#include "rng_engine_static.hh"
#include "random_sequence_base.hh"

#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <string>

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cassert>

namespace index_of_smallest_testing
{
  
/*
 * A container used to hold information
 * about success and failure with respect to
 * the results of a function implementation
 * selected as the golden reference, in
 * randomized tests.
 * */
struct ResultsInfoHolder
{
  unsigned int
    no_success_in_indices ,
    no_failure_in_indices ;
  double
    rate_in_indices ;
    
  unsigned int  
    no_success_in_values ,
    no_failure_in_values ;
  double
    rate_in_values ;
    
  double
    sec_duration_total ,
    sec_duration_average ;
  
  ResultsInfoHolder  ()
  {
    reset();
  }
  
  ~ResultsInfoHolder () = default;
  
  ResultsInfoHolder             
    (const  ResultsInfoHolder &)  = default;
  ResultsInfoHolder &  operator=
    (const  ResultsInfoHolder &)  = default;
  
  ResultsInfoHolder &
  reset  
  ()
  {
    no_success_in_indices = 0;
    no_failure_in_indices = 0;
    rate_in_indices = 0.;
    
    no_success_in_values = 0;
    no_failure_in_values = 0;
    rate_in_values  = 0.;
    
    sec_duration_total   = 0.;
    sec_duration_average = 0.;
    
    return *this;
  } // function - reset
};
  
/*
 * The tester class definition.
 * */
template
<typename ComparableType>
class IndexOfSmallestTester
{
// typedefs
public:
  using  LocalClassType =
    IndexOfSmallestTester;
#define  LocalClassTypeName  \
    IndexOfSmallestTester
    
  using  CPPFunctionPtrType
    = unsigned int(*)
        (ComparableType *, unsigned int);
   
  /*
   * Instances of this type will be used
   * to manage polymorphic pointers of
   * random array generators.
   * */
  using  ArrayRNGType
    = std::shared_ptr
        < os_core
          ::random_sequence_generators
          ::ArrayRNG<ComparableType> >;
        
// member variables
private:
  
  std::vector<CPPFunctionPtrType>
    cpp_func_ptr_vec_;
    
  unsigned int
    index_of_func_ptr_selected_as_ref_;
    
  std::map
    < CPPFunctionPtrType , std::string >
      func_ptr_to_string_map_;
      
  std::map
    < CPPFunctionPtrType , ResultsInfoHolder >
      func_ptr_to_results_map_;
      
  unsigned int
    width_max_of_func_annotations_;
    
  ArrayRNGType
    array_generator_;
    
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
  unsigned int
    size_of_array_limit_left_  ,
    size_of_array_limit_right_ ;
    
// ctor dtor
public:
  
  LocalClassTypeName
  ()
  {
    populate_function_ptr_vectors_();
  }
  
//   virtual
  ~LocalClassTypeName
  ()
  {}
  
// setters and getters
public:
  
  ArrayRNGType &
  get_array_generator
  ()
  {
    return array_generator_;
  }
  
  LocalClassType &
  set_array_generator
  (
    ArrayRNGType  generator
  )
  {
    array_generator_ = generator;
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
  set_size_of_array_limits
  (
    unsigned int  limit_left  ,
    unsigned int  limit_right
  )
  {
    assert
      ( limit_left > 0 );
    assert
      ( limit_left < limit_right );
      
    size_of_array_limit_left_
      = limit_left;
    size_of_array_limit_right_
      = limit_right;
    
    return *this;
  }
  
// setters and getters
private:
  
  unsigned int
  get_index_of_func_ptr_selected_as_ref
  ()
  const
  {
    return index_of_func_ptr_selected_as_ref_;
  }
  
  unsigned int
  get_width_max_of_func_annotations
  ()
  const
  {
    return width_max_of_func_annotations_;
  }
  
// member functions
public:
  
  LocalClassType &
  reset
  ()
  {
    ensemble_volume_ = 0;
    
    size_of_array_limit_left_  = 1;
    size_of_array_limit_right_ = 2;
    
    func_ptr_to_results_map_.clear();
    
    return *this;
  }
  
  /*
   * Call all available functions on a
   * given array and report the computed
   * indices.
   * */
  LocalClassType &
  demo_calls_all_available_functions
  (
    ComparableType *  array_ptr ,
    unsigned int      size_of_array
  )
  {
    using namespace std;
    
    unsigned int  width_max 
      = get_width_max_of_func_annotations();
    
    cout 
      << endl
      << setw( width_max + 2 ) << ""
      << setw( 8 ) << "Index"
      << endl;
        
    for ( auto *  func_ptr : cpp_func_ptr_vec_ )
      cout 
        << setw( width_max + 2 )
        << func_ptr_to_string_map_[func_ptr]
        << setw(8) << func_ptr( array_ptr , size_of_array ) 
        << endl;
    
    return *this;
  } // function - demo_calls_all_available_functions

  /*
   * Randomized testing member function to be
   * called after necessary configuration.
   * */
  LocalClassType &
  run_randomized_test
  ()
  {
    using namespace std;
    using namespace
      os_core::random_sequence_generators;
    
    unsigned int cnt_func;
    
    /*
     * Populate 'func_ptr_to_results_map_',
     * and skip the reference function.
     * */
    cnt_func = 0;
    func_ptr_to_results_map_.clear();
    for ( auto * func_ptr_ : cpp_func_ptr_vec_ )
      func_ptr_to_results_map_[ func_ptr_ ]
        = ResultsInfoHolder();
    
    /*
     * Get reference to rng engine.
     * */
    auto & rng_engine 
      = os_prng_utils_addenda
          ::StaticPRNGInstanceHolder
          ::get();
          
    /*
     * Sequence of tests and storage. Go through the whole
     * ensemble.
     * */
    for ( unsigned int 
            kk_ensemble = 0 ;
            kk_ensemble < ensemble_volume_ ;
          ++kk_ensemble
        )
    {
      unsigned int  size_of_array
        = rng_engine.rand_int
            ( 
              1 , 
              size_of_array_limit_left_ , 
              size_of_array_limit_right_
            ) [0];
            
      /*
       * Generate random array.
       * */
      auto array_sh_ptr
        = array_generator_->generate( size_of_array );
        
      /*
       * Record results computed by the reference function.
       * */
      auto t_start
        = os_core::chrono_utils::tic();
      auto index_found_by_ref
        = cpp_func_ptr_vec_[index_of_func_ptr_selected_as_ref_]
            ( array_sh_ptr.get() , size_of_array );
      double sec_duration
        = os_core::chrono_utils::toc( t_start );
      func_ptr_to_results_map_
        [ cpp_func_ptr_vec_[index_of_func_ptr_selected_as_ref_] ] 
          . sec_duration_total
            += sec_duration;
            
      auto value_found_by_ref
        = array_sh_ptr.get()[index_found_by_ref];
        
      /*
       * Check and record results calculated by the other
       * functions.
       * */
      cnt_func = 0;
      for ( auto * func_ptr_ : cpp_func_ptr_vec_ )
        if ( cnt_func++ 
               != get_index_of_func_ptr_selected_as_ref() )
        {
          t_start
            = os_core::chrono_utils::tic();
          auto index_found
            = func_ptr_( array_sh_ptr.get() , size_of_array );
          sec_duration
            = os_core::chrono_utils::toc( t_start );
            
          auto value_found
            = array_sh_ptr.get()[index_found];
          
          /*
           * Record 'sec_duration'.
           * */
          func_ptr_to_results_map_[ func_ptr_ ] . sec_duration_total
            += sec_duration;
            
          /*
           * Check index.
           * */
          if ( index_found == index_found_by_ref )
            ++( func_ptr_to_results_map_[ func_ptr_ ]
                  . no_success_in_indices );
          else
            ++( func_ptr_to_results_map_[ func_ptr_ ]
                  . no_failure_in_indices );
            
          /*
           * Check value. Making use of only the less than
           * operator in case of restrictions.
           * */
          if  
              ( ! 
                (
                  ( value_found        < value_found_by_ref )
                  ||
                  ( value_found_by_ref < value_found )
                )
              )
              
              /*
               * The '==' check does not compile if the operator
               * overload is not available.
               * */
              /*
              (
                value_found == value_found_by_ref
              )
              */
            ++( func_ptr_to_results_map_[ func_ptr_ ]
                  . no_success_in_values );
          else
            ++( func_ptr_to_results_map_[ func_ptr_ ]
                  . no_failure_in_values );
        } // if
    
    } // for kk_ensemble
    
    /*
     * Compute rates and average durations.
     * */
    cnt_func = 0;
    for ( auto * func_ptr_ : cpp_func_ptr_vec_ )
    {
      func_ptr_to_results_map_[ func_ptr_ ] 
        . sec_duration_average
          = func_ptr_to_results_map_[ func_ptr_ ] 
              . sec_duration_total
            /
            ensemble_volume_;
      
      if ( cnt_func++ 
             != get_index_of_func_ptr_selected_as_ref() )
      {
        func_ptr_to_results_map_[ func_ptr_ ] . rate_in_indices
          = ( (double) 
              func_ptr_to_results_map_[ func_ptr_ ]
                . no_success_in_indices
            )
            /
            ( (double) 
              ensemble_volume_
            )
            * 100.;
        
        func_ptr_to_results_map_[ func_ptr_ ] . rate_in_values
          = ( (double) 
              func_ptr_to_results_map_[ func_ptr_ ]
                . no_success_in_values
            )
            /
            ( (double) 
              ensemble_volume_
            )
            * 100.;
      } // if
    } // for func_ptr_
          
    return *this;
  } // function - run_randomized_test
  
  /*
   * Reporting results of randomized tests.
   * */
  LocalClassType &
  report_results
  ()
  {
    using namespace std;
    
    unsigned int  width_max 
      = get_width_max_of_func_annotations();
    unsigned int  width_heading 
      = 10;
    
    /*
     * Lambda expressions for printing tables.
     * */
    auto fh_print_column_headings
      = [ width_max , width_heading ]
          ( const std::vector<std::string>  
              headings_vec
          ) -> void
          {
            cout 
              << setw( width_max + 2 ) << "";
            for ( const auto & heading : headings_vec )
              cout
                << setw( width_heading ) << heading;
            cout << endl;
          };
          
    auto fh_print_row_of_results
      = [ this , width_max , width_heading ]
          (
            CPPFunctionPtrType    
              func_ptr ,
            bool 
              flag_account_for_reference = false
          ) -> void
          {
            auto   func_name
              = ( this->func_ptr_to_string_map_ ) [func_ptr];
            cout 
              << setw( width_max + 2 ) << func_name;
              
            auto & results
              = ( this->func_ptr_to_results_map_ )[func_ptr];
            unsigned int no_cols_before_duration
              = 6;
              
            if ( ! flag_account_for_reference )
            {
              cout << std::fixed
                << setw( width_heading )
                  << results.no_success_in_indices
                << setw( width_heading )
                  << results.no_failure_in_indices
                << setw( width_heading ) << setprecision(2)
                  << results.rate_in_indices
                << setw( width_heading )
                  << results.no_success_in_values
                << setw( width_heading )
                  << results.no_failure_in_values
                << setw( width_heading ) << setprecision(2)
                  << results.rate_in_values;
            } // if
            else
            {
              cout
                << setw( width_heading * no_cols_before_duration )
                << "";
            } // else
            
            cout << std::scientific
              << setw( width_heading ) << setprecision(2)
                << results.sec_duration_average;
            
            cout << endl;
            return;
          };
          
    cout << endl;
    fh_print_column_headings
      ( { "INDEX" , "INDEX" , "INDEX" , 
          "VALUE" , "VALUE" , "VALUE" , "AVERAGE" } );
    fh_print_column_headings
      ( { "SUCCESS" , "FAILURE" , "RATE" , 
          "SUCCESS" , "FAILURE" , "RATE" , "SECONDS" } );
      
    unsigned int
      cnt_func = 0;
    for ( auto * func_ptr_ : cpp_func_ptr_vec_ )
      if ( cnt_func++ 
             != get_index_of_func_ptr_selected_as_ref() )
      {
        fh_print_row_of_results( func_ptr_ );
      } // if
      else
      {
        fh_print_row_of_results( func_ptr_ , true );
      }
      
    return *this;
  } // function - report_results
  
// member functions
private:
  
  LocalClassType &
  populate_function_ptr_vectors_
  ()
  {
    using namespace
      os_core::index_of_smallest__implementations;
    
    /*
     * For each available function, push pointer
     * into the vector, and add a new entry to the map.
     * */
    CPPFunctionPtrType ptr
      = ns__storing_index_only
          ::index_for_smallest;
    cpp_func_ptr_vec_.push_back
      ( ptr );
    func_ptr_to_string_map_
      [ ptr ] = "storing_index_only";
          
    ptr
      = ns__with_tuple
          ::index_for_smallest;
    cpp_func_ptr_vec_.push_back
      ( ptr );
    func_ptr_to_string_map_
      [ ptr ] = "with_tuple";
      
    ptr
      = ns__with_tuple_and_lambda_expression
          ::index_for_smallest;
    cpp_func_ptr_vec_.push_back
      ( ptr );
    func_ptr_to_string_map_
      [ ptr ] = "with_tuple_and_lambda_expression";
      
    ptr
      = ns__with_comparisons_in_pairs
          ::index_for_smallest;
    cpp_func_ptr_vec_.push_back
      ( ptr );
    func_ptr_to_string_map_
      [ ptr ] = "with_comparisons_in_pairs";
    
    ptr
      = ns__with_divide_and_conquer
          ::index_for_smallest;
    cpp_func_ptr_vec_.push_back
      ( ptr );
    func_ptr_to_string_map_
      [ ptr ] = "with_divide_and_conquer";
    
    ptr
      = ns__with_priority_queue
          ::index_for_smallest;
    cpp_func_ptr_vec_.push_back
      ( ptr );
    func_ptr_to_string_map_
      [ ptr ] = "with_priority_queue";
    
    /*
     * Set index of the function pointer to be
     * used as reference in the tests.
     * */
    index_of_func_ptr_selected_as_ref_
      = 0;
      
    /*
     * Compute the max width for function annotations.
     * To be used in printing demo and test results.
     * */
    unsigned int  width_max = 0;
    std::for_each
      (
        cpp_func_ptr_vec_.begin() ,
        cpp_func_ptr_vec_.end() ,
        [ &width_max , this ]
          (
            CPPFunctionPtrType  func_ptr
          ) -> void
          {
            unsigned int str_length
              = (this->func_ptr_to_string_map_)[func_ptr].length();
            if ( str_length > width_max )
              width_max = str_length;
            return;
          } // lambda
      );
    width_max_of_func_annotations_
      = width_max;
      
    return *this;
  } // function - populate_function_ptr_vectors_
    
#undef  LocalClassTypeName
}; // class IndexOfSmallestTester
  
} // namespace index_of_smallest_testing