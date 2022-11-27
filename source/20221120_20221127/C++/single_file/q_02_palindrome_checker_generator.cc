/*
 * The function 'solution...' tries to generate
 * a palindrome out of the string 'S' given
 * as an input argument, replacing the '?'
 * characters by what is required, and returns
 * the palindrome or the string 'NO', the
 * latter being the error identifier in case
 * no palindrome construction is possible.
 * */

// worked on this code on 
//                       Nov 22, 2022 / Tue

#include <vector>
#include <tuple>
#include <string>
#include <iostream>

namespace os_types
{
  using tuple_of_int_string_type =
    std::tuple<int, std::string>;
} // namespace os_types

namespace os_core
{
  
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
} // vector_of_characters_to_string

std::tuple<int, std::string>
solution_generate_palindrome_if_possible
(
  std::string  A ,
  bool         flag_debug = true
)
{
  using local_tuple_type =
    os_types::tuple_of_int_string_type;
  
  auto s_list = 
    string_to_vector_of_characters( A );
    
  int 
    index_middle ,
    index_right ,
    index_left ,
    n_max;
    
  if ( s_list.size() % 2 == 1 )
  {
    index_middle = (s_list.size() - 1) / 2;
    if ( s_list[index_middle] == '?' )
      s_list[index_middle] = 'a';
    
    index_right = index_middle + 1;
    index_left  = index_middle - 1;
    n_max = (s_list.size() - 1) / 2;
  } // if
  else
  {
    index_right = s_list.size() / 2;
    index_left  = s_list.size() / 2 - 1;
    n_max = s_list.size() / 2;
  } // else
  
  for ( int kk = 0 ; kk < n_max ; ++kk )
  {
    int
      index_right_c = index_right + kk ,
      index_left_c  = index_left  - kk ;
      
    if  (
          ( s_list[index_right_c] != '?' ) &&
          ( s_list[index_left_c]  != '?' )
        )
      if  ( ( s_list[index_right_c] != s_list[index_left_c] ) )
      {
        local_tuple_type res( -1 , "NO" );
        return res;
      } // if
      
    if  (
          ( s_list[index_right_c] == '?' ) &&
          ( s_list[index_left_c]  == '?' )
        )
    {
      s_list[index_right_c] = 'a';
      s_list[index_left_c]  = 'a';
    } // if
    
    if  (
          ( s_list[index_right_c] != '?' ) &&
          ( s_list[index_left_c]  == '?' )
        )
      s_list[index_left_c] = s_list[index_right_c];
    
    if  (
          ( s_list[index_right_c] == '?' ) &&
          ( s_list[index_left_c]  != '?' )
        )
      s_list[index_right_c] = s_list[index_left_c];
  } // for
  
  local_tuple_type
    res( 0 , 
         vector_of_characters_to_string(s_list) );
  return res;
} // solution_generate_palindrome_if_possible

} // namespace os_core

namespace os_test
{
using namespace os_core;

void 
test_solution ()
{
  using namespace std;
  
  std::vector<std::string> s_inputs = 
    {
      "?" ,
      "ba?" ,
      "ab" ,
      "a?b" ,
      "bac?b" ,
      "?acab"
    };
  
  cout << endl;
  for ( auto item : s_inputs )
  {
    auto ret_val
      = solution_generate_palindrome_if_possible
          (item, false);
          
    cout 
      << "Original String:" << endl
      << "  " << item << endl;
    cout
      << "Returned Error Code:" << endl
      << "  " << std::get<0>(ret_val) << endl;
    if ( std::get<0>(ret_val) != -1 )
      cout
        << "Returned Palindrome:" << endl;
    else
      cout
        << "Returned String Denoting Error:" << endl;
    cout
      << "  " << std::get<1>(ret_val) << endl << endl;
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