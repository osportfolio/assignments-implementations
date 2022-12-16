#!/usr/bin/lua

--[=====[
  Given a string of digits each in the range from
  0 to 9, generates all the strings that correspond
  to numbers that are divisible by three, which
  are allowed to be devised only through modifications
  on each of the digits in the original string.
  Returns the total number of such strings; naturally
  the original string is not included in the count
  even if its corresponding number is divisible by three.
--]=====]

--[=====[
  Worked on this code on
                        Dec 16, 2022 / Fri
--]=====]



--[=====[
  The two functions below are inspired by the
  explanations in
    https://www.lua.org/pil/13.1.html

  The functions are
    returns_array_as_intersection_set(a, b)
    returns_array_as_difference_set  (a, b)
--]=====]

function returns_array_as_intersection_set(a, b)
  local result = {}
  
  local a__hash = {}
  for _ , item in ipairs(a) do
    a__hash[item] = true
  end
  
  for _ , item in ipairs(b) do
    if ( a__hash[item] ) then
      result[item] = true
    end
  end
  
  local result_array = {}
  for key , _ in pairs(result) do
    table.insert( result_array , key )
  end
  
  return result_array
end

function returns_array_as_difference_set(a, b)
  local result = {}
  
  local b__hash = {}
  for _ , item in ipairs(b) do
    b__hash[item] = true
  end
  
  for _ , item in ipairs(a) do
    if ( not b__hash[item] ) then
      result[item] = true
    end
  end
  
  local result_array = {}
  for key , _ in pairs(result) do
    table.insert( result_array , key )
  end
  
  return result_array
end

function returns_checker_hash()
  local checker_all = {}
  for kk = -12 , 13 do
    if kk % 3 == 0 then
      table.insert( checker_all , kk )
    end
  end -- for kk
  
  local range_of_int = {}
  for kk = 0 , 9 do
    table.insert( range_of_int , kk )
  end -- for kk
  
  local checker = {}
  
  fh = function(n, item, remainder)
    return n + item + (3-remainder)
  end
  
  for remainder = 0 , 2 do
    for _ , item in ipairs(range_of_int) do
      
      local checker_current = {}
      for _ , n in ipairs(checker_all) do
        table.insert( checker_current , fh(n, item, remainder) )
      end -- for n
      
      checker_current =
        returns_array_as_intersection_set(
          checker_current ,
          range_of_int
        )
        
      checker_current =
        returns_array_as_difference_set(
          checker_current ,
          { item }
        )
        
      table.sort( checker_current )
      checker[ string.format( "%d_%d" , item , remainder ) ] =
        checker_current
    end -- for item
  end -- for remainder
  
  return checker
end

function integer_array_to_string_with_delimiter(array, delim)
  local str = {"{ "}
  
  for kk = 1 , -1+#array do
    table.insert( str , string.format( "%d%s" , array[kk] , delim ) )
  end
  table.insert( str , string.format( "%d" , array[#array] ) )
  table.insert( str , " }" )
  
  return table.concat(str)
end -- function integer_array_to_string_with_delimiter

function print_checker_hash(checker)
  local keys_array = {}
  for key , _ in pairs(checker) do
    table.insert( keys_array , key )
  end
  table.sort(keys_array)
  
  print( "\nChecker Hash\n" )
  for _ , item in ipairs(keys_array) do
    print( string.format( "  %s -> %s" , item , 
           integer_array_to_string_with_delimiter( 
              checker[item] , " , ") ) )
  end
end -- function  prints_checker_hash

function character_to_digit(character)
  return string.byte(character) - string.byte('0')
end

function digit_to_character(digit)
  return string.char( string.byte('0') + digit )
end
  
function solution(s_input)
  local num = {}
  for kk = 1 , string.len(s_input) do
    table.insert( num , character_to_digit( s_input:sub(kk , kk) ) )
  end
  --print( string.format( "%s" ,
  --  integer_array_to_string_with_delimiter(num, " , ") ) )
  
  checker = returns_checker_hash()
  
  local sum_of_num = 0
  for _ , v in ipairs(num) do
    sum_of_num = sum_of_num + v
  end
  remainder = sum_of_num % 3
  
  cnt = 1
  res = {}
  total = 0
  
  for _ , item in ipairs(num) do
    local checker_current
      = checker[ string.format( "%d_%d" , item , remainder ) ]
    total = total + #checker_current
    
    for _ , n in ipairs(checker_current) do
      --[=====[
        Shallow copy as in an answer in
          https://stackoverflow.com/questions/640642/how-do-you-copy-a-lua-table-by-value
      --]=====]
      local num_current = {}
      for j , x in ipairs(num) do num_current[j] = x end
      
      num_current[cnt] = n
      
      local num_current_str = {}
      for kk = 1 , #num_current do
        table.insert( num_current_str , 
                      digit_to_character( num_current[kk] ) )
      end
      
      tba = table.concat( num_current_str )
      table.insert( res , tba )
    end -- for n
    
    cnt = cnt + 1
  end -- for item
  
  res = returns_array_as_difference_set(res , {})
  table.sort(res)
  
  print ( string.format(
    "Generated Strings with the Input \"%s\" :\n  %s" ,
    s_input ,
    table.concat( res , "  " ) ) )
    
  return total
end -- function solution
  
-- SCRIPT
checker = returns_checker_hash()
print_checker_hash(checker)

list_of_strings = {
  '0081' , '23' , '22454' }

for _ , item in ipairs(list_of_strings) do
  print()
  print(
    string.format( "Response to \"%s\" :\n  %s" , 
                   item , solution(item) ) )
end
