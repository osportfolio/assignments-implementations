#pragma once

/*
 * The function 'solution' tries to generate
 * a palindrome out of the string 'S' given
 * as an input argument, replacing the '?'
 * characters by what is required, and returns
 * the palindrome or the string 'NO', the
 * latter being the error identifier in case
 * no palindrome construction is possible.
 * */

#ifdef __cplusplus
extern "C" {
#endif

char *
solution_palindrome_checker_generator
(
  const char *  S
);

#ifdef __cplusplus
}
#endif