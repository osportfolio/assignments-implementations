/*
 * tic/toc implementations with 'std::chrono'.
 * */

/*
 * Worked on this code on
 *   Jan  3, 2023 / Tue
 * */

#include "durations.hh"

namespace os_core
{
namespace chrono_utils
{
  
std::chrono::high_resolution_clock::time_point
tic
()
{
  using namespace std::chrono;
  return high_resolution_clock::now();
}

double
toc
(
  std::chrono::high_resolution_clock::time_point  t_start
)
{
  using namespace std::chrono;
  auto  t_end 
    = high_resolution_clock::now();
  duration<double>  sec_d
    = t_end - t_start;
  return  sec_d . count();
}
  
} // namespace chrono_utils
} // namespace os_core
