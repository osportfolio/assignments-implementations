#!/usr/bin/tclsh

; # The function 'solution' tries to generate
  # a palindrome out of the string 'S' given
  # as an input argument, replacing the '?'
  # characters by what is required, and returns
  # the palindrome or the string 'NO', the
  # latter being the error identifier in case
  # no palindrome construction is possible.

; # Worked on this code on
  #                       Dec 11, 2022 / Sun

proc solution {S} {
  set s_list [ split $S {} ]
  set sz     [ llength $s_list ]
  # Generate a list of characters from the
  # given string, and record the length.
  
  # Below, the variables 'index_right',
  # 'index_left', and 'n_max' have to be
  # calculated separately for an odd and
  # an even number of characters within
  # the original string. 
  #  
  # 'n_max' is the number of characters
  # to the right and left of the character
  # in the middle position (if there are an
  # odd number of characters) or in the 
  # position between the characters in the
  # middle (if there are even number of
  # characters).
  #  
  # 'index_right' and 'index_left' are the
  # starting values of the indices calculated
  # through integer offsets from the middle 
  # position (as explained above for the number 
  # of characters being odd or even) for the
  # characters to the right and to the left,
  # respectively, of the indicated position.
  
  if { $sz % 2 == 1 } {
    set  index_middle  [ expr ($sz - 1) / 2 ]
    if { [ lindex $s_list $index_middle ] == "?" } {
      lset s_list $index_middle "a"
    }
    # For a string with an odd number of
    # characters, the character in the middle
    # has to be set, if it has not already been
    # set.
    
    set index_right [ expr  $index_middle + 1 ]
    set index_left  [ expr  $index_middle - 1 ]
    set n_max [ expr  ($sz - 1) / 2 ]
  } else {
    set index_right [ expr  $sz / 2 ]
    set index_left  [ expr  $sz / 2 - 1 ]
    set n_max [ expr  $sz / 2 ]
  }
  
  for { set kk 0 } { $kk < $n_max } { incr kk } {
    set index_right_c [ expr  $index_right + $kk ]
    set index_left_c  [ expr  $index_left  - $kk ]
    # Calculate the current indices through
    # the update 'kk' upon the initial values
    # for the indices of the entries to the
    # right and left of the entry in the middle.
    # The odd and even cases have already been
    # taken care of, so the codes above and
    # below within the scope of this for loop
    # apply to both cases.
    
    if { ( [ lindex  $s_list  $index_right_c ] != "?" ) && 
         ( [ lindex  $s_list  $index_left_c ]  != "?" ) } {
      if { [ lindex  $s_list  $index_right_c ] !=
           [ lindex  $s_list  $index_left_c ] } {
        return "NO"
      }
    }
    # If the entries at the same distance to the 
    # right and left of the middle position are 
    # already set and are not the same, then
    # the string cannot be a palindrome.
    
    if { ( [ lindex  $s_list  $index_right_c ] == "?" ) && 
         ( [ lindex  $s_list  $index_left_c ]  == "?" ) } {
      lset s_list $index_right_c "a"
      lset s_list $index_left_c  "a"
    }
    # If the entries of interest to the right and
    # left have not already been set, then set them
    # as the same character.
    
    if { ( [ lindex  $s_list  $index_right_c ] != "?" ) && 
         ( [ lindex  $s_list  $index_left_c ]  == "?" ) } {
      lset s_list $index_left_c   [ lindex  $s_list  $index_right_c ]
    }
    # If the entry of interest to the right has
    # been set but that to the left not so, then
    # set the entry to the left to continue
    # in the path to obtaining a palindrome at
    # the end.
    
    if { ( [ lindex  $s_list  $index_right_c ] == "?" ) && 
         ( [ lindex  $s_list  $index_left_c ]  != "?" ) } {
      lset s_list $index_right_c  [ lindex  $s_list  $index_left_c ]
    }
    # If the entry of interest to the left has
    # been set but that to the right not so, then
    # set the entry to the right to continue
    # in the path to obtaining a palindrome at
    # the end.
  } ; # for i
  
  return [ join $s_list "" ]
  # Join the resulting characters into a string,
  # and return this string.
}

set list_of_strings { 
  "?"  "ba?"  "ab"  "a?b"  "bac?b"  "?acab" "?a?b" }

puts ""
for { set i 0 } { $i < [llength $list_of_strings] } { incr i } {
  set item [ lindex $list_of_strings $i ]
  set str "Response to \"%s\" :\n  %s"
  puts [ format  $str  $item  [ solution $item ] ]
}
