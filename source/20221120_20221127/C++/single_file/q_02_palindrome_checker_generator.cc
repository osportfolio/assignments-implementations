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

/*
 * I collected the type definitions I will need
 * in a separate namespace so as to make them
 * reusable in a different context if necessary.
 * Confining these definitions in namespace scope
 * is a good practice.
 * */
namespace os_types
{
  using tuple_of_int_string_type =
    std::tuple<int, std::string>;
} // namespace os_types

/*
 * The namespace below contains computation and
 * reporting related functions, as opposed to tests.
 * I did not make use of classes for the current 
 * problem in hand.
 * */
namespace os_core
{
  
/*
 * The function below is a counterpart for the statement
 * 'list_variable = list(string_variable)' in Python.
 * 'std::vector<char>' is a replacement for 'list'
 * in Python.
 * */
std::vector<char>
string_to_vector_of_characters
(
  std::string  s_in
)
{
  /*
   * The reference definition below makes use of a
   * feature called template deduction through the 
   * 'auto' keyword. What it does in effect is to
   * produce an alias.
   * */
  auto & A = s_in;
  std::vector<char>  s_list;
  
  s_list.reserve( A.length() );
  
  /*
   * The statement below makes it possible to gain
   * access to the internal C-type char array accommodated
   * by an std::string variable. Again template deduction
   * is at work.
   * */
  const auto * c_ptr = A.c_str();
  
  /*
   * The post-increment for the const char pointer
   * below enables the developer to code a single-statement
   * body inside the for loop, so {} are not necessary.
   * */
  for ( unsigned int kk = 0 ; kk < A.length() ; ++kk )
    s_list.push_back( *(c_ptr++) );
  
  return s_list;
} // string_to_vector_of_characters

/*
 * What the function below does is to provide a counterpart
 * for 'string_variable = ''.join(list_of_strings_variable)'
 * in Python. The characters are joined with an empty string
 * '' between consecutive items.
 * */
std::string
vector_of_characters_to_string
(
  std::vector<char>  v_in
)
{
  /*
   * Thanks to the iterator-based constructor overload for
   * std::string, the statement below is actually as brief
   * as it is.
   * */
  std::string  res( v_in.begin() , v_in.end() );
  return res;
} // vector_of_characters_to_string

/*
 * Function for devising a palindrome out of the input string
 * if possible. If not possible the tuple consisting of (-1, "NO")
 * will be returned. In C++, only a single return value or reference 
 * is allowed; therefore, I am making use of a tuple.
 * */
std::tuple<int, std::string>
solution_generate_palindrome_if_possible
(
  std::string  A ,
  bool         flag_debug = true
)
/*
 * The default value for 'flag_debug' is set, and this setting
 * will print strings along the way to the final result. For
 * resetting 'flag_debug', the value for the indicated argument
 * has to be expressed as false while calling this function.
 * */
{
  using local_tuple_type =
    os_types::tuple_of_int_string_type;
  /*
   * Setting the local type to be used in this function.
   * */
  
  auto s_list = 
    string_to_vector_of_characters( A );
  /*
   * Obtain the list of characters within the given
   * string A.
   * */
    
  int 
    index_middle ,
    index_right ,
    index_left ,
    n_max;
  /*
   * Declare the variables to be computed and used within
   * the control flow statements below.
   * */
    
  /*
   * Below, the variables 'index_right',
   * 'index_left', and 'n_max' have to be
   * calculated separately for an odd and
   * an even number of characters within
   * the original string. 
   * 
   * 'n_max' is the number of characters
   * to the right and left of the character
   * in the middle position (if there are an
   * odd number of characters) or in the 
   * position between the characters in the
   * middle (if there are even number of
   * characters).
   * 
   * 'index_right' and 'index_left' are the
   * starting values of the indices calculated
   * through integer offsets from the middle 
   * position (as explained above for the number 
   * of characters being odd or even) for the
   * characters to the right and to the left,
   * respectively, of the indicated position.
   * */
  if ( s_list.size() % 2 == 1 )
  {
    index_middle = (s_list.size() - 1) / 2;
    if ( s_list[index_middle] == '?' )
      s_list[index_middle] = 'a';
    /*
     * For a string with an odd number of
     * characters, the character in the middle
     * has to be set, if it has not already been
     * set.
     * */
    
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
    /*
     * Calculate the current indices through
     * the update 'kk' upon the initial values
     * for the indices of the entries to the
     * right and left of the entry in the middle.
     * The odd and even cases have already been
     * taken care of, so the codes above and
     * below within the scope of this for loop
     * apply to both cases.
     * */
      
    if  (
          ( s_list[index_right_c] != '?' ) &&
          ( s_list[index_left_c]  != '?' )
        )
      if  ( ( s_list[index_right_c] != s_list[index_left_c] ) )
      {
        local_tuple_type res( -1 , "NO" );
        return res;
      } // if
    /*
     * If the entries at the same distance to the 
     * right and left of the middle position are 
     * already set and are not the same, then
     * the string cannot be a palindrome.
     * */
      
    if  (
          ( s_list[index_right_c] == '?' ) &&
          ( s_list[index_left_c]  == '?' )
        )
    {
      s_list[index_right_c] = 'a';
      s_list[index_left_c]  = 'a';
    } // if
    /*
     * If the entries of interest to the right and
     * left have not already been set, then set them
     * as the same character.
     * */
    
    if  (
          ( s_list[index_right_c] != '?' ) &&
          ( s_list[index_left_c]  == '?' )
        )
      s_list[index_left_c] = s_list[index_right_c];
    /*
     * If the entry of interest to the right has
     * been set but that to the left not so, then
     * set the entry to the left to continue
     * in the path to obtaining a palindrome at
     * the end.
     * */
    
    if  (
          ( s_list[index_right_c] == '?' ) &&
          ( s_list[index_left_c]  != '?' )
        )
      s_list[index_right_c] = s_list[index_left_c];
    /*
     * If the entry of interest to the left has
     * been set but that to the right not so, then
     * set the entry to the right to continue
     * in the path to obtaining a palindrome at
     * the end.
     * */
  } // for
  
  local_tuple_type
    res( 0 , 
         vector_of_characters_to_string(s_list) );
  return res;
  /*
   * Join the resulting characters into a string, form
   * the tuple, and return this tuple. '0' for the return
   * value means 'no problem encountered'.
   * */
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
  /*
   * Vector of string inputs.
   * */
  
  cout << endl;
  for ( auto item : s_inputs )
  {
    auto ret_val
      = solution_generate_palindrome_if_possible
          (item, false);
    /*
     * Reset the debug flag. Get the returned value
     * from the solution function. 'auto' enables
     * type deduction to set the type of 'ret_val'
     * as a tuple of an integer and a string.
     * */
          
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
    /*
     * Report by obtaining the values contained within
     * the returned tuple.
     * */
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