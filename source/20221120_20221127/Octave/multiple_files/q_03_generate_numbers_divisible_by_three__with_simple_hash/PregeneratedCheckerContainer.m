classdef PregeneratedCheckerContainer < handle

%{
# Worked on this code on
#                       Dec 15, 2022 / Thu
%}

  properties(Constant=true, Static=true, SetAccess=private, GetAccess=public)
    checker_all  = [ -12 : 3 : 12 ]
    range_of_int = [ 0 : 9 ]
  end
  
  properties(SetAccess=private, GetAccess=public)
    checker
  end
  
  methods(public)
  
    function obj = PregeneratedCheckerContainer()
      obj.checker = ...
        SimpleHashWithCustomValueTypes('double', [1 2]);
      compute_checker(obj);
      return;
    end % function - PregeneratedCheckerContainer
  
  end % methods - public
  
  methods(private)
    
    function compute_checker(obj)
      for remainder = 0:2
        for ll = 1:numel(PregeneratedCheckerContainer.range_of_int)
          item = PregeneratedCheckerContainer.range_of_int( ll );
          checker_current = ...
            zeros( 1 , ...
                   numel( PregeneratedCheckerContainer.checker_all ) );
          for kk = 1:numel(checker_current)
            checker_current(kk) = ...
              PregeneratedCheckerContainer.generate_digit ...
                (
                  PregeneratedCheckerContainer.checker_all(kk) , ...
                  item , ...
                  remainder ...
                );
          end % for kk
          % Computed checker_current in raw form.
          
          checker_current_temp = [];
          checker_current__hash = ...
            SimpleHashWithCustomValueTypes( 'double' , [1 , 1] );
          for kk = 1:numel(checker_current)
            checker_current__hash.set( checker_current(kk) , 1 );
          end % for kk
          for kk = 1:numel(PregeneratedCheckerContainer.range_of_int)
            if checker_current__hash.is_key_present_in_hash( ...
               PregeneratedCheckerContainer.range_of_int(kk) )
              checker_current_temp(end+1) = ...
                PregeneratedCheckerContainer.range_of_int(kk);
            end
          end % for kk
          checker_current = checker_current_temp;
          clear checker_current_temp;
          %{
            Computed intersection set of checker_current and
            range_of_int.
          %}
          
          checker_current_temp = [];
          for kk = 1:numel(checker_current)
            if item ~= checker_current(kk)
              checker_current_temp(end+1) = ...
                checker_current(kk);
            end
          end % for kk
          checker_current = checker_current_temp;
          clear checker_current_temp;
          % Eliminated item from checker_current.
          
          obj.checker.set( [item, remainder] , checker_current );
        end % for item
      end % for remainder
    end % function - compute_checker
    
  end % methods - private
  
  methods(Static=true, private)
  
    function ret_val = generate_digit(n, item, remainder)
      ret_val = n + item + (3 - remainder);
      return;
    end
    
  end % methods - static private

end % classdef PregeneratedCheckerContainer