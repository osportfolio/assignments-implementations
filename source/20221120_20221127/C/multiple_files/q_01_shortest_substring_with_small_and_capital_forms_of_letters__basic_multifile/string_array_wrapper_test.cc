/*
 * Worked on this code on
 *                       Dec 13, 2022 / Tue
 * */

#include "wrappers.hh"

#include <iostream>

int
main (void)
{
  using namespace os_wrappers;
  
  StringArrayWrapper::test();
  
  /*
   * Each of the cases below produces
   * compilation error due to deleted copy
   * constructor and copy assignment operator.
   * */
  
  /*
  StringArrayWrapper  obj;
  StringArrayWrapper  obj_other (obj);
  */
  
  /*
  StringArrayWrapper  obj;
  StringArrayWrapper  obj_other ( std::move( obj ) );
  */
  
  /*
  StringArrayWrapper  obj , obj_other;
  obj = obj_other;
  */
  
  /*
  StringArrayWrapper  obj , obj_other;
  obj = std::move( obj_other );
  */
  
  return 0;
}