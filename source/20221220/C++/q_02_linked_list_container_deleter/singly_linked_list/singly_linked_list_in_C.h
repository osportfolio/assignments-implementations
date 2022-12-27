/*
 * Structure definition and function prototypes for
 * singly linked list implementation.
 * */

/*
 * Worked on this code on
 *   Dec 25, 2022 / Sun
 * */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef
struct SLL_Node 
{
  int 
    data;
    
  struct SLL_Node *  
    next;
} SLL_Node;
  
SLL_Node **
SinglyLinkedList_construct
();

void
SinglyLinkedList_destruct
(
  SLL_Node **  ptr_to_ptr
);

int
SinglyLinkedList_isEmpty
(
  SLL_Node **  ptr_to_ptr
);

unsigned int
SinglyLinkedList_size
(
  SLL_Node **  ptr_to_ptr
);

SLL_Node *
SinglyLinkedList_front
(
  SLL_Node **   ptr_to_ptr
);

SLL_Node *
SinglyLinkedList_back
(
  SLL_Node **   ptr_to_ptr
);

void
SinglyLinkedList_insertAtIndex
(
  SLL_Node **   ptr_to_ptr ,
  unsigned int  index ,
  int           data_new
);

void
SinglyLinkedList_push_back
(
  SLL_Node **   ptr_to_ptr ,
  int           data_new
);

void
SinglyLinkedList_push_front
(
  SLL_Node **   ptr_to_ptr ,
  int           data_new
);

/*
 * Returned pointer should be freed by the
 * caller.
 * */
SLL_Node *
SinglyLinkedList_removeAtIndex
(
  SLL_Node **   ptr_to_ptr ,
  unsigned int  index
);

/*
 * Returned pointer should be freed by the
 * caller.
 * */
SLL_Node *
SinglyLinkedList_pop_back
(
  SLL_Node **   ptr_to_ptr
);

/*
 * Returned pointer should be freed by the
 * caller.
 * */
SLL_Node *
SinglyLinkedList_pop_front
(
  SLL_Node **   ptr_to_ptr
);

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
);

SLL_Node **
SinglyLinkedList_copy
(
  SLL_Node **   ptr_to_ptr
);

#ifdef __cplusplus
}
#endif