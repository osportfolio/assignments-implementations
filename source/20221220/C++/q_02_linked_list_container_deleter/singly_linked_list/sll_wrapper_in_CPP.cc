/*
 * 'print' member function implementation.
 * */

/*
 * Worked on this code on
 *   Dec 25, 2022 / Sun
 * */

#include "sll_wrapper_in_CPP.hh"

#include <iostream>

namespace os_wrappers
{
  
void 
SinglyLinkedListWrapper
  ::print()
{
  using namespace std;
  
  for ( 
        unsigned int 
            kk = 0 ;
            kk < size() ;
          ++kk
      )
  {
    int temp;
    getAtIndex( kk , &temp );
    cout << "  " << temp;
  }
  cout << endl;
} // function - print
  
} // namespace os_wrappers