#pragma once

/*
The function 'solution' given
a string input computes the length of the shortest 
substring that only accommodates both small and capital
versions of all the letters included in the indicated
substring.
*/

/*
  Worked on this code on
                        Dec 11-12, 2022 / Sun-Mon
*/

#ifdef __cplusplus
extern "C" {
#endif

char *
solution_shortest_substring_with_small_and_capital_forms_of_letters
(
  const char * string_given
);

void
test_of_solution
();

#ifdef __cplusplus
}
#endif