#include "shortest_substring.h"

#include "utilities/string_array.h"
#include "utilities/character_sequences.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
solution_shortest_substring_with_small_and_capital_forms_of_letters
(
  const char * string_given
)
{
  /*
   * 'string_out' should be freed by the caller; calloc instead
   * of malloc is crucial for zeroed bits along the sequence.
   * Not forgetting '1 +' for the NULL terminator.
   * */
  char * string_out
    = (char *) calloc( 1 + strlen(string_given) , sizeof(char) );
  
  // Ranges of small and capital letters
  char * characters_small
    = range_char( 'a' , 'z' );
  char * characters_capital
    = range_char( 'A' , 'Z' );
    
  int s_length , s_index_start;
  for ( s_length = 2 ; s_length < 1 + strlen(string_given) ; ++s_length )
  {
    for ( s_index_start = 0 ; 
          s_index_start < strlen(string_given) - s_length + 1 ;
        ++s_index_start )
    {
      // Array of strings initialized.
      StringArrayContainer * container_ptr
        = StringArray_initialize();
        
      /* 
       * A character is not by itself recognized as a string.
       * Putting a single character into a holder with
       * guaranteed NULL termination.
       * */
      char ch_holder[8] , ch_corresponding[8];
      int ll;
      for ( ll = 0 ; ll < sizeof(ch_holder)/sizeof(char) ; ++ll )
      {
        ch_holder[ll]        = 0;
        ch_corresponding[ll] = 0;
      }
      
      /*
       * Forms a set of the characters found in the current
       * substring. No duplicates, mind the check with if.
       * Search is linear time.
       * */
      int kk;
      for ( kk = s_index_start ;
            kk < s_index_start + s_length ;
          ++kk
      )
      {
        ch_holder[0] 
          = string_given[kk];
        if ( ! StringArray_is_given_string_present
                 (container_ptr, ch_holder) )
          StringArray_add_string(container_ptr, ch_holder);
      } // for kk
      
      int
      flag_found = 1;
      
      /*
       * Lengthy for loop to determine the flags in each iteration
       * and to decide whether to continue with the seach or
       * to break out. Searches within the character sequences
       * and the array of strings (characters in this case)
       * are all linear time in the absence of hashes.
       * */
      for ( kk = 0 ;
            kk < StringArray_get_length(container_ptr) ;
          ++kk )
      {
        char * item 
          = StringArray_get_string_at_index(container_ptr, kk);
        int
          flag_is_item_in_characters_small   = 0 ,
          flag_is_item_in_characters_capital = 0 ,
          flag_is_corresponding_capital_in_the_substring = 0 ,
          flag_is_corresponding_small_in_the_substring   = 0 ;
          
        flag_is_item_in_characters_small
          = is_character_present_in_sequence
              ( item[0] , characters_small , 
                strlen(characters_small) );
        flag_is_item_in_characters_capital
          = is_character_present_in_sequence
              ( item[0] , characters_capital , 
                strlen(characters_capital) );
              
        if ( flag_is_item_in_characters_small )
        {
          int index 
            = index_of_first_occurence_of_character_in_sequence
                (item[0], characters_small, strlen(characters_small));
          ch_corresponding[0]
            = characters_capital[index];
          flag_is_corresponding_capital_in_the_substring
            = StringArray_is_given_string_present
                (container_ptr, ch_corresponding);
        }
        
        if ( flag_is_item_in_characters_capital )
        {
          int index 
            = index_of_first_occurence_of_character_in_sequence
                (item[0], characters_capital, 
                 strlen(characters_capital));
          ch_corresponding[0]
            = characters_small[index];
          flag_is_corresponding_small_in_the_substring
            = StringArray_is_given_string_present
                (container_ptr, ch_corresponding);
        }
        
        if
          (
            (
              flag_is_item_in_characters_small
              &&
              flag_is_corresponding_capital_in_the_substring
            )
            ||
            (
              flag_is_item_in_characters_capital
              &&
              flag_is_corresponding_small_in_the_substring
            )
          )
          ;
        else
        {
          flag_found = 0;
          break;
        }
      } // for kk
      
      /*
       * Deallocation of the temporary array of strings.
       * */
      StringArray_destroy
        (container_ptr);
        
      if ( flag_found )
      {
        /*
         * memcpy operation for string characters.
         * NULL termination guaranteed even in the extreme
         * case of returning the whole given string.
         * 
         * sizeof(char) is 1 byte and this is compiler
         * independent. Still including the sizeof
         * expression, although it is not necessary
         * in this case.
         * */
        memcpy
          ( string_out ,
            string_given + s_index_start , 
            s_length * sizeof(char) );
        return string_out;
      }
    } // for s_index_start
  } // for s_length
  
  return string_out;
}

void
test_of_solution
()
{
  const char *list_of_strings[4]
    = { "Bb" ,
        "aACCCxA" ,
        "CCzzcZazAxAZ" ,
        "CCzzcybzAxAZ" 
      };
     
  printf( "\n" );
        
  int kk;
  for ( kk = 0 ; kk < sizeof(list_of_strings) / sizeof(char *) ; ++kk )
  {
    char * item
      = solution_shortest_substring_with_small_and_capital_forms_of_letters
          ( list_of_strings[kk] );
          
    printf( "\n" );
    printf( "Response to \"%s\" :\n  " , list_of_strings[kk] );
    printf( "%s\n" , 
            strlen(item) ? item : "No such substring could be found" );
    printf( "Length of Returned Substring :\n  %d\n" ,
            strlen(item) );
    
    // freed by the caller
    free(item);
  } // for kk
}