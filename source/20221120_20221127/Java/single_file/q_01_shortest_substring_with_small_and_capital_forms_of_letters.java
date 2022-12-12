/*
The function 'solution' given
a string input computes the length of the shortest 
substring that only accommodates both small and capital
versions of all the letters included in the indicated
substring.
*/

/*
  Worked on this code on 
                        Dec 12, 2022 / Mon
*/

import java.util.*;

public class Main 
{

  /*
  Function to compute a range of characters in the
  ASCII table. I obtained this function from a webpage.
  */
  static
  String
  range_char
  (
    char  c_start , 
    char  c_stop
  )
  {
    StringBuilder sb = new StringBuilder();
    for ( char c = c_start; c <= c_stop ; ++c )
    {
      sb.append(c);
    }
    return sb.toString();
  }
  
  static
  int
  solution
  (
    String  A
  )
  {
    String  smalls   = range_char( 'a' , 'z' );
    String  capitals = range_char( 'A' , 'Z' );
    /*
    Make use of the function 'range_char' to
    compute separately the ranges for the small
    and capital letters. These are now available
    as lists.
    */
    
    HashMap<Character, Character> mp_small = new HashMap<>();
    HashMap<Character, Character> mp_cap   = new HashMap<>();
    
    for ( Integer kk = 0 ; kk < smalls.length() ; ++kk )
    {
      mp_small.put( smalls.charAt(kk)   , capitals.charAt(kk) );
      mp_cap  .put( capitals.charAt(kk) , smalls.charAt(kk) );
    }
    /*
    Set up maps to map each of the small
    letters to the corresponding capital letter,
    and vice versa. Hashes will save us time through
    the virtually constant-time access facility.
    */
    
    /*
    for ( Character key : mp_small.keySet() ) 
    {
      System.out.printf ( "%c -> %c\n" , key , mp_small.get(key) );
    }
    */
    
    for ( Integer 
          s_length = 2 ; s_length < A.length() + 1 ; ++s_length )
    {
      for ( Integer 
            s_index_start = 0 ; 
            s_index_start < A.length() - s_length + 1 ;
          ++s_index_start )
      {
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
        
        String temp = A.substring( s_index_start , 
                                   s_index_start + s_length );
        /*
        The list of characters for the current substring in
        question.
        */
        
        /*
          See the answer at:
            stackoverflow.com/questions/6319775/java-collections-convert-a-string-to-a-list-of-characters
        */
        Set<Character> temp_set = new HashSet<Character>();
        for( char c : temp.toCharArray() ) 
        {
          temp_set.add(c);
        }
        /*
        Generated a set from the characters within the
        substring. A set rules out duplicates. Will be
        making use of the dictionaries to check if a 
        character together with its small or capital 
        form is included within the substring in question.
        */
/*
        System.out.printf ( "%4d%4d  %s  " , 
          s_index_start , s_length , temp );
        for ( char c : temp_set )
        {
          System.out.printf ( "%c" , c );
        }
        System.out.printf ( "\n" );
*/
        boolean flag_found = true;
        /*
        If the flag above remains true after the 'for' loop
        below, then it will be time to return and yield
        the result.
        */
      
        for ( char item : temp_set )
        {
          if
            (
              ( ( mp_small.containsKey(item) ) 
                && 
                ( temp_set.contains( mp_small.get(item) ) ) ) 
              ||
              ( ( mp_cap.containsKey(item) ) 
                && 
                ( temp_set.contains( mp_cap.get(item) ) ) ) 
            )
          {
          /*
            Making use of the maps (and drawing
            benefits through the constant-time access)
            to check if a character together with its
            corresponding small or capital form exists
            within the current substring.
          */
          }
          else
          {
            flag_found = false;
            break;
            /*
            If the condition above is not satisfied even for
            a single character, then we should break out of the
            for loop since there is no need to lose time
            checking the remaining characters. Setting the
            flag to false will prevent the remaining 'if'
            conditional from terminating the function.
            */
          }
        } // for item
        
        if ( flag_found )
        {
          System.out.printf (
            "String found in \'%s\' :\n  %s\n" , A , temp );
          return s_length;
        }
        /*
        The first success to be encountered has the function
        return the length of the string in question.
        */

      } // for s_index_start
    } // for s_length
    return -1;
    /*
    No possible success meaning there is no substring within
    the original string accommodating both small and capital
    forms of some letters, and nothing else.
    */
  }
  
  public static void main(String[] args) 
  {
    List<String> list_of_strings 
      = Arrays.asList
          (
            "Bb" ,
            "aACCCxA" ,
            "CCzzcZazAxAZ" ,
            "CCzzcybzAxAZ"
          );
          
    for ( String item : list_of_strings )
    {
      System.out.printf ( "\n" );
      Integer i_out = solution(item);
      System.out.printf (
        "Response to \'%s\' :\n  %s\n" , item , i_out );
    }
  } // main
} // class Main