/*
 * Function bodies for the singly linked list
 * implementation.
 * */

/*
 * Worked on this code on
 *   Dec 25, 2022 / Sun
 * */

#include "singly_linked_list_in_C.h"

#include <stdlib.h>

SLL_Node **
SinglyLinkedList_construct
()
{
  SLL_Node **
    ptr_to_ptr = (SLL_Node **) calloc( 1 , sizeof(SLL_Node *) );
    
  *ptr_to_ptr = NULL;
    
  return ptr_to_ptr;
}

void
SinglyLinkedList_destruct
(
  SLL_Node **  ptr_to_ptr
)
{
  SLL_Node * ptr_current
    = *ptr_to_ptr;
  while ( ptr_current != NULL )
  {
    SLL_Node * ptr_next
      = ptr_current->next;
    free( ptr_current );
    ptr_current = ptr_next;
  }
  *ptr_to_ptr = NULL;
  free( ptr_to_ptr );
}

int
SinglyLinkedList_isEmpty
(
  SLL_Node **  ptr_to_ptr
)
{
  return ( *ptr_to_ptr == NULL );
}

unsigned int
SinglyLinkedList_size
(
  SLL_Node **  ptr_to_ptr
)
{
  unsigned int  size = 0;
  
  SLL_Node * ptr_current 
    = *ptr_to_ptr;
    
  while ( ptr_current != NULL )
  {
    ptr_current = ptr_current->next;
    ++size;
  }
  
  return size;
}

SLL_Node *
SinglyLinkedList_front
(
  SLL_Node **   ptr_to_ptr
)
{
  return *ptr_to_ptr;
}

SLL_Node *
SinglyLinkedList_back
(
  SLL_Node **   ptr_to_ptr
)
{
  if ( *ptr_to_ptr == NULL )
    return NULL;
  
  SLL_Node * ptr_current 
    = *ptr_to_ptr;
    
  while ( ptr_current->next != NULL )
    ptr_current = ptr_current->next;
  
  return ptr_current;
}

/*
 * Indices begin at 0 (zero).
 * Inserting at the index that is equal to
 * the size is allowed; is equivalent to the
 * push operation.
 * */
void
SinglyLinkedList_insertAtIndex
(
  SLL_Node **   ptr_to_ptr ,
  unsigned int  index ,
  int           data_new
)
{
  /*
   * Out of bounds, designed not to insert.
   * */
  if ( index > SinglyLinkedList_size( ptr_to_ptr ) )
    return;
  if ( index < 0 )
    return;
  
  /*
   * Allocate memory, set data.
   * */
  SLL_Node *  ptr_new 
    = (SLL_Node *) calloc( 1 , sizeof(SLL_Node) );
  ptr_new->data = data_new;
  
  /*
   * The first container to be inserted to the list
   * is the recently created one.
   * */
  if ( 0 == SinglyLinkedList_size( ptr_to_ptr ) )
  {
    *ptr_to_ptr   = ptr_new;
    ptr_new->next = NULL;
    return;
  }
  
  /*
   * The same as pushing back.
   * */
  if ( index == SinglyLinkedList_size( ptr_to_ptr ) )
  {
    SLL_Node * ptr_back 
      = SinglyLinkedList_back( ptr_to_ptr );
    ptr_back->next = ptr_new;
    ptr_new->next  = NULL;
    return;
  }
  
  /*
   * The same as unshift (push_front).
   * */
  if ( index == 0 )
  {
    SLL_Node * ptr_temp = *ptr_to_ptr;
    *ptr_to_ptr   = ptr_new;
    ptr_new->next = ptr_temp;
    return;
  }
  
  /*
   * And the rest.
   * */
  unsigned int cnt = 0;
  SLL_Node * ptr_current 
    = *ptr_to_ptr;
  while ( 1 )
  {
    SLL_Node * ptr_next 
      = ptr_current->next;
    if ( ++cnt == index )
    {
      ptr_current->next 
        = ptr_new;
      ptr_new->next
        = ptr_next;
      return;
    }
    ptr_current = ptr_next;
  }
} // function - SinglyLinkedList_insertAtIndex

void
SinglyLinkedList_push_back
(
  SLL_Node **   ptr_to_ptr ,
  int           data_new
)
{
  SinglyLinkedList_insertAtIndex
  (
    ptr_to_ptr ,
    SinglyLinkedList_size( ptr_to_ptr ) ,
    data_new
  );
  return;
}

void
SinglyLinkedList_push_front
(
  SLL_Node **   ptr_to_ptr ,
  int           data_new
)
{
  SinglyLinkedList_insertAtIndex
  (
    ptr_to_ptr ,
    0 ,
    data_new
  );
  return;
}

/*
 * Returned pointer should be freed by the
 * caller.
 * */
SLL_Node *
SinglyLinkedList_removeAtIndex
(
  SLL_Node **   ptr_to_ptr ,
  unsigned int  index
)
{
  /*
   * Out of bounds.
   * */
  if ( index >= SinglyLinkedList_size( ptr_to_ptr ) )
    return NULL;
  if ( index <  0 )
    return NULL;
  
  /*
   * List is empty.
   * */
  if ( 0 == SinglyLinkedList_size( ptr_to_ptr ) )
    return NULL;
  
  /*
   * Equivalent to shift (pop_front).
   * */
  if ( index == 0 )
  {
    SLL_Node * ptr_temp
      = *ptr_to_ptr;
      
    *ptr_to_ptr = ptr_temp->next;
      
    ptr_temp->next = NULL;
    return ptr_temp;
  }
  
  /*
   * And the rest.
   * */
  unsigned int cnt = 0;
  SLL_Node * ptr_previous 
    = *ptr_to_ptr;
  while ( 1 )
  {
    SLL_Node * ptr_current 
      = ptr_previous->next;
    if ( ++cnt == index )
    {
      ptr_previous->next 
        = ptr_current->next;
      ptr_current->next
        = NULL;
      return ptr_current;
    }
    ptr_previous = ptr_current;
  }
} // function - SinglyLinkedList_removeAtIndex

/*
 * Returned pointer should be freed by the
 * caller.
 * */
SLL_Node *
SinglyLinkedList_pop_back
(
  SLL_Node **   ptr_to_ptr
)
{
  return
    SinglyLinkedList_removeAtIndex
      (
        ptr_to_ptr ,
        -1 + SinglyLinkedList_size( ptr_to_ptr )
      );
}

/*
 * Returned pointer should be freed by the
 * caller.
 * */
SLL_Node *
SinglyLinkedList_pop_front
(
  SLL_Node **   ptr_to_ptr
)
{
  return
    SinglyLinkedList_removeAtIndex
      (
        ptr_to_ptr ,
        0
      );
}

/*
 * Returns
 *   0 - if no problem occurs
 *  -1 - if index is out of bounds
 *  -2 - if list is empty
 * */
int
SinglyLinkedList_getAtIndex
(
  SLL_Node **   ptr_to_ptr ,
  unsigned int  index ,
  int *         number
)
{
  /*
   * Empty.
   * */
  if ( SinglyLinkedList_isEmpty( ptr_to_ptr ) )
    return -2;
  /*
   * Out of bounds.
   * */
  if ( index >= SinglyLinkedList_size( ptr_to_ptr ) )
    return -1;
  if ( index <  0 )
    return -1;
  
  
  unsigned int cnt = 0;
  SLL_Node *  ptr_temp = *ptr_to_ptr;
  while ( 1 )
  {
    if ( cnt == index )
    {
      *number = ptr_temp->data;
      return 0;
    }
    
    ++cnt;
    ptr_temp = ptr_temp->next;
  }
}

SLL_Node **
SinglyLinkedList_copy
(
  SLL_Node **   ptr_to_ptr
)
{
  SLL_Node **
    ptr_to_ptr__new
      = SinglyLinkedList_construct();
      
  unsigned int kk;
  for ( kk = 0 ; 
        kk < SinglyLinkedList_size( ptr_to_ptr ) ;
      ++kk )
  {
    int number_temp;
    SinglyLinkedList_getAtIndex
      (
        ptr_to_ptr ,
        kk ,
        & number_temp
      );
    SinglyLinkedList_push_back
      (
        ptr_to_ptr__new ,
        number_temp
      );
  }
  
  return ptr_to_ptr__new;
}