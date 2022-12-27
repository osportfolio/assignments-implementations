#include "updaters_in_C.h"

#include <stdlib.h>

void
update__with_pointers_in_C
(
  int * i_1st ,
  int * i_2nd
)
{
  int
    i_1st_original = *i_1st ,
    i_2nd_original = *i_2nd ;
    
  *i_1st 
    = i_1st_original + i_2nd_original;
  
  int i_difference 
    = i_1st_original - i_2nd_original;
    
  if ( i_difference > 0 )
    *i_2nd = i_difference;
  else
    *i_2nd = - i_difference;
  
  return;  
}

void
update__with_ternary_operator_in_C
(
  int * i_1st ,
  int * i_2nd
)
{
  int
    i_1st_original = *i_1st ,
    i_2nd_original = *i_2nd ;
    
  *i_1st 
    = i_1st_original + i_2nd_original;
  
  int i_difference 
    = i_1st_original - i_2nd_original;
    
  *i_2nd 
    = ( i_difference > 0 )
        ? (i_difference) : (- i_difference);
        
  return;  
}

void
update__with_abs_in_C
(
  int * i_1st ,
  int * i_2nd
)
{
  int
    i_1st_original = *i_1st ,
    i_2nd_original = *i_2nd ;
    
  *i_1st 
    = i_1st_original + i_2nd_original;
  
  int i_difference 
    = i_1st_original - i_2nd_original;
    
  *i_2nd = abs( i_difference );
  
  return;  
}


/*
 * Intentional wrong implementation
 * to observe some failures in tests.
 * */
void
update__doomed_to_fail_in_C
(
  int * i_1st ,
  int * i_2nd
)
{
  *i_1st = *i_1st + *i_2nd;
  *i_2nd = *i_1st - *i_2nd;
  
  return;
}
