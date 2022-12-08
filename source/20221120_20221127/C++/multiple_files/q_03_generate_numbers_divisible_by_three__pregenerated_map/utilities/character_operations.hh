/*
 * Reorganized code into a multiple source file project
 *              on Dec 2, 2022 / Fri
 * */

#pragma once

#include <vector>
#include <set>
#include <string>
#include <iostream>

namespace os_types
{
  using set_of_int_type =
    std::set<int>;
} // namespace os_types

namespace os_utilities
{

std::vector<int>
range_of_integers
(
  int  i_start ,
  int  i_end ,
  int  i_increment
);

std::vector<char>
string_to_vector_of_characters
(
  std::string  s_in
);

std::string
vector_of_characters_to_string
(
  std::vector<char>  v_in
);

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

} // namespace os_utilities