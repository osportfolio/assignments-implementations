#!/usr/bin/python3

# Given a string of digits each in the range from
# 0 to 9, generates all the strings that correspond
# to numbers that are divisible by three, which
# are allowed to be devised only through modifications
# on each of the digits in the original string.
# Returns the total number of such strings; naturally
# the original string is not included in the count
# even if its corresponding number is divisible by three.

# Worked on this code on
#                       Dec 7, 2022 / Wed

import copy as cp

class PregeneratedCheckerContainer(object):
  
  checker_all = \
    range(-12, 13, 3)
  range_of_int = \
    range(10)
  
  def __init__(self):
    self.checker = \
      {}
    
    fh = \
      lambda n, item, rem : n + item + (3-rem)
    
    for rem in range(3):
      for item in \
        PregeneratedCheckerContainer.range_of_int:
        
        checker_current = \
          [ fh(n, item, rem) for n in 
              PregeneratedCheckerContainer.checker_all ]
        checker_current = \
          list( set.intersection( 
                  set(checker_current) , 
                  set(PregeneratedCheckerContainer.range_of_int) ) )
        checker_current = \
          list( set(checker_current) - set([item]) )
        
        checker_current.sort()
        self.checker[(item, rem)] = \
          checker_current

def solution(S):
  num = \
    [ int(item) for item in S ]
  obj_checker = \
    PregeneratedCheckerContainer()
  
  sum_of_num = \
    sum(num)
  rem = \
    sum_of_num % 3
  
  cnt   = 0
  res   = []
  total = 0
  
  for item in num:
    checker_current = \
      obj_checker.checker[ (item, rem) ]
    total += \
      len(checker_current)
    
    for n in checker_current:
      num_current = cp.copy(num)
      
      num_current[cnt] = n
      num_current_str  = [ str(s) for s in num_current ]
      
      tba = ''.join(num_current_str)
      
      res.append( tba )
      
    cnt += 1
    
  res = list( set(res) )
  res.sort()
  print (
    "Generated Strings with the Input \"%s\" :\n " % ( S ) ,
    ' '.join( res ) )
  
  return total

#*** Script ***  
#flag_print_checker_dict = False
flag_print_checker_dict = True

if flag_print_checker_dict:
  print()
  print( "Checker Dictionary :" )
  print()
  obj_checker = PregeneratedCheckerContainer()
  for key in sorted(obj_checker.checker):
    print( " " , key , " " , obj_checker.checker[key] )

  
list_of_strings = [
  '0081' , '23' , '22454' ]

for item in list_of_strings:
  print()
  print (
    "Response to \"%s\" :\n" % (item) ,
    "" , solution(item) )