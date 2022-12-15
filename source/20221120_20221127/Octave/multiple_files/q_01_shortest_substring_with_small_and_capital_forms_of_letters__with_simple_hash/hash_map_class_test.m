close all;
clear all;

%  ch_test = 'with_keys_of_char';
ch_test = 'with_keys_of_double';

switch ( ch_test )

  case 'with_keys_of_char'
    obj = SimpleHashWithCustomValueTypes('char');
    
    obj.set('qwer', 1)
    obj.set('asdf', 2)
    obj.set('zxcv', [3,4])
    
    keys_array = obj.get_keys();
    for kk = 1:numel(keys_array)
      disp(' ')
      disp( sprintf( 'Key :\n  "%s"' , keys_array{kk} ) )
      disp( 'Value :' )
      disp( obj.get_value_for_key( keys_array{kk} ) )
    end
    
    obj.set('qwer', 101)
    disp( sprintf( '\nHave just set new value for existing key.' ) )
    
    keys_array = obj.get_keys();
    for kk = 1:numel(keys_array)
      disp(' ')
      disp( sprintf( 'Key :\n  "%s"' , keys_array{kk} ) )
      disp( 'Value :' )
      disp( obj.get_value_for_key( keys_array{kk} ) )
    end
    
    keys_to_check = { 'qwer' , 'ghjk' };
    for kk = 1:numel(keys_to_check)
      disp(' ')
      disp( sprintf( 'Is "%s" present as key?' , keys_to_check{kk} ) )
      disp( obj.is_key_present_in_hash( keys_to_check{kk} ) )
    end
    
    % Error - wrong class for key
    % obj.set([3 , 4], 1)
    
    obj.erase_key('asdf')
    disp( sprintf( '\nHave just erased a key.' ) )
    
    keys_array = obj.get_keys();
    for kk = 1:numel(keys_array)
      disp(' ')
      disp( sprintf( 'Key :\n  "%s"' , keys_array{kk} ) )
      disp( 'Value :' )
      disp( obj.get_value_for_key( keys_array{kk} ) )
    end
    
  case 'with_keys_of_double'
  
    obj = SimpleHashWithCustomValueTypes('double', [2  1]);
    
    % Both produce errors as expected.
    %obj.set('qwer', 1)
    %obj.set([3 4], 1)
    
    obj.set([3 ; 4], 1)
    obj.set([6 ; -4], 2)
    obj.set([6 ; 11], [1 2])

    keys_array = obj.get_keys();
    for kk = 1:numel(keys_array)
      disp(' ')
      disp( 'Key :' )
      disp( keys_array{kk} )
      disp( 'Value :' )
      disp( obj.get_value_for_key( keys_array{kk} ) )
    end
    
    obj.erase_key([3 ; 4])
    disp( sprintf( '\nHave just erased a key.' ) )
    
    keys_array = obj.get_keys();
    for kk = 1:numel(keys_array)
      disp(' ')
      disp( 'Key :' )
      disp( keys_array{kk} )
      disp( 'Value :' )
      disp( obj.get_value_for_key( keys_array{kk} ) )
    end
    
    obj.set([6.1 ; -3.9], 202)
    disp( sprintf( '\nHave just set new value for existing key.' ) )
    
    keys_array = obj.get_keys();
    for kk = 1:numel(keys_array)
      disp(' ')
      disp( 'Key :' )
      disp( keys_array{kk} )
      disp( 'Value :' )
      disp( obj.get_value_for_key( keys_array{kk} ) )
    end
    
    keys_to_check = { [6.3 ; -4.2] , [8 ; 6] };
    for kk = 1:numel(keys_to_check)
      disp(' ')
      disp( 'Key to check :' )
      disp( keys_to_check{kk} )
      disp( 'Is this present as a key in the hash map?' )
      disp( obj.is_key_present_in_hash( keys_to_check{kk} ) )
    end
    
    obj.erase_key([6.2 ; -3.8])
    obj.erase_key([6 ; 11])
    
    disp( sprintf( '\nHave just erased remaining keys.' ) )
    
    keys_array = obj.get_keys();
    for kk = 1:numel(keys_array)
      disp(' ')
      disp( 'Key :' )
      disp( keys_array{kk} )
      disp( 'Value :' )
      disp( obj.get_value_for_key( keys_array{kk} ) )
    end
    
end
