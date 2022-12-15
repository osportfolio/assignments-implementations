%{
# Worked on this code on
#                       Dec 15, 2022 / Thu
%}

close all;
clear classes;

list_of_strings = { ...
  '0081' , '23' , '22454' };

for kk=1:numel(list_of_strings)
  [ total , result ] ...
    = solution_divisible_by_3( list_of_strings{kk} );
  
  disp( ' ' );
  disp( sprintf( 'Response to \"%s\" :' , list_of_strings{kk} ) );
  disp( sprintf('  %s' , strjoin( result , '  ' ) ) );
  disp( 'Total number of generated strings :' );
  disp( sprintf( '  %d' , total ) );
end