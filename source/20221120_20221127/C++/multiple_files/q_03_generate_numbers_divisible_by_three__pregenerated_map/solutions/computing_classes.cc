/*
 * Incorporated a pre-generated map into the class definitions.
 *              on Dec 8, 2022 / Thu
 * */

#include "computing_classes.hh"

#include <algorithm>
#include <iostream>

namespace os_core
{
  using namespace os_types;
  using namespace os_utilities;
  
  std::vector<int>
  PregeneratedCheckerContainer::checker_
    = std::move( range_of_integers(-12, +13, +3) );
  std::vector<int>
  PregeneratedCheckerContainer::range_of_int_
    = std::move( range_of_integers(0, 10, 1) );

  bool
  DivisibleByThreeGeneratorBase::flag_debug = true;

  PregeneratedCheckerContainer
  DivisibleByThreeGeneratorBase::checker_map_container_obj_;
  
  PregeneratedCheckerContainer::PregeneratedCheckerContainer
  ()
  {
    using local_set_type =
      os_types::set_of_int_type;
      
    local_set_type  range_of_int__set
      ( range_of_int_.begin() , range_of_int_.end() );
    
    tuple_to_vec_map_.clear();
    for ( int rem = 0 ; rem < 3 ; ++rem )
    {
      for ( auto item : range_of_int_ )
      {
        decltype(checker_)
          checker_current;
        checker_current.reserve( checker_.size() );
        
        std::transform
        (
          checker_.begin() ,
          checker_.end() ,
          std::back_inserter(checker_current) ,
          [item, rem] (const int  n)
            { // lambda
              return n + item + ( 3 - rem );
            } // lambda
        );
        /*
         * Computed 2checker_current' in raw form.
         * */
        
        local_set_type  checker_current__set
          ( checker_current.begin() , checker_current.end() );
        
        std::vector<int>  checker_temp
          ( 
              checker_current__set.size() 
            + range_of_int__set.size()
          );
        auto  it =
          std::set_intersection
            ( 
              checker_current__set.begin() ,
              checker_current__set.end() ,
              range_of_int__set.begin() ,
              range_of_int__set.end() ,
              checker_temp.begin()
            );
        checker_temp.resize( it - checker_temp.begin() );
        /*
         * First pruning done.
         * */
        
        checker_current = checker_temp;
        checker_current__set.clear();
        checker_current__set.insert
          ( checker_current.begin() , checker_current.end() );
        local_set_type  single_element__set = { item };
      
        checker_temp.clear();
        checker_temp.resize
          (
              checker_current__set.size()
            + single_element__set.size() ,
            0
          );
      
        it = 
          std::set_difference
            (
              checker_current__set.begin() ,
              checker_current__set.end() ,
              single_element__set.begin() ,
              single_element__set.end() ,
              checker_temp.begin()
            );
        checker_temp.resize( it - checker_temp.begin() );
        /*
         * Second pruning done.
         * */
        
        checker_current = checker_temp;
        checker_temp.clear();
        checker_current__set.clear();
        single_element__set.clear();
        /*
         * Clear memory.
         * */
      
        digit_remainder_tuple_type
          key( item , rem );
        tuple_to_vec_map_[key] = checker_current;
      } // for item
    } // for rem
  }
  
  DivisibleByThreeGeneratorBase::DivisibleByThreeGeneratorBase
  (
    std::string  S
  )
  :
  s_input_( S )
  {
    using namespace std;
    
    auto s_list = 
      string_to_vector_of_characters( S );
      
    num_.reserve( s_list.size() );
    std::transform
      (
        s_list.begin() ,
        s_list.end() ,
        std::back_inserter(num_) ,
        [] (const char  item) -> int
          { // lambda
            return item - '0';
          } // lambda
      );
      
    sum_of_num_ = 0;
    std::for_each
      (
        num_.begin() ,
        num_.end() ,
        [this] (const int  item)
          { // lambda
            this->sum_of_num_ += item;
          } // lambda
      );
    rem_ = sum_of_num_ % 3;
      
    total_ = 0;
      
    if (flag_debug)
    {
      print_container_of_items
        (S    , "vector of characters" );
      print_container_of_items
        (num_ , "vector of digits" );
    }
  } // ctor
  
  DivisibleByThreeGeneratorBase &
  DivisibleByThreeGeneratorBase::solve
  ()
  {
    int cnt = 0;
    for ( auto item : num_ )
    {
      digit_remainder_tuple_type
        key( item , this->rem_ );
      auto & checker_map_ref
        = checker_map_container_obj_.get_checker_map();
      auto & checker_current
        = checker_map_ref [key];
      
      total_ += checker_current.size();
      
      append_to_set_of_generated_strings
        (cnt, checker_current);
      
      ++cnt;
    } // for
    
    if ( flag_debug )
    {
      std::cout
        << "Total Number of Generated Strings:"
        << std::endl
        << "  " << total_
        << std::endl;
    } // if
    
    compute_list_of_generated_strings();
    return *this;
  } // solve
  
  
  DivisibleByThreeGeneratorWithListComputer &
  DivisibleByThreeGeneratorWithListComputer
    ::append_to_set_of_generated_strings
  (
    int 
      cnt ,
    const std::vector<int> &
      checker_current
  )
  {
    for ( auto n : checker_current )
    {
      auto  num_current = num_;
      num_current[cnt] = n;
      
      std::vector<char>
        num_current_str;
      num_current_str.reserve
        ( num_current.size() );
      std::transform
        (
          num_current.begin() ,
          num_current.end() ,
          std::back_inserter( num_current_str ) ,
          [] ( int item ) -> char
          {
            return ('0' + item);
          }
        );
        
      auto  tba =
        vector_of_characters_to_string
          ( num_current_str );
      generated_strings__set_.insert
        ( tba );
    } // for n
    
    return *this;
  }
  
  DivisibleByThreeGeneratorWithListComputer &
  DivisibleByThreeGeneratorWithListComputer
    ::compute_list_of_generated_strings
  ()
  {
    generated_strings_.insert
      (
        generated_strings_.begin() ,
        generated_strings__set_.begin() ,
        generated_strings__set_.end()
      );
      
    if ( flag_debug )
      print_container_of_items
        (
          generated_strings_ ,
          "vector of generated strings"
        );
      
    return *this;
  }
  
} // namespace os_core
