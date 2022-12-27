#pragma once

#include <tuple>

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
);
  
} // namespace ns__with_references_in_CPP

namespace ns__with_tuples_holding_references_in_CPP
{
  
void
update
(
  std::tuple<int &, int &>  arg_tuple
);
  
} // namespace ns__with_tuples_holding_references_in_CPP
  
} // namespace os_core
} // namespace os_core
