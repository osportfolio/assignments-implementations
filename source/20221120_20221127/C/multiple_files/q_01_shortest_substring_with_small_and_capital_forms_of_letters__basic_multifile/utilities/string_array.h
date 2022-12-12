#pragma once

#ifdef __cplusplus
extern "C" {
#endif

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
();

void
StringArray_destroy
(
  StringArrayContainer * container_ptr
);

void
StringArray_add_string
(
  StringArrayContainer *  container_ptr ,
  const char *            additional_string
);

int
StringArray_is_given_string_present
(
  StringArrayContainer *  container_ptr ,
  const char *            string_given
);

int
StringArray_get_length
(
  StringArrayContainer *  container_ptr
);

char *
StringArray_get_string_at_index
(
  StringArrayContainer *  container_ptr ,
  int                     index
);

void
StringArray_print_information_and_content
(
  StringArrayContainer *  container_ptr
);

void
StringArray_test
();

#ifdef __cplusplus
}
#endif