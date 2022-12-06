#!/usr/bin/python3

"""
  Slightly modified for modular implementation
      on Dec 2, 2022 / Fri
"""

import shortest_substrings as shsu

list_of_strings = [
    'aACCCxA' ,
    'CCzzcZazAxAZ' ,
    'CCzzcybzAxAZ' ,
  ]

for item in list_of_strings:
  print()
  print (
    "Response to \"%s\" :\n" % (item) ,
    "" , shsu.solution(item) )