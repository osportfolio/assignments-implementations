classdef SimpleHashWithCustomValueTypes < handle

  %{
    Simple hash implementation capturing string and
    double classes for keys. Makes use of a cell array
    and a possible structure array at each cell item
    to store (key, value) pairs. Can populate multiple
    structure items that are referenced by the same
    hash key, and the value corresponding to a key
    is then found through a linear-time search in
    the structure array. Getting all the keys from
    the hash map is an aspect that can and should be
    optimized in terms of computational complexity.
    
    Key class is set at construction. If an incompatible
    key is provided through the available methods,
    then errors are issued. For keys of class double,
    the size of keys to be used is also set at construction,
    and the size of a double key provided to a method is
    checked for consistency; in case of an incompatibility,
    errors are issued. Floating point values in the entity
    of a hash key for class double are each rounded to the 
    nearest integer in setting and checking (key, value) pairs.
  %}
  
  %{
    Worked on this code on
                          Dec 14-15, 2022 / Wed-Thu
  %}
  
  properties(SetAccess=private, GetAccess=public)
    hash_map
    
    flag_key_class_has_been_set = logical(0)
    key_class
    
    key_size_of_double_class
  end
  
  properties(Static=true, Constant=true, Access=public)
    size_of_keys = 997 % big enough prime
  end
  
  methods(public)
  
    % ctor
    function obj = SimpleHashWithCustomValueTypes(key_class, varargin)
      obj.erase_all_keys();
      set_key_class(obj, key_class, varargin)
      return;
    end
    
    function flag = is_key_present_in_hash(obj, key)
      obj.check_key(key);
      kk = SimpleHashWithCustomValueTypes. ...
             compute_index_for_given_key(key);
      if isempty( obj.hash_map{kk} )
        flag = logical(0);
        return;
      end
      
      index_internal = ...
        get_item_index_at_hash_index...
          (obj, key, kk);
          
      flag = ~isempty( index_internal );
      return;
    end
    
    % Searches for the available keys in the
    % whole hash map. Should be optimized.
    function keys_array = get_keys(obj)
      keys_array = {};
      for kk = 1:numel(obj.hash_map)
        if ~isempty( obj.hash_map{kk} )
          items = obj.hash_map{kk}.items;
          for ll = 1:numel(items)
            keys_array{end+1} = items(ll).key;
          end
        end
      end
      return;
    end
    
    function erase_key(obj, key)
      if ~is_key_present_in_hash(obj, key)
        return;
      end
      
      kk = SimpleHashWithCustomValueTypes. ...
             compute_index_for_given_key(key);
      index_internal = ...
        get_item_index_at_hash_index...
          (obj, key, kk);
          
      flag_all_items_to_be_erased = logical(0);
      if 1 == numel(obj.hash_map{kk}.items)
        flag_all_items_to_be_erased = logical(1);
      end
      
      obj.hash_map{kk}.items(index_internal) = [];
      if flag_all_items_to_be_erased
        obj.hash_map{kk} = [];
      end
    end
    
    function erase_all_keys(obj)
      obj.hash_map = ...
        cell(1, SimpleHashWithCustomValueTypes.size_of_keys);
    end
    
    function ret_val = get_value_for_key(obj, key)
      obj.check_key(key);
      kk = SimpleHashWithCustomValueTypes. ...
             compute_index_for_given_key(key);
      if isempty( obj.hash_map{kk} )
        ret_val = [];
        return;
      end
      
      index_internal = ...
        get_item_index_at_hash_index...
          (obj, key, kk);
      
      if isempty( index_internal )
        ret_val = [];
        return;
      end
      
      ret_val = obj.hash_map{kk}.items(index_internal).value;
      return;
    end
    
    function set(obj, key, value)
      obj.check_key(key);
      kk = SimpleHashWithCustomValueTypes. ...
             compute_index_for_given_key(key);
      if isempty( obj.hash_map{kk} )
        obj.hash_map{kk}.items = [];
        obj.hash_map{kk}.items(end+1).key = ...
          SimpleHashWithCustomValueTypes.treat_key( key );
        obj.hash_map{kk}.items(end).value = value;
        return;
      end
      
      index_internal = ...
        get_item_index_at_hash_index...
          (obj, key, kk);
      
      if isempty( index_internal )
        obj.hash_map{kk}.items(end+1).key = ...
          SimpleHashWithCustomValueTypes.treat_key( key );
        obj.hash_map{kk}.items(end).value = value;
      else
        %{
          The key is already stored. No need to save it again.
        %}
        
        %obj.hash_map{kk}.items(index_internal(1)).key   = ...
        %  SimpleHashWithCustomValueTypes.treat_key( key );
        obj.hash_map{kk}.items(index_internal(1)).value = value;
      end
    end % set
    
  end % methods
  
  methods(private)
  
    %{
      ctor helper. Sets key class and additional properties if
      necessary. Can be updated to capture other classes of keys.
    %}
    function set_key_class(obj, key_class, varargin)
      obj.key_class = lower(key_class);
      
      switch( lower( key_class ) )
        case 'char'
        
        case 'double'
          if ( nargin < 3 ) || ...
            ( ( 1 == numel(varargin) ) && isempty( varargin{1} ) )
            error( 'Common size of double matrices to be used for key should be provided.' );
          else
            key_size_tentative = round( varargin{1}{1} );
            if 0 ~= norm( size( key_size_tentative ) - [1 , 2] )
              error( 'The size matrix itself should be of size [1 , 2].' );
            else
              obj.key_size_of_double_class = key_size_tentative;
            end
          end
          
        otherwise
          error( 'Unsupported type for key.' );
      end
      
      return;
    end % function - set_key_class
    
    % Checks key class and other additional settings.
    function check_key(obj, key)
      if ~strcmpi( obj.key_class , class(key) )
        error( sprintf( ...
          'Expecting keys of class "%s". Encountered key of class "%s".' , ...
          obj.key_class , lower(class(key)) ) );
      end
      
      switch( lower( class(key) ) )
        case 'char'
        case 'double'
          if 0 ~= norm( obj.key_size_of_double_class - size(key) )
            error( 'Encountered incompatible key size for provided double key.' );
          end
      end
    end % function - check_key
  
    % Linear-time search function for pairs at a single hash key.
    function index_internal = get_item_index_at_hash_index...
                                (obj, key, hash_index)
      items = obj.hash_map{hash_index}.items;
      switch( lower( class(key) ) )
      
        case 'char'
          index_internal = [];
          for kk = 1:numel(items)
            if strcmp( items(kk).key , key )
              index_internal = kk;
              break;
            end
          end
          
        case 'double'
          index_internal = [];
          for kk = 1:numel(items)
            if 0 == norm( round(key) - items(kk).key )
              index_internal = kk;
              break;
            end
          end
          
      end % switch
    end % function - get_item_index
  
  end % methods
  
  % Static Methods
  methods(private, Static=true)
    
    % Hash generator out of a key for captured key classes
    function index_for_key = compute_index_for_given_key(key)
      switch( lower( class(key) ) )
        case 'char'
          index_for_key = sum( double(key) );
        case 'double'
          index_for_key = sum( sum( round(key) ) );
        otherwise
          error( 'Unsupported type for key.' );
      end % switch
      
      index_for_key = ...
        1 + mod(index_for_key, ...
                SimpleHashWithCustomValueTypes.size_of_keys);
    end % function
    
    %{
      Treatment of keys before storage for captured key classes
    %}
    function key_treated = treat_key(key)
      key_treated = key;
      switch( lower( class(key) ) )
        case 'char'
        case 'double'
          key_treated = round(key);
      end
      return;
    end
    
  end % methods - static

end % classdef