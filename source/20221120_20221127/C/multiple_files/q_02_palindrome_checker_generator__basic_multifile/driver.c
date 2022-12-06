#include "palindrome.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int
main (void)
{
  /*
   * Initialize the list of input strings as a
   * array of char pointers. The array size is 6.
   * */
  const char *list_of_strings[6]
    = { "?" , "ba?" , "ab" , "a?b" , "bac?b" , "?acab" };
  int kk;
  
  for ( kk=0 ; kk<6 ; ++kk )
  {
    /*
     * Get the output string returned by the function.
     * */
    char * s_target_ptr
      = solution_palindrome_checker_generator
          ( list_of_strings[kk] );
    
    /*
     * Report
     * */
    printf( "Response to \"%s\" :\n" , list_of_strings[kk] );
    printf( "  %s\n" , s_target_ptr );
    
    /*
     * The char pointer returned by the function points
     * to dynamically allocated memory, and this should be
     * freed by the user. There is no automatic garbage
     * collection in C. The indicated pointer has to be
     * freed outside the scope of the function as illustrated
     * below.
     * */
    free( s_target_ptr );
  } // for
  
  return 0;
}