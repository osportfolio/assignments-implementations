list_of_strings = { ...
  '?' , 'ba?' , 'ab' , 'a?b' , 'bac?b' , '?acab' };

for kk=1:numel(list_of_strings)
  disp( sprintf( 'Response to \"%s\" :' , list_of_strings{kk} ) );
  disp( sprintf('  %s' , ...
                solution_palindrome_checker_generator ...
                  (list_of_strings{kk}) ) );
end