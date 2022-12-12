#!/usr/bin/ruby

=begin
This script with the function 'solution' given
a string input computes the length of the shortest 
substring that only accommodates both small and capital
versions of all the letters included in the indicated
substring.
=end

=begin
  Worked on this code on 
                        Dec 12, 2022 / Mon
=end

require 'set'

def solution(s_input)
  sz = s_input.length
=begin
  Obtained size.
=end
      
  smalls   = ("a".."z").to_a
  capitals = ("A".."Z").to_a
=begin
  Got the arrays of smalls and capitals.
=end
  
#   puts smalls.join(" ")
#   puts capitals.join(" ")
  
  mp_small = Hash.new
  mp_cap   = Hash.new
  
  for kk in 0..(-1+smalls.length) do
    mp_small[smalls[kk]]   = capitals[kk]
    mp_cap  [capitals[kk]] = smalls[kk]
  end
=begin
  Created hashes for pointers between
  corresponding characters.
=end
  
#   for key , value in mp_small
#     puts "#{key} -> #{value}"
#   end
  
  for s_length in 2..sz
    for s_index_start in 0..(sz-s_length)
=begin
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
=end
      temp = s_input[s_index_start..(s_index_start+s_length-1)]
      temp_set = Set.new(temp.chars)
=begin
      Created a set out of the characters in 'temp'.
      No duplicates allowed.
=end
      
#       puts temp
#       puts (temp_set.to_a).join(" ")
      
      flag_found = true
=begin
        If the flag above remains true after the 'for' loop
        below, then it will be time to return and yield
        the result.
=end
      
      temp_set.each do |item|
        if ( mp_small.key?(item) and temp_set.include?( mp_small[item] ) ) or \
           ( mp_cap.key?(item)   and temp_set.include?( mp_cap[item] ) )
        else
          flag_found = false
          break
=begin
            If the condition above is not satisfied even for
            a single character, then we should break out of the
            for loop since there is no need to lose time
            checking the remaining characters. Setting the
            flag to false will prevent the remaining 'if'
            conditional from terminating the function.
=end
        end # if
      end # each item
=begin
      Checks for element in hash or set in each iteration
      of the loop above.
=end
      
      if flag_found
        puts "String found in \'#{s_input}\' :\n  #{temp}"
        return s_length
      end
=begin
        The first success to be encountered has the function
        return the length of the string in question.
=end
    end # for s_index_start
  end # for s_length
  
  return -1
=begin
    No possible success meaning there is no substring within
    the original string accommodating both small and capital
    forms of some letters, and nothing else.
=end
end


list_of_strings = [
  "Bb" ,
  "aACCCxA" ,
  "CCzzcZazAxAZ" ,
  "CCzzcybzAxAZ" ]

list_of_strings.each do |s_input|
  puts ""
  
  response = solution(s_input)
  puts "Response to \"#{s_input}\" :"
  puts "  " + String(response)
end
