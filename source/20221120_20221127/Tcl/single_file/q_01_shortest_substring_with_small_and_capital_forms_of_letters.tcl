#!/usr/bin/tclsh

# This script with the function 'solution' given
# a string input computes the length of the shortest 
# substring that only accommodates both small and capital
# versions of all the letters included in the indicated
# substring.

#   Worked on this code on 
#                         Dec 18, 2022 / Sun


# Inspired by the answer at
#   https://www.allinterview.com/showanswers/123965/how-increment-a-character-for-example-i-give-a-and-i-should-get-b.html
proc range_char {c_start  c_stop} {
  #puts $c_start
  #puts $c_stop
  
  set char_list {}
  set c_start_index [scan $c_start %c]
  set c_stop_index  [scan $c_stop  %c]
  
  for { set kk 0 } \
      { $kk < [expr 1 + $c_stop_index - $c_start_index] } \
      { incr kk } {
    lappend char_list \
            [ format %c [expr {$c_start_index + $kk}] ]
    #puts [ llength $char_list ]
  } ; # for kk

  #return [ join $char_list "" ]
  return $char_list
} ; # proc range_char

proc solution {A} {
  set smalls   [ range_char "a" "z" ]
  set capitals [ range_char "A" "Z" ]
  #  Make use of the function 'range_char' to
  #  compute separately the ranges for the small
  #  and capital letters. These are now available
  #  as arrays.
  
  set mp_small(letter) 0
  set mp_cap(letter) 0
  for { set kk 0 } \
      { $kk < [ llength $smalls ] } \
      { incr kk } {
    set  mp_small([lindex $smalls $kk])  [ lindex $capitals $kk ]
    set  mp_cap([lindex $capitals $kk])  [ lindex $smalls   $kk ]
  } ; # for kk
  array unset mp_small letter
  array unset mp_cap   letter
  #  Set up associative arrays to map each of the small
  #  letters to the corresponding capital letter,
  #  and vice versa. Hashes will save us time through
  #  the virtually constant-time access facility.
  
  #parray mp_small
  #parray mp_cap
  
  set s_list [ split $A {} ]
  set sz     [ llength $s_list ]
  #  Obtain the list of characters within the given
  #  string A.
  
  for { set s_length 2 } \
      { $s_length < $sz + 1 } \
      { incr s_length } {
    for { set s_index_start 0 } \
        { $s_index_start < $sz - $s_length + 1 } \
        { incr s_index_start } {
      #  A useful substring has a length starting from 2
      #  and extending to the length of the whole string.
      #  
      #  The starting index for the substring in question
      #  has to have a range as indicated by the statement
      #  defining the iteration index for the inner 'for'
      #  loop.
      #  
      #  Since 's_length' is iteratively set starting
      #  from the lowest length possible, the first
      #  success to be encountered during the search
      #  will mark the time to draw the function to
      #  an end, having found the shortest string that
      #  accommodates nothing other than some characters
      #  in both small and capital forms.
        
      set  temp  [ lrange  $s_list \
                     $s_index_start \
                     [ expr ($s_index_start + $s_length - 1) ] ]
      #  The array of characters for the current substring in
      #  question.
                
      array  unset  temp_set  *
      set  temp_set(NONE)  0
      for { set kk 0 } \
          { $kk < [ llength $temp ] } \
          { incr kk } {
        set  temp_set([lindex $temp $kk])  1
      }
      array  unset  temp_set  NONE
      #  Generated a set from the characters within the
      #  substring. A set rules out duplicates. Will be
      #  making use of the associative arrays to check if a 
      #  character together with its small or capital 
      #  form is included within the substring in question.
      
      #puts   [ join $temp "" ]
      #parray temp_set
      
      set  flag_found  1
      #  If the flag above remains true after the 'for' loop
      #  below, then it will be time to return and yield
      #  the result.
      foreach {item  value} [ array get temp_set ] {
        set flag_is_item_in_mp_small [ info exists mp_small($item) ]
        set flag_is_item_in_mp_cap   [ info exists mp_cap($item) ]

        set flag_is_corresponding_cap_in_temp_set   0
        set flag_is_corresponding_small_in_temp_set 0
        
        if { $flag_is_item_in_mp_small } {
          set  char_temp [ lindex [ array get mp_small $item ] 1 ]
          #puts $char_temp
          if { [ info exists temp_set($char_temp) ] } {
            set flag_is_corresponding_cap_in_temp_set   1
          }
        }
        
        if { $flag_is_item_in_mp_cap } {
          set  char_temp [ lindex [ array get mp_cap $item ] 1 ]
          #puts $char_temp
          if { [ info exists temp_set($char_temp) ] } {
            set flag_is_corresponding_small_in_temp_set 1
          }
        }
        
        #puts -nonewline $item
        #puts -nonewline $flag_is_item_in_mp_small
        #puts -nonewline $flag_is_corresponding_cap_in_temp_set
        #puts -nonewline $flag_is_item_in_mp_cap
        #puts $flag_is_corresponding_small_in_temp_set
        
        if { \
             ( $flag_is_item_in_mp_small \
               && \
               $flag_is_corresponding_cap_in_temp_set ) \
             || \
             ( $flag_is_item_in_mp_cap \
               && \
               $flag_is_corresponding_small_in_temp_set )
           } {
          #  Making use of the dictionaries (and drawing
          #  benefits through the constant-time access)
          #  to check if a character together with its
          #  corresponding small or capital form exists
          #  within the current substring.
        } else {
          set  flag_found  0
          break
          #  If the condition above is not satisfied even for
          #  a single character, then we should break out of the
          #  for loop since there is no need to lose time
          #  checking the remaining characters. Setting the
          #  flag to false will prevent the remaining 'if'
          #  conditional from terminating the function.
        }
      } ; # foreach {item  value}
      
      if { $flag_found } {
        set  str  "String found in \"%s\" :\n  %s"
        puts [ format  $str  $A  [ join $temp "" ] ]
        return $s_length
      }
      #  The first success to be encountered has the function
      #  return the length of the string in question.
    } ; # for s_index_start
  } ; # for s_length
  
  return -1
  #  No possible success meaning there is no substring within
  #  the original string accommodating both small and capital
  #  forms of some letters, and nothing else.
}


### SCRIPT
# set list_of_strings { 
#   "Bb"
# }
set list_of_strings { 
  "Bb"
  "aACCCxA"
  "CCzzcZazAxAZ"
  "CCzzcybzAxAZ"  
}

puts ""
for { set i 0 } { $i < [llength $list_of_strings] } { incr i } {
  puts ""
  set item [ lindex $list_of_strings $i ]
  set str "Response to \"%s\" :\n  %s"
  puts [ format  $str  $item  [ solution $item ] ]
}
