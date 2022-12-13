#include "string_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initial capacity for StringArrayContainer
#define CAPACITY_INITIAL 2

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
    
  // printf( "StringArray object created.\n" );
    
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
  
  // printf( "StringArray object destroyed.\n" );
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
