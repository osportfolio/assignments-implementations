#!/usr/bin/python3

"""
The function 'solution' tries to generate
a palindrome out of the string 'S' given
as an input argument, replacing the '?'
characters by what is required, and returns
the palindrome or the string 'NO', the
latter being the error identifier in case
no palindrome construction is possible.
"""

"""
  Worked on this code on
                        Nov 20, 2022 / Sun
"""

def solution(S):
  s_list = list(S)
  """
    Generate a list of characters from the
    given string
  """
  
  """
    Below, the variables 'index_right',
    'index_left', and 'n_max' have to be
    calculated separately for an odd and
    an even number of characters within
    the original string. 
    
    'n_max' is the number of characters
    to the right and left of the character
    in the middle position (if there are an
    odd number of characters) or in the 
    position between the characters in the
    middle (if there are even number of
    characters).
    
    'index_right' and 'index_left' are the
    starting values of the indices calculated
    through integer offsets from the middle 
    position (as explained above for the number 
    of characters being odd or even) for the
    characters to the right and to the left,
    respectively, of the indicated position.
  """
  if len(s_list) % 2 == 1:
    index_middle = int((len(s_list) - 1) / 2)
    if s_list[index_middle] == '?':
      s_list[index_middle] = 'a'
    """
      For a string with an odd number of
      characters, the character in the middle
      has to be set, if it has not already been
      set.
    """
    index_right = index_middle + 1
    index_left  = index_middle - 1
    n_max = int((len(s_list) - 1) / 2)
  else:
    index_right = int((len(s_list)) / 2)
    index_left  = int((len(s_list)) / 2 - 1)
    n_max = int((len(s_list)) / 2)
  
  for kk in range(n_max):
    index_right_c = index_right + kk
    index_left_c  = index_left  - kk
    """
      Calculate the current indices through
      the update 'kk' upon the initial values
      for the indices of the entries to the
      right and left of the entry in the middle.
      The odd and even cases have already been
      taken care of, so the codes above and
      below within the scope of this for loop
      apply to both cases.
    """
      
    if ( s_list[index_right_c] != '?' ) and \
       ( s_list[index_left_c]  != '?' ):
      if ( s_list[index_right_c] != s_list[index_left_c] ):
        return 'NO'
      else:
        pass
    """
      If the entries at the same distance to the 
      right and left of the middle position are 
      already set and are not the same, then
      the string cannot be a palindrome.
    """
        
    if ( s_list[index_right_c] == '?' ) and \
       ( s_list[index_left_c]  == '?' ):
      s_list[index_right_c] = 'a'
      s_list[index_left_c]  = 'a'
    """
      If the entries of interest to the right and
      left have not already been set, then set them
      as the same character.
    """
        
    if ( s_list[index_right_c] != '?' ) and \
       ( s_list[index_left_c]  == '?' ):
      s_list[index_left_c] = s_list[index_right_c]
    """
      If the entry of interest to the right has
      been set but that to the left not so, then
      set the entry to the left to continue
      in the path to obtaining a palindrome at
      the end.
    """
      
    if ( s_list[index_right_c] == '?' ) and \
       ( s_list[index_left_c]  != '?' ):
      s_list[index_right_c] = s_list[index_left_c]
    """
      If the entry of interest to the left has
      been set but that to the right not so, then
      set the entry to the right to continue
      in the path to obtaining a palindrome at
      the end.
    """
    
  return ''.join(s_list)
  """
    Join the resulting characters into a string,
    and return this string.
  """


list_of_strings = [
  '?' , 'ba?' , 'ab' , 'a?b' , 'bac?b' , '?acab' ]

for item in list_of_strings:
  print (
    "Response to \"%s\" :\n" % (item) ,
    "" , solution(item) )