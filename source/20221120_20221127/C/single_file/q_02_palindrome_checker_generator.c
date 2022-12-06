/*
 * The function 'solution' tries to generate
 * a palindrome out of the string 'S' given
 * as an input argument, replacing the '?'
 * characters by what is required, and returns
 * the palindrome or the string 'NO', the
 * latter being the error identifier in case
 * no palindrome construction is possible.
 * */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *
solution_palindrome_checker_generator
(
  const char *  S
)
{
  /*
   * Predeclarations necessary even for indices
   * such as 'kk' to be used in 'for' loops in C.
   * */
  int
    index_middle , index_right , index_left ,
    n_max , kk;
  
  /*
   * Dynamic memory allocation for the target string.
   * The additional character is for NULL that should
   * exist at the end of each C string.
   * */
  char * s_target
    = (char *) calloc( 1 + strlen(S) , sizeof(char) );
  /*
   * Copy original string into the allocated space.
   * */
  strcpy( s_target , S );
  
  int size
    = strlen( s_target );
  
  /*
   * Below, the variables 'index_right',
   * 'index_left', and 'n_max' have to be
   * calculated separately for an odd and
   * an even number of characters within
   * the original string. 
   *  
   * 'n_max' is the number of characters
   * to the right and left of the character
   * in the middle position (if there are an
   * odd number of characters) or in the 
   * position between the characters in the
   * middle (if there are even number of
   * characters).
   *  
   * 'index_right' and 'index_left' are the
   * starting values of the indices calculated
   * through integer offsets from the middle 
   * position (as explained above for the number 
   * of characters being odd or even) for the
   * characters to the right and to the left,
   * respectively, of the indicated position.
   * */
    
  if ( size % 2 == 1 )
  {
    index_middle = (size - 1) / 2;
    if ( s_target[index_middle] == '?' )
      s_target[index_middle] = 'a';
    /*
     * For a string with an odd number of
     * characters, the character in the middle
     * has to be set, if it has not already been
     * set.
     * */
    index_right = index_middle + 1;
    index_left  = index_middle - 1;
    n_max = (size - 1) / 2;
  } // if
  else
  {
    index_right = size / 2;
    index_left  = size / 2 - 1;
    n_max = size / 2;
  } // else
  
  for ( kk=0 ; kk<n_max ; ++kk )
  {
    int 
      index_right_c = index_right + kk,
      index_left_c  = index_left  - kk;
    /*
     * Calculate the current indices through
     * the update 'kk' upon the initial values
     * for the indices of the entries to the
     * right and left of the entry in the middle.
     * The odd and even cases have already been
     * taken care of, so the codes above and
     * below within the scope of this for loop
     * apply to both cases.
     * */
      
    if ( ( s_target[index_right_c] != '?' ) &&
         ( s_target[index_left_c]  != '?' ) )
      if ( s_target[index_right_c] != s_target[index_left_c] )
      {
        strcpy( s_target , "NO" );
        return s_target;
      }
    /*
     * If the entries at the same distance to the 
     * right and left of the middle position are 
     * already set and are not the same, then
     * the string cannot be a palindrome.
     * */
      
    if ( ( s_target[index_right_c] == '?' ) &&
         ( s_target[index_left_c]  == '?' ) )
    {
      s_target[index_right_c] = 'a';
      s_target[index_left_c]  = 'a';
    }
    /*
     * If the entries of interest to the right and
     * left have not already been set, then set them
     * as the same character.
     * */
    
    if ( ( s_target[index_right_c] != '?' ) &&
         ( s_target[index_left_c]  == '?' ) )
      s_target[index_left_c] = s_target[index_right_c];
    /*
     * If the entry of interest to the right has
     * been set but that to the left not so, then
     * set the entry to the left to continue
     * in the path to obtaining a palindrome at
     * the end.
     * */
    
    if ( ( s_target[index_right_c] == '?' ) &&
         ( s_target[index_left_c]  != '?' ) )
      s_target[index_right_c] = s_target[index_left_c];
    /*
     * If the entry of interest to the left has
     * been set but that to the right not so, then
     * set the entry to the right to continue
     * in the path to obtaining a palindrome at
     * the end.
     * */
  } // for
  
  return s_target;
}

int
main(void)
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