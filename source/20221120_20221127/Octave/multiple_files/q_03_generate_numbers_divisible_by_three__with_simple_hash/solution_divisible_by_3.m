function [ total , res ] = ...
  solution_divisible_by_3(s_input)
  
%{
# Given a string of digits each in the range from
# 0 to 9, generates all the strings that correspond
# to numbers that are divisible by three, which
# are allowed to be devised only through modifications
# on each of the digits in the original string.
# Returns the total number of such strings; naturally
# the original string is not included in the count
# even if its corresponding number is divisible by three.

# Worked on this code on
#                       Dec 15, 2022 / Thu
%}
  
  num = zeros( 1 , numel(s_input) );
  for kk = 1:numel(num)
    num(kk) = s_input(kk) - '0';
  end
  
  checker = PregeneratedCheckerContainer().checker;
  
  sum_of_num = sum( num , 2 );
  remainder  = rem( sum_of_num , 3 );
  
  cnt = 1;
  res = cell(1, 0);
  total = 0;
  
  for kk = 1:numel(num)
    item = num(kk);
    checker_current ...
      = checker.get_value_for_key( [ item , remainder ] );
    total += numel( checker_current );
    
    for ll = 1:numel(checker_current)
      n = checker_current(ll);
      
      num_current = num;
      num_current(cnt) = n;
      
      tba = zeros( 1 , numel(num_current) );
      for mm = 1:numel(tba)
        tba(mm) = '0' + num_current(mm);
      end
      tba = char(tba);
      
      res{end+1} = tba;
    end % for ll
    
    cnt += 1;
  end % for kk
  
  res__hash = SimpleHashWithCustomValueTypes( 'char' );
  for kk = 1:numel(res)
    res__hash.set( res{kk} , 1 );
  end % for kk
  res = sort( res__hash.get_keys() );
  
  return;
end % function - solution