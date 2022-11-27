/*
 * Given a string of digits each in the range from
 * 0 to 9, generates all the strings that correspond
 * to numbers that are divisible by three, which
 * are allowed to be devised only through modifications
 * on each of the digits in the original string.
 * Returns the total number of such strings; naturally
 * the original string is not included in the count
 * even if its corresponding number is divisible by three.
 * */

// worked on this code 
//        from  Nov 22, 2022 / Tue
//        to    Nov 24, 2022 / Thu

#include <vector>
#include <tuple>
#include <set>
#include <string>
#include <algorithm>
#include <memory>
#include <iostream>

namespace os_types
{
  using set_of_int_type =
    std::set<int>;
} // namespace os_types

namespace os_core
{

std::vector<int>
range_of_integers
(
  int  i_start ,
  int  i_end ,
  int  i_increment
)
{
  std::vector<int>  v;
  for ( int kk=i_start ; kk<i_end ; kk+=i_increment )
    v.push_back( kk );
  return v;
}

std::vector<char>
string_to_vector_of_characters
(
  std::string  s_in
)
{
  auto & A = s_in;
  std::vector<char>  s_list;
  
  s_list.reserve( A.length() );
  
  const auto * c_ptr = A.c_str();
  for ( unsigned int kk = 0 ; kk < A.length() ; ++kk )
    s_list.push_back( *(c_ptr++) );
  
  return s_list;
} // string_to_vector_of_characters

std::string
vector_of_characters_to_string
(
  std::vector<char>  v_in
)
{
  std::string  res( v_in.begin() , v_in.end() );
  return res;
} // vector

template
< typename Container >
void
print_container_of_items
(
  Container    c_input ,
  std::string  identifier = "unspecified"
)
{
  using namespace std;
  cout 
    << "Printing items (of " 
    << identifier
    << "):" 
    << endl << "  ";
  
  for ( auto item : c_input )
    cout << item << " ";
  cout << endl;
} // print_container_of_items

class DivisibleByThreeGeneratorBase
{
// typedefs
public:
  using LocalClassType =
    DivisibleByThreeGeneratorBase;
#define  LocalClassTypeName  \
    DivisibleByThreeGeneratorBase

// static member variables
public:
  static
  bool  flag_debug;
  
// static member variables
protected:
  static
  std::vector<int>
    checker_, range_of_int_;
  
// member variables
protected:
  std::string
    s_input_;
  
  std::vector<int>
    num_;
  int
    sum_of_num_;
  int
    rem_;
    
  int 
    total_;
    
// ctor dtor  
public:
  
  LocalClassTypeName
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
  
  virtual
  ~LocalClassTypeName
  () = default;
  
public:
  
  LocalClassType &
  solve
  ()
  {
    using local_set_type =
      os_types::set_of_int_type;
    
    local_set_type  range_of_int__set
      ( range_of_int_.begin() , range_of_int_.end() );
      
    int cnt = 0;
    for ( auto item : num_ )
    {
      decltype(checker_)
        checker_current;
      checker_current.reserve( checker_.size() );
      
      std::transform
        (
          checker_.begin() ,
          checker_.end() ,
          std::back_inserter(checker_current) ,
          [this, item] (const int  n)
            { // lambda
              return n + item + ( 3 - this->rem_ );
            } // lambda
        );
        
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
      
      if (flag_debug)
      {
        print_container_of_items
          ( checker_temp , 
            "vector from set of digits (after intersection)" );
      } // if
      
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
      
      if (flag_debug)
      {
        print_container_of_items
          ( checker_temp , 
            "vector from set of digits (after difference)" );
      } // if
      
      checker_current = checker_temp;
      checker_temp.clear();
      checker_current__set.clear();
      single_element__set.clear();
      
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
  
  int
  get_total_number_of_generated_strings
  ()
  const
  {
    return  total_;
  }
  
  std::string
  get_original_string
  ()
  const
  {
    return  s_input_;
  }
  
protected:
  
  virtual
  LocalClassType &
  append_to_set_of_generated_strings
  (
    int 
      cnt ,
    const std::vector<int> & 
      checker_current
  )
  {
    return *this;
  }
  
  virtual
  LocalClassType &
  compute_list_of_generated_strings
  ()
  {
    return *this;
  }
  
#undef  LocalClassTypeName  
}; // class DivisibleByThreeGeneratorBase

bool
DivisibleByThreeGeneratorBase::flag_debug = true;

std::vector<int>
DivisibleByThreeGeneratorBase::checker_
  = std::move( range_of_integers(-12, +13, +3) );
std::vector<int>
DivisibleByThreeGeneratorBase::range_of_int_
  = std::move( range_of_integers(0, 10, 1) );


class DivisibleByThreeGeneratorWithListComputer
:
public
DivisibleByThreeGeneratorBase
{
// typedefs
public:
  using LocalClassType =
    DivisibleByThreeGeneratorWithListComputer;
#define  LocalClassTypeName  \
    DivisibleByThreeGeneratorWithListComputer

// member variables
protected:
  std::set<std::string>  
    generated_strings__set_;
  std::vector<std::string>
    generated_strings_;
    
// ctor dtor
public:

  LocalClassTypeName
  (
    std::string  S
  )
  :
  DivisibleByThreeGeneratorBase(S)
  {
    generated_strings__set_.clear();
    generated_strings_.clear();
  } // ctor
  
  virtual
  ~LocalClassTypeName
  () {}
  
// getters
public:
  
  const std::vector<std::string> &
  get_list_of_generated_strings
  ()
  const
  {
    return  generated_strings_;
  }
  
// computing member functions
protected:
  virtual
  LocalClassType &
  append_to_set_of_generated_strings
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
  
  virtual
  LocalClassType &
  compute_list_of_generated_strings
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
  
#undef  LocalClassTypeName
};
  
} // namespace os_core

namespace os_test
{
using namespace os_core;

void 
test_solution ()
{
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

} // test_solution

} // namespace os_test

int
main(void)
{
  using namespace os_test;
  
  test_solution();
  
  return 0;
}