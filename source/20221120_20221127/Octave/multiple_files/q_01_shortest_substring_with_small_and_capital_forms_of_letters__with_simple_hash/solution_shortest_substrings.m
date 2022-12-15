function [ len , s_out ] = solution_shortest_substrings(A)

%{
The function 'solution' given
a string input computes the length of the shortest 
substring that only accommodates both small and capital
versions of all the letters included in the indicated
substring.
%}

%{
  Worked on this code on 
                        Dec 15, 2022 / Thu
%}

  smalls   = [ 'a' : 'z' ];
  capitals = [ 'A' : 'Z' ];
  %{
    Compute separately the ranges for the small
    and capital letters. These are now available
    as strings.
  %}
  
  mp_small = SimpleHashWithCustomValueTypes('char');
  mp_cap   = SimpleHashWithCustomValueTypes('char');
  
  for kk = 1:numel(smalls)
    mp_small.set( smalls(kk)   , capitals(kk) );
    mp_cap  .set( capitals(kk) , smalls(kk) );
  end
  %{
    Set up hash maps to map each of the small
    letters to the corresponding capital letter,
    and vice versa. Hashes will save us time through
    the virtually constant-time access facility.
  %}
  
  for s_length = 2:numel(A)
    for s_index_start = 1 : ( numel(A) - s_length + 1 )
    
      %{
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
      %}
    
      temp = A( s_index_start : ( s_index_start + s_length - 1 ) );
      %{
        The array of characters for the current substring in
        question.
      %}
      
      temp_hash = SimpleHashWithCustomValueTypes('char');
      for kk = 1:numel(temp)
        temp_hash.set( temp(kk) , 1 );
      end % for kk
      temp_set = temp_hash.get_keys();
      %{
        Generated a set from the characters within the
        substring. A set rules out duplicates. Will be
        making use of the dictionaries to check if a 
        character together with its small or capital 
        form is included within the substring in question.
      %}
      
      flag_found = logical(1);
      %{
        If the flag above remains true after the 'for' loop
        below, then it will be time to return and yield
        the result.
      %}
      for kk_item = 1:numel(temp_set)
        if ( ( mp_small.is_key_present_in_hash( temp_set{kk_item} ) ) ...
             && ...
             ( temp_hash.is_key_present_in_hash( mp_small.get_value_for_key( temp_set{kk_item} ) ) ) ) ...
           || ...
           ( ( mp_cap.  is_key_present_in_hash( temp_set{kk_item} ) ) ...
             && ...
             ( temp_hash.is_key_present_in_hash( mp_cap  .get_value_for_key( temp_set{kk_item} ) ) ) )
          %{
            Making use of the dictionaries (and drawing
            benefits through the constant-time access)
            to check if a character together with its
            corresponding small or capital form exists
            within the current substring.
          %}
        else
          flag_found = logical(0);
          break;
          %{
            If the condition above is not satisfied even for
            a single character, then we should break out of the
            for loop since there is no need to lose time
            checking the remaining characters. Setting the
            flag to false will prevent the remaining 'if'
            conditional from terminating the function.
          %}
        end
      end % for kk_item
    
      if flag_found
        len   = numel(temp);
        s_out = temp;
        return;
      end
      %{
        The first success to be encountered has the function
        return the length of the string and the string itself
        in question.
      %}
    end % for s_index_start
  end % for s_length

  len   = -1;
  s_out = '';
  return;
  %{
    No possible success meaning there is no substring within
    the original string accommodating both small and capital
    forms of some letters, and nothing else.
  %}
end % function