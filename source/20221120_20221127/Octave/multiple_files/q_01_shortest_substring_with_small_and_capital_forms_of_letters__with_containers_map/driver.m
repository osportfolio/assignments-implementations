%{
  Worked on this code on 
                        Dec 15, 2022 / Thu
%}

list_of_strings = { ...
  'Bb' , ...
  'aACCCxA' , ...
  'CCzzcZazAxAZ' , ...
  'CCzzcybzAxAZ' ...
};

for kk=1:numel(list_of_strings)
  [ len , s_out ] = ...
    solution_shortest_substrings ...
      (list_of_strings{kk});

  disp( ' ' );
  disp( sprintf( 'Response to \"%s\" :' , list_of_strings{kk} ) );
  disp( sprintf( '  %d' , len ) );
  if len > 0
    disp( 'Substring found :' );
    disp( sprintf( '  %s' , s_out ) );
  end
end