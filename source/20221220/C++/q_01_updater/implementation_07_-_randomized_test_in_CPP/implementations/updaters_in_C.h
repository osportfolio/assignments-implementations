#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void
update__with_pointers_in_C
(
  int * i_1st ,
  int * i_2nd
);

void
update__with_ternary_operator_in_C
(
  int * i_1st ,
  int * i_2nd
);

void
update__with_abs_in_C
(
  int * i_1st ,
  int * i_2nd
);

/*
 * Intentional wrong implementation
 * to observe some failures in tests.
 * */
void
update__doomed_to_fail_in_C
(
  int * i_1st ,
  int * i_2nd
);

#ifdef __cplusplus
}
#endif