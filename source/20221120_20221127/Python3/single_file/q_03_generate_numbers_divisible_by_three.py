#!/usr/bin/python3

"""
Given a string of digits each in the range from
0 to 9, generates all the strings that correspond
to numbers that are divisible by three, which
are allowed to be devised only through modifications
on each of the digits in the original string.
Returns the total number of such strings; naturally
the original string is not included in the count
even if its corresponding number is divisible by three.
"""

"""
  Worked on this code on
                        Nov 20, 2022 / Sun
"""

import copy as cp
"""
    The module copy is necessary for
    copying a list; assignment means
    generating a reference copy for
    lists and many other classes.
"""

def solution(S):
  a = list(S)
  """
    Generates a list of characters from
    the given string S.
  """
  
  flag_compute_list = True
  #flag_compute_list = False
  """
    The flag above distinguishes betweeen
    generating or not the whole list of strings,
    whose number is of interest in the question
    statement. The flag with the False value
    assigned should yield a better result in
    terms of computational complexity.
  """

  num = [ int(item) for item in S ]
  #print( num )
  """
    A generator (or list comprehension)
    that converts characters into integers.
  """
  
  sum_of_num = sum(num)
  #print(sum_of_num)
  
  rem = sum_of_num % 3
  #print(rem)
  """
    If the digits in a number total up to
    a number divisible by 3, then the number
    itself is divisible by three.
  """
  
  #checker = [ -12, -9, -6, -3, 0, 3, 6, 9, 12 ]
  checker = range(-12, 13, 3)
  """
    Will be adding the integers in the list above
    to modify single digits in a number. Indeed,
    the range from -9 to +9 is enough.
  """
  
  range_of_int = range(10)
  """
    Range of digits from 0 to 9. Will be checking
    through this list if certain integers exist
    as items in this list.
  """
  
  if flag_compute_list:
    cnt   = 0
    res = []
  else:
    total = 0
  """
    The variables for either choice for the flag
    differ.
  """
  
  for item in num:
    checker_current = \
      [ n+item+(3-rem) for n in checker ]
    #print(checker_current)
    """
      Generator for computing the modified
      integer for a digit 'item' that will make
      the whole number divisible by 3.
    """
    
    checker_current = \
      list( set.intersection( set(checker_current) , 
                              set(range_of_int) ) )
    """
      For computing those of the modified integers
      that fall within the accepted range from 0 to 9
      for a single digit.
    """
    
    checker_current = \
      list( set(checker_current) - set([item]) )
    #print(checker_current)
    """
      Getting rid of the original digit if it is
      actually within the resulting list.
    """
    
    if flag_compute_list:
      for n in checker_current:
        num_current = cp.copy(num)
        """
          Obtain value copy, not a reference copy.
        """
        
        num_current[cnt] = n
        """
          Set the new value for the digit.
        """
        num_current_str  = [ str(s) for s in num_current ]
        """
          List comprehension to convert integers to
          characters.
        """
      
        tba = ''.join(num_current_str)
        #print( tba )
        """
          Obtain the resulting string for the number.
        """
        res.append( tba )
        """
          Append the string to the resulting list res.
        """
    
      cnt += 1
      #print()
      
    else:
      total += len(checker_current)
      """
        The number of possibilities that count for
        the digit in question is the number of digits
        calculated and contained within 'checker_current'.
      """
      
  if flag_compute_list:
    res = list( set(res) )
    res.sort()
    print (
      "Generated Strings with the Input \"%s\" :\n " % ( S ) ,
      ' '.join( res ) )
    return len(res)
    """
       Rule out duplicates if any with the set class,
       and return the number of elements within the set.
    """
  else:
    return total
    """
      'total' already holds the requested number.
    """
  """
    Return statements for either choice for the flag
    differ.
  """
      
  
list_of_strings = [
  '0081' , '23' , '22454' ]

for item in list_of_strings:
  print()
  print (
    "Response to \"%s\" :\n" % (item) ,
    "" , solution(item) )