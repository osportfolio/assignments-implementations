/*
 * tic/toc implementations with 'std::chrono'.
 * */

/*
 * Worked on this code on
 *   Jan  3, 2023 / Tue
 * */

#pragma once

#include <chrono>

namespace os_core
{
namespace chrono_utils
{

std::chrono::high_resolution_clock::time_point
tic
();

double
toc
(
  std::chrono::high_resolution_clock::time_point  t_start
);

} // namespace chrono_utils
} // namespace os_core
