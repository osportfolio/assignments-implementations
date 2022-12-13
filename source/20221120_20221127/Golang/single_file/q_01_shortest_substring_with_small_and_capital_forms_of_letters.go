package main

/*
The function 'solution' given
a string input computes the length of the shortest 
substring that only accommodates both small and capital
versions of all the letters included in the indicated
substring.
*/

/*
  Worked on this code on 
                        Dec 13, 2022 / Tue
*/

import (
  "fmt" 
//   "sort"
//   "strings"
)

func range_char(c_start rune, c_stop rune) [] rune {
  var  chars  [] rune
  for i := c_start ; i <= c_stop ; i++ {
    chars = append(chars, i)
  }
  return chars
}
/*
  Function to compute a range of characters in the
  ASCII table. I obtained this function from a webpage.
*/

func solution( A string ) int {
  smalls   := range_char( 'a' , 'z' )
  capitals := range_char( 'A' , 'Z' )
  /*
    Make use of the function 'range_char' to
    compute separately the ranges for the small
    and capital letters. These are now available
    as arrays.
  */
  
  mp_small := make( map[rune] rune )
  mp_cap   := make( map[rune] rune )
  for kk , item := range smalls {
    mp_small[ item ]         = capitals[kk]
    mp_cap  [ capitals[kk] ] = item
  }
  /*
    Set up maps to map each of the small
    letters to the corresponding capital letter,
    and vice versa. Hashes will save us time through
    the virtually constant-time access facility.
  */
  
  /*
  fmt.Printf( "\n" );
  for key := range mp_small {
    fmt.Printf( "  %c -> %c\n" , key , mp_small[key] )
  }
  */
  
  s_list := [] rune( A )
  /*
    Obtain an array of the characters within the given
    string A.
  */
  
  var  s_length  int
  var  s_index_start  int
  for s_length = 2 ; s_length < len(A) + 1 ; s_length++ {
    for s_index_start = 0 ; s_index_start < len(A) - s_length + 1 ; s_index_start++ {
      /*
        A useful substring has a length starting from 2
        and extending to the length of the whole string.
        
        The starting index for the substring in question
        has to have a range as indicated by the statement
        defining the iteration index for the inner 'for'
        loop.
        
        Since 's_length' is iteratively set starting
        from the lowest length possible, the first
        success to be encountered during the search
        will mark the time to draw the function to
        an end, having found the shortest string that
        accommodates nothing other than some characters
        in both small and capital forms.
      */
      
      temp := s_list[ s_index_start : (s_index_start+s_length) ]
      /*
        The array of characters for the current substring in
        question.
      */

/*      
      temp_string := string( temp )
      fmt.Printf( "%4d  %4d  %s\n" , 
                  s_index_start , s_length , temp_string )
*/      
      
      temp_set := make( map[rune] int )
      for _, v := range temp {
        temp_set[v] = 1
      }
      // No duplicates in the keys of 'temp_set'
      /*
        Keys of a map can be treated as a set.
       
        Generated a set from the characters within the
        substring. A set rules out duplicates. Will be
        making use of the maps to check if a 
        character together with its small or capital 
        form is included within the substring in question.
      */
      
      flag_found := true
      /*
        If the flag above remains true after the 'for' loop
        below, then it will be time to return and yield
        the result.
      */
      
      for item := range temp_set {
        _ , flag_is_item_in_mp_small := mp_small[item]
        _ , flag_is_item_in_mp_cap   := mp_cap  [item]
        
        flag_is_corresponding_cap_in_temp_set   := false
        flag_is_corresponding_small_in_temp_set := false
        
        if flag_is_item_in_mp_small {
          _ , flag_is_corresponding_cap_in_temp_set   = temp_set[ mp_small[item] ]
        }
        if flag_is_item_in_mp_cap {
          _ , flag_is_corresponding_small_in_temp_set = temp_set[ mp_cap  [item] ]
        }
        
        /*
          Making use of the maps (and drawing
          benefits through the constant-time access)
          to check if a character together with its
          corresponding small or capital form exists
          within the current substring.
        */
        if  ! ( 
            ( ( flag_is_item_in_mp_small ) && 
              ( flag_is_corresponding_cap_in_temp_set ) ) ||
            ( ( flag_is_item_in_mp_cap ) && 
              ( flag_is_corresponding_small_in_temp_set ) ) ) {
          flag_found = false
          // fmt.Printf( "False\n" )
          break
          
          /*
            If the condition above is not satisfied even for
            a single character, then we should break out of the
            for loop since there is no need to lose time
            checking the remaining characters. Setting the
            flag to false will prevent the remaining 'if'
            conditional from terminating the function.
          */
        } // if
      } // for item
      
      if flag_found {
        fmt.Printf (
          "String found in \"%s\" :\n  %s\n" , A ,
          string( temp ) )
        return len(temp)
      }
      /*
        The first success to be encountered has the function
        return the length of the string in question.
      */
      
    } // for s_index_start
  } // for s_length
  
  return -1
  /*
    No possible success meaning there is no substring within
    the original string accommodating both small and capital
    forms of some letters, and nothing else.
  */
}

func main() {
  s_inputs := [] string {
    "Bb" ,
    "aACCCxA" , 
    "CCzzcZazAxAZ" , 
    "CCzzcybzAxAZ" }

  for _, str := range s_inputs {
    fmt.Println()
      
    s_out := solution( str )
    fmt.Println( 
      fmt.Sprintf( "Response to \"%s\" :" , str ) )
    fmt.Println( " " , s_out )
  }
}