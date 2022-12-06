/*
 * Reorganized code into a multiple source file project
 *              on Dec 2, 2022 / Fri
 * */

#include "character_operations.hh"

namespace os_utilities
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

} // namespace os_utilities