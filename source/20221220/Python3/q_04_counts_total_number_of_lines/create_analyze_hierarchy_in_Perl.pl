#!/usr/bin/perl

# Worked on this code on
#   Jan  6, 2023 / Fri

use strict;
use warnings;

{ # block bgn

package DirTreeNode;
sub new
{
  my ($class, @args) = @_;
  my $self = bless {}, $class;
  return $self->_init(@args);
}

sub _init
{
  my ($self, $name, @args) = @_;
  $self->id   ( 'DirTreeNode' );
  $self->name ( $name );
  $self->flag_has_parent ( 0 );
  
  $self->subdirs_list( [] );
  $self->files_list  ( [] );
  return $self;
}

sub get_depth_and_path
{
  my ($self, $hash_ref, @args) = @_;
  
  my @dirs_list = ();
  unshift @dirs_list , $self->name;
  
  my $cnt = 0;
  if ( $self->flag_has_parent )
  {
    my $node_current = $self->parent;
    
    while ( 1 )
    {
      ++$cnt;
      unshift @dirs_list , $node_current->name;
      
      if ( $node_current->flag_has_parent )
      {
        $node_current = $node_current->parent;
      }
      else
      {
        last;
      }
    } # while
  } # if
  
  $hash_ref->{'depth'} = $cnt;
  $hash_ref->{'path'}  = join( '/' , @dirs_list );
} # sub get_depth_and_path

sub id
{
  $_[0]->{id} = $_[1] if defined $_[1];
  $_[0]->{id}
}

sub name
{
  $_[0]->{name} = $_[1] if defined $_[1];
  $_[0]->{name}
}

sub parent
{
  $_[0]->{parent} = $_[1] if defined $_[1];
  $_[0]->{parent}
}

sub flag_has_parent
{
  $_[0]->{flag_has_parent} = $_[1] if defined $_[1];
  $_[0]->{flag_has_parent}
}

sub subdirs_list
{
  $_[0]->{subdirs_list} = $_[1] if defined $_[1];
  $_[0]->{subdirs_list}
}

sub files_list
{
  $_[0]->{files_list} = $_[1] if defined $_[1];
  $_[0]->{files_list}
}

sub print_info
{
  my ($node_topmost, @args) = @_;
  
  my @nodes_all
    = ( $node_topmost );
  my @nodes_processed
    = ( $node_topmost );
  while ( 1 + $#nodes_processed > 0 )
  {
    my $node_current = shift @nodes_processed;
    push 
      @nodes_all ,
      @{ $node_current->subdirs_list };
    push 
      @nodes_processed ,
      @{ $node_current->subdirs_list };
  } # while
  
  foreach my $item ( @nodes_all )
  {
    print "\n";
    print "Directory :\n  " , $item->name , "\n";
    
    my %hash__depth_path
      = (
          'depth' => 0  ,
          'path'  => ''
        );
    $item->get_depth_and_path( \%hash__depth_path );
    print "Depth :\n  " , 
          $hash__depth_path{depth} , "\n";
    print "Path :\n  " ,
          $hash__depth_path{path}  , "\n";
          
    my $parent_name = 'None';
    if ( $item->flag_has_parent )
    {
      $parent_name = $item->parent->name;
    } # if
    print "Parent :\n  " , $parent_name , "\n";
    
    print "Files :\n  " ,
          join( "\n  " , @{ $item->files_list } ) , "\n";
          
    my @subdirs_names = ();
    foreach my $child ( @{ $item->subdirs_list } )
    {
      push @subdirs_names , $child->name;
    } # foreach $child
    print "Subdirectories :\n  " ,
          join( "\n  " , @subdirs_names ) , "\n";
  } # foreach $item
} # sub print_info

1;

package RandomDirHierarchyCreator;
our @available_characters_list
  = ();
push @available_characters_list , ('a'..'z');
push @available_characters_list , ('A'..'Z');
push @available_characters_list , '_';

sub new
{
  my ($class, @args) = @_;
  my $self = bless {}, $class;
  return $self->_init(@args);
}

sub _init
{
  my ($self, $options_ref, @args) = @_;
  $self->id   ( 'RandomDirHierarchyCreator' );
  $self->options_ref ( $options_ref );
  return $self;
}

sub id
{
  $_[0]->{id} = $_[1] if defined $_[1];
  $_[0]->{id}
}

sub options_ref
{
  $_[0]->{options_ref} = $_[1] if defined $_[1];
  $_[0]->{options_ref}
}

sub node_topmost
{
  $_[0]->{node_topmost} = $_[1] if defined $_[1];
  $_[0]->{node_topmost}
}

sub generate_whole_random_hierarchy
{
  my ($self, @args) = @_;
  
  my $node_topmost 
    = DirTreeNode->new( $self->options_ref->{dname_topmost} );
  $self->node_topmost( $node_topmost  );
  my @nodes_processed
    = ( $self->node_topmost );
    
  while ( 1 + $#nodes_processed > 0 )
  {
    my $node_current = shift  @nodes_processed;
    
    my %hash__depth_path
      = (
          'depth' => 0  ,
          'path'  => ''
        );
    $node_current->get_depth_and_path( \%hash__depth_path );
    if ( $hash__depth_path{depth} 
         < 
         $self->options_ref->{depth_max} )
    {
      my @array__d_f 
        = $self->get_random_lists_of_subdirs_and_files();
      my $subdirs_list_ref = $array__d_f[0];
      my $files_list_ref   = $array__d_f[1];
      
      $node_current
        ->files_list( $files_list_ref );
      $node_current
        ->subdirs_list( [] );
      foreach my $s_name ( @{ $subdirs_list_ref } )
      {
        push 
          @{ $node_current->subdirs_list } ,
          DirTreeNode->new($s_name);
      } # foreach $s_name
      
      foreach my $item ( @{ $node_current->subdirs_list } )
      {
        $item->parent( $node_current );
        $item->flag_has_parent( 1 );
      } # foreach $item
      
      push 
        @nodes_processed , 
        @{ $node_current->subdirs_list };
    } # if
  } # while
  
  return $self;
} # sub generate_whole_random_hierarchy

sub create_generated_hierarchy
{
  my ($self, @args) = @_;
  
  my $path_topmost
    = $self->options_ref->{dname_topmost};
  
  if ( -e $path_topmost and -d $path_topmost )
  {
    die "Directory \'$path_topmost\' already exists. Cannot continue.\n";
  } # if
  
  print "\nCreating Randomized Directory Hierarchy :\n";
  
  my @nodes_processed
    = ( $self->node_topmost );
  while ( 1 + $#nodes_processed > 0 )
  {
    my $node_current = shift @nodes_processed;
    push  @nodes_processed ,
          @{ $node_current->subdirs_list };
    
    my %hash__depth_path
      = (
          'depth' => 0  ,
          'path'  => ''
        );
    $node_current->get_depth_and_path( \%hash__depth_path );
    
    my $mk_string_dir
      = "  mkdir -p  $hash__depth_path{path}";
    print $mk_string_dir , "\n";
    system( $mk_string_dir );
    
    foreach my $item_f ( @{ $node_current->files_list } )
    {
      my $path_file
        = sprintf( "%s/%s.%s" ,
                   $hash__depth_path{path} ,
                   $item_f ,
                   $self->options_ref->{extension} );
      print "  Created file  $path_file\n";
      
      open( FILE , ">$path_file" );
      print FILE  $self->get_random_file_content();
      close(FILE);
    } # foreach $item_f
  } # while
  
  return $self;
} # sub create_generated_hierarchy

sub get_random_name
{
  my ($self, @args) = @_;
  
  my $no_characters 
    = $self->options_ref->{no_char_min}
    + int( rand( 1 + $self->options_ref->{no_char_max}
                   - $self->options_ref->{no_char_min} ) );
                   
  my $name = '';
  for ( my $kk = 0 ; $kk < $no_characters ; ++$kk )
  {
    $name 
      .= $available_characters_list
           [ int( rand( 1 + $#available_characters_list ) ) ];
  } # for $kk
  
  return $name;
} # sub get_random_name

sub get_random_lists_of_subdirs_and_files
{
  my ($self, @args) = @_;
  
  my $no_subdirs
    = $self->options_ref->{no_subdir_min}
    + int( rand( 1 + $self->options_ref->{no_subdir_max}
                   - $self->options_ref->{no_subdir_min} ) );
  
  my $no_files
    = $self->options_ref->{no_files_min}
    + int( rand( 1 + $self->options_ref->{no_files_max}
                   - $self->options_ref->{no_files_min} ) );
  
  my $no_total = $no_subdirs + $no_files;
  
  my @names_list = ();
  while ( 1 + $#names_list < $no_total )
  {
    my $no_remaining
      = $no_total - ( 1 + $#names_list );
    my @names_list_remaining = ();
    for ( my $kk = 0 ; $kk < $no_remaining ; ++$kk )
    {
      push @names_list_remaining , $self->get_random_name();
    } # for $kk
    push @names_list , @names_list_remaining;
    
    my %names_list__hash = map { $_ => 1 } @names_list;
    @names_list = sort( keys %names_list__hash );
  } # while
  
  my @subdirs_list
    = @names_list[ 0..(-1+$no_subdirs) ];
  my @files_list
    = @names_list[ $no_subdirs..$#names_list ];
    
  @subdirs_list = sort ( @subdirs_list );
  @files_list   = sort ( @files_list );
  
  my @array = ( \@subdirs_list , \@files_list );
  return @array;
} # sub get_random_lists_of_subdirs_and_files

sub get_random_file_content
{
  my ($self, @args) = @_;
  
  my $no_items
    = $self->options_ref->{no_line_min}
    + int( rand( 1 + $self->options_ref->{no_line_max}
                   - $self->options_ref->{no_line_min} ) );
  
  my @lines_list = ();
  for ( my $kk = 0 ; $kk < $no_items ; ++$kk )
  {
    my $tmp = $self->options_ref->{line_common};
    if ( rand() < $self->options_ref->{prob_blank_line} )
    {
      $tmp = '';
    }
    
    push @lines_list , $tmp;
  } # for $kk
  
  return  join( "\n" , @lines_list );
} # sub get_random_file_content

1;

package LinesCounter;
sub new
{
  my ($class, @args) = @_;
  my $self = bless {}, $class;
  return $self->_init(@args);
}

sub _init
{
  my ($self, $options_ref, @args) = @_;
  $self->id   ( 'LinesCounter' );
  $self->options_ref ( $options_ref );
  return $self;
}

sub id
{
  $_[0]->{id} = $_[1] if defined $_[1];
  $_[0]->{id}
}

sub options_ref
{
  $_[0]->{options_ref} = $_[1] if defined $_[1];
  $_[0]->{options_ref}
}

sub node_topmost
{
  $_[0]->{node_topmost} = $_[1] if defined $_[1];
  $_[0]->{node_topmost}
}

sub build_tree
{
  my ($self, @args) = @_;
  
  my $path_topmost
    = $self->options_ref->{dname_topmost};
  if ( ! (-e $path_topmost and -d $path_topmost) )
  {
    die "Directory \'$path_topmost\' does not exist. Cannot continue.\n";
  } # if
  
  my $node_topmost 
    = DirTreeNode->new( $self->options_ref->{dname_topmost} );
  $self->node_topmost( $node_topmost  );
  my @nodes_processed
    = ( $self->node_topmost );
    
  while ( 1 + $#nodes_processed > 0 )
  {
    my $node_current = shift  @nodes_processed;
    
    my %hash__depth_path
      = (
          'depth' => 0  ,
          'path'  => ''
        );
    $node_current->get_depth_and_path( \%hash__depth_path );
    
    opendir( D , $hash__depth_path{path} );
    my @d_f_list = readdir(D);
    closedir(D);
    
    my @subdirs_names = ();
    my @files_names   = ();
    foreach my $item ( @d_f_list )
    {
      if ( ($item ne '.') and ($item ne '..') )
      {
        if ( -d "$hash__depth_path{path}/$item" )
        {
          push @subdirs_names , $item;
        }
        else
        {
          push @files_names   , $item;
        }
      } # if
    } # foreach $item
    @subdirs_names = sort @subdirs_names;
    @files_names   = sort @files_names;
    
    $node_current
      ->files_list( \@files_names );
    $node_current
      ->subdirs_list( [] );
    foreach my $s_name ( @subdirs_names )
    {
      push 
        @{ $node_current->subdirs_list } ,
        DirTreeNode->new($s_name);
    } # foreach $s_name
      
    foreach my $item ( @{ $node_current->subdirs_list } )
    {
      $item->parent( $node_current );
      $item->flag_has_parent( 1 );
    } # foreach $item
      
    push 
      @nodes_processed , 
      @{ $node_current->subdirs_list };
  } # while
  
  return $self;
} # sub build_tree

sub count
{
  my ($self, @args) = @_;

  my $no_files       = 0;
  my $no_lines       = 0;
  my $no_lines_blank = 0;
  
  my @nodes_processed
    = ( $self->node_topmost );
  while ( 1 + $#nodes_processed > 0 )
  {
    my $node_current = shift @nodes_processed;
    push  @nodes_processed ,
          @{ $node_current->subdirs_list };
    
    my %hash__depth_path
      = (
          'depth' => 0  ,
          'path'  => ''
        );
    $node_current->get_depth_and_path( \%hash__depth_path );
    
    foreach my $item_f ( @{ $node_current->files_list } )
    {
      my $path_file
        = sprintf( "%s/%s" ,
                   $hash__depth_path{path} ,
                   $item_f );
      
      my @record
        = LinesCounter::count_lines_in_file
            ( $path_file );
            
      ++$no_files;      
      $no_lines       += $record[0];
      $no_lines_blank += $record[1];
    } # foreach $item_f
  } # while
  
  print "\n";
  print "Number of Files :\n  $no_files\n";
  print "Number of Lines :\n  $no_lines\n";
  print "Number of Blank Lines :\n  $no_lines_blank\n";
  
  return $self;
} # sub count

sub count_lines_in_file
{
  my ($path_file, @args) = @_;
  
  open( FILE , "<$path_file" );
#   my @lines = <FILE>;
  read  FILE , my $content , -s FILE;
  close(FILE);
  
#   my $content = join( '' , @lines );
#   my @lines   = split( "\n" , $content );
  
  # See an answer to the question at
  #   https://stackoverflow.com/questions/34437248/is-there-a-better-way-to-count-occurrence-of-char-in-a-string
  my $char  = "\n";
  my $count = length( $content =~ s/[^\Q$char\E]//rg );
  
  # See an answer to the question at
  #   https://stackoverflow.com/questions/2114185/how-can-i-count-overlapping-substrings-in-perl
  my $count_blank = () = $content =~ /((?<=\n)\n)/g;
  
  ++$count_blank
    if ( substr( $content , - 1 + length($content) ) eq "\n" );
  ++$count_blank
    if ( substr( $content , 0 , 1 ) eq "\n" );
  
  my $no_lines       = 1 + $count;
  my $no_lines_blank = $count_blank;
  
  return ( $no_lines , 
           $no_lines_blank );
} # sub count_lines_in_file

1;
} # block end

### SCRIPT

my %options
  = (
      'dname_topmost'   => 'text_files' ,
      'extension'       => 'txt' ,
      'line_common'     => 'THIS IS A LINE' ,
      'prob_blank_line' => 0.20 ,
  
      'depth_max' => 3 ,
  
      'no_char_min' =>  5 ,
      'no_char_max' => 12 ,
  
      'no_subdir_min' => 2 ,
      'no_subdir_max' => 4 ,
  
      'no_files_min'  => 2 ,
      'no_files_max'  => 4 ,
  
      'no_line_min'   =>  25 ,
      'no_line_max'   => 200
    );

#Simple command line argument processing
my $error_str
  = "Action should be indicated as \'create' or \'analyze\'.\n";

die $error_str if ( 1 + $#ARGV < 1 );

if    ( $ARGV[0] eq 'create' )
{
  my $obj_creator 
    = RandomDirHierarchyCreator->new( { %options } );
  $obj_creator
    ->generate_whole_random_hierarchy();
  DirTreeNode::print_info
    ( $obj_creator->node_topmost );
  $obj_creator
    ->create_generated_hierarchy();
} # if
elsif ( $ARGV[0] eq 'analyze' )
{
  my $obj_analyze
    = LinesCounter->new( { %options } );
  $obj_analyze
    ->build_tree();
  DirTreeNode::print_info
    ( $obj_analyze->node_topmost );
  $obj_analyze
    ->count();
} # elsif
elsif ( $ARGV[0] eq 'debug' )
{
  my $flag_debug = 1;
    
  my $obj_dtn 
    = DirTreeNode->new;
  my $obj_creator 
    = RandomDirHierarchyCreator->new( { %options } );
  
  if ( $flag_debug )
  {
    print "\n" ,
      join( "" , @RandomDirHierarchyCreator::available_characters_list ) ,
      "\n";
    
    print "\n" , $obj_creator->get_random_name() , "\n";
  }

  my @array_ref__d_f
    = $obj_creator->get_random_lists_of_subdirs_and_files();
  
  if ( $flag_debug )
  {
    print 
      "\nList of Random Subdirectories :\n  " ,
      join( "\n  " , @{ $array_ref__d_f[0] } ) , "\n";
    print 
      "\nList of Random Files :\n  " ,
      join( "\n  " , @{ $array_ref__d_f[1] } ) , "\n";
#     print
#       "\nRandom File Content :\n" , 
#       $obj_creator->get_random_file_content() , "\n";
  }
} # elsif
else
{
  die $error_str;
}
