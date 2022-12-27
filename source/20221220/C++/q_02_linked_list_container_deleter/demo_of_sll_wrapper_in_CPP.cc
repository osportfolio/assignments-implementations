/*
 * Several tests concerning the features of
 * the singly linked list implementation.
 * */

/*
 * Worked on this code on
 *   Dec 25, 2022 / Sun
 * */

#include "sll_wrapper_in_CPP.hh"

#include <iostream>

int
main (void)
{
  using namespace std;
  using namespace os_wrappers;
  
  int array[] = { -4 , 5 , 2 , 7 };
  unsigned int size    
    = sizeof(array) / sizeof(int);
  
  unsigned int  kk , ll;
  unsigned int  index_fixed;
  
  SinglyLinkedListWrapper  obj;
  
  cout 
    << endl 
    << "Push Back Operations in Succession :" << endl;
  for ( kk = 0 ; kk < size ; ++kk )
  {
    obj.push_back( array[kk] );
    obj.print();
  }

  for ( kk = 0 ; kk < size ; ++kk )
  {
    SinglyLinkedListWrapper obj_other( obj );
    
    cout
      << endl
      << "Copied the Original List with the Copy Constructor :" << endl;
    obj_other.print();
    
    index_fixed = kk;
    cout 
      << "Now Removing Element Always at Index " << index_fixed 
      << " for " << size << " times :" << endl;
    for ( ll = 0 ; ll < size ; ++ll )
    {
      obj_other.removeAtIndex_with_free( index_fixed );
      obj_other.print();
    } // for ll
    
    cout
      << "The Original List Remains Unchanged :" << endl;
    obj.print();
  } // for kk
  
  for ( kk = 0 ; kk < size ; ++kk )
  {
    SinglyLinkedListWrapper obj_other;
    obj_other = obj;
    
    cout
      << endl
      << "Copied the Original List with the Copy Assignment Operator :" << endl;
    obj_other.print();
    
    int number_fixed = 99;
    cout 
      << "Now Inserting Element Always at Index " << kk 
      << " for " << size << " times :" << endl;
    for ( ll = 0 ; ll < size ; ++ll )
    {
      obj_other.insertAtIndex( kk , number_fixed );
      obj_other.print();
    } // for ll
    
    cout
      << "The Original List Remains Unchanged :" << endl;
    obj.print();
  } // for kk
  
  for ( kk = 6 ; kk > 6 - size ; --kk )
  {
    SinglyLinkedListWrapper obj_other;
    obj_other = obj;
    
    cout
      << endl
      << "Copied the Original List with the Copy Assignment Operator :" << endl;
    obj_other.print();
    
    int number = 99 - kk;
    cout 
      << "Now Inserting Element " << number
      << " at Index " << kk 
      << " (Supports Push Back through Insert at Index " 
      << obj.size() << ") :" << endl;
    obj_other.insertAtIndex( kk , number );
    obj_other.print();
    
    cout
      << "The Original List Remains Unchanged :" << endl;
    obj.print();
  } // for kk
  
  return 0;
}