#!/usr/bin/lua

--[=====[
This script with the function 'solution' given
a string input computes the length of the shortest 
substring that only accommodates both small and capital
versions of all the letters included in the indicated
substring.
--]=====]

--[=====[
  Worked on this code on 
                        Dec 16, 2022 / Fri
--]=====]

--[=====[
  Function to compute a range of characters in the
  ASCII table. I obtained this function from a webpage.
--]=====]
function range_char(c_start, c_stop)
  local s_list = {}
  
  for kk = 0 , ( c_stop:byte() - c_start:byte() ) do
    table.insert( s_list, string.char( c_start:byte() + kk ) )
  end -- for kk
  
  return s_list
end

--[=====[
  See the answer at:
    https://stackoverflow.com/questions/20066835/lua-remove-duplicate-elements
--]=====]
function remove_duplicates(array_input)
  local hash = {}
--   local res = {}

  for _ , v in ipairs(array_input) do
    if (not hash[v]) then
--       res[#res+1] = v
      hash[v] = true
    end
  end
  
  return hash
end -- function remove_duplicates

function solution(A)
  local smalls   = range_char( 'a' , 'z' )
  local capitals = range_char( 'A' , 'Z' )
  --[=====[
    Make use of the function 'range_char' to
    compute separately the ranges for the small
    and capital letters. These are now available
    as tables.
  --]=====]
  
  local mp_small = {}
  local mp_cap   = {}
  
  for kk = 1 , #smalls do
    mp_small[smalls[kk]]   = capitals[kk]
    mp_cap  [capitals[kk]] = smalls[kk]
  end -- for kk
  --[=====[
    Set up hashes to map each of the small
    letters to the corresponding capital letter,
    and vice versa. Hashes will save us time through
    the virtually constant-time access facility.
  --]=====]
  
  --[=====[
  for key , val in pairs(mp_small) do
    print( string.format( "  %s -> %s" , key , mp_small[key] ) )
  end -- for key val
  --]=====]
  
  local s_list = {}
  for s in A:gmatch(".") do
    table.insert(s_list, s)
  end
  local sz = string.len(A)
  --[=====[
    Obtain the table of characters within the given
    string A.
  --]=====]
  
  for s_length = 2 , sz do
    for s_index_start = 1 , (sz - s_length + 1) do
      --[=====[
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
      --]=====]
      
      local temp =
        table.pack( table.unpack( s_list ,
          s_index_start , -1+s_index_start+s_length ) )
      --[=====[
        The table of characters for the current substring in
        question.
      --]=====]
      
      local temp_set = 
        remove_duplicates( temp )
      --[=====[
        Generated a set from the characters within the
        substring. A set rules out duplicates. Will be
        making use of the hashes to check if a 
        character together with its small or capital 
        form is included within the substring in question.
        
        The keys in the table 'temp_set' are without
        duplicates (unique).
      --]=====]
        
      local flag_found = true
      --[=====[
        If the flag above remains true after the 'for' loop
        below, then it will be time to return and yield
        the result.
      --]=====]
      
      for item , _ in pairs( temp_set ) do
        if ( ( mp_small[item] ) and ( temp_set[ mp_small[item] ] ) ) or
           ( ( mp_cap  [item] ) and ( temp_set[ mp_cap  [item] ] ) ) then
          --[=====[
            Making use of the hashes (and drawing
            benefits through the constant-time access)
            to check if a character together with its
            corresponding small or capital form exists
            within the current substring.
          --]=====]
        else
          flag_found = false
          break
          --[=====[
            If the condition above is not satisfied even for
            a single character, then we should break out of the
            for loop since there is no need to lose time
            checking the remaining characters. Setting the
            flag to false will prevent the remaining 'if'
            conditional from terminating the function.
          --]=====]
        end
      end -- for item
      
      if flag_found then
        print( string.format( 
                 "String found in \'%s\' :\n  %s" , 
                 A , table.concat( temp ) ) )
        return #temp
      end
      --[=====[
        The first success to be encountered has the function
        return the length of the string in question.
      --]=====]

    end -- for s_index_start
  end -- for s_length
  
  return -1
  --[=====[
    No possible success meaning there is no substring within
    the original string accommodating both small and capital
    forms of some letters, and nothing else.
  --]=====]
end -- function solution


list_of_strings = {
  "Bb" ,
  "aACCCxA" ,
  "CCzzcZazAxAZ" ,
  "CCzzcybzAxAZ" 
}

for _ , item in ipairs(list_of_strings) do
  print()
  print(
    string.format( "Response to \"%s\" :\n  %s" , 
                   item , solution(item) ) )
end
