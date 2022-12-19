#!/usr/bin/tclsh

# Given a string of digits each in the range from
# 0 to 9, generates all the strings that correspond
# to numbers that are divisible by three, which
# are allowed to be devised only through modifications
# on each of the digits in the original string.
# Returns the total number of such strings; naturally
# the original string is not included in the count
# even if its corresponding number is divisible by three.

# Worked on this code on
#                       Dec 18-19, 2022 / Sun-Mon

proc returns_array_as_intersection_set {array_names} {
  set elem [lindex $array_names 0]
  upvar $elem a

#   puts [llength $a]
#   foreach d $a {
#     puts -nonewline "$d "
#   }
#   puts " "
  
  set elem [lindex $array_names 1]
  upvar $elem b
  
#   puts [llength $b]
#   foreach d $b {
#     puts -nonewline "$d "
#   }
#   puts " "
  
  set result__hash(NOT_LIKELY_TO_BE_KEY)  0

  set a__hash(NOT_LIKELY_TO_BE_KEY) 0
  foreach item $a {
    set a__hash($item) 1
  } ; # foreach item
  array  unset  a__hash  NOT_LIKELY_TO_BE_KEY
  
  foreach item $b {
    if { [ info exists a__hash($item) ] } {
      set result__hash($item) 1
    }
  } ; # foreach item
  array  unset  result__hash   NOT_LIKELY_TO_BE_KEY
  
  set result_array {}
  foreach key [array names result__hash] {
    lappend result_array $key
  }
  
  return $result_array
} ; # proc returns_array_as_intersection_set

proc returns_array_as_difference_set {array_names} {
  set elem [lindex $array_names 0]
  upvar $elem a
  
#   puts [llength $a]
#   foreach d $a {
#     puts -nonewline "$d "
#   }
#   puts " "

  set elem [lindex $array_names 1]
  upvar $elem b
  
#   puts [llength $b]
#   foreach d $b {
#     puts -nonewline "$d "
#   }
#   puts " "

  set result__hash(NOT_LIKELY_TO_BE_KEY)  0
  
  set b__hash(NOT_LIKELY_TO_BE_KEY) 0
  foreach item $b {
    set b__hash($item) 1
  } ; # foreach item
  array  unset  b__hash  NOT_LIKELY_TO_BE_KEY
  
  foreach item $a {
    if { ! [ info exists b__hash($item) ] } {
      set result__hash($item) 1
    }
  } ; # foreach item
  array  unset  result__hash   NOT_LIKELY_TO_BE_KEY
  
  set result_array {}
  foreach key [array names result__hash] {
    lappend result_array $key
  }
  
  return $result_array
} ; #proc returns_array_as_difference_set

proc returns_range_of_integers \
  { i_start   i_stop   i_incr } {
  set result {}
  for { set i $i_start } { $i < $i_stop } { incr i $i_incr } {
    lappend  result  $i
  } ; # for i
  return $result
} ; # proc returns_range_of_integers

proc checker_helper { n   item   remainder } {
  return  [ expr $n + $item + ( 3 - $remainder ) ]
}

proc prints_checker {checker} {
  foreach key [array names checker] {
    puts $key
  }
} ; # proc prints_checker

proc returns_checker {} {
  set checker(NONE) 0

  set checker_all  [ returns_range_of_integers -12 13 3 ]
  set range_of_int [ returns_range_of_integers   0 10 1 ]
  
  for { set remainder 0 } { $remainder < 3 } { incr remainder } {
    for { set kk 0 } \
        { $kk < [llength $range_of_int] } { incr kk } {
      set item [ lindex $range_of_int $kk ]
      
      set checker_current {}
      for { set ll 0 } \
          { $ll < [llength $checker_all] } { incr ll } {
        set n [ lindex $checker_all $ll ]
        lappend checker_current [ checker_helper $n $item $remainder ]
      } ; # for ll
      
#       puts [llength $checker_current]
#       foreach d $checker_current {
#         puts -nonewline "$d "
#       }
#       puts " "
      
      set checker_current \
          [ returns_array_as_intersection_set \
              { checker_current  range_of_int } ]
              
#       puts [llength $checker_current]
#       foreach d $checker_current {
#         puts -nonewline "$d "
#       }
#       puts " "
      
      set single_item_list {}
      lappend single_item_list $item
      set checker_current \
          [ returns_array_as_difference_set \
              { checker_current  single_item_list } ]
              
#       puts [llength $checker_current]
#       foreach d $checker_current {
#         puts -nonewline "$d "
#       }
#       puts " "

      set checker_current [ lsort $checker_current ]
              
      set key [ format "%d_%d" $item $remainder ]
      set checker($key) $checker_current
      
      #puts -nonewline "${key}  ->  "
      #foreach digit $checker_current {
      #  puts -nonewline "${digit} "
      #}
      #puts " "
    } ; # for kk
  } ; # for remainder
  
  array  unset  checker  NONE
  
#   foreach key [array names checker] {
#     puts -nonewline "$key  ->  "
#     
#     set  digits [ lindex [ array  get  checker  $key ] 1 ]
#     foreach d $digits {
#       puts -nonewline "$d  "
#     }
#     puts " "
#   }
  
  return [ array get checker ]
} ; # proc returns_checker

proc converts_character_list_to_digit_list { list_names } {
  set    elem  [lindex $list_names 0]
  upvar $elem  char_list
  
  set digit_list {}
  set char_zero  "0"
  set char_zero_code [ scan $char_zero %c ]
  foreach  ch  $char_list {
    set char_current $ch
    set char_current_code [ scan $char_current %c ]
    lappend  digit_list  \
      [ expr ( $char_current_code - $char_zero_code ) ]
  } ; # foreach  ch
  
  return $digit_list
} ; # proc converts_character_list_to_digit_list

proc converts_digit_list_to_character_list { list_names } {
  set    elem  [lindex $list_names 0]
  upvar $elem  digit_list
  
  set char_list  {}
  set char_zero  "0"
  set char_zero_code [ scan $char_zero %c ]
  foreach  digit  $digit_list {
    set digit_current [ expr ( $char_zero_code + $digit ) ]
    lappend char_list \
            [ format %c [expr $digit_current] ]
  } ; # foreach digit
  
  return $char_list
} ; # proc converts_digit_list_to_character_list

proc removes_duplicates_in_list { list_names } {
  set    elem  [lindex $list_names 0]
  upvar $elem  list_current
  
  set result__hash(NOT_LIKELY_TO_BE_KEY)  0
  foreach  item  $list_current {
    set result__hash($item) 1
  } ; # foreach item
  array  unset  result__hash  NOT_LIKELY_TO_BE_KEY
  
  set result_array {}
  foreach key [array names result__hash] {
    lappend result_array $key
  }
  
  return $result_array
} ; # proc removes_duplicates_in_list

proc solution {S} {
  set s_list [ split $S {} ]
  set sz     [ llength $s_list ]
  
  set num [ converts_character_list_to_digit_list {s_list} ]
  
#   set dummy_array(HERE) $num
#   parray dummy_array

  array set checker [returns_checker]

  set  sum_of_num  0
  foreach item $num {
    set sum_of_num [ expr ( $sum_of_num + $item ) ]
  } ; # foreach item
  set  remainder  [ expr ( $sum_of_num % 3 ) ]
  
#   puts $sum_of_num
#   puts $remainder

  set  cnt  0
  set  res  {}
  set  total  0
  
  foreach  item  $num {
    set  key  [ format "%d_%d" $item $remainder ]
    set  checker_current  [ lindex [ array get checker $key ] 1 ]
    set  no_additional  [ llength $checker_current ]
    
#     puts $key
#     puts $checker_current
#     puts $no_additional
    
    set  total  [ expr ( $total + $no_additional ) ]
    
    foreach n $checker_current {
      set num_current {}
      foreach digit $num {
        lappend num_current $digit
      } ; # foreach digit
      
      lset  num_current  $cnt  $n
      set num_current_str \
        [ converts_digit_list_to_character_list {num_current} ]
        
      lappend res [ join $num_current_str "" ]
    } ; # foreach n
    
    set cnt [ expr ( $cnt + 1 ) ]
  } ; # foreach  item
  
  set res [ removes_duplicates_in_list { res } ]
  set res [ lsort $res ]
  
  return $res
} ; # proc solution

### SCRIPT
array set checker [returns_checker]
puts " "
puts "Checker Array :\n"
parray checker

# set list_of_strings { 
#   "23"
# }
set list_of_strings { 
  "0081"
  "23"
  "22454"
}

# puts ""
for { set i 0 } { $i < [llength $list_of_strings] } { incr i } {
  puts ""
  set item  [ lindex $list_of_strings $i ]
  set l_out [ solution $item ]
  
  set str "Response to \"%s\" :\n  %s"
  puts [ format  $str  $item  [ join  $l_out  " " ] ]
  puts [ format  "Number of Computed Strings :\n  %d" \
                 [ llength $l_out ] ]
}