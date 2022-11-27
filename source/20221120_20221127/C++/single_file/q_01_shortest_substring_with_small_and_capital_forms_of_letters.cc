/*
 * This code with the function 'solution...' given
 * a string input computes the length of the shortest 
 * substring that only accommodates both small and capital
 * versions of all the letters included in the indicated
 * substring.
 * */

// worked on this code on 
//                       Nov 20, 2022 / Sun

#include <vector>
#include <unordered_map>
#include <set>
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
  using unordered_map_char_char_type = 
    std::unordered_map<char, char>;
  using set_of_char_type =
    std::set<char>;
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
 * The function below is almost a direct translation
 * of the 'range_char' function in the Python 
 * implementation for the same solution.
 * */
std::vector<char>
get_range_of_characters
(
  char  c_start,
  char  c_end
)
{
  std::vector<char>  result;
  
  /*
   * The 'reserve' member function takes care of
   * preallocation of necessary memory in cases
   * where the number of items to be stored in a 
   * vector can be prespecified.
   * */
  result.reserve( c_end - c_start + 1 );
  for ( char item = c_start ; item <= c_end ; ++item )
    result.push_back( item );
  
  return  result;
} // get_range_of_characters

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
 * The reporter function template below is able to operate
 * on a 'c_input' that can for example be of the type
 * 'std::vector<char>'. Instead of 'std::vector', virtually
 * any type iterable by iterators, and instead of char,
 * virtually any type with '<<' overload can be type-detected
 * by template deduction. So what we have is a versatile
 * function of great and convenient utility.
 * */
template
< typename Container >
void
print_container_of_items
(
  Container    c_input ,
  std::string  identifier = "unspecified"
)
{
  /*
   * The identifier can be set through the second argument
   * setting by the caller of the function. Otherwise, the
   * default value for it is used.
   * */
  using namespace std;
  cout 
    << "Printing items (of " 
    << identifier
    << "):" 
    << endl << "  ";
  
  /*
   * The range-based for loop below is dependent on the
   * iterable type, of which 'std::vector' is an example.
   * */
  for ( auto item : c_input )
    cout << item << " ";
  cout << endl;
} // print_container_of_items

/*
 * Function for computing the shortest string with the specified
 * property and for returning both the length and the string
 * itself through a tuple. In C++, only a single return value
 * or reference is allowed.
 * */
std::tuple<int, std::string>
solution_min_length_of_string_with_both_capital_and_small_letters
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
  using local_map_type = 
    os_types::unordered_map_char_char_type;
  using local_set_type =
    os_types::set_of_char_type;
  using local_tuple_type =
    os_types::tuple_of_int_string_type;
  /*
   * Setting the local types to be used in this function.
   * */
    
  local_map_type  mp_small;
  local_map_type  mp_cap;
  /*
   * Declaring the maps from small to capital, and 
   * vice versa.
   * 
   * Set these up to map each of the small
   * letters to the corresponding capital letter,
   * and vice versa. Hashes will save us time through
   * the virtually constant-time access facility.
   * */
    
  auto smalls =
    get_range_of_characters('a', 'z');
  auto capitals =
    get_range_of_characters('A', 'Z');
  /*
   * Getting the ranges for small and capital
   * letters.
   * */
    
  int cnt = 0;
  for ( auto item : smalls )
  {
    mp_small[item] 
      = capitals[cnt];
    mp_cap[capitals[cnt]]
      = item;
    ++cnt;
  } // for
  /*
   * Populating the maps.
   * */
  
  auto s_list = 
    string_to_vector_of_characters( A );
  /*
   * Obtain the list of characters within the given
   * string A.
   * */
  
  if ( flag_debug )
    print_container_of_items( s_list );
  
  for ( unsigned int 
          s_length = 2 ;
          s_length < A.length() + 1 ;
          ++s_length
      )
  {
    for ( unsigned int
            s_index_start = 0 ;
            s_index_start < A.length() - s_length + 1  ;
            ++s_index_start
        )
    /*
     *  A useful substring has a length starting from 2
     *  and extending to the length of the whole string.
     *
     *  The starting index for the substring in question
     *  has to have a range as indicated by the statement
     *  defining the iteration index for the inner 'for'
     *  loop.
     *   
     *  Since 's_length' is iteratively set starting
     *  from the lowest length possible, the first
     *  success to be encountered during the search
     *  will mark the time to draw the function to
     *  an end, having found the shortest string that
     *  accommodates nothing other than some characters
     *  in both small and capital forms.
     * */
    {
      decltype(s_list)
        temp(
              s_list.begin() + s_index_start ,
              s_list.begin() + s_index_start + s_length
            );
      if ( flag_debug )
        print_container_of_items( temp , "vector" );
      /*
       * The list of characters for the current substring in
       * question.
       *
       * Declaration type through 'decltype' is very handy;
       * auto will not work in here. The iterator based
       * ctor overload of containers is called.
       * */
      
      local_set_type
        temp_set( 
                  temp.begin() ,
                  temp.end()
                );
      if ( flag_debug )
        print_container_of_items( temp_set , "set" );
      /*
       * Declare and initialize set from vector, again
       * through iterator based ctor.
       * 
       * Generated a set from the characters within the
       * substring. A set rules out duplicates. Will be
       * making use of the dictionaries to check if a 
       * character together with its small or capital 
       * form is included within the substring in question.
       * */
      
      bool flag_found = true;
      /*
       * If the flag above remains true after the 'for' loop
       * below, then it will be time to return and yield
       * the result.
       * */
      
      for ( auto item : temp_set )
      {
        if
          (
            ( 
              ( mp_small.find(item) != mp_small.end() ) 
              && 
              ( temp_set.find(mp_small[item]) != temp_set.end() ) 
            )
            ||
            (
              ( mp_cap.find(item) != mp_cap.end() )
              &&
              ( temp_set.find(mp_cap[item]) != temp_set.end() )
            )
          )
          /*
           * Making use of the maps (and drawing
           * benefits through the constant-time access)
           * to check if a character together with its
           * corresponding small or capital form exists
           * within the current substring.
           * */
        {}
        else
        {
          flag_found = false;
          break;
          /*
           * If the condition above is not satisfied even for
           * a single character, then we should break out of the
           * for loop since there is no need to lose time
           * checking the remaining characters. Setting the
           * flag to false will prevent the remaining 'if'
           * conditional from terminating the function.
           * */
        }
      } // for item
      
      if ( flag_found )
      {
        if ( flag_debug )
          print_container_of_items( temp , "vector" );
        
        local_tuple_type
          res( s_length , 
               vector_of_characters_to_string(temp) );
        return res;
        /*
         * The first success to be encountered has the function
         * return the length of the string in question and the
         * string itself in a tuple.
         * */
      }
      
    } // for s_index_start
  } // for s_length

  local_tuple_type res( -1 , "" );
  return res;
  /*
   * No possible success meaning there is no substring within
   * the original string accommodating both small and capital
   * forms of some letters, and nothing else.
   * */
} // solution_min_length_of_string_with_both_capital_and_small_letters

} // namespace os_core

namespace os_test
{
using namespace os_core;

void
test_print_range_of_characters
()
{
  auto 
  result = get_range_of_characters('a', 'z');
  print_container_of_items(result);
  result = get_range_of_characters('A', 'Z');
  print_container_of_items(result);
} // test_print_range_of_characters
  
void 
test_solution ()
{
  using namespace std;
  
  std::vector<std::string> s_inputs = 
    {
      "aACCCxA" ,
      "CCzzcZazAxAZ" ,
      "CCzzcybzAxAZ"
    };
  
  cout << endl;
  for ( auto item : s_inputs )
  {
    auto ret_val
      = solution_min_length_of_string_with_both_capital_and_small_letters
          (item, false);
    /*
     * Call the function with 'flag_debug' reset and obtain the
     * resulting tuple.
     * */
          
    cout 
      << "Original String:" << endl
      << "  " << item << endl;
    cout
      << "Returned Length or Error Code (of -1):" << endl
      << "  " << std::get<0>(ret_val) << endl;
    if ( std::get<0>(ret_val) != -1 )
      cout
        << "Returned String:" << endl
        << "  " << std::get<1>(ret_val) << endl << endl;
    /*
     * Get the values stored in the returned tuple with
     * std::get and print.
     * */
  } // for
  
} // test_solution
  
} // namespace os_test

int
main(void)
{
  using namespace os_test;
  
//   test_print_range_of_characters();
  test_solution();
  
  return 0;
}