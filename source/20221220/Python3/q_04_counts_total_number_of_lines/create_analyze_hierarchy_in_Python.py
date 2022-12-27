#!/usr/bin/python3

"""
  Script to generate a randomized directory hierarchy of
  text files and then to count the total number of lines
  in the relevant files.
"""

"""
  Worked on this script on
    Dec 25, 2022 / Sun
"""

import random
import os
import sys
import copy as cp

def range_char(start, stop):
  """
    Returns a string as a range of characters from 'start'
    to 'stop'.
  """
  return [chr(n) for n in range(ord(start), ord(stop) + 1)]

class DirTreeNode(object):
  """
    Used to build a tree representation of a directory hierarchy
    taking into account the subdirectories and files under each
    directory.
  """
  
  def __init__(self, name):
    self.parent = None
    self.subdirs_list = []
    self.files_list   = []
    
    self.name = name
    
  def get_depth_and_path(self):
    """
      Find the depth of node and the relative path with respect
      to the topmost node.
    """
    dirs_list = []
    dirs_list.append( self.name )
    
    cnt = 0
    node_current = self
    while  node_current.parent is not None:
      node_current = node_current.parent
      dirs_list.append( node_current.name )
      cnt += 1
      
    return cnt , ( './%s' % '/'.join( dirs_list[::-1] ) )

class RandomDirHierarchyCreator(object):
  """
    Creates a randomized directory hierarchy as specified
    by the options provided to the ctor.
  """
  
  available_characters_list \
    =   list(range_char('a', 'z')) \
      + list(range_char('A', 'Z')) + list('_')
  """
    Above is the static list of characters to choose from
    when forming the directory and file names.
  """
  
  def __init__(self, options):
    self.options = cp.copy(options)
    
  def reset(self):
    self.node_topmost = None
    return self
    
  def print_info(self):
    """
      Prints the available information about each node in
      a tree representation of a directory hierarchy.
      Breadth first search preferred.
    """
    
    nodes_all \
      = [ self.node_topmost ]
    nodes_processed \
      = [ self.node_topmost ]
    while nodes_processed:
      node_current \
        = nodes_processed.pop(0)
      nodes_all = \
        nodes_all       + node_current.subdirs_list
      nodes_processed = \
        nodes_processed + node_current.subdirs_list
      
    for item in nodes_all:
      print()
      print( 'Directory :\n  %s' % item.name )
      
      depth_c , path_c \
        = item.get_depth_and_path()
      print( 'Depth :\n  %d' % depth_c )
      print( 'Path :\n  %s'  % path_c )
      
      parent_name = 'None'
      if item.parent is not None:
        parent_name = item.parent.name
      print( 'Parent :\n  %s' % parent_name )
      
      print( 'Files :' )
      print( ' ' , item.files_list )
      
      subdirs_names \
        = [ child.name for child in item.subdirs_list ]
      print( 'Subdirectories :' )
      print( ' ' , subdirs_names )
      
    return self
    
  def generate_whole_random_hierarchy(self):
    """
      Generates the tree representation of a randomized
      directory hierarchy. Does not create the relevant
      files or directories.
    """
    
    node_topmost \
      = DirTreeNode( options['dname_topmost'] )
    self.node_topmost \
      = node_topmost
    nodes_processed \
      = [ node_topmost ]
    while len(nodes_processed) > 0:
      node_current = nodes_processed.pop(0)
      depth_c , path_c = node_current.get_depth_and_path()
      if depth_c < options['depth_max']:
        subdirs_list , files_list \
          = obj.get_random_lists_of_subdirs_and_files()
        """
          Register files.
        """
        node_current.files_list \
          = files_list
        """
          Instantiate new nodes, and set name and parent for
          each.
        """
        node_current.subdirs_list \
          = [ DirTreeNode(s_name) for s_name in subdirs_list ]
        for item in node_current.subdirs_list:
          item.parent = node_current
        """
          Breadth-first approach marked by the order in the
          concatenation below.
        """
        nodes_processed \
          = nodes_processed + node_current.subdirs_list
        
    return self
  
  def create_generated_hierarchy(self):
    """
      Creates the directory hierarchy corresponding to a
      tree representation generated a priori. Does not
      proceed if the topmost directory already exists.
      In each text file a random number of lines, some of
      which are probabilistically set to be blank, are
      written.
    """
    
    if os.path.isdir( './%s' % options['dname_topmost'] ):
      raise OSError( 
        'Directory \'./%s\' already exists. Cannot continue.' % 
        options['dname_topmost'] )
    
    nodes_processed \
      = [ self.node_topmost ]
    while nodes_processed:
      node_current \
        = nodes_processed.pop(0)
      nodes_processed = \
        nodes_processed + node_current.subdirs_list
      
      depth_c , path_c \
        = node_current.get_depth_and_path()
      os.system( 
        "mkdir -p %s" % path_c )
      
      for item_f in node_current.files_list:
        path_file = "%s/%s.%s" % \
          ( path_c , item_f , self.options['extension'] )
        with open( path_file, 'w' ) as fhandle:
          fhandle.write( self.get_random_file_content() )
          
    return self
    
  def get_random_name(self):
    """
      Generates random directory and file names.
    """
    
    no_characters \
      = random.randint( self.options['no_char_min'] , 
                        self.options['no_char_max'] )
    
    #for readability
    char_list_full \
      = RandomDirHierarchyCreator.available_characters_list
    char_list = [ 
      char_list_full[ random.randint(0, -1+len(char_list_full)) ]
      for kk in range(0, no_characters) ]
    
    return  ''.join( char_list )
  
  def get_random_lists_of_subdirs_and_files(self):
    """
      Generates randomized lists of subdirectories and files.
    """
    
    no_subdirs \
      = random.randint( 
          self.options['no_subdir_min'] , 
          self.options['no_subdir_max'] )
    no_files \
      = random.randint( 
          self.options['no_files_min'] , 
          self.options['no_files_max'] )
    
    no_total = no_subdirs + no_files
    
    names_list = []
    while len(names_list) < no_total:
      no_remaining \
        = no_total - len(names_list)
      names_list_remaining \
        = [ self.get_random_name() for kk in range(0 , no_remaining) ]
      names_list \
        = list( set( names_list + names_list_remaining ) )
      
    subdirs_list \
      = names_list[0:no_subdirs]
    files_list \
      = names_list[no_subdirs:]
    
    subdirs_list.sort()
    files_list.sort()
      
    return subdirs_list , files_list
  
  def get_random_file_content(self):
    """
      A probabilistic ratio of the random number of lines
      written into a file are set to be blank. The others
      contain always the same text communicated by the options.
    """
    
    no_items \
      = random.randint( 
          self.options['no_line_min'] , 
          self.options['no_line_max'] )
    fh_flag_blank \
      = lambda : ( 
          random.uniform(0., 1.)
            < self.options['prob_blank_line'] )
    
    lines_list \
      = [ '' if fh_flag_blank() 
             else self.options['line_common']
               for kk in range(no_items) ]
    
    return '\n'.join( lines_list )
    
    
class LinesCounter(object):
  """
    Counts and reports the number of lines in each file
    under a directory hierarchy. The number of blank lines
    are also reported. Totals are displayed at the end.
  """
  
  def __init__(self, options):
    self.options = cp.copy( options )
  
  def count(self):
    if not os.path.isdir( './%s' % options['dname_topmost'] ):
      raise OSError( 
        'Directory \'./%s\' does not exist. Cannot continue.' % 
        options['dname_topmost'] )
    
    path_topmost \
      = './%s' % self.options['dname_topmost']
    
    dirs_list \
      = [ x[0] for x in os.walk(path_topmost) ]
    files_list \
      = [ x[2] for x in os.walk(path_topmost) ]
    
    no_files = 0
    no_lines_total = 0
    no_lines_blank = 0
    
    for kk in range( len(dirs_list) ):
      for file_item in files_list[kk]:
        no_files += 1
        
        print()
        
        path_file \
          = "%s/%s" % \
              ( dirs_list[kk] , file_item )
        print( "File :\n  %s" % path_file )
        
        with open( path_file , 'r' ) as file_handle:
          text_content_list \
            = file_handle.read().split( "\n" )
          
          print( "Number of Lines :\n  %d" 
                   % len(text_content_list) )
          no_lines_total += len(text_content_list)
          
          no_lines_blank_local \
            = [ 0 if item != '' else 1 
                  for item in text_content_list ]
          no_lines_blank_local \
            = sum( no_lines_blank_local )
          
          print( "Number of Blank Lines :\n  %d" 
                   % no_lines_blank_local )
          no_lines_blank += no_lines_blank_local
          
          
    print( "\n" )
    print( "Total Number of Files :\n  %d" \
             % no_files )
    print( "Total Number of Lines :\n  %d" \
             % no_lines_total )
    print( "Total Number of Blank Lines :\n  %d" \
             % no_lines_blank )
    
    return self
          
    
    
###SCRIPT
options = {
  'dname_topmost'   : 'text_files' ,
  'extension'       : 'txt' ,
  'line_common'     : 'THIS IS A LINE' ,
  'prob_blank_line' : 0.20 ,
  
  'depth_max' : 3 ,
  
  'no_char_min' :  5 ,
  'no_char_max' : 12 ,
  
  'no_subdir_min' : 2 ,
  'no_subdir_max' : 4 ,
  
  'no_files_min'  : 2 ,
  'no_files_max'  : 4 ,
  
  'no_line_min'   :  25 ,
  'no_line_max'   : 200
}

#Simple command line argument processing
error_str \
  = "Action should be indicated as \'create' or \'analyze\'."

if len(sys.argv) < 2:
  raise RuntimeError( error_str )

if   sys.argv[1] == "create":
  obj = RandomDirHierarchyCreator(options)

  obj.generate_whole_random_hierarchy()
  obj.print_info()
  obj.create_generated_hierarchy()

elif sys.argv[1] == "analyze":
  obj = LinesCounter( options )
  
  obj.count()

else:
  raise RuntimeError( error_str )
