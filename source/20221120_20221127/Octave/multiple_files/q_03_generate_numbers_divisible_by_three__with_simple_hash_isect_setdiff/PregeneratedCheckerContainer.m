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
          
          checker_current = ...
            intersect( checker_current , ...
                       PregeneratedCheckerContainer.range_of_int );
          %{
            Computed intersection set of checker_current and
            range_of_int.
          %}
          
          checker_current = ...
            setdiff( checker_current , item );
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