#pragma once

#ifdef __cplusplus
extern "C" {
#endif

char *
range_char
(
  char  c_start ,
  char  c_stop
);

int
is_character_present_in_sequence
(
  const char   ch ,
  const char * sequence_ptr ,
  const int    length
);

int
index_of_first_occurence_of_character_in_sequence
(
  const char   ch ,
  const char * sequence_ptr ,
  const int    length
);

void
test_on_range_of_characters
();

#ifdef __cplusplus
}
#endif