/*
This code with the function 'solution' given
a string input computes the length of the shortest 
substring that only accommodates both small and capital
versions of all the letters included in the indicated
substring.
*/

/*
  Worked on this code on
                        Dec 11-12, 2022 / Sun-Mon
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initial capacity for StringArrayContainer
#define CAPACITY_INITIAL 2

/*
 * Structure to hold an array strings, appending
 * to the array is allowed, removal operation not
 * implemented. The capacity is doubled as it becomes
 * fully utilized.
 * */
typedef
struct StringArrayContainer
{
  char ** content_ptr_ptr;
  int     capacity;
  int     length;
}
StringArrayContainer;

StringArrayContainer *
StringArray_initialize
()
{
  typedef StringArrayContainer  local_type;
  local_type * container_ptr
    = (local_type *) calloc( 1 , sizeof(local_type) );
    
  container_ptr->capacity
    = CAPACITY_INITIAL;
  container_ptr->content_ptr_ptr
    = (char **) calloc( CAPACITY_INITIAL , sizeof(char *) );
  container_ptr->length
    = 0;
    
  return container_ptr;
}

void
StringArray_destroy
(
  StringArrayContainer * container_ptr
)
{
  int kk;
  
  for ( kk = 0 ; kk < container_ptr->length ; ++kk )
    free( (container_ptr->content_ptr_ptr)[kk] );
  
  free( container_ptr->content_ptr_ptr );
  free( container_ptr );
}

/*
 * Appending function, capacity is doubled if
 * it needs to be. calloc and memcpy used instead
 * of realloc, which does not produce the expected
 * result.
 * */
void
StringArray_add_string
(
  StringArrayContainer *  container_ptr ,
  const char *            additional_string
)
{
  if ( container_ptr->length >= container_ptr->capacity )
    container_ptr->capacity *= 2;
  
  char ** ptr_ptr_other
    = calloc( container_ptr->capacity , sizeof( char * ) );
  memcpy( 
    ptr_ptr_other , container_ptr->content_ptr_ptr , 
    container_ptr->length * sizeof( char * ) );
  container_ptr->content_ptr_ptr
    = ptr_ptr_other;
    
  // Not forgetting '1 +' for NULL
  (container_ptr->content_ptr_ptr)[container_ptr->length]
    = (char *) calloc( 1 + strlen(additional_string) , sizeof(char) );
  strcpy
    ( 
      (container_ptr->content_ptr_ptr)[container_ptr->length] ,
      additional_string
    );
    
  ++(container_ptr->length);
}

/*
 * Linear time search inside the array for a given
 * string. Returns a boolean.
 * */
int
StringArray_is_given_string_present
(
  StringArrayContainer *  container_ptr ,
  const char *            string_given
)
{
  int flag_present = 0;
  int kk;
  for ( kk = 0 ; kk < container_ptr->length ; ++kk )
  {
    if ( ! strcmp
             ( 
               string_given ,
               (container_ptr->content_ptr_ptr)[kk]
             ) 
       )
    {
      flag_present = 1;
      break;
    }
  }
  
  return flag_present;
}

int
StringArray_get_length
(
  StringArrayContainer *  container_ptr
)
{
  return container_ptr->length;
}

char *
StringArray_get_string_at_index
(
  StringArrayContainer *  container_ptr ,
  int                     index
)
{
  char * ptr = NULL;
  if 
    (
      ( index < container_ptr->length )
      &&
      ( index >= 0 )
    )
    ptr = (container_ptr->content_ptr_ptr) [index];
  
  return ptr;
}

void
StringArray_print_information_and_content
(
  StringArrayContainer *  container_ptr
)
{
  printf( "\n" );
  printf( "Report on StringArray Object\n\n" );
  printf( "  Capacity :\n    %d\n" , container_ptr->capacity );
  printf( "  Length :\n    %d\n"   , container_ptr->length );
  printf( "  Contents :\n" );
  
  int kk;
  for ( kk = 0 ; kk < container_ptr->length ; ++kk )
    printf( "    %4d -> %s\n" , 
            kk , (container_ptr->content_ptr_ptr)[kk]
    );
  printf( "\n" );
}

void
StringArray_test
()
{
  StringArrayContainer * container_ptr
    = StringArray_initialize();
    
  printf( "\nObject Created\n" );
  StringArray_print_information_and_content
    (container_ptr);
    
  StringArray_add_string
    ( container_ptr , "This is " );
  StringArray_add_string
    ( container_ptr , "a beautiful" );
  StringArray_add_string
    ( container_ptr , "day! " );
  StringArray_print_information_and_content
    (container_ptr);
  
  StringArray_add_string
    ( container_ptr , "Isn't it? " );
  StringArray_add_string
    ( container_ptr , "Don't you " );
  StringArray_add_string
    ( container_ptr , "agree?" );
  StringArray_print_information_and_content
    (container_ptr);
  
  StringArray_add_string
    ( container_ptr , "Let's go " );
  StringArray_add_string
    ( container_ptr , "out for " );
  StringArray_add_string
    ( container_ptr , "a stroll." );
  StringArray_print_information_and_content
    (container_ptr);
    
  char string_temp[32];
  sprintf( string_temp , "da" );
  printf 
    ( 
      "Is \"%s\" present in container?\n  %s\n" ,
      string_temp ,
      StringArray_is_given_string_present(container_ptr, string_temp) 
        ? "YES" : "NO"
    );
    
  sprintf( string_temp , "day! " );
  printf 
    ( 
      "Is \"%s\" present in container?\n  %s\n" ,
      string_temp ,
      StringArray_is_given_string_present(container_ptr, string_temp) 
        ? "YES" : "NO"
    );
    
  StringArray_destroy
    (container_ptr);
    
  printf( "\nObject Destroyed\n" );
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
    printf( "Response to \"%s\" :\n  " , list_of_strings[kk] );
    printf( "%s\n" , 
            strlen(item) ? item : "No such substring could be found" );
    
    // freed by the caller
    free(item);
  } // for kk
}

int
main (void)
{
//   StringArray_test();
//   test_on_range_of_characters();
  test_of_solution();
  
  return 0;
}