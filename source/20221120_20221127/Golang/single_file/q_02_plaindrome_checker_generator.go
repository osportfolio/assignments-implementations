/*
 * The function 'solution' tries to generate
 * a palindrome out of the string 'S' given
 * as an input argument, replacing the '?'
 * characters by what is required, and returns
 * the palindrome or the string 'NO', the
 * latter being the error identifier in case
 * no palindrome construction is possible.
 * */

/*
  Worked on this code on
                        Dec 4, 2022 / Sun
*/

package main

import "fmt"

func solution(s_input string) string {
  s_list := [] rune(s_input)
  var sz = len( s_list )
  /*
   * Obtain a list of characters from the input string,
   * and also the length of the list.
   * */
  
  var index_middle , index_right , index_left , n_max int
  var kk int
  /*
   * Declare variables with types.
   * */
  
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
  if sz % 2 == 1 {
    index_middle = (sz - 1) / 2
    if s_list[index_middle] == '?' {
      s_list[index_middle] = 'a'
    }
    /*
     * For a string with an odd number of
     * characters, the character in the middle
     * has to be set, if it has not already been
     * set.
     * */
    
    index_right = index_middle + 1
    index_left  = index_middle - 1
    n_max = (sz - 1) / 2
  } else {
    index_right = sz / 2
    index_left  = sz / 2 - 1
    n_max = sz / 2
  }
  
  for kk = 0 ; kk < n_max ; kk++ {
    index_right_c := index_right + kk
    index_left_c  := index_left  - kk
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
    
    if ( s_list[index_right_c] != '?' ) &&
       ( s_list[index_left_c]  != '?' ) {
      if ( s_list[index_right_c] != s_list[index_left_c] ) {
        return "NO"
      }
    }
    /*
     * If the entries at the same distance to the 
     * right and left of the middle position are 
     * already set and are not the same, then
     * the string cannot be a palindrome.
     * */
    
    if ( s_list[index_right_c] == '?' ) &&
       ( s_list[index_left_c]  == '?' ) {
      s_list[index_right_c] = 'a'
      s_list[index_left_c]  = 'a'
    }
    /*
     * If the entries of interest to the right and
     * left have not already been set, then set them
     * as the same character.
     * */
    
    if ( s_list[index_right_c] != '?' ) &&
       ( s_list[index_left_c]  == '?' ) {
      s_list[index_left_c] = s_list[index_right_c]
    }
    /*
     * If the entry of interest to the right has
     * been set but that to the left not so, then
     * set the entry to the left to continue
     * in the path to obtaining a palindrome at
     * the end.
     * */
    
    if ( s_list[index_right_c] == '?' ) &&
       ( s_list[index_left_c]  != '?' ) {
      s_list[index_right_c] = s_list[index_left_c]
    }
    /*
     * If the entry of interest to the left has
     * been set but that to the right not so, then
     * set the entry to the right to continue
     * in the path to obtaining a palindrome at
     * the end.
     * */
  } // for
  
  return string(s_list)
}

func main() {
  s_inputs := [6] string {
    "?" , "ba?" , "ab" , "a?b" , "bac?b" , "?acab" }
  var kk int
  
  for kk = 0 ; kk < 6 ; kk++ {
    s_out := solution( s_inputs[kk] )
    fmt.Println( 
      fmt.Sprintf( "Response to \"%s\" :" , s_inputs[kk] ) )
    fmt.Println( " " , s_out )
  }
}