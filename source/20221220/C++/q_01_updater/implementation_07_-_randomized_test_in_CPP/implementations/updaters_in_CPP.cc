#include "updaters_in_CPP.hh"

#include <cstdlib>

namespace os_core
{
namespace updaters
{

namespace ns__with_references_in_CPP
{

void
update
(
  int &  i_1st ,
  int &  i_2nd
)
{
  int
    i_1st_original = i_1st ,
    i_2nd_original = i_2nd ;
    
  i_1st 
    = i_1st_original + i_2nd_original;
  
  int i_difference 
    = i_1st_original - i_2nd_original;
    
  i_2nd = abs( i_difference );
  
  return;  
} // update
  
} // namespace ns__with_references_in_CPP

namespace ns__with_tuples_holding_references_in_CPP
{
  
void
update
(
  std::tuple<int &, int &>  arg_tuple
)
{
  auto & i_1st = std::get<0>( arg_tuple );
  auto & i_2nd = std::get<1>( arg_tuple );
  
  int
    i_1st_original = i_1st ,
    i_2nd_original = i_2nd ;
  
  i_1st
    = i_1st_original + i_2nd_original;
  
  i_2nd 
    = abs( i_1st_original - i_2nd_original );
    
  return;
} // update
  
} // namespace ns__with_tuples_holding_references_in_CPP
  
} // namespace os_core
} // namespace os_core
