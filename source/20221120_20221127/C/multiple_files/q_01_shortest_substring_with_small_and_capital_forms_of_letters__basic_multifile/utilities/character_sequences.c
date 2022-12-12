#include "character_sequences.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*
 * Returns true if character is present in
 * sequence, which may not always be NULL
 * terminated, so the length of the sequence
 * should also be provided as input.
 * */
int
is_character_present_in_sequence
(
  const char   ch ,
  const char * sequence_ptr ,
  const int    length
)
{
  int kk , flag_present = 0;
  
  for ( kk = 0 ; kk < length ; ++kk )
  {
    if ( sequence_ptr[kk] == ch )
    {
      flag_present = 1;
      break;
    }
  }
  
  return flag_present;
}

int
index_of_first_occurence_of_character_in_sequence
(
  const char   ch ,
  const char * sequence_ptr ,
  const int    length
)
{
  int kk , index = -1;
  
  for ( kk = 0 ; kk < length ; ++kk )
  {
    if ( sequence_ptr[kk] == ch )
      return kk;
  }
  
  return index;
}

void
test_on_range_of_characters
()
{
  char * characters_small
    = range_char( 'a' , 'r' );
  char * characters_capital
    = range_char( 'A' , 'R' );
    
  printf( "\n" );
  printf( "Range of Small Characters :\n  %s\n" , 
          characters_small );
  printf( "Range of Capital Characters :\n  %s\n" , 
          characters_capital );
  
  char string_temp[8] , string_other[8];
  int kk;
  for ( kk = 0 ; kk < sizeof(string_temp)/sizeof(char) ; ++kk )
    string_temp[kk] = string_other[kk] = 0;
  
  char ch = 'z';
  string_temp[0] = ch;
  printf( "Is \"%s\" in the range?\n  %s\n" , 
          string_temp , 
          is_character_present_in_sequence
            (ch, characters_small, strlen(characters_small)) 
          ? "YES" : "NO"
        );
  
  ch = 'k';
  string_temp[0] = ch;
  printf( "Is \"%s\" in the range?\n  %s\n" , 
          string_temp , 
          is_character_present_in_sequence
            (ch, characters_small, strlen(characters_small)) 
          ? "YES" : "NO"
        );
  
  int index 
    = index_of_first_occurence_of_character_in_sequence
        (ch, characters_small, strlen(characters_small));
  printf( "What is the index of \"%s\" in the range (starting with 0)?\n  %d\n" , 
          string_temp , 
          index
        );
  
  string_other[0]
    = characters_capital[index];
  printf( "What is the capital form of \"%s\"?\n  \"%s\"\n" , 
          string_temp , 
          string_other
        );
}
