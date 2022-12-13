/*
 * Static test member function for the wrapper class
 * */

/*
 * Worked on this code on
 *                       Dec 13, 2022 / Tue
 * */

#include "wrappers.hh"

namespace os_wrappers
{
  
void
StringArrayWrapper::test
()
{
  StringArrayWrapper  obj;
    
  printf( "\nObject Created\n" );
  obj.print_information_and_content
    ();
    
  obj.add_string
    ( "This is " );
  obj.add_string
    ( "a beautiful" );
  obj.add_string
    ( "day! " );
  obj.print_information_and_content
    ();
  
  obj.add_string
    ( "Isn't it? " );
  obj.add_string
    ( "Don't you " );
  obj.add_string
    ( "agree?" );
  obj.print_information_and_content
    ();
  
  obj.add_string
    ( "Let's go " );
  obj.add_string
    ( "out for " );
  obj.add_string
    ( "a stroll." );
  obj.print_information_and_content
    ();
    
  char string_temp[32];
  sprintf( string_temp , "da" );
  printf 
    ( 
      "Is \"%s\" present in container?\n  %s\n" ,
      string_temp ,
      obj.is_given_string_present( string_temp ) 
        ? "YES" : "NO"
    );
    
  sprintf( string_temp , "day! " );
  printf 
    ( 
      "Is \"%s\" present in container?\n  %s\n" ,
      string_temp ,
      obj.is_given_string_present( string_temp ) 
        ? "YES" : "NO"
    );
    
  printf( "\nObject Destroyed\n" );
}
  
} // namespace os_wrappers