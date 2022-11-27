#!/usr/bin/python3

"""
This script with the function 'solution' given
a string input computes the length of the shortest 
substring that only accommodates both small and capital
versions of all the letters included in the indicated
substring.
"""

"""
  Worked on this code on 
                        Nov 20, 2022 / Sun
"""

def range_char(start, stop):
  return [chr(n) for n in range(ord(start), ord(stop) + 1)]
"""
  Function to compute a range of characters in the
  ASCII table. I obtained this function from a webpage.
"""

def solution(A):
  smalls   = range_char('a', 'z')
  capitals = range_char('A', 'Z')
  """
    Make use of the function 'range_char' to
    compute separately the ranges for the small
    and capital letters. These are now available
    as lists.
  """
  
  #print( smalls )
  #print( capitals )
  #print()

  mp_small = {}
  mp_cap   = {}
  
  for kk in range(len(smalls)):
    mp_small[smalls[kk]]   = capitals[kk]
    mp_cap  [capitals[kk]] = smalls[kk]
  """
    Set up dictionaries to map each of the small
    letters to the corresponding capital letter,
    and vice versa. Hashes will save us time through
    the virtually constant-time access facility.
  """
    
  s_list = list(A)
  """
    Obtain the list of characters within the given
    string A.
  """
    
  for s_length in range(2, len(A)+1):
    for s_index_start in range(0, len(A)-s_length+1):
      """
        A useful substring has a length starting from 2
        and extending to the length of the whole string.
        
        The starting index for the substring in question
        has to have a range as indicated by the statement
        defining the iteration index for the inner 'for'
        loop.
        
        Since 's_length' is iteratively set starting
        from the lowest length possible, the first
        success to be encountered during the search
        will mark the time to draw the function to
        an end, having found the shortest string that
        accommodates nothing other than some characters
        in both small and capital forms.
      """
      
      temp = s_list[s_index_start:(s_index_start+s_length)]
      #print(temp)
      """
        The list of characters for the current substring in
        question.
      """
      
      temp_set = set(temp)
      #print(temp_set)
      """
        Generated a set from the characters within the
        substring. A set rules out duplicates. Will be
        making use of the dictionaries to check if a 
        character together with its small or capital 
        form is included within the substring in question.
      """
      
      flag_found = True
      """
        If the flag above remains true after the 'for' loop
        below, then it will be time to return and yield
        the result.
      """
      for item in temp_set:
        if ((item in mp_small) and (mp_small[item] in temp_set)) or \
           ((item in mp_cap)   and (mp_cap[item]   in temp_set)):
          """
            Making use of the dictionaries (and drawing
            benefits through the constant-time access)
            to check if a character together with its
            corresponding small or capital form exists
            within the current substring.
          """
          pass
        else:
          flag_found = False
          break
          """
            If the condition above is not satisfied even for
            a single character, then we should break out of the
            for loop since there is no need to lose time
            checking the remaining characters. Setting the
            flag to false will prevent the remaining 'if'
            conditional from terminating the function.
          """
      #print()
      
      if flag_found:
        print (
          "String found in \'%s\' :\n " % (A) , 
          ''.join( temp ) )
        return s_length
      """
        The first success to be encountered has the function
        return the length of the string in question.
      """

  return -1
  """
    No possible success meaning there is no substring within
    the original string accommodating both small and capital
    forms of some letters, and nothing else.
  """


list_of_strings = [
    'aACCCxA' ,
    'CCzzcZazAxAZ' ,
    'CCzzcybzAxAZ' ,
  ]

for item in list_of_strings:
  print()
  print (
    "Response to \"%s\" :\n" % (item) ,
    "" , solution(item) )