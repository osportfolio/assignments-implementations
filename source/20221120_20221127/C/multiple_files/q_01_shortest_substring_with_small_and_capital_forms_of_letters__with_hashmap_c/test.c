/*
The function 'solution' given
a string input computes the length of the shortest 
substring that only accommodates both small and capital
versions of all the letters included in the indicated
substring.
*/

/*
  Worked on this code on
                        Dec 16, 2022 / Fri
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

typedef
struct CharToCharContainer
{
  char key;
  char value;
}
CharToCharContainer;

int 
CharToChar_compare
(const void *a, const void *b, void *udata) 
{
  const CharToCharContainer *ia = a;
  const CharToCharContainer *ib = b;
  return 
    (ia->key > ib->key) ? 1 : 
      ( (ia->key < ib->key) ? -1 : 0 );
}

uint64_t 
CharToChar_hash
(const void *item, uint64_t seed0, uint64_t seed1) 
{
  const CharToCharContainer *current = item;
  return hashmap_sip(&(current->key), 1 * sizeof(char), seed0, seed1);
}

/*
 * The block of memory pointed to by the returned
 * pointer must be freed by the caller.
 * */
char *
range_char
(
  char  c_start ,
  char  c_stop
)
{
  // Size 'sz' accounts for the NULL character as well.
  int sz = c_stop - c_start + 2;
  
  // Allocates memory and fills with bitwise zeros.
  char * sequence_ptr
    = (char *) calloc( sz , sizeof(char) );
  
  int kk;
  for ( kk = c_start ; kk <= c_stop ; ++kk )
    sequence_ptr[kk-c_start] = kk;
    
  return  sequence_ptr;
}

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
    
  int kk;
  
  // Ranges of small and capital letters
  // Pointers to be freed in this function.
  char * characters_small
    = range_char( 'a' , 'z' );
  char * characters_capital
    = range_char( 'A' , 'Z' );
    
  struct hashmap *mp_small_ptr
    = hashmap_new( sizeof(CharToCharContainer), 0, 0, 0, 
                   CharToChar_hash, 
                   CharToChar_compare, 
                   NULL, NULL);
  struct hashmap *mp_cap_ptr
    = hashmap_new( sizeof(CharToCharContainer), 0, 0, 0, 
                   CharToChar_hash, 
                   CharToChar_compare, 
                   NULL, NULL);
  
  for ( kk = 0 ; kk < strlen( characters_small ) ; ++kk )
  {
    hashmap_set(
      mp_small_ptr ,
      &(CharToCharContainer)
        { .key   = characters_small  [kk] ,
          .value = characters_capital[kk] } );
    hashmap_set(
      mp_cap_ptr ,
      &(CharToCharContainer)
        { .key   = characters_capital[kk] ,
          .value = characters_small  [kk] } );
  } // for kk
  
  int s_length , s_index_start;
  for ( s_length = 2 ; s_length < 1 + strlen(string_given) ; ++s_length )
  {
    for ( s_index_start = 0 ; 
          s_index_start < strlen(string_given) - s_length + 1 ;
        ++s_index_start )
    {
      struct hashmap *temp_set_ptr
        = hashmap_new( sizeof(CharToCharContainer), 0, 0, 0, 
                       CharToChar_hash, 
                       CharToChar_compare, 
                       NULL, NULL);
      
      for ( kk = s_index_start ;
            kk < s_index_start + s_length ;
          ++kk
      )
      {
        hashmap_set(
          temp_set_ptr ,
          &(CharToCharContainer)
            { .key   = string_given[kk] ,
              .value = 0 } );
      } // for kk
      
      int
      flag_found = 1;
      
      size_t  iter = 0;
      void *  item_ptr_raw;
      while ( hashmap_iter(temp_set_ptr, &iter, &item_ptr_raw) ) 
      {
        const CharToCharContainer * item_ptr = item_ptr_raw;
        
        CharToCharContainer 
          * flag_is_item_in_characters_small   = NULL ,
          * flag_is_item_in_characters_capital = NULL ,
          * flag_is_corresponding_capital_in_the_substring = NULL ,
          * flag_is_corresponding_small_in_the_substring   = NULL ;
          
        flag_is_item_in_characters_small
          = hashmap_get( mp_small_ptr , item_ptr );
        flag_is_item_in_characters_capital
          = hashmap_get( mp_cap_ptr   , item_ptr );
          
        if ( flag_is_item_in_characters_small )
        {
          CharToCharContainer * temp_ptr
            = flag_is_item_in_characters_small;
          flag_is_corresponding_capital_in_the_substring
            = hashmap_get( temp_set_ptr , 
                           &(CharToCharContainer)
                             { .key = temp_ptr->value }
            );
        }
        
        if ( flag_is_item_in_characters_capital )
        {
          CharToCharContainer * temp_ptr
            = flag_is_item_in_characters_capital;
          flag_is_corresponding_small_in_the_substring
            = hashmap_get( temp_set_ptr , 
                           &(CharToCharContainer)
                             { .key = temp_ptr->value }
            );
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
      } // while
      
      // Freeing memory.  
      hashmap_free(temp_set_ptr);
      
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
      } // if flag_found
    } // for s_index_start
  } // for s_length
  /*
   * Freeing memory.
   * */
  free( characters_small );
  free( characters_capital );
  
  hashmap_free(mp_small_ptr);
  hashmap_free(mp_cap_ptr);
  
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
     
//   printf( "\n" );
        
  int kk;
  for ( kk = 0 ; kk < sizeof(list_of_strings) / sizeof(char *) ; ++kk )
  {
    char * item
      = solution_shortest_substring_with_small_and_capital_forms_of_letters
          ( list_of_strings[kk] );
    printf( "\nResponse to \"%s\" :\n  " , list_of_strings[kk] );
    printf( "%s\n" , 
            strlen(item) ? item : "No such substring could be found" );
    printf( "Length of string found :\n  %d\n" , strlen(item) );
    
    // freed by the caller
    free(item);
  } // for kk
}

int
main (void)
{
  test_of_solution();
  
  return 0;
}